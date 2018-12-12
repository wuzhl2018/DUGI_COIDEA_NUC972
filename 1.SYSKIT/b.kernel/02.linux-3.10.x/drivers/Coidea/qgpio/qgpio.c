#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>


#include <linux/io.h>
#include <linux/errno.h>
#include <linux/acpi.h>
#include <linux/platform_device.h>
#include <mach/gpio.h>
#include <linux/clk.h>

#include <mach/map.h>
#include <mach/regs-gpio.h>
#include <mach/regs-clock.h>
#include <mach/regs-gcr.h>

#include <mach/irqs.h>


#include <linux/miscdevice.h>
#include <linux/platform_device.h>
#include <mach/regs-gpio.h>
#include <asm/io.h>
#include <linux/regulator/consumer.h>
#include <linux/delay.h>


void set_gpio_direction(unsigned int gpio_port,unsigned short reg);
int  get_gpio_direction(unsigned int gpio_port);
void set_gpio_odr(unsigned int gpio_port,unsigned short reg);
int  get_gpio_odr(unsigned int gpio_port);
int  get_gpio_idr(unsigned int gpio_port);


int QGPIO_MAJOR = 0;
int QGPIO_MINOR = 0;
int NUMBER_OF_DEVICES = 2;
 
struct class *my_class;
struct cdev cdev;
dev_t devno;
/*************************************************************************************/ 


static DEFINE_SPINLOCK(gpio_lock);


struct gpio_port {
	volatile unsigned int * dir;
	volatile unsigned int * out;
	volatile unsigned int * in;
};

const struct gpio_port port_class[] = {
	{(volatile unsigned int *)REG_GPIOA_DIR, (volatile unsigned int *)REG_GPIOA_DATAOUT,
	 (volatile unsigned int *)REG_GPIOA_DATAIN},
	{(volatile unsigned int *)REG_GPIOB_DIR, (volatile unsigned int *)REG_GPIOB_DATAOUT,
	 (volatile unsigned int *)REG_GPIOB_DATAIN},
	{(volatile unsigned int *)REG_GPIOC_DIR, (volatile unsigned int *)REG_GPIOC_DATAOUT,
	 (volatile unsigned int *)REG_GPIOC_DATAIN},
	{(volatile unsigned int *)REG_GPIOD_DIR, (volatile unsigned int *)REG_GPIOD_DATAOUT,
	 (volatile unsigned int *)REG_GPIOD_DATAIN},
	{(volatile unsigned int *)REG_GPIOE_DIR, (volatile unsigned int *)REG_GPIOE_DATAOUT,
	 (volatile unsigned int *)REG_GPIOE_DATAIN},
	{(volatile unsigned int *)REG_GPIOF_DIR, (volatile unsigned int *)REG_GPIOF_DATAOUT,
	 (volatile unsigned int *)REG_GPIOF_DATAIN},
	{(volatile unsigned int *)REG_GPIOG_DIR, (volatile unsigned int *)REG_GPIOG_DATAOUT,
	 (volatile unsigned int *)REG_GPIOG_DATAIN},
	{(volatile unsigned int *)REG_GPIOH_DIR, (volatile unsigned int *)REG_GPIOH_DATAOUT,
	 (volatile unsigned int *)REG_GPIOH_DATAIN},
	{(volatile unsigned int *)REG_GPIOI_DIR, (volatile unsigned int *)REG_GPIOI_DATAOUT,
	 (volatile unsigned int *)REG_GPIOI_DATAIN},
	{(volatile unsigned int *)REG_GPIOJ_DIR, (volatile unsigned int *)REG_GPIOJ_DATAOUT,
         (volatile unsigned int *)REG_GPIOJ_DATAIN},
	{},
};


