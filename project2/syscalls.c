 /*
  Author: Ashok Tamang and Anuraag Rijal
  The syscall implementation of project 2, part 2.
 */
 #include <linux/errno.h>
 #include <linux/kernel.h>
 #include <linux/slab.h>
 #include <linux/spinlock.h>
 #include <linux/uaccess.h>
 #include <linux/linkage.h>
 
 unsigned int my_accumulator;
 char* my_string;
 
 /* Symbols to be extracted for logging purposes; Kernel variables */
 EXPORT_SYMBOL(my_string);
 EXPORT_SYMBOL(my_accumulator);
 
 /* Initialize the kernel variables with user inputs */
 asmlinkage long sys_my_set_state(char *the_string, int accumulator) {
 	if (accumulator < 0) {
 		return -EINVAL;
 	}
 	my_accumulator = accumulator;
 
 	printk("\nUser input for accumulator: %d\n", accumulator);
 	printk("So, the value of my_accumulator is set as: %d\n\n", my_accumulator);
 
 	unsigned int len_string = strlen_user(the_string);
 
 	if (my_string)
 		kfree(my_string);
 	if ((my_string = (char *) kmalloc(len_string, GFP_KERNEL)) == NULL) {
 		return -EFAULT;
 	}
 	/* Verify copy */
 	if (copy_from_user(my_string, the_string, len_string)) {
 		kfree(my_string);
 		return -EFAULT;
 	}
 
 	/* Log output of kernel variables if sucess */
 	printk("Copy successful.\n");
 	printk("User input for the_string: %s\n", the_string);
 	printk("\n So, the value of my_string is set as: %s\n", my_string);
 	
 	return 0;	
 }
 
 /* Increment the value of my_accumulator by user input, inc_value. */
 asmlinkage long sys_my_get_and_sum(int *my_value, int inc_value) {
 	if (inc_value < 0) {
 		return -EINVAL;
 	}
 	printk("\nCurrent value of my_accumulator: %d\n", my_accumulator);
 	printk("inc_value: %d\n\n", inc_value);
 	if ((my_accumulator + inc_value) >= INT_MAX) {
 		return -EOVERFLOW;
 	}
 	*my_value = my_accumulator + inc_value;
 	my_accumulator = my_accumulator + inc_value;
 	printk("New incremented my_accumulator: %d\n", my_accumulator);
 
 	/* Verify copy */
 	if (copy_from_user(my_value, &my_accumulator, sizeof(int))) {
 		return -EFAULT;
 	}
 	printk(KERN_INFO "Currently my_value pointer points to a value of %d\n", my_value);
 
 	return 0;
 
 }
 
 /* Compare my_string and user input string, and store the string with minimum length. */
 asmlinkage long sys_my_get_string(char *buf, int bsize) {
 	unsigned int copylen, slen;
 	char* temp_str;
 	
 	if(my_string == NULL) {
 		return -ENODATA;
 	}
 	slen = strlen(my_string);
 	copylen = min(slen, bsize - 1);
 	if (copylen == slen) {
 		if ((temp_str = (char *) kmalloc(sizeof(slen), GFP_KERNEL)) != NULL) {
 			return -EFAULT;
 		}
 		strcpy(temp_str, my_string);
 		if (copy_to_user(buf, temp_str, slen)) {
 			return -EFAULT;
 		}
 	} else {
 		if ((temp_str = (char *) kmalloc(sizeof(bsize), GFP_KERNEL)) != NULL) {
 			return -EFAULT;
 		}
 		strcpy(temp_str, my_string);
 		if (copy_to_user(buf, my_string, bsize)) {
 			return -EFAULT;
 		}
 	}
 	printk(KERN_INFO "\n mystring: %s\n", my_string);
 	printk(KERN_INFO "\n buffer size: %d\n", copylen);
 	printk(KERN_INFO "\n buffer value: %s\n", buf);
 	return 0;
 }
