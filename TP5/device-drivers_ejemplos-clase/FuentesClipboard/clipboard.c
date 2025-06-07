#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/vmalloc.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Clipboard Kernel Module - FDI-UCM");
MODULE_AUTHOR("Juan Carlos Saez");

#define BUFFER_LENGTH       PAGE_SIZE

static struct proc_dir_entry *proc_entry;
static char *clipboard;                     // Space for the "clipboard"

static ssize_t clipboard_write(struct file *filp, const char __user *buf, size_t len, loff_t *off) {
  int available_space = BUFFER_LENGTH-1;
  
  if ((*off) > 0) /* The application can write in this entry just once !! */
    return 0;
  
  if (len > available_space) {
    printk(KERN_INFO "clipboard: not enough space!!\n");
    return -ENOSPC;
  }
  
  /* Transfiere data desde el espacio de usuario al espacio de kernel */
  /* echo un mensaje > /proc/clipboard                                */

  if (copy_from_user( &clipboard[0], buf, len ))  
    return -EFAULT;

  clipboard[len] = '\0';  /* Add the `\0' */  
  *off+=len;              /* Update the file pointer */
  
  return len;
}

static ssize_t clipboard_read(struct file *filp, char __user *buf, size_t len, loff_t *off) {
  
  int nr_bytes;
  
  if ((*off) > 0) /* Tell the application that there is nothing left to read */
      return 0;
    
  nr_bytes=strlen(clipboard);
    
  if (len<nr_bytes)
    return -ENOSPC;
  
    /* Transfiere data desde el espacio de kernel al espacio de usuario */ 
    /* cat /proc/clipboard                                              */

  if (copy_to_user(buf, clipboard, nr_bytes))
    return -EINVAL;
    
  (*off)+=len;  /* Update the file pointer */

  return nr_bytes; 
}

static const struct proc_ops proc_entry_fops = {
    .proc_read = clipboard_read,
    .proc_write = clipboard_write,    
};



int init_clipboard_module( void )
{
  int ret = 0;
  clipboard = (char *)vmalloc( BUFFER_LENGTH );

  if (!clipboard) {
    ret = -ENOMEM;
  } else {

    memset( clipboard, 0, BUFFER_LENGTH );
    proc_entry = proc_create( "clipboard", 0666, NULL, &proc_entry_fops);
    if (proc_entry == NULL) {
      ret = -ENOMEM;
      vfree(clipboard);
      printk(KERN_INFO "Clipboard: No puede crear entrada en /proc..!!\n");
    } else {
      printk(KERN_INFO "Clipboard: Modulo cargado..!!\n");
    }
  }
  return ret;
}


void exit_clipboard_module( void )
{
  remove_proc_entry("clipboard", NULL);
  vfree(clipboard);
  printk(KERN_INFO "Clipboard: Modulo descargado..!!\n");
}


module_init( init_clipboard_module );
module_exit( exit_clipboard_module );
