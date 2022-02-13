#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITPPC)),)
$(error "Please set DEVKITPPC in your environment. export DEVKITPPC=<path to>devkitPPC")
endif

include $(DEVKITPPC)/wii_rules

ifeq ($(REGION),)

all: us
us: elf2rso
	@$(MAKE) --no-print-directory REGION=us GAMECODE=RMHE08

clean: clean_elf2rso
	@$(MAKE) --no-print-directory clean_target REGION=us GAMECODE=RMHE08



#---------------------------------------------------------------------------------
# For now, make elf2rso a phony target
# Place target here (instead of inside recursive Makefile call) so it's only built once
#---------------------------------------------------------------------------------

# Unexport some compiler vars exported by devkitppc as they interfere
# when we build elf2rso, which uses the system compiler
unexport AS
unexport CC
unexport CXX
unexport AR
unexport OBJCOPY
unexport STRIP
unexport NM
unexport RANLIB

ELF2RSO_BUILD := $(CURDIR)/tools/elf2rso/build

elf2rso:
	@echo "Compiling elf2rso..."
	mkdir -p $(ELF2RSO_BUILD)
	cd $(ELF2RSO_BUILD) && cmake ..
	$(MAKE) -C $(ELF2RSO_BUILD) -f $(ELF2RSO_BUILD)/Makefile

clean_elf2rso:
	@echo "clean ... elf2rso"
	@rm -rf $(ELF2RSO_BUILD)

.PHONY: all clean us elf2rso clean_elf2rso

else

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
#---------------------------------------------------------------------------------
TARGET		:=	$(notdir $(CURDIR)).$(GAMECODE)
BUILD		:=	build.$(GAMECODE)
SOURCES		:=	rso $(wildcard rso/*)
DATA		:=	data  
INCLUDES	:=	rso/include

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------

MACHDEP		= -mno-sdata -mgcn -DGEKKO -mrvl -mcpu=750 -meabi -mhard-float

# -Wno-write-strings because some GC SDK functions take non-const char *,
# and Ghidra can't represent const char * anyhow
# -fmacro-prefix-map makes __FILE__ macro use filepaths relative to the source dir
CFLAGS		= -nostdlib -ffreestanding -ffunction-sections -fdata-sections -g -Os -Wall -Wno-write-strings -fmacro-prefix-map=$(abspath $(CURDIR)/../rso)=. $(MACHDEP) $(INCLUDE)
CXXFLAGS	= -fno-exceptions -fno-rtti -std=gnu++20 $(CFLAGS)
ASFLAGS     = -mregnames # Don't require % in front of register names

LDFLAGS		= -r -e _prolog -u _prolog -u _epilog -u _unresolved -Wl,--gc-sections -nostdlib -g $(MACHDEP) #-Wl,-Map,$(notdir $@).map

# Platform options
ifeq ($(GAMECODE),RMHE08)
	PRINTVER = "US"
else ifeq ($(GAMECODE),RMHJ08)
	PRINTVER = "JAP"
else ifeq ($(GAMECODE),RMHP08)
	PRINTVER = "PAL"
endif


#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
LIBS	:= 

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:=

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
			$(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

#---------------------------------------------------------------------------------
# automatically build a list of object files for our project
#---------------------------------------------------------------------------------
CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
sFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.S)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
	export LD	:=	$(CC)
else
	export LD	:=	$(CXX)
endif

export OFILES_BIN	:=	$(addsuffix .o,$(BINFILES))
export OFILES_SOURCES := $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(sFILES:.s=.o) $(SFILES:.S=.o)
export OFILES := $(OFILES_BIN) $(OFILES_SOURCES)

export HFILES := $(addsuffix .h,$(subst .,_,$(BINFILES)))

# For RSO linking
export LDFILES		:= $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.ld)))
#export MAPFILE		:= $(CURDIR)/rel/include/mkb2.$(REGION).lst

#---------------------------------------------------------------------------------
# build a list of include paths
#---------------------------------------------------------------------------------
export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
			$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
			-I$(CURDIR)/$(BUILD) \
			-I$(LIBOGC_INC)

#---------------------------------------------------------------------------------
# build a list of library paths
#---------------------------------------------------------------------------------
export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib) \
			-L$(LIBOGC_LIB)

export OUTPUT	:=	$(CURDIR)/$(TARGET)
.PHONY: $(BUILD) clean_target

#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean_target:
	@echo clean ... $(GAMECODE)
	@rm -fr $(BUILD) $(OUTPUT).elf $(OUTPUT).dol $(OUTPUT).rel $(OUTPUT).gci

#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

TOOLS := $(abspath $(CURDIR)/../tools)
ELF2RSO := $(TOOLS)/elf2rso/build/elf2rso

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).rso: $(OUTPUT).elf
$(OUTPUT).elf: $(LDFILES) $(OFILES)

$(OFILES_SOURCES) : $(HFILES)

# RSO linking
%.rso: %.elf
	@echo output ... $(notdir $@)
	@$(ELF2RSO) -i $< -ne
	@cp $@ $(CURDIR)/../riivolution/MH3G/MH3G.rso

-include $(DEPENDS)

#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------
endif
