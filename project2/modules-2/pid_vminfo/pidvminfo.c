#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h> 
#include <linux/fs.h>
#include <linux/seq_file.h>
#include <linux/jiffies.h>


struct pid *pid_struct;
struct task_struct *task;
struct task_struct *parent_task;
struct task_struct *children_task;
struct list_head *list;
int current_pid;
int current_map_count;
unsigned long current_vm_start;
unsigned long current_vm_end;
//pgprot_t current_page_prot; 

//struct proc_dir_entry *proc_file_entry;

static int pidvminfo_show(struct seq_file *m, void *v){

	seq_printf(m, "Process ID: %d \n", current_pid);

	seq_printf(m, "Number of memory areas: %d \n", current_map_count);

	seq_printf(m, "VMA start, inclusive: %d \n", current_vm_start);

	seq_printf(m, "VMA end, exclusive: %d \n", current_vm_end);

	//seq_printf(m, "current_vm_page_prot: %d \n", current_vm_page_prot);
	return 0;
}


static int pidvminfo_open(struct inode *inode, struct file *file){
	return single_open(file, pidvminfo_show, NULL);
}

static const struct file_operations pidvminfo_fops = { 
	.owner = THIS_MODULE,
	.open = pidvminfo_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release, 
};

int P_module_init(void)
{
	proc_create("pidvminfo", 0, NULL, &pidvminfo_fops);
	current_pid = current->pid;
	current_map_count = current->mm->map_count;
	current_vm_start = current->mm->mmap->vm_start;
	current_vm_end = current->mm->mmap->vm_end;
	//current_vm_page_prot = current->mm->mmap->vm_page_prot;
	return 0;
}

void P_cleanup(void)
{
	remove_proc_entry("pidvminfo", NULL);
}

module_init( P_module_init );
module_exit( P_cleanup );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Process ID information");
MODULE_AUTHOR("Subhay Manandhar Shitosh Parajuli");
