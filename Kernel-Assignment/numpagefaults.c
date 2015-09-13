#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/mm.h> 
#include <linux/vm_event_item.h> 

static int pagefaults_show(struct seq_file *m, void *v)
{
	unsigned long temp[NR_VM_EVENT_ITEMS];
	all_vm_events(temp);
    	seq_printf(m, "%lu\n",temp[PGFAULT]);
    	return 0;
}
	
static int pagefaults_open(struct inode *inode, struct file *file)
{
    return single_open(file, pagefaults_show, NULL);
}

static const struct file_operations pagefaults_fops = {
    .owner      = THIS_MODULE,
    .open       = pagefaults_open,
    .read       = seq_read,
    .llseek     = seq_lseek,
    .release    = single_release,
};

static int __init pagefaults_init(void)
{
	proc_create("num_pagefaults", 0, NULL, &pagefaults_fops);
	return 0;
}

static void __exit pagefaults_cleanup(void)
{
    
    printk(KERN_INFO "Cleaning up module.\n");
}


module_init(pagefaults_init);
module_exit(pagefaults_cleanup);

MODULE_LICENSE("GPL");
