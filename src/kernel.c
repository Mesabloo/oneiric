#include "kernel.h"
#include "stdio.h"

/* extern */ int kMain(void* bootData) {
    // do some stuff here
    clear_();
    puts_(makeColor(GREEN, BLACK), "Kernel started!");
    
    while (1); // never ending loop, cause we don't want the kernel to just stop
    
    return 1;
}
