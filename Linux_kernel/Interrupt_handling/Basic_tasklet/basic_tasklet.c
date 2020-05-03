/*
 * basic_tasklet.c
 *
 * Description: Basic linux driver to demostrate interrupt handling with tasklet
 *              Registring request_irq(), spinlock usage with read function
 *
 *  Created on: 03-Mar-2020
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
#include <linux/spinlock.h> /* Included for spin lock support */
#include <linux/interrupt.h> /* Included for interrupt handler support, and bottom half support. */

MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
MODULE_AUTHOR("Sunil Sharma P <sunilsharma.pv@gmail.com>");
MODULE_DESCRIPTION("A simple device driver - Tasklet & Spinlock");

/* Interrupt line */
/* On my laptop, IRQ number 1 corresponds to keyboard controller which generates interrupt whenever any key is pressed. */
#define INTERRUPT_LINE 1

/* Buffer to hold the driver data */
char basic_tasklet_buffer[256];
int basic_tasklet_buffer_length = 0;

/* To hold the major number for the device */
dev_t basic_tasklet_dev = 0;

/* Structure to hold the character driver information */
struct cdev basic_tasklet_cdev;

/* To hold the class for the device */
static struct class *basic_tasklet_class;

/* Spin lock to avoid a race condition during read() and timer handler */
spinlock_t basic_spin_lock;

/* Structure to hold the wait queue for putting an application to sleep */
wait_queue_head_t basic_wait_queue;

/* Structure to hold the tasklet information */
struct tasklet_struct basic_tasklet;

ssize_t basic_tasklet_read(struct file *pFile, char __user *pBuffer, size_t length, loff_t *pOffset)
{
    printk("Inside the %s() function\n", __FUNCTION__);

    /* Check whether the driver has any data to be returned to the called. If not, put the caller to sleep. */
    if (basic_tasklet_buffer_length == 0) {

        /* If wait_event_interruptible() returns a negative value, it means the sleep was interrupted */
        if (wait_event_interruptible(basic_wait_queue, (basic_tasklet_buffer_length > 0)) < 0) {
            /* Since the program was interrupted from sleep, return 0 (EOF) */
            return 0;
        }
    }

    /* memcpy(dst, str, length) */
    copy_to_user(pBuffer, basic_tasklet_buffer, basic_tasklet_buffer_length);
    length = basic_tasklet_buffer_length;
    spin_lock_bh(&basic_spin_lock);
    basic_tasklet_buffer_length = 0;
    spin_unlock_bh(&basic_spin_lock);

    /* Since the buffer is empty, wake up any pending write */
    wake_up_interruptible(&basic_wait_queue);

    return length;
}

void basic_tasklet_handler(unsigned long param)
{
    printk("Inside the %s() function\n", __FUNCTION__);

    /* Copy the user buffer to the driver buffer */
    memset(basic_tasklet_buffer, 0, 256);

    /* Generate some data */
    sprintf(basic_tasklet_buffer, "Tasklet data generated @ jiffies = %li\n", jiffies);
    spin_lock_bh(&basic_spin_lock);
    basic_tasklet_buffer_length = strlen(basic_tasklet_buffer) + 1 /* Null Termination */;
    spin_unlock_bh(&basic_spin_lock);

    /* Since some data has arrived, wake up any pending read */
    wake_up_interruptible(&basic_wait_queue);
}

irqreturn_t basic_tasklet_irq_handler(int irq_number /* This will be first parameter of request_irq */,
        void *irq_param /* This will be last parameter of request_irq */)
{
    printk("\nInside the %s() function\n", __FUNCTION__);

    /* Schedule the tasklet */
    tasklet_schedule(&basic_tasklet);

    /* Successfully handled the inrerrupt */
    return IRQ_HANDLED;
}

