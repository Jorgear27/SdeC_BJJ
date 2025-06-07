#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>

static int __init drv1_init(void) /* Constructor */
{
    printk(KERN_INFO "SdeC: drv1 Registrado exitosamente..!!\n");

    return 0;
}

static void __exit drv1_exit(void) /* Destructor */
{
    printk(KERN_INFO "SdeC: drv1 dice Adios mundo cruel..!!\n");
}

module_init(drv1_init);
module_exit(drv1_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anil Kumar Pugalia <email@sarika-pugs.com>");
MODULE_DESCRIPTION("Nuestro primer driver de SdeC");
