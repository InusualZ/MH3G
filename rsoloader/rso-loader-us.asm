# Save the link register, so we can return from this function
stwu r1,-0x0060(r1)
mfspr r0,LR
stw r0,0x64(r1)
# Locate `01/hbm_data.rso`
lis r3,-0x7fa8
subi r3, r3,0x35c0 # 0x8057ca40
#  Replace `01/hbm_data.rso` with `00/hbm_data.rso`
li r5,0x3030
sth r5,0(r3) # `00`
#  Locate where are we going to load the mod rso
lwz r4,-0x4668(r13) # MOD_MODULE_START_PTR
li r5,0xff # set 3rd parameter
# Call `game_load_rso`
nop # 0x4bb65d91 bl game_load_rso
# Call `_prolog` function of the loaded module
lwz r12,0x24(r3)
mtspr CTR,r12
bctrl
# Load the link register to return to the function that called us
lwz r0,0x64(r1)
mtspr LR,r0
addi r1,r1,0x60
blr

# Replace
# 3c80aaab800300503884aaab38a000007c0400165400e8ff7c0903a64081002c8083004c8003002c7c842a14808400047c0400404082000c386000004e800020
# With 17 instruction
# 9421FFA07C0802A6900100643C6080583863CA4038A03030B0A30000808DB99838A000FF4bb65d91818300247D8903A64E800421800100647C0803A6382100604E800020
# 80040598 game_load_rso
# 804da7e4 zz_04da7e4 + 0x24
# 804da7e4 + 0x24 = 804DA808
# Delta
# 804DA808 - 80040598 = 49A270
#                    = B65D90
# 807ad7c0
# 807ad760