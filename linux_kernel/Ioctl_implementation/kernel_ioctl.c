/*
 * kernel_ioctl.c
 *
 * Description: http://opensourceforu.com/2011/08/io-control-in-linux/
 *              Anil Kumar Pugalia
 *
 *  Created on: 29-Apr-2020
 *      Author: Sunil Sharma P <sunilsharma.pv@gmail.com>
 *
 *     Version: 1.0v
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <linux/uaccess.h>

#include "header_ioctl.h"

#define FIRST_MINOR 0
#define MINOR_CNT 1

static dev_t dev;
static struct cdev c_dev;
static struct class *cl;
static int status = 1, dignity = 3, ego = 5;

static int my_open(struct inode *i, struct file *f)
{
	return 0;
}

static int my_close(struct inode *i, struct file *f)
{
	return 0;
}

static long my_ioctl(struct file *f, unsigned int cmd, unsigned long arg)
{
	query_arg_t q;

	switch(cmd) {
	case QUERY_GET_VARIABLES:
		q.status = status;
		q.dignity = dignity;
		q.ego = ego;
		if(copy_to_user((query_arg_t *) arg, &q, sizeof(query_arg_t))) {
			return -EACCES;
		}
	break;
	case QUERY_CLR_VARIABLES:
		status = 0;
		dignity = 0;
		ego = 0;
	break;
	case QUERY_SET_VARIABLES:
		if(copy_from_user(&q, (query_arg_t *) arg, sizeof(query_arg_t))) {
			return -EACCES;
		}
		status = q.status;
		dignity = q.dignity;
		ego = q.ego;
	break;
	default:
		return -EINVAL;
	}

	return 0;
}

static struct file_operations query_fops = {.owner = THIS_MODULE, .open = my_open, .release = my_close, .unlocked_ioctl = my_ioctl};

static int __init query_ioctl_init(void)
{
	int ret;
	struct device *dev_ret;

	/**
	 * alloc_chrdev_region() - register a range of char device numbers
	 * @dev: output parameter for first assigned number
	 * @baseminor: first of the requested range of minor numbers
	 * @count: the number of minor numbers required
	 * @name: the name of the associated device or driver
	 *
	 * Allocates a range of char device numbers.  The major number will be
	 * chosen dynamically, and returned (along with the first minor number)
	 * in @dev.  Returns zero or a negative error code.

	 int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count, const char *name)
	 */
	if ((ret = alloc_chrdev_region(&dev, FIRST_MINOR, MINOR_CNT, "query_ioctl")) < 0) {
		return ret;
	}

	/**
	 * cdev_init() - initialize a cdev structure
	 * @cdev: the structure to initialize
	 * @fops: the file_operations for this device
	 *
	 * Initializes @cdev, remembering @fops, making it ready to add to the
	 * system with cdev_add().

	 void cdev_init(struct cdev *cdev, const struct file_operations *fops)
	 */
	cdev_init(&c_dev, &query_fops);

	/**
	 * cdev_add() - add a char device to the system
	 * @p: the cdev structure for the device
	 * @dev: the first device number for which this device is responsible
	 * @count: the number of consecutive minor numbers corresponding to this
	 *         device
	 *
	 * cdev_add() adds the device represented by @p to the system, making it
	 * live immediately.  A negative error code is returned on failure.

	 int cdev_add(struct cdev *p, dev_t dev, unsigned count)
	 */
	if ((ret = cdev_add(&c_dev, dev, MINOR_CNT)) < 0) {
		return ret;
	}

	/**
	 * class_create - create a struct class structure
	 * @owner: pointer to the module that is to "own" this struct class
	 * @name: pointer to a string for the name of this class.
	 *
	 * This is used to create a struct class pointer that can then be used
	 * in calls to device_create().
	 *
	 * Returns &struct class pointer on success, or ERR_PTR() on error.
	 *
	 * Note, the pointer created here is to be destroyed when finished by
	 * making a call to class_destroy().
	 */
	if (IS_ERR(cl = class_create(THIS_MODULE, "char"))) {
		cdev_del(&c_dev);
		unregister_chrdev_region(dev, MINOR_CNT);
		return PTR_ERR(cl);
	}

	/**
	 * device_create - creates a device and registers it with sysfs
	 * @class: pointer to the struct class that this device should be registered to
	 * @parent: pointer to the parent struct device of this new device, if any
	 * @devt: the dev_t for the char device to be added
	 * @drvdata: the data to be added to the device for callbacks
	 * @fmt: string for the device's name
	 *
	 * This function can be used by char device classes.  A struct device
	 * will be created in sysfs, registered to the specified class.
	 *
	 * A "dev" file will be created, showing the dev_t for the device, if
	 * the dev_t is not 0,0.
	 * If a pointer to a parent struct device is passed in, the newly created
	 * struct device will be a child of that device in sysfs.
	 * The pointer to the struct device will be returned from the call.
	 * Any further sysfs files that might be required can be created using this
	 * pointer.
	 *
	 * Returns &struct device pointer on success, or ERR_PTR() on error.
	 *
	 * Note: the struct class passed to this function must have previously
	 * been created with a call to class_create().

	 struct device *device_create(struct class *class, struct device *parent, dev_t devt, void *drvdata, const char *fmt, ...)
	 */
	if (IS_ERR(dev_ret = device_create(cl, NULL, dev, NULL, "query-Sharma"))) {
		class_destroy(cl);
		cdev_del(&c_dev);
		unregister_chrdev_region(dev, MINOR_CNT);
		return PTR_ERR(dev_ret);
	}

	return 0;
}

static void __exit query_ioctl_exit(void)
{	device_destroy(cl, dev);
	class_destroy(cl);
	cdev_del(&c_dev);
	unregister_chrdev_region(dev, MINOR_CNT);
}

module_init( query_ioctl_init);
module_exit( query_ioctl_exit);

MODULE_LICENSE("GPL");
