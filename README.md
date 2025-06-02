# :confetti_ball: Monster Hunter Tri G Mod

A Monster Hunter Tri mod for general experimentation.

Features include:

* Display player (position, rotation)
* Display arena id

# Building

## Install devkitPro

devkitPro is a gcc-based compiler suite for Wii and other consoles.

See [here](https://devkitpro.org/wiki/devkitPro_pacman) for full installation details.

## Clone

```sh
git clone https://github.com/InusualZ/MH3G.git
```

## Download elf2rso

The compilation of the mod produce a ELF file. We need to convert that ELF into a [RSO](https://www.metroid2002.com/retromodding/wiki/RSO_(File_Format)) module. In order to that we use [elf2rso](https://github.com/InusualZ/elf2rso).

**Currently I only have precompiled binary for [Windows x64](https://github.com/InusualZ/elf2rso/releases). The program should be compatible with any OS with CMake and a compiler. You would have to compile from source.**

After you have the `elf2rso` binary. You need to place the executable in `tools/` folder with the name `elf2rso.exe` (Or without extension for non-Windows platforms)

## Build

**On Windows use the Msys2 terminal from the devkitPro**

```sh
cd MH3G
make
```

The final `MH3G.rso` would be placed in the folder `riivolution/MH3G/`.

# Using the mod

Right now the mod could only be used with a [Riivolution](https://wiibrew.org/wiki/Riivolution) patch

## Dolphin

`Start with Riivolution` -> Select `MH3G.xml` from the `riivolution/` folder

## Wii

* Copy the `riivolution` folder to the root of your SD card. 

* Insert your Monster Hunter Tri disk and load Riivolution. You should see the patch options appear with default settings; **do not change these settings from their defaults.**

* Launch the game with the patches via Riivolution and enjoy! 

# Credits

Thank you to:

**ComplexSphere** for [ApeSphere](https://github.com/ComplexPlane/ApeSphere) template mod
