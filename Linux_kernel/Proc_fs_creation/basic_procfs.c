/*
 * basic_procfs.c
 *
 * Description: Basic linux driver to demostrate proc fs creation
 *              interrupt, workque, mutex usage with read function
 *
 *  Created on: 06-Mar-2020
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
#include <linux/mutex.h> /* Included for mutex support */
#include <linux/workqueue.h> /* Included for work queue support */
#include <linux/interrupt.h> /* Included for interrupt handler support, and bottom half support. */
#include <linux/proc_fs.h> /* Included for /proc file system support */
#include <linux/seq_file.h> /* Included for seqfile support */

MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
MODULE_AUTHOR("Sunil Sharma P <sunilsharma.pv@gmail.com>");
MODULE_DESCRIPTION("A simple device driver - Proc fs");

/* Interrupt line */
/* On my laptop, IRQ number 1 corresponds to keyboard controller,
   which generates interrupt whenever any key is pressed. */
#define INTERRUPT_LINE 1

/* Counters to keep track of the number of interrupts, number bytes generated and number of bytes read */
int basic_procfs_interrupt_count = 0;
int basic_procfs_bytes_generated_count = 0;
int basic_procfs_bytes_read_count = 0;

/* Buffer to hold the driver data */
char basic_procfs_buffer[256];
int  basic_procfs_buffer_length = 0;

/* To hold the major number for the device */
dev_t basic_procfs_dev = 0;

/* Structure to hold the character driver information */
struct cdev basic_procfs_cdev;

/* To hold the class for the device */
static struct class *basic_procfs_class;

/* Mutex to avoid a race condition during read() function call */
struct mutex basic_procfs_read_mutex;

/* Structure to hold the wait queue for putting an application to sleep */
wait_queue_head_t basic_procfs_wait_queue;

/* Structure to hold the work information */
struct work_struct basic_procfs_work;

ssize_t basic_procfs_read(struct file *pFile, char __user *pBuffer, size_t length, loff_t *pOffset)
{
    printk("Inside the %s() function\n", __FUNCTION__);

    /* Check whether the driver has any data to be returned to the called. If not, put the caller to sleep. */
    if (basic_procfs_buffer_length == 0) {

        /* If wait_event_interruptible() returns a negative value, it means the sleep was interrupted */
        if (wait_event_interruptible(basic_procfs_wait_queue, (basic_procfs_buffer_length > 0)) < 0) {
            /* Since the program was interrupted from sleep, return 0 (EOF) */
            return 0;
        }
    }

    /* Take the mutex before copying the data */
    mutex_lock_interruptible(&basic_procfs_read_mutex);

    /* memcpy(dst, str, length) */
    copy_to_user(pBuffer, basic_procfs_buffer, basic_procfs_buffer_length);
    length = basic_procfs_buffer_length;
    basic_procfs_buffer_length = 0;

    /* Increment the number of bytes read */
    basic_procfs_bytes_read_count += length;

    /* Release the mutex */
    mutex_unlock(&basic_procfs_read_mutex);

    /* Since the buffer is empty, wake up any pending write */
    wake_up_interruptible(&basic_procfs_wait_queue);

    return length;
}

void basic_procfs_work_handler(struct work_struct *work)
{
    printk("Inside the %s() function\n", __FUNCTION__);

	/* Take the mutex before copying the data */
    mutex_lock_interruptible(&basic_procfs_read_mutex);

    /* Copy the user buffer to the driver buffer */
    memset(basic_procfs_buffer, 0, 256);

    /* Generate some data */
    sprintf(basic_procfs_buffer, "Data generated @ jiffies = %li\n", jiffies);
    basic_procfs_buffer_length = strlen(basic_procfs_buffer) + 1 /* Null Termination */;

    /* Increment the number of bytes generated */
    basic_procfs_bytes_generated_count += basic_procfs_buffer_length;

    /* Release the mutex */
    mutex_unlock(&basic_procfs_read_mutex);

    /* Since some data has arrived, wake up any pending read */
    wake_up_interruptible(&basic_procfs_wait_queue);
}

irqreturn_t basic_procfs_irq_handler(int irq_number /* This will be first parameter of request_irq */,
                                           void *irq_param /* This will be last parameter of request_irq */)
{
    printk("Inside the %s() function\n", __FUNCTION__);

    /* Schedule the work */
    schedule_work(&basic_procfs_work);

    /* Increment the number of interrupts counter */
    basic_procfs_interrupt_count++;

    /* Successfully handled the inrerrupt */
	return IRQ_HANDLED;
}

int basic_procfs_open(struct inode *pInode, struct file *pFile)
{
    printk("Inside the %s() function\n", __FUNCTION__);

    /* Initialize the mutex */
    mutex_init(&basic_procfs_read_mutex);

    /* Initialize the work to be done in response to the interrupt */
    INIT_WORK(&basic_procfs_work, basic_procfs_work_handler);

    /* Register the interrupt handler */
    /* request_irq(unsigned int irq, irq_handler_t handler, unsigned long flags, const char *name, void *dev) */
    request_irq(INTERRUPT_LINE,
                basic_procfs_irq_handler,
                IRQF_SHARED, /* Because on my laptop, IRQ INTERRUPT_LINE is already used by keyboard controller */
                "basic_procfs_irq_hdlr",
                &basic_procfs_buffer);

    return 0;
}

