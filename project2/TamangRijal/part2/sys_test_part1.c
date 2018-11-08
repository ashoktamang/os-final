/*
 * Test the stephen syscall (#329)
 */
#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

/*
 * Put your syscall number here.
 */
#define SYS_my_set_state 545
#define SYS_my_get_and_sum 546
#define SYS_my_get_string 547

int main(int argc, char **argv)
{
  if (argc <= 1) {
    printf("Must provide a string to give to system call.\n");
    return -1;
  }
  char *my_string = argv[1];
  int accumulator = 0;
  if (sscanf (argv[2], "%i", &accumulator) != 1) {
    fprintf(stderr, "error - not an integer");
  }
  printf("Making system call with \"%s\".\n", my_string);
  printf("Accumulator should be %d.\n", accumulator);
  long res = syscall(SYS_my_set_state, my_string);
  printf("System call returned %ld.\n", res);
  return res;
}
