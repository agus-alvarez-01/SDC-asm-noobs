#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define DEVICE_NAME "asmn_driver"

static dev_t dev_num;
static struct cdev asmn_cdev;

static int asmn_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "OPEN\n");
    return 0;
}

static int asmn_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "CLOSE\n");
    return 0;
}

static ssize_t asmn_read(struct file *file, char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "READ\n");
    return 0;
}

static ssize_t asmn_write(struct file *file, const char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "WRITE\n");
    return len;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = asmn_open,
    .release = asmn_release,
    .read = asmn_read,
    .write = asmn_write,
};

static int __init asmn_init(void)
{
    alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);

    cdev_init(&asmn_cdev, &fops);
    cdev_add(&asmn_cdev, dev_num, 1);

    printk(KERN_INFO "ASMN Driver registered. Major=%d\n", MAJOR(dev_num));

    return 0;
}

static void __exit asmn_exit(void)
{
    cdev_del(&asmn_cdev);

    unregister_chrdev_region(dev_num, 1);

    printk(KERN_INFO "ASMN Driver unloaded\n");
}

module_init(asmn_init);
module_exit(asmn_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("asm_noobs");
MODULE_DESCRIPTION("TP5 Character Device Driver");
