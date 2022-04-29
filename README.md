# Project layout helper and Scripts/Documentations for developing IF817 Course project

**REMIDER**: This project layout it's not mandatory! You can feel free to use whatever build system you use for developing a user application. This has only a simple Makefile for people who don't need to setup a complex build system and just want to develop a simple C/C++/Assembly application. BUT be careful with the 'driver' folder, inside it has a Makefile that is vital for building the driver/module and one must not remove it.

## Content
 - [Useful Commands](docs/commands.md)

## Current project tree

	.
	├── app
	│   ├── include
	│   │   ├── display.h
	│   │   └── ioctl_cmds.h
	│   └── src
	│       └── main.cpp
	├── docs
	│   └── commands.md
	├── driver
	│   ├── char-lkm-exemple.c
	│   ├── de2i-150-ioctl-exemple.c
	│   ├── de2i-150-mockup.c
	│   ├── ioctl_cmds.h
	│   └── Makefile
	├── exemples
	│   ├── app-ioctl-exemple.c
	│   └── syscalls-exemple.c
	├── LICENSE
	├── Makefile
	├── README.md
	└── scripts
	    ├── app-ioctl-exemple.py
	    ├── ioctl_cmds.py
	    └── syscalls-exemple.py

