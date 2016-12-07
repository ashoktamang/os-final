#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/kernel.h>

//i got error while trying to take Pid as a parameter of the funciton so I defined the global variable named pid to store the pid_number that we want to investigate 

int p_id=2;
struct pid *pid_struct;
struct task_struct *task;
struct task_struct *parent_task;
struct task_struct *children_task;
struct list_head *list;

//module_param(p_id, int, 0);
//funciton that gets called when module is loaded int he kernel 
int P_module_init(void)
{	
	//printk (KERN_INFO "CURRENT Memory state: %d \n", current->pid); 

	printk (KERN_INFO "Module loaded\n");	


	//gets the process id of the given process
	pid_struct = find_get_pid(p_id);


	// the task points to the task_struct of the process of p_id
	task = pid_task(pid_struct, PIDTYPE_PID);


	//printing the process ID
	printk (KERN_INFO "Process ID: %d \n", task->pid); 

	//printting the process name 
	printk (KERN_INFO "Process name: %s \n", task->comm); 
 
	//printing the UID
	printk (KERN_INFO "UID:  %d \n", task->cred->uid); 

	//printing the GID
	printk (KERN_INFO "GID: %d \n", pid_vnr(task_pgrp(task))); 


	//parent_task points to the paremt process of the process defined p_id
	parent_task = task->parent; 

	//prints the process id of the parent process	
	printk (KERN_INFO "Parent_Process ID: %d \n", parent_task->pid);

	//prints the name of thep parent process
	printk (KERN_INFO "Parent_process name: %s \n", parent_task->comm);

	//prints out all the childern process associated with the process p_id
	list_for_each(list, &task->children) 
	{
		children_task = list_entry(list, struct task_struct, children);
		printk (KERN_INFO "Children_Process ID: %d \n", children_task->pid);
		printk (KERN_INFO "Children_process name: %s \n", children_task->comm);	
	}

	return 0;
}


//function that gets called whtn module is unloaded 
void P_cleanup(void)
{
	printk (KERN_INFO "Module unloaded\n");
}

//defining the loading and unloading functions 
module_init( P_module_init );
module_exit( P_cleanup );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Process ID information");
MODULE_AUTHOR("Subhay Manandhar Shitosh Parajuli");
