/*
    Authors: Ashok Tamang and Anuraag Rijal
    Description: An executable program that list all the attributes of given file/directory name.
*/

#include <stdio.h>
#include <stdlib.h> /* for atoi() */
#include <sys/syscall.h>
#include <unistd.h>
#include <libgen.h> //For basename()

int main(int argc,char *argv[]) {
    char *attrName;

    if (argc < 3) {
        printf("Usage: %s 'AttrName' filename\n", argv[0]);
        printf("Additional file names can passed as argument, followed by a space.\n");
        
        return 1;
    }
    
    attrName = argv[1];
    for (int i = 2; i < argc; i++) {
        char *filename = argv[i];
        char *attrValue;
        long int sys_ret = syscall(355, filename, attrName, attrValue, 100);
        if (sys_ret < 0)
        {
            printf("%s %s=NULL", basename(filename), attrName);
        } else
        {
            printf("%s %s=%s", basename(filename), attrName, attrValue);
        }
    }

    return 0;
}