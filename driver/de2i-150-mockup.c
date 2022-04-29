#include <linux/init.h>
#include <linux/module.h>	/* THIS_MODULE macro */
#include <linux/fs.h>		/* VFS related */
#include <linux/ioctl.h>	/* ioctl syscall */
#include <linux/errno.h>	/* error codes */
#include <linux/types.h>	/* dev_t number */
#include <linux/cdev.h>		/* char device registration */
#include <linux/uaccess.h>	/* copy_*_user functions */
#include <linux/pci.h>		/* pci funcs and types */

#include "ioctl_cmds.h"

/* driver constants */

#define DRIVER_NAME 	"my_driver"
#define FILE_NAME 	"mydev"
#define DRIVER_CLASS 	"MyModuleClass"
#define MY_PCI_VENDOR_ID 0x1172
#define MY_PCI_DEVICE_ID 0x0004

/* meta information */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("mfbsouza");
MODULE_DESCRIPTION("simple pci driver for DE2i-150 dev board");

/* lkm entry and exit points */

static int  __init my_init (void);
static void __exit my_exit (void);

module_init(my_init);
module_exit(my_exit);

/* char device system calls */

static int	my_open   (struct inode*, struct file*);
static int 	my_close  (struct inode*, struct file*);
static ssize_t 	my_read   (struct file*, char __user*, size_t, loff_t*);
static ssize_t 	my_write  (struct file*, const char __user*, size_t, loff_t*);
static long int	my_ioctl  (struct file*, unsigned int, unsigned long);

/* pci functions */

static int  my_pci_probe  (struct pci_dev *dev, const struct pci_device_id *id);
static void my_pci_remove (struct pci_dev *dev);

/* pci ids which this driver supports */

static struct pci_device_id pci_ids[] = {
	{PCI_DEVICE(MY_PCI_VENDOR_ID, MY_PCI_DEVICE_ID), },
	{0, }
};
MODULE_DEVICE_TABLE(pci, pci_ids);

/* device file operations */

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = my_read,
	.write = my_write,
	.unlocked_ioctl	= my_ioctl,
	.open = my_open,
	.release = my_close
};

/* pci driver operations */

static struct pci_driver pci_ops = {
	.name = "alterahello",
	.id_table = pci_ids,
	.probe = my_pci_probe,
	.remove = my_pci_remove
};

/* variables for char device registration to kernel */

static dev_t my_device_nbr;
static struct class* my_class;
static struct cdev my_device;

/* device data */

static void* display_r = NULL;
static void* display_l = NULL;
static void* switches = NULL;
static void* p_buttons = NULL;

static void* read_pointer = NULL;
static void* write_pointer = NULL;

static const char* perf_names[] = {
	"switches",
	"p_buttons",
	"display_l",
	"display_r",
	"green_leds",
	"red_leds"
};
static int write_name_index = 2 + 1;
static int read_name_index = 0;

/* functions implementation */