int basic_procfs_close(struct inode *pInode, struct file *pFile)
{
    printk("Inside the %s() function\n", __FUNCTION__);

    /* Delete / unregister the interrupt handler */
    free_irq(INTERRUPT_LINE, &basic_procfs_buffer);

    /* Flush any work that is pending */
    flush_work(&basic_procfs_work);

    /* Destroy the mutex */
    mutex_destroy(&basic_procfs_read_mutex);

    return 0;
}

/* Define the file operations structure indicating the functions to be called when the device is accessed */
static struct file_operations basic_procfs_file_ops =
{
    .owner   = THIS_MODULE,
    .open    = basic_procfs_open,
    .read    = basic_procfs_read,
    .release = basic_procfs_close,
};

/* Define the proc fs open function */
int basic_procfs_profs_handler(struct seq_file *pSeqFile, void *data)
{
    printk("Inside the %s() function\n", __FUNCTION__);

    seq_printf(pSeqFile, "Number of Interrupt Generated : %d\n", basic_procfs_interrupt_count);
    seq_printf(pSeqFile, "Number of Bytes Generated     : %d\n", basic_procfs_bytes_generated_count);
    seq_printf(pSeqFile, "Number of Bytes Read          : %d\n", basic_procfs_bytes_read_count);

    return 0;
}

int basic_procfs_procfs_open(struct inode *pInode, struct file *pFile)
{
    single_open(pFile, basic_procfs_profs_handler, NULL);
    return 0;
}

static struct file_operations basic_procfs_proc_fops =
{
    .owner   = THIS_MODULE,
    .open    = basic_procfs_procfs_open,
    .read    = seq_read,
    .release = single_release,
    .llseek  = seq_lseek,
};

int basic_procfs_init(void)
{
    printk("Inside the %s() function\n", __FUNCTION__);

    /* Create an entry for the /proc file system */
    proc_create("basic_procfs_statistics", 0666, NULL /* Parent Directory */, &basic_procfs_proc_fops);

    /* Initialize the wait queue used for putting an application to sleep */
    init_waitqueue_head(&basic_procfs_wait_queue);

    /* Initialize the driver buffer */
    sprintf(basic_procfs_buffer, "Buffer for module %s\n", __FILE__);
    basic_procfs_buffer_length = strlen(basic_procfs_buffer) + 1 /* For Null Termination */;

    /* Increment the number of bytes generated */
    basic_procfs_bytes_generated_count += basic_procfs_buffer_length;

    /* Inform the kernel about your character device driver */
    /* Register the character device driver using the 2.6 or higher style of interface */
    /* extern int alloc_chrdev_region(dev_t *, unsigned, unsigned, const char *); */
    alloc_chrdev_region(&basic_procfs_dev,
			0 /* First Minor Number for the device */,
			1 /* Number of instances */,
			"basic_procfs_simple_drv");

    /* Register the file operations for the major number / minor number device for 'n' number of instances */
    /* void cdev_init(struct cdev *, const struct file_operations *); */
    cdev_init(&basic_procfs_cdev, &basic_procfs_file_ops);

    /* Link the major / minor number of the device, 'n' instance of the device and the file operations */
    /* int cdev_add(struct cdev *, dev_t, unsigned); */
	cdev_add(&basic_procfs_cdev,
			basic_procfs_dev /* First Device */,
			1 /* Number of Instances */);


	/*Creating struct class*/
	basic_procfs_class = class_create(THIS_MODULE, "basic_procfs_class");

	/*Creating device, this will apper in /dev files system, does somethig like `mknod` */
	device_create(basic_procfs_class,
			NULL,
			basic_procfs_dev,
			NULL,
			"basic_procfs_device");

    return 0;
}

void basic_procfs_exit(void)
{
    printk("Inside the %s() function\n", __FUNCTION__);

	/* Inform the kernel that you are not going to handle the device any more */
	device_destroy(basic_procfs_class, basic_procfs_dev);

	/* Inform the kernel that you are not going to handle the class any more */
	class_destroy(basic_procfs_class);

    /* Inform the kernel that you are not going to handle the character driver any more */
    /* Delete the device */
    /* void cdev_del(struct cdev *); */
    cdev_del(&basic_procfs_cdev);

    /* Release the major / minor number region */
    /* extern void unregister_chrdev_region(dev_t, unsigned); */
    unregister_chrdev_region(basic_procfs_dev, 1 /* Number of instances */);

    /* Remove the /proc entry for the module */
    remove_proc_entry("basic_procfs_statistics", NULL /* Parent Directory */);

}

module_init(basic_procfs_init);
module_exit(basic_procfs_exit);

