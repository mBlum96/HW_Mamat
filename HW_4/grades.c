/* chat.c: Example char device module.
 *
 */
/* Kernel Programming */
#define MODULE
#define LINUX
#define __KERNEL__

#include <linux/kernel.h>  	
#include <linux/module.h>
#include <linux/fs.h>       		
#include <asm/uaccess.h>
#include <linux/errno.h>  
#include <asm/segment.h>
#include <asm/current.h>

#include "pubsub.h"

#define MY_DEVICE "pubsub"
#define MAX_CHARACTERS 1000
#define MAX_PROCESSES 512

MODULE_AUTHOR("Anonymous");
MODULE_LICENSE("GPL");

/* globals */
int my_major = 0; /* will hold the major # of my device driver */
int buffers_counter = 0;

typedef struct myDevice{
    char *data;
    int minor;
    int write_p;
    int users_count;
    struct Process** pid_array;
    int reach_EOF_count;
    struct myDevice *next;
    struct myDevice *prev;
}myDevice;

typedef struct Process{
    myDevice *device;
    int pid;
    int read_p;
    int permission;
}Process;

myDevice *head_device;
myDevice *tail_device;

struct file_operations my_fops = {
    .open = my_open,
    .release = my_release,
    .read = my_read,
    .ioctl = my_ioctl,
};

int find_available_id(Process** pid_array){
	int i=0;
    for (i; i < MAX_PROCESSES; ++i) {
        if(pid_array[i] != NULL) return i;
    }
    //not supposed to reach here
    return 0;
}

void init_array(Process** pid_array){
	int i=0;
    for (i; i < MAX_PROCESSES; ++i) {
        pid_array[i] = NULL;
    }
}

void init_all_read_p(Process **pid_array){
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        if(pid_array[i] != NULL){
            pid_array[i]->read_p = 0;
        }
    }
}
int init_module(void)
{
    // This function is called when inserting the module using insmod

    my_major = register_chrdev(my_major, MY_DEVICE, &my_fops);

    if (my_major < 0)
    {
	printk(KERN_WARNING "can't get dynamic major\n");
	return my_major;
    }

    head_device = NULL;
    tail_device = NULL;

    return 0;
}


void cleanup_module(void)
{
    // This function is called when removing the module using rmmod

    unregister_chrdev(my_major, MY_DEVICE);

    //
    // do clean_up();
    //
    return;
}


int my_open(struct inode *inode, struct file *filp)
{
    printk("my_open is called!\n");

    /////////////////// Allocating New Proccess ///////////////////

    //allocating new process
    Process *new_process = kmalloc(sizeof(Process),GFP_KERNEL);
    //checking ig allocating succeed
    if(!new_process){
        printk("device cannot be opened! kmalloc was failed\n");
        return -ENOMEM;
    }

    ///////////////// Matching Process With Buffer ///////////////

    int curr_minor = MINOR(inode->i_rdev);
    myDevice *curr_device = head_device;

    //checking if the buffer is already exist
    while(curr_device){
        if(curr_device->minor == curr_minor){
            printk("Device is found! Device's minor : %d\n", curr_minor);

            new_process->device = curr_device;
            new_process->pid = find_available_id(curr_device->pid_array);
            new_process->read_p = 0;
            new_process->permission = TYPE_NONE;
            filp->private_data = new_process;

            curr_device->users_count++;
            curr_device->pid_array[new_process->pid] = new_process;

            return 0;
        }
        curr_device = curr_device->next;
    }

    //if reached here the buffer is not exist
    printk("Device was not found! Setting new device... Device's minor : %d\n", curr_minor);

    curr_device = kmalloc(sizeof(myDevice),GFP_KERNEL);
    //checking if allocating succeed
    if(!curr_device){
        printk("device cannot be opened! kmalloc was failed\n");
        return -ENOMEM;
    }
    curr_device->data = kmalloc(sizeof(char)*(MAX_CHARACTERS),GFP_KERNEL);
    //checking if allocating succeed
    if(!curr_device->data){
        printk("device cannot be opened! kmalloc was failed\n");
        kfree(curr_device);
        return -ENOMEM;
    }
    curr_device->minor = curr_minor;
    curr_device->write_p = 0;
    curr_device->users_count = 1;

    curr_device->pid_array = kmalloc(sizeof(*Process)*MAX_PROCESSES,GFP_KERNEL);
    if(!curr_device->pid_array){
            printk("device cannot be opened! kmalloc was failed\n");
            kfree(curr_device->data);
            kfree(curr_device);
            return -ENOMEM;
    }
    init_array(curr_device->pid_array);
    curr_device->pid_array[0] = new_process;

    curr_device->reach_EOF_count = 0;
    curr_device->next = NULL;
    curr_device->prev = NULL;

    new_process->device = curr_device;
    new_process->read_p = 0;
    new_process->permission = TYPE_NONE;

    filp->private_data = new_process;

    if(head_device == NULL){
        head_device = curr_device;
    }
    else if(tail_device == NULL){
        head_device->next = curr_device;
        curr_device->prev = head_device;
        tail_device = curr_device;
    }
    else{
        tail_device->next = curr_device;
        tail_device = curr_device;
    }
    buffers_counter++;
    return 0;
}


