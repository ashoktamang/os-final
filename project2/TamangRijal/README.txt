How to Apply Patches before testing the Project:

a. Download the linux 3.16.0 image from (https://www.kernel.org/pub/linux/kernel/v3.x/linux-3.16.tar.gz)
b. Extract the tar file using:
    tar -xzvf linux-3.16.tar.gz
   This directory will be the image where the patch will be applied.
c. cd /path/to/linux-3.16
d. patch -p4 < /path/to/patchProject2.diff

The sources in the /path/to/linux-3.16 directory should now be transformed into your experimental sources. 

How to Run Part 1:

a. Copy "pid_info" and "pid_vminfo" directory to /path/to/linux-3.16
b. Go to the directory pid_info and run the command: `make`
c. sudo insmod pid_info.ko p_id=<ProcessID> to load the module.
d. sudo rmmod pid_info to unload the module.

a. Go to the directory pid_vminfo and run the command: `make`
b. sudo insmod pid_vminfo.ko to load the module.
c. cat /proc/pid_vminfo for log output.
d. sudo rmmod pid_vminfo to unload the module.

How to Run Part 2:
a. Create C file to call the syscalls.
b. Syscall Number is as follows: 
    System call 1: sys_my_set_state: 354
    System call 2: sys my_get_and_sum: 355
    System call 3: sys_my_get_string: 366
c. Run `dmesg` to see the log output

Notes:

System call 3 has been implemented but while calling it in the test program, the program crashes.

Acknowledgements:
a. Got assistance from Saurav Keshari Aryal to fix bugs while adding syscalls in syscall tables.