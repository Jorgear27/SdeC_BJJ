#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "cdd_signals"
#define CLASS_NAME "cdd"
#define GPIO_SIGNAL_1 1
#define GPIO_SIGNAL_2 2
#define TIMER_INTERVAL (HZ) // 1 segundo

static dev_t dev_num;
static struct class *cdd_class = NULL;
static struct device *cdd_device = NULL;
static struct cdev cdd_cdev;

static struct timer_list my_timer;
static int selected_signal = 0;
static int last_value = 0;

static void read_signal(struct timer_list *t) {
  int gpio = (selected_signal == 0) ? GPIO_SIGNAL_1 : GPIO_SIGNAL_2;
  last_value = gpio_get_value(gpio);
  mod_timer(&my_timer, jiffies + TIMER_INTERVAL);
}

static ssize_t cdd_read(struct file *file, char __user *buf, size_t len,
                        loff_t *offset) {
  char msg[16];
  int n;

  if (*offset > 0)
    return 0;

  n = snprintf(msg, sizeof(msg), "%d\n", last_value);

  if (copy_to_user(buf, msg, n))
    return -EFAULT;

  *offset += n;
  return n;
}

static ssize_t cdd_write(struct file *file, const char __user *buf, size_t len,
                         loff_t *offset) {
  char kbuf[2];

  if (len < 1)
    return -EINVAL;

  if (copy_from_user(kbuf, buf, 1))
    return -EFAULT;

  kbuf[1] = '\0';
  selected_signal = (kbuf[0] == '1') ? 1 : 0;

  return 1;
}

static int cdd_open(struct inode *inode, struct file *file) { return 0; }

static int cdd_release(struct inode *inode, struct file *file) { return 0; }

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = cdd_read,
    .write = cdd_write,
    .open = cdd_open,
    .release = cdd_release,
};

static int __init cdd_init(void) {
  int ret;

  // Reserva número de dispositivo
  ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
  if (ret < 0) {
    printk(KERN_ERR "CDD: No se pudo asignar el major\n");
    return ret;
  }

  // Inicializa cdev
  cdev_init(&cdd_cdev, &fops);
  cdd_cdev.owner = THIS_MODULE;
  ret = cdev_add(&cdd_cdev, dev_num, 1);
  if (ret < 0) {
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_ERR "CDD: No se pudo agregar cdev\n");
    return ret;
  }

  // Crea clase y dispositivo
  cdd_class = class_create(THIS_MODULE, CLASS_NAME);
  if (IS_ERR(cdd_class)) {
    cdev_del(&cdd_cdev);
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_ERR "CDD: No se pudo crear la clase\n");
    return PTR_ERR(cdd_class);
  }

  cdd_device = device_create(cdd_class, NULL, dev_num, NULL, DEVICE_NAME);
  if (IS_ERR(cdd_device)) {
    class_destroy(cdd_class);
    cdev_del(&cdd_cdev);
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_ERR "CDD: No se pudo crear el dispositivo\n");
    return PTR_ERR(cdd_device);
  }

  // Inicializa GPIOs
  gpio_request(GPIO_SIGNAL_1, "SIG1");
  gpio_direction_input(GPIO_SIGNAL_1);
  gpio_request(GPIO_SIGNAL_2, "SIG2");
  gpio_direction_input(GPIO_SIGNAL_2);

  // Inicializa timer
  timer_setup(&my_timer, read_signal, 0);
  mod_timer(&my_timer, jiffies + TIMER_INTERVAL);

  printk(KERN_INFO "CDD: Módulo cargado. Major: %d\n", MAJOR(dev_num));
  return 0;
}

static void __exit cdd_exit(void) {
  del_timer_sync(&my_timer);
  gpio_free(GPIO_SIGNAL_1);
  gpio_free(GPIO_SIGNAL_2);

  device_destroy(cdd_class, dev_num);
  class_destroy(cdd_class);
  cdev_del(&cdd_cdev);
  unregister_chrdev_region(dev_num, 1);

  printk(KERN_INFO "CDD: Módulo descargado\n");
}

module_init(cdd_init);
module_exit(cdd_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jorge Arbach");
MODULE_DESCRIPTION("CDD Signals para Raspberry Pi");
