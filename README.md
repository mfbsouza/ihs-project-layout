# Project layout helper and Scripts/Documentations for developing IF817 Course project

**REMIDER**: This project layout it's not mandatory! You can feel free to use whatever build system you use for developing a user application. This has only a simple Makefile for people who don't need to setup a complex build system and just want to develop a simple C/C++/Assembly application. BUT be careful with the 'driver' folder, inside it has a Makefile that is vital for building the driver/module and one must not remove it.

## Content
 - [Useful Commands](docs/commands.md)

## Current project tree

	.
	├── src
	│   └── main.cpp
	├── include
	│   ├── display.h
	│   └── ioctl_cmds.h
	├── driver
	│   ├── char
	│   │   ├── dummy.c
	│   │   └── Makefile
	│   └── pci
	│       ├── de2i-150.c
	│       └── Makefile
	├── exemples
	│   ├── c
	│   │   ├── app-char.c
	│   │   └── app-pci.c
	│   └── python
	│       ├── app-char.py
	│       └── app-pci.py
	├── docs
	│   └── commands.md
	├── LICENSE
	├── Makefile
	├── README.md
	└── setup.sh
