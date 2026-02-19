# STM32 Nucleo-F303K8 Bare-Metal Project
 
## Overview
 
This project demonstrates bare-metal firmware development on the STM32 Nucleo-F303K8 board without using HAL or CubeIDE. The project uses CMSIS, a startup file, linker script, and Makefile for building the firmware.
 
The firmware is built using arm-none-eabi toolchain and flashed/debugged using OpenOCD and GDB.
 
---
 
## Board Used

STM32 Nucleo-F303K8
 
---
 
## Software Tools Used
 
- arm-none-eabi-gcc (compiler)
- make (build system)
- OpenOCD (flashing and debugging)
- gdb-multiarch (debugging)
- vim (editor)
- Git and GitHub (version control)
- Ubuntu Linux
 
---

## Project Structure
 
```
project/
│
├── Core/
│   ├── Inc/              # Header files
│   ├── Src/              # Source files
│   └── startup/
│       └── startup.c     # Startup file
│
├── Drivers/
│   └── CMSIS/            # CMSIS files
│
├── Linker/
│   └── linker_script.ld  # Linker script
│
├── Debug/
│   └── Makefile          # Makefile
│
├── build/                # Build output files
│
└── README.md
```
---

## Build Instructions
 
- Navigate to the Debug directory:

``` 
cd Debug
```

- Build the project using make:

``` 
make
```
 
- After successful build, output files will be generated in the `build/` directory:
 
    - `project.elf` – Executable file used for debugging and flashing
    - `project.bin` – Binary file used for flashing
 
---
 
## Flash Instructions
 
- Start OpenOCD in a terminal:

```
openocd -f interface/stlink.cfg -f target/stm32f3x.cfg
```
 
- Open another terminal and start GDB:

```
gdb-multiarch build/project.elf
```
 
- Inside GDB, run the following commands:

```
target remote localhost:3333
monitor reset halt
load
monitor reset init
continue
```
 
---
 
## Debug Instructions
 
Common GDB debugging commands:
 
- Set breakpoint at main:

```
break main
```
 
- Run the program:

```
continue
```
 
- Check CPU registers:

```
info registers
```
 
---

## Requirements

- Install required tools on Ubuntu/Linux:

```
sudo apt install gcc-arm-none-eabi
sudo apt install gdb-multiarch
sudo apt install openocd
sudo apt install make
```
---
 
## Features
 
- Custom startup file implementation
- Custom linker script configuration
- Bare-metal register-level programming
- CMSIS-based development
- Makefile-based build system
- OpenOCD-based flashing and debugging
- GDB-based debugging support
 
---

## Development Environment
 
```
Ubuntu Linux
Vim Editor
ARM GCC Toolchain
OpenOCD
GDB
Git and GitHub
```
 
---

