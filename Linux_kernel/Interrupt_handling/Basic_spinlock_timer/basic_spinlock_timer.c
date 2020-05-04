/*
 * basic_spinlock_timerr.c
 *
 * Description: Basic linux driver to demostrate spinlock and timer
 *              hadling with read function
 *
 *  Created on: 04-Mar-2020
 *      Author: Sunil Sharma P <sunilsharma.pv@gmail.com>
 *
 *     Version: 1.0v
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h> /* Included for character device driver support */
#include <linux/uaccess.h> /* Included for copy_to_user() */
#include <linux/cdev.h> /* Included for 2.6 or higher character driver support */
#include <linux/sched.h> /* Because wait will put you to sleep and the schedule will move the called to wait queue */
#include <linux/wait.h> /* Included for wait queue support */
#include <linux/delay.h> /* Included for delay support */
#include <linux/timer.h> /* Included for kernel timer support */
#include <linux/spinlock.h> /* Included for spin lock support */

MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
MODULE_AUTHOR("Sunil Sharma P <sunilsharma.pv@gmail.com>");
MODULE_DESCRIPTION("A simple device driver - Spinlock and Timers");

/* Buffer to hold the driver data */
char basic_spinlock_timer_buffer[256];
int  basic_spinlock_timer_buffer_length = 0;

/* To hold the major number for the device */
dev_t basic_spinlock_timer_dev = 0;

/* Structure to hold the character driver information */
struct cdev basic_spinlock_timer_cdev;

/* To hold the class for the device */
static struct class *basic_spinlock_timer_class;

/* Structure to hold the wait queue for putting an application to sleep */
wait_queue_head_t basic_spinlock_timer_wait_queue;

/* Spin lock to avoid a race condition during read() and timer handler */
spinlock_t basic_spinlock_timer_spin_lock;

/* Timer to generate the data for the read function */
struct timer_list basic_spinlock_timer_data_generation_timer;

ssize_t basic_spinlock_timer_read(struct file *pFile, char __user *pBuffer, size_t length, loff_t *pOffset)
{
    printk("Inside the %s() function\n", __FUNCTION__);

    /* Check whether the driver has any data to be returned to the called. If not, put the caller to sleep. */
    if (basic_spinlock_timer_buffer_length == 0) {

        /* If wait_event_interruptible() returns a negative value, it means the sleep was interrupted */
        if (wait_event_interruptible(basic_spinlock_timer_wait_queue, (basic_spinlock_timer_buffer_length > 0)) < 0) {
            /* Since the program was interrupted from sleep, return 0 (EOF) */
            return 0;
        }
    }

    /* memcpy(dst, str, length) */
    copy_to_user(pBuffer, basic_spinlock_timer_buffer, basic_spinlock_timer_buffer_length);
    length = basic_spinlock_timer_buffer_length;

	spin_lock(&basic_spinlock_timer_spin_lock);
    basic_spinlock_timer_buffer_length = 0;
    spin_unlock(&basic_spinlock_timer_spin_lock);

    /* Since the buffer is empty, wake up any pending write */
    wake_up_interruptible(&basic_spinlock_timer_wait_queue);

    return length;
}

void basic_spinlock_timer_timer_handler(struct timer_list *list)
{
    printk("Inside the %s() function\n", __FUNCTION__);

    /* Copy the user buffer to the driver buffer */
    memset(basic_spinlock_timer_buffer, 0, 256);

    /* Generate some data */
    sprintf(basic_spinlock_timer_buffer, "Spinlock Timer data generated @ jiffies = %li\n", jiffies);
    spin_lock(&basic_spinlock_timer_spin_lock);
    basic_spinlock_timer_buffer_length = strlen(basic_spinlock_timer_buffer) + 1 /* Null Termination */;
    spin_unlock(&basic_spinlock_timer_spin_lock);

    /* Initialize the timer to expiry again after some time */
	/* int mod_timer (struct timer_list * timer, unsigned long expires); */
	/* expires in millisecond, 2000 millisec */
	mod_timer(&basic_spinlock_timer_data_generation_timer, jiffies + HZ * 2);

    /* Since some data has arrived, wake up any pending read */
    wake_up_interruptible(&basic_spinlock_timer_wait_queue);
}

