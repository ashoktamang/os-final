/*
    Authors: Ashok Tamang and Anuraag Rijal
    Description: An executable program that list all the attributes of given file/directory name.
*/
#include <stdio.h>
#include <stdlib.h> /* for atoi() */
#include <string.h>

int main(int argc,char *argv[]) {
    char *attribute;

    if (argc < 3) {
        printf("Usage: %s 'AttrName=AttrValue' filename\n", argv[0]);
        printf("Additional file names can passed as argument, followed by a space.\n");
        
        return 1;
    }
    attribute = argv[1];
    printf("Attrube: %s\n", attribute);
    char *attrName, *attrValue;
    
    
    char *delimeter = "=";


    // Token will point to "attrName".
    attrName = strtok(attribute, delimeter);
    printf("name: %s\n", attrName);

    // Token will point to "attrValue".
    attrValue = strtok(NULL, delimeter);
    printf("value: %s\n", attrValue);
   

    for (int i = 2; i < argc; i++) {
        char *filename = argv[i];
        long int sys_ret = syscall(354, filename, attrName, attrValue, strlen(attrValue));
        if (sys_ret != 0)
        {
            printf("Attribute couldn't be set for %s.\n", filename);
        }
    }
    return 0;
}