#include <linux/erno.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/uaccess.h>

unsigned int my_accumulator;
char* my_string;


asmlinkage long cs401_set_attribute(char *filename, char *attrname, char *attrvalue, int size) {

    return 0;
}

asmlinkage long cs401_get_attribute(char *filename, char *attrname, char *buf, int bufsize) {
    return 0;
}

asmlinkage long cs401_get_attribute_names(char *filename, char *buf, int bufsize) {
    return 0;
}

asmlinkage long cs401_remove_attribute(char *filename, char *attrname) {
    return 0;
}