#include <stdio.h>
#include <stdlib.h>

void main() {
    // Print Kernel version
    printf("\nKernel Version:\n");
    system("cat /proc/sys/kernel/osrelease");

    // Print CPU information
    printf("\nCPU Information:\n");
    system("cat /proc/cpuinfo");
    
}
