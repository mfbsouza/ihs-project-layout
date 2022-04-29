# Useful commands

## driver related commands

**REMINDER**: most device files in a Unix-based system are stored at /dev directory

insert a compiled module/driver to the kernel

	$ sudo insmod path/to/file.ko

remove a module/driver from the kernel

	$ sudo rmmod module_name

obs: usually the 'module name' is the same name as the .ko file inserted

change the permissions of a file or device file

	$ sudo chmod 666 /path/to/my_device_file

obs: permission number is a octal number, where 4 = read, 2 = write, 1 = execute.
So 7 = 4 + 2 + 1, wich means RWX. 6 = 4 + 2, wich means RW-.

list all running modules/drivers

	$ lsmod

list all running modules/drivers and search the output for a matching string

	$ lsmod | grep string

watch the kernel output messages

	$ sudo dmesg

watch the kernel output messages with more readable timestamp

	$ sudo dmesg -wT

## file related commands

print out a string to the standard output (usually a terminal)

	$ echo "string"

redirect the output of a command to a file using '>'

	$ echo "string" > test
	$ ls > test2

obs: the '>' operation will empty the content of the file if the file already exists

redirect and append the output of a command to a file using '>>'

	$ echo "string" >> test
	$ ls >> test2

redirect the output of a command to the input of another using the '|' operator

	$ ls | grep Documents

print out the full content of a file

	$ cat path/to/file

print out N bytes from the beginning of a file

	$ head -c N path/to/file

print out N bytes from the ending of a file

	$ tail -c N path/to/file

print out N lines (util the '\n' character) from the beginning of a file

	$ head -n N path/to/file

print out N lines (util the '\n' character) from the ending of a file

	$ tail -n N path/to/file

info about a given file

	$ file path/to/file

list the permission number, major and minor number, and other info about a file

	$ ls -la path/to/file
