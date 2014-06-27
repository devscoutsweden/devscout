/*
 * The official /dev/scout kernel module!
 */
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "scout"

static int device_open(struct inode *inode, struct file *file)
{
        return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
        return 0;
}

static ssize_t device_write(struct file *filep, 
                        const char *buff, 
                        size_t len,
                        loff_t *offset)
{
        pr_err("scout doesn't support write operations");
        return -EINVAL;
}

static ssize_t device_read(struct file *file,
                       char *buffer,
                       size_t length,
                       loff_t *offset)
{
        char * fair_dice_roll;
        long ret;

        fair_dice_roll = "4\n"; /* Guaranteed to be random */
        ret = copy_to_user(buffer, fair_dice_roll, 2);

        if (*offset == 0) {
                *offset += 1;
                return 2;
        } else {
                return 0;
        }
}

static const struct file_operations fops = {
        .owner = THIS_MODULE,
        .read = device_read,
        .open = device_open,
        .write = device_write,
        .release = device_release
};

static struct miscdevice scout_dev = {
        .minor = MISC_DYNAMIC_MINOR,
        .name = DEVICE_NAME,
        .fops = &fops,
        .mode = S_IRUGO /* read-only device */
};

static int scout_init(void)
{
        int err;
        printk(KERN_INFO "Scout module registered");
        err = misc_register(&scout_dev);
        if (err) {
                pr_err("scout device register failed");
                return err;
        }

        return 0;
}

static void scout_exit(void)
{
        misc_deregister(&scout_dev);
        printk(KERN_INFO "Scout module unregistered");
}

module_init(scout_init);
module_exit(scout_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Emil Tullstedt <emiltu@kth.se>");
MODULE_DESCRIPTION("The official /dev/scout kernel module!");
