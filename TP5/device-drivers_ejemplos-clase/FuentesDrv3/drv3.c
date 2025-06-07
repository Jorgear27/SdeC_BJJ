// Bibliografía a consultar:
// https://www.kernel.org/doc/htmldocs/kernel-api/index.html

// Las llamadas a operaciones comunes de archivos también se aplican para cualquier dispositivo.
// En definitiva un archivo es un archivo y para Linus casi todo es un archivo, desde la perspectiva del usuario.
// La diferencia radica en el espacio del kernel, donde el VFS decodifica el tipo de archivo 
// y transfiere las operaciones de archivo al canal apropiado, ya sea al módulo del sistema de 
// archivos en el caso de un archivo o directorio normal, o al "device driver" correspondiente 
// en el caso de un "device file". Nos interesa este último caso.

// Para que VFS pase operaciones del "device file" al "device driver", debe estar informado al respecto.
// Esto es registrar en el VFS las operaciones del "device file" vinculadas al "device driver".
// Esto implica dos pasos:
// PRIMERO: Declarar y completar una estructura "file_operations" con las operaciones de archivo deseadas
// (my_open, my_close, my_read, my_write, ...) e inicializar la estructura del "char device" (struct cdev c_dev)
// utilizando cdev_init().
// SEGUNDO: Entregar esta estructura al VFS usando la llamada cdev_add().
// Luego habrá que completar las operaciones (my_open, my_close, my_read, my_write, ...).

// ¿ Cómo voy a chequear el funcionamiento del device driver ?
// $echo "Hola driver..." > /dev/SdeC_drv3
// $dmesg
// $cat /dev/SdeC_drv3
// $dmesg

#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>

static dev_t first; 		// Vble global para device number "first"
static struct cdev c_dev; 	// Global variable for the character device structure
static struct class *cl; 	// Global variable for the device class

static int my_open(struct inode *i, struct file *f)
{
    printk(KERN_INFO "Driver3_SdeC: open()\n");
    return 0;
}
static int my_close(struct inode *i, struct file *f)
{
    printk(KERN_INFO "Driver3_SdeC: close()\n");
    return 0;
}
static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Driver3_SdeC: read()\n");
    return 0;
}
static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Driver3_SdeC: write()\n");
    return len;
}

static struct file_operations pugs_fops =
{
    // Dentro de file_operations defino las funciones que voy a implementar..!!

    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_close,
    .read = my_read,
    .write = my_write
};

static int __init drv3_init(void) /* Constructor */
{
    int ret;
    struct device *dev_ret;

    printk(KERN_INFO "SdeC_drv3 Registrado exitosamente..!!\n");
    
    // alloc_chrdev_region calcula (¿ obtiene ?) dinámicamente un MAJOR libre (se devuelve en 
    // first) y registra 1 número de device MINOR a partir de <el mayor libre, primer menor>, 
    // con el nombre SdeC_drv3. Si devuelve 0, está todo bien..!!

    if ((ret = alloc_chrdev_region(&first, 0, 1, "SdeC_drv3")) < 0)
    {
        return ret;
    }

    // En versiones del kernel 2.4 y anteriores, la creación automática de "device files" fue
    // la realizaba el mismo kernel, llamando a las API apropiadas de devfs. 
    // A medida que el kernel evolucionó, los desarrolladores del kernel se dieron cuenta de que
    // los "device files" son más una cuestión de espacio de usuario y, por lo tanto, como política, 
    // solo los usuarios deberían tratarlo, no el kernel. 
    // Con esta idea, ahora el kernel ofrece información sobre los dispositivos, organizado por clases
    // en la carpeta /sys/class. En particular para char device driver, está /sys/class/chardrv.
    // Luego, el espacio de usuario necesita interpretar y tomar una acción apropiada. 
    // En la mayoría de los desktop Linux, el demonio udev recoge esa información y, en consecuencia, 
    // crea los archivos del dispositivo.
    // Luego, con class_create se crea un puntero a un objeto de la clase device particular (chardrv).


    if (IS_ERR(cl = class_create(THIS_MODULE, "chardrv")))
    {
        unregister_chrdev_region(first, 1);
        return PTR_ERR(cl);
    }

    // Ese puntero "cl" será utilizado en la llamada a device_create, junto a los valores de
    // MAJOR y MINOR contenidos en "first" y el nombre que se le dará a esta nueva entrada.

    if (IS_ERR(dev_ret = device_create(cl, NULL, first, NULL, "SdeC_drv3")))
    {
        class_destroy(cl);
        unregister_chrdev_region(first, 1);
        return PTR_ERR(dev_ret);
    }

    // Lo que queda es inicializar cdev, recordando la estructura file_operations, preparándola para 
    // agregar al sistema con cdev_add.

    cdev_init(&c_dev, &pugs_fops);
    if ((ret = cdev_add(&c_dev, first, 1)) < 0)
    {
        device_destroy(cl, first);
        class_destroy(cl);
        unregister_chrdev_region(first, 1);
        return ret;
    }
    return 0;
}

static void __exit drv3_exit(void) /* Destructor */
{
    cdev_del(&c_dev);
    device_destroy(cl, first);
    class_destroy(cl);
    unregister_chrdev_region(first, 1);
    printk(KERN_INFO "SdeC_drv3 dice Adios mundo cruel..!!\n");
}

module_init(drv3_init);
module_exit(drv3_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cátedra Sistemas de Computación");
MODULE_DESCRIPTION("Nuestro tercer driver de SdeC");