void set_gpio_direction(unsigned int gpio_port,unsigned short reg)
{

	const struct gpio_port *port;

        port=&port_class[gpio_port];

	spin_lock(&gpio_lock);
	__raw_writel(reg, port->dir);
	spin_unlock(&gpio_lock);
	printk (KERN_INFO "gpio %d dir is set to %d\n",gpio_port,reg);

}
int get_gpio_direction(unsigned int gpio_port)
{
	int reg;
	const struct gpio_port *port;
        port=&port_class[gpio_port];
	reg=__raw_readl(port->dir);
	printk (KERN_INFO "gpio %d dir read \n",gpio_port);
	return reg;

}
void set_gpio_odr(unsigned int gpio_port,unsigned short reg)
{

	const struct gpio_port *port;

        port=&port_class[gpio_port];

	spin_lock(&gpio_lock);
	__raw_writel(reg, port->out);
	spin_unlock(&gpio_lock);
	printk (KERN_INFO "gpio %d odr is set to %d\n",gpio_port,reg);

}
int get_gpio_odr(unsigned int gpio_port)
{
	int reg;
	const struct gpio_port *port;
        port=&port_class[gpio_port];
	reg=__raw_readl(port->out);
	printk (KERN_INFO "gpio %d odr read \n",gpio_port);
	return reg;

}
int get_gpio_idr(unsigned int gpio_port)
{
	int reg;
	const struct gpio_port *port;
        port=&port_class[gpio_port];
	reg=__raw_readl(port->in);
	printk (KERN_INFO "gpio %d idr read \n",gpio_port);
	return reg;

}



int qgpio_open(struct inode *inode,struct file *filp)
{
	printk("leds Initialize\n");
	return nonseekable_open(inode,filp);
}

long qgpio_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
	
	unsigned short iocmd;
        unsigned short portx;

	iocmd=cmd/0xff;
	portx=cmd&0xff;
	printk("debug: port is %d reg is %d \n" , portx,iocmd);


	switch(iocmd)
	{
		case 1:
		  set_gpio_direction(portx,arg);
		break;
		case 2:
		  return get_gpio_direction(portx);
		break;
		case 3:
		  set_gpio_odr(portx,arg);
		break;
		case 4:
		  return get_gpio_odr(portx);
		break;
		case 5:
		  return get_gpio_idr(portx);
		break;
		default:
			return -EINVAL;
	}
	return 0;
}

struct file_operations qgpio_fops = {
	.owner = THIS_MODULE,
	.open 	= qgpio_open,
	.unlocked_ioctl = qgpio_ioctl,
};


/**************************************************************************************/
static int __init qgpio_init (void)
{
    int result;
    devno = MKDEV(QGPIO_MAJOR, QGPIO_MINOR);
    if (QGPIO_MAJOR)
        result = register_chrdev_region(devno, 2, "qgpio");
    else
    {
        result = alloc_chrdev_region(&devno, 0, 2, "qgpio");
        QGPIO_MAJOR = MAJOR(devno);
    }  
    printk("MAJOR IS %d\n",QGPIO_MAJOR);
    my_class = class_create(THIS_MODULE,"qgpio_class");  //类名为
    if(IS_ERR(my_class)) 
    {
        printk("Err: failed in creating class.\n");
        return -1; 
    }
    device_create(my_class,NULL,devno,NULL,"qgpio");      //设备名为
    if (result<0) 
    {
        printk (KERN_WARNING "hello: can't get major number %d\n", QGPIO_MAJOR);
        return result;
    }
 
    cdev_init(&cdev, &qgpio_fops);
    cdev.owner = THIS_MODULE;
    cdev_add(&cdev, devno, NUMBER_OF_DEVICES);
    printk (KERN_INFO "Qgpio driver Registered\n");

    return 0;
}
 
static void __exit qgpio_exit (void)
{
    cdev_del (&cdev);
    device_destroy(my_class, devno);         //delete device node under /dev//必须先删除设备，再删除class类
    class_destroy(my_class);                 //delete class created by us
    unregister_chrdev_region (devno,NUMBER_OF_DEVICES);
    printk (KERN_INFO "char driver cleaned up\n");
}
 
module_init (qgpio_init);
module_exit (qgpio_exit);
 
MODULE_LICENSE ("GPL");
