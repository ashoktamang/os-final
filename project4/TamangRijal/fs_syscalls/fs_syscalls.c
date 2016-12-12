/* 
    Authors: Ashok Tamang and Anuraag Rijal
    Description: Source file for syscalls pertaining to Filesystem Attributes    
*/
#include <linux/errno.h>
#include <linux/fcntl.h> // Header file for open and writing into Filesystem
#include <linux/kernel.h>
#include <linux/linkage.h>
#include <libgen.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
//Open dir
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>


long sys_set_attribute(char *filename, char *attrname, char *attrvalue, int size) {
    // Check if attrname is empty
    unsigned int len_attrname = strlen_user(attrname);
    if ((attrname = (char *) kmalloc(len_attrname, GFP_KERNEL)) == NULL)
        return -EFAULT;
    // Verify that attrvalue is not an empty string. 'size' is the length of 'attrvalue'.
    if (size < 0) 
        return -EINVAL;
    
    /*
     Check if the attribute directory exists. Attribute directory is named as: .filename_attr
     If no such directory exists, then create a new directory.
    */
    char *attr_dir_name = "." + filename + "_attr/";
    char *attr_dir_path = dirname(filename);
    if (opendir(attr_dir_path) == NULL) {
        mkdir(attr_dir_path, S_IRUSR | S_IWUSR | S_IXUSR);
    }
    char *attrname_path = attr_dir_path + attrname;
    int filedesc = open(attrname_path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    write(filedesc, attrvalue, size);
    printk("Attribute is set.\n");

    return 0;
}

long sys_get_attribute(char *filename, char *attrname, char *buf, int bufsize) {
    struct stat sb;
    /*
     Check if the attribute directory exists. Attribute directory is named as: .filename_attr
     If no such directory exists, return -1.
    */
    char *attr_dir_name = "." + filename + "_attr/";
    char *attr_dir_path = dirname(filename);
    if (opendir(attr_dir_path) == NULL) {
        return -1;
    }
    char *attrname_path = attr_dir_path + attrname;

    if (stat(attrname_path, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    unsigned int size = sb.st_size;
    if (bufsize < size)
    {
        return -1;
    }

    int filedesc = open(attrname_path, O_RDWR);

    return read(filedesc, buf, bufsize);
}

long sys_get_attribute_names(char *filename, char *buf, int bufsize) {
    DIR *attr_dir;
    struct dirent *dp;
    char *attr_dir_name = "." + filename + "_attr/";
    attr_dir = opendir(attr_dir_name);
    while(dp = readdir(attr_dir) != NULL && strlen(buf) < bufsize) {
        if ( !strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..") )
        {
            // do nothing (straight logic)
            continue;
        } else {
            buf += dp -> d_name + ":";
        }
    }
    closedir(attr_dir);
    return 0;
}

long sys_remove_attribute(char *filename, char *attrname) {
    char *attr_dir_name = "." + filename + "_attr/";
    char *attr_dir_path = dirname(filename);

    char *attrname_path = attr_dir_path + attrname;

    int status_remove_dir = rmdir(attr_dir_name);

    if (status_remove_dir == 0)
    {
        printk("\nNo other attribues are set. Removed attr_dir_name");
        return 0;
    } else
    {
        return remove(attrname_path);
    }

}