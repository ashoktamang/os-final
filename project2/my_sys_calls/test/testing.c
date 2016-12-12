/* Authors: Ashok Tamang and Anuraag Rijal
   Description: Test program for Project 2, part 2
*/
#include <sys/syscall.h>
#include <stdio.h>
#include <linux/kernel.h>
#include <unistd.h>

int main() {
	long int amma = syscall(354, "Hello", 5);
	int *value;
	char *buf = "hellorandi";
	long int bamma = syscall(355, value, 5);
	long int camma = syscall(356, buf, sizeof(int));

		
	printf("amma %ld\n", amma);
	printf("bmma %ld\n", bamma);
	printf("pointer value: %d", &value);
	
	printf("cmma %ld\n", camma);
	
	return 0;
}

