#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/utsname.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SdeC_BJJ");
MODULE_DESCRIPTION(
    "Módulo firmado del kernel que imprime el hostname del sistema");
MODULE_VERSION("0.1");

static int __init hello_init(void) {
  printk(KERN_INFO "Hola desde el kernel. Hostname: %s\n",
         init_uts_ns.name.nodename);
  return 0;
}

static void __exit hello_exit(void) {
  printk(KERN_INFO "Adiós desde el kernel.\n");
}

module_init(hello_init);
module_exit(hello_exit);