int basic_tasklet_open(struct inode *pInode, struct file *pFile)
{
    printk("Inside the %s() function\n", __FUNCTION__);

    /* Initialize the spin lock */
    spin_lock_init(&basic_spin_lock);

    /* Initialize the tasklet */
    /* extern void tasklet_init(struct tasklet_struct *t, void (*func)(unsigned long), unsigned long data) */
    tasklet_init(&basic_tasklet, basic_tasklet_handler, 0);

    /* Register the interrupt handler */
    /* request_irq(unsigned int irq, irq_handler_t handler, unsigned long flags, const char *name, void *dev) */
    request_irq(INTERRUPT_LINE,
            basic_tasklet_irq_handler,
            IRQF_SHARED, /* Because on my laptop, IRQ 1 is already used by key board controller, so sharing with that */
            "basic_irq_hdlr",
            &basic_tasklet_buffer);

    return 0;
}

int basic_tasklet_close(struct inode *pInode, struct file *pFile)
{
    printk("Inside the %s() function\n", __FUNCTION__);

    /* Delete / unregister the interrupt handler */
    free_irq(INTERRUPT_LINE, &basic_tasklet_buffer);

    /* Kill any pending tasklets */
    tasklet_kill(&basic_tasklet);

    return 0;
}

/* Define the file operations structure indicating the functions to be called when the device is accessed */
struct file_operations basic_tasklet_file_ops =
{
    .owner   = THIS_MODULE,
    .open    = basic_tasklet_open,
    .read    = basic_tasklet_read,
    .release = basic_tasklet_close,
};

int basic_tasklet_init(void)
{
    printk("Inside the %s() function\n", __FUNCTION__);

    /* Initialize the wait queue used for putting an application to sleep */
    init_waitqueue_head(&basic_wait_queue);

    /* Initialize the driver buffer */
    sprintf(basic_tasklet_buffer, "Buffer for module %s\n", __FILE__);
    basic_tasklet_buffer_length = strlen(basic_tasklet_buffer) + 1 /* For Null Termination */;

    /* Inform the kernel about your character device driver */
    /* Register the character device driver using the 2.6 or higher style of interface */
    /* extern int register_chrdev_region(dev_t, unsigned, const char *); */
    // register_chrdev_region(basic_major_minor_number, 1 /* Number of Devices */, "basic_simple_drv");
    /* extern int alloc_chrdev_region(dev_t *, unsigned, unsigned, const char *); */
    alloc_chrdev_region(&basic_tasklet_dev,
            0 /* First Minor Number for the device */,
            1 /* Number of instances */,
            "basic_tasklet_drv");

    /* Register the file operations for the major number / minor number device for 'n' number of instances */
    /* void cdev_init(struct cdev *, const struct file_operations *); */
    cdev_init(&basic_tasklet_cdev, &basic_tasklet_file_ops);

    /* Link the major / minor number of the device, 'n' instance of the device and the file operations */
    /* int cdev_add(struct cdev *, dev_t, unsigned); */
    cdev_add(&basic_tasklet_cdev, basic_tasklet_dev /* First Device */, 1 /* Number of Instances */);

    /*Creating struct class*/
    basic_tasklet_class = class_create(THIS_MODULE, "basic_tasklet_class");

    /*Creating device, this will apper in /dev files system, does somethig like `mknod` */
    device_create(basic_tasklet_class,
            NULL,
            basic_tasklet_dev,
            NULL,
            "basic_tasklet_device");

    return 0;
}

void basic_tasklet_exit(void)
{
    printk("Inside the %s() function\n", __FUNCTION__);

    /* Inform the kernel that you are not going to handle the device any more */
    device_destroy(basic_tasklet_class, basic_tasklet_dev);

    /* Inform the kernel that you are not going to handle the class any more */
    class_destroy(basic_tasklet_class);

    /* Inform the kernel that you are not going to handle the character driver any more */
    /* Delete the device */
    /* void cdev_del(struct cdev *); */
    cdev_del(&basic_tasklet_cdev);

    /* Release the major / minor number region */
    /* extern void unregister_chrdev_region(dev_t, unsigned); */
    unregister_chrdev_region(basic_tasklet_dev, 1 /* Number of instances */);

}

module_init(basic_tasklet_init);
module_exit(basic_tasklet_exit);