int basic_spinlock_timer_open(struct inode *pInode, struct file *pFile)
{
    printk("Inside the %s() function\n", __FUNCTION__);

    /* Initialize the spin lock */
    spin_lock_init(&basic_spinlock_timer_spin_lock);

    /* Initialize the time when timer expires, function to be called on expiry, parameter to be passed to the function */
	/* void timer_setup(timer, callback, flags) */
	timer_setup(&basic_spinlock_timer_data_generation_timer, basic_spinlock_timer_timer_handler, 0);

	/* Give the initial value for timer to expire */
    basic_spinlock_timer_data_generation_timer.expires = jiffies + HZ * 2;

    /* Activate the timer */
    add_timer(&basic_spinlock_timer_data_generation_timer);

    return 0;
}

int basic_spinlock_timer_close(struct inode *pInode, struct file *pFile)
{
    printk("Inside the %s() function\n", __FUNCTION__);

    /* Delete any timers that are running */
    del_timer_sync(&basic_spinlock_timer_data_generation_timer);

    return 0;
}

/* Define the file operations structure indicating the functions to be called when the device is accessed */
static struct file_operations basic_spinlock_timer_file_ops =
{
    .owner   = THIS_MODULE,
    .open    = basic_spinlock_timer_open,
    .read    = basic_spinlock_timer_read,
    .release = basic_spinlock_timer_close,
};

int basic_spinlock_timer_init(void)
{
    printk("Inside the %s() function\n", __FUNCTION__);

    /* Initialize the wait queue used for putting an application to sleep */
    init_waitqueue_head(&basic_spinlock_timer_wait_queue);

    /* Initialize the driver buffer */
    sprintf(basic_spinlock_timer_buffer, "Buffer for module %s\n", __FILE__);
    basic_spinlock_timer_buffer_length = strlen(basic_spinlock_timer_buffer) + 1 /* For Null Termination */;

    /* Inform the kernel about your character device driver */
    /* Register the character device driver using the 2.6 or higher style of interface */
    /* extern int alloc_chrdev_region(dev_t *, unsigned, unsigned, const char *); */
    alloc_chrdev_region(&basic_spinlock_timer_dev,
            0 /* First Minor Number for the device */,
            1 /* Number of instances */,
            "basic_spinlock_timer_simple_drv");

    /* Register the file operations for the major number / minor number device for 'n' number of instances */
    /* void cdev_init(struct cdev *, const struct file_operations *); */
    cdev_init(&basic_spinlock_timer_cdev, &basic_spinlock_timer_file_ops);

    /* Link the major / minor number of the device, 'n' instance of the device and the file operations */
    /* int cdev_add(struct cdev *, dev_t, unsigned); */
    cdev_add(&basic_spinlock_timer_cdev,
            basic_spinlock_timer_dev /* First Device */,
            1 /* Number of Instances */);

    /*Creating struct class*/
    basic_spinlock_timer_class = class_create(THIS_MODULE, "basic_spinlock_timer_class");

    /*Creating device, this will apper in /dev files system, does somethig like `mknod` */
    device_create(basic_spinlock_timer_class,
            NULL,
            basic_spinlock_timer_dev,
            NULL,
            "basic_spinlock_timer_device");

    return 0;
}

void basic_spinlock_timer_exit(void)
{
    printk("Inside the %s() function\n", __FUNCTION__);

    /* Inform the kernel that you are not going to handle the device any more */
    device_destroy(basic_spinlock_timer_class, basic_spinlock_timer_dev);

    /* Inform the kernel that you are not going to handle the class any more */
    class_destroy(basic_spinlock_timer_class);

    /* Inform the kernel that you are not going to handle the character driver any more */
    /* Delete the device */
    /* void cdev_del(struct cdev *); */
    cdev_del(&basic_spinlock_timer_cdev);

    /* Release the major / minor number region */
    /* extern void unregister_chrdev_region(dev_t, unsigned); */
    unregister_chrdev_region(basic_spinlock_timer_dev, 1 /* Number of instances */);
}

module_init(basic_spinlock_timer_init);
module_exit(basic_spinlock_timer_exit);

