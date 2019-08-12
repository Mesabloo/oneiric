#include <core/kernel.h>
#include <std/stdio.h>
#include <core/paging.h>
#include <core/multiboot.h>

/* extern */ int kMain(MultibootHeader* bootData)
{
    // do some stuff here
    clear();

    unsigned char const whiteOnBlack = makeColor(WHITE, BLACK),
                        greenOnBlack = makeColor(GREEN, BLACK),
                        redOnBlack = makeColor(RED, BLACK);

    puts(whiteOnBlack, "[      ] Booting kernel...\n");

    // load everything there

    // enable paging
    puts(whiteOnBlack, "[      ] Enabling paging...\n");
    enablePaging(bootData->load_addr, bootData->load_end_addr);
    puts(whiteOnBlack, "[");
    puts(greenOnBlack, "  OK  ");
    puts(whiteOnBlack, "] Enabled paging.\n");

    // for now let's just wait a bit
    for (unsigned long i = 0; i < 1000000000L; ++i)
        ;

    puts(whiteOnBlack, "[");
    puts(greenOnBlack, "  OK  ");
    puts(whiteOnBlack, "] Booted kernel!\n");

    while (1)
        ; // never ending loop, cause we don't want the kernel to just stop

    return 1;
}