static int __init my_init(void)
{
	printk("my_driver: loaded to the kernel\n");

	/* 0. register pci driver to the kernel */
	if (pci_register_driver(&pci_ops) < 0) {
		printk("my_driver: PCI driver registration failed\n");
		return -EAGAIN;
	}

	/* 1. request the kernel for a device number */
	if (alloc_chrdev_region(&my_device_nbr, 0, 1, DRIVER_NAME) < 0) {
		printk("my_driver: device number could not be allocated!\n");
		return -EAGAIN;
	}
	printk("my_driver: device number %d was registered!\n", MAJOR(my_device_nbr));

	/* 2. create class : appears at /sys/class */
	if ((my_class = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL) {
		printk("my_driver: device class count not be created!\n");
		goto ClassError;
	}

	/* 3. associate the cdev with a set of file operations */
	cdev_init(&my_device, &fops);

	/* 4. create the device node */
	if (device_create(my_class, NULL, my_device_nbr, NULL, FILE_NAME) == NULL) {
		printk("my_driver: can not create device file!\n");
		goto FileError;
	}

	/* 5. now make the device live for the users to access */
	if (cdev_add(&my_device, my_device_nbr, 1) == -1){
		printk("my_driver: registering of device to kernel failed!\n");
		goto AddError;
	}

	return 0;

AddError:
	device_destroy(my_class, my_device_nbr);
FileError:
	class_destroy(my_class);
ClassError:
	unregister_chrdev(my_device_nbr, DRIVER_NAME);
	pci_unregister_driver(&pci_ops);
	return -EAGAIN;
}

static void __exit my_exit(void)
{
	cdev_del(&my_device);
	device_destroy(my_class, my_device_nbr);
	class_destroy(my_class);
	unregister_chrdev(my_device_nbr, DRIVER_NAME);
	pci_unregister_driver(&pci_ops);
	printk("my_driver: goodbye kernel!\n");
}

static int my_open(struct inode* inode, struct file* filp)
{
	printk("my_driver: open was called\n");
	return 0;
}

static int my_close(struct inode* inode, struct file* filp)
{
	printk("my_driver: close was called\n");
	return 0;
}

/* mockup read */
static ssize_t my_read(struct file* filp, char __user* buf, size_t count, loff_t* f_pos)
{
	ssize_t retval = 0;
	int to_cpy = 0;
	static unsigned int temp_read = 0;

	/* read from the """device""" */
	//temp_read = ioread32(read_pointer);
	temp_read = 0x40792430; // fake ioread32
	printk("my_driver: red 0x%X from the %s\n", temp_read, perf_names[read_name_index]);

	/* get amount of bytes to copy to user */
	to_cpy = (count <= sizeof(temp_read)) ? count : sizeof(temp_read);

	/* copy data to user */
	retval = to_cpy - copy_to_user(buf, &temp_read, to_cpy);

	return retval;
}

/* mockup write */
static ssize_t my_write(struct file* filp, const char __user* buf, size_t count, loff_t* f_pos)
{
	ssize_t retval = 0;
	int to_cpy = 0;
	static unsigned int temp_write = 0;

	/* get amount of bytes to copy from user */
	to_cpy = (count <= sizeof(temp_write)) ? count : sizeof(temp_write);

	/* copy data from user */
	retval = to_cpy - copy_from_user(&temp_write, buf, to_cpy);

	/* send to """device""" */
	//iowrite32(temp_write, write_pointer);
	printk("my_writer: wrote 0x%X to the %s\n", temp_write, perf_names[write_name_index]);

	return retval;
}

static long int my_ioctl(struct file*, unsigned int cmd, unsigned long arg)
{
	switch(cmd){
	case RD_SWITCHES:
		read_pointer = switches;
		read_name_index = 0;
		printk("my_driver: updated read pointer to %s\n", perf_names[read_name_index]);
		break;
	case RD_PBUTTONS:
		read_pointer = p_buttons;
		read_name_index = 1;
		printk("my_driver: updated read pointer to %s\n", perf_names[read_name_index]);
		break;
	case WR_L_DISPLAY:
		write_pointer = display_l;
		write_name_index = 2 + 0;
		printk("my_driver: updated write pointer to %s\n", perf_names[write_name_index]);
		break;
	case WR_R_DISPLAY:
		write_pointer = display_r;
		write_name_index = 2 + 1;
		printk("my_driver: updated write pointer to %s\n", perf_names[write_name_index]);
		break;
	default:
		printk("my_driver: unknown ioctl command: 0x%X\n", cmd);
	}
	return 0;
}

static int my_pci_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	int vendor, retval;
	u8 revision;
	unsigned long resource;

	retval = pci_enable_device(dev);

	pci_read_config_byte(dev, PCI_REVISION_ID, &revision);
	printk("my_driver: PCI revision: %d\n", revision);

	pci_read_config_dword(dev, 0, &vendor);
	printk("my_driver: PCI device found. Vendor: 0x%X\n", vendor);

	resource = pci_resource_start(dev, 0);
	printk("my_driver: PCI device resources start at bar 0: 0x%lx\n", resource);
	
	display_r = ioremap(resource + 0xC000, 0x20);
	display_l = ioremap(resource + 0xC140, 0x20);
	switches = ioremap(resource + 0xC040, 0x20);
	p_buttons = ioremap(resource + 0xC080, 0x20);

	read_pointer = switches; // default read peripheral pointer
	write_pointer = display_r; // default write peripheral pointer

	return 0;
}

static void my_pci_remove(struct pci_dev *dev)
{
	read_pointer = NULL;
	write_pointer = NULL;

	iounmap(display_r);
	iounmap(display_l);
	iounmap(switches);
	iounmap(p_buttons);
	pci_disable_device(dev);
}
