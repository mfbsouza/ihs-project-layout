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
	printf("hello world\n");
	return 0;
}
