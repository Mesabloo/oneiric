#include <core/kernel.h>
#include <std/stdio.h>

/* extern */ int kMain(void* bootData)
{
    // do some stuff here
    clear();
    
    unsigned char const whiteOnBlack = makeColor(WHITE, BLACK),
                        greenOnBlack = makeColor(GREEN, BLACK),
                        redOnBlack   = makeColor(RED,   BLACK);
                        
    puts(whiteOnBlack, "[      ] Booting kernel...\n");
    
    // load everything there
    // for now let's just wait a bit
    for (unsigned long i = 0; i < 1000000000L; ++i);
    
    puts(whiteOnBlack, "[");
    puts(greenOnBlack, "  OK  ");
    puts(whiteOnBlack, "] Booted kernel!\n");
    
    while (1); // never ending loop, cause we don't want the kernel to just stop
    
    return 1;
}