int my_release(struct inode *inode, struct file *filp) {
    // handle file closing
    Process *curr_process = filp->private_data;

    curr_process->device->pid_array[curr_process->pid] = NULL;
    curr_process->device->users_count--;



    // last process is closed, we need to remove this buffer
    if (curr_process->device->users_count == 0) {
        kfree(curr_process->device->data);
        kfree(curr_process->device->pid_array);

        buffers_counter--;
        // last buffer is closed
        if(buffers_counter == 0){
            kfree(curr_process->device);
            cleanup_module();
        }
        // remove buffer from global buffer list
        else {
            if (curr_process->device == head_device) {
                head_device = head_device->next;
            } else if (curr_process->device == tail_device) {
                tail_device = tail_device->prev;
            } else {
                curr_process->device->prev->next = curr_process->device->next;
            }
            kfree(curr_process->device);
        }
    }
    kfree(curr_process);

    return 0;
}

ssize_t my_write(struct file *filp, char *buf, size_t count, loff_t *f_pos){

    printk("my_write is called!\n");

    if(buf == NULL){
        printk("Invalid input! Check your input!\n");
        return -EFAULT;
    }

    if(count > MAX_CHARACTERS){
        printk("It's more than 1000! Check your input!\n");
        return -EINVAL;
    }

    Process *curr_process = filp->private_data;
    myDevice *curr_device = curr_process->device;
    int written_bytes = 0;

    if(curr_process->permission != TYPE_PUB){
        printk("Wrong type!\n");
        return -EACCES;
    }

    if(curr_device->write_p + count > MAX_CHARACTERS){
        printk("There is not enough space! Check your input!\n");
        return -EAGAIN;
    }

    for (int i = 0; i < count; ++i) {
        //not sure if the check is necessary
        if(&buf[i] == NULL){
            printk("Buffer reading error! Check your input!\n");
            return -EBADF;
        }
        curr_device->data[curr_device->write_p] = buf[i];
        curr_device->write_p++;
        written_bytes++;
    }

    return written_bytes;
}

ssize_t my_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
    //
    // Do read operation.
    printk("my_read is called!\n");

    if(buf == NULL){
        printk("Invalid buffer! Check your input!\n");
        return -EFAULT;
    }

    //there are more valid input checks?

    Process *curr_process = filp->private_data;
    myDevice *curr_device = curr_process->device;

    // Wrong type
    if(curr_process->permission != TYPE_SUB){
        printk("Wrong type!\n");
        return -EACCES;
    }

    // No data to read
    if(curr_process->read_p == curr_device->write_p){
        printk("No data to read!");
        return -EAGAIN;
    }

    int read_bytes = 0;

    for (int i = 0; i < count && curr_process->read_p < curr_device->write_p; ++i) {
        buf[i] = curr_device[curr_process->read_p];
        curr_process->read_p++;
        read_bytes++;
    }

    if(curr_process->read_p == MAX_CHARACTERS){
        curr_device->reach_EOF_count++;
    }


    // If all processes reached EOF, we will reset the buffer
    if(curr_device->reach_EOF_count == curr_device->users_count){
        curr_device->write_p = 0;
        init_all_read_p(curr_device->pid_array);
        curr_device->reach_EOF_count = 0;
    }
    
    // Return number of bytes read.
    return read_bytes;
}



int my_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{

    switch(cmd)
    {
    case SET_TYPE:
        if(filp->private_data->permission != TYPE_NONE){
            printk("Error! Type is already set!\n");
            return -EPERM;
        }

        else{
            if(cmd == TYPE_PUB||cmd == TYPE_SUB){
                printk("Changed permission type");
                filp->private_data->permission=cmd;
            }
            else{
                return -EINVAL;
            }
        }

	break;
    case GET_TYPE:
	return (Process*)(filp->private_data)->permission;
	break;
    default:
	return -ENOTTY;
    }

    return 0;
}
