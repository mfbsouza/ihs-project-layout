#!/usr/bin/python3

import os, sys
from fcntl import ioctl
from ioctl_cmds import *

if len(sys.argv) < 2:
    print("Error: expected more command line arguments")
    print("Syntax: %s </dev/device_file>"%sys.argv[0])
    exit(1)

fd = os.open(sys.argv[1], os.O_RDWR)

# data to write
data = 0x40404079;
# converting data to a string
data_str_value = data.to_bytes(4, 'little').decode()

ioctl(fd, WR_R_DISPLAY)
retval = os.write(fd, data_str_value)
print("wrote %d bytes"%retval)

# data to write
data = 0x79404040;
# converting data to a string
data_str_value = data.to_bytes(4, 'little').decode()

ioctl(fd, WR_L_DISPLAY)
retval = os.write(fd, data_str_value)
print("wrote %d bytes"%retval)

ioctl(fd, RD_PBUTTONS)
red = os.read(fd, 1); # read 1 byte and store in red var
print("red 0x%X"%int(red))

os.close(fd)
