#include <linux/erno.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/uaccess.h>

unsigned int my_accumulator;
char* my_string;

EXPORT_SYMBOL(my_string);
EXPORT_SYMBOL(my_accumulator);

asmlinkage long sys_my_set_state(char string, int accumulator) {
	if (accumulator < 0) {
		return -EINVAL;
	}
	my_accumulator = accumulator;

	printk("\nUser value received: %d\n", accumulator);
	printk("Value of my_accumulator set as: %d\n\n", my_accumulator);

	unsigned int len_string = strlen_user(string);

	if (my_string)
		kfree(my_string);
	if ((my_string = (char *) kmalloc(len_string, GFP_KERNEL)) == NULL) {
		return -EFAULT;
	}
	// Check if copy fails
	if (copy_from_user(my_string, string, len_string) {
		kfree(my_string);
		return -EFAUlT;
	}

	// Return success
	printk("Succeeded in copying.\n");
	printk("Received User String: %s\n", string);
	printk("\n Value of my_string set as: %s\n", my_string);
	
	return 0;	
}

asmlinkage long sys_my_get_and_sum(int *my_value, int inc_value) {
	if (inc_value < 0) {
		return -EINVAL;
	}
	printk("\nCurrent value of my_accumulator: %d\n", my_accumulator);
	printk("inc_value is given as: %d\n\n", inc_value);
	if ((my_accumulator + inc_value) >= INT_MAX) {
		return -EOVERFLOW;
	}
	*my_value = my_accumulator + inc_value;
	my_accumulator = my_accumulator + inc_value;
	printk("my_accumulator new value: %d\n", my_accumulator);

	// Check if copy fails
	if (copy_from_user(my_value, &my_accumulator, sizeof(int)) {
		return -EFAUlT;
	}
	printk(KERN_INFO "Currently my_value pointer points to a value of %d\n", my_value);

	return 0;

}

asmlinkage long sys_my_get_string(char *buf, int bsize) {
	unsigned int copylen, slen;
	char* temp_str;
	
	if(my_string == NULL) {
		return -ENODATA;
	}
	slen = strlen(my_string);
	copylen = min(slen, bsize - 1);
	if (copylen === slen) {
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
