#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc, atoi, rand... */
#include <string.h>	/* memcpy, strlen... */
#include <stdint.h>	/* uints types */
#include <sys/types.h>	/* size_t ,ssize_t, off_t... */
#include <unistd.h>	/* close() read() write() */
#include <fcntl.h>	/* open() */
#include <sys/ioctl.h>	/* ioctl() */
#include <errno.h>	/* error codes */

// ioctl commands defined in the pci driver header
#define RD_SWITCHES   _IO('a', 'a')
#define RD_PBUTTONS   _IO('a', 'b')
#define WR_L_DISPLAY  _IO('a', 'c')
#define WR_R_DISPLAY  _IO('a', 'd')
#define WR_RED_LEDS   _IO('a', 'e')
#define WR_GREEN_LEDS _IO('a', 'f')

int main(int argc, char** argv)
{
	int fd, retval;

	if (argc < 2) {
		printf("Syntax: %s <device file path>\n", argv[0]);
		return -EINVAL;
	}

	if ((fd = open(argv[1], O_RDWR)) < 0) {
		fprintf(stderr, "Error opening file %s\n", argv[1]);
		return -EBUSY;
	}

	unsigned int data = 0x40404079;
	
	ioctl(fd, WR_R_DISPLAY);
	retval = write(fd, &data, sizeof(data));
	printf("wrote %d bytes\n", retval);
	
	ioctl(fd, WR_L_DISPLAY);
	retval = write(fd, &data, sizeof(data));
	printf("wrote %d bytes\n", retval);
	
	ioctl(fd, RD_PBUTTONS);
	read(fd, &data, 1);
	printf("new data: 0x%X\n", data);
	
	close(fd);
	return 0;
}
