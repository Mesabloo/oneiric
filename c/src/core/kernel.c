#include <core/kernel.h>
#include <std/stdio.h>
#include <core/paging.h>
#include <core/multiboot.h>

/* extern */ int kMain(uint32_t magicNumber, MultibootInfo* kernelInfoPtr, MultibootTable* tablePtr)
{
    // do some stuff here
    clear();

    unsigned char const whiteOnBlack = makeColor(WHITE, BLACK),
                        greenOnBlack = makeColor(GREEN, BLACK),
                        redOnBlack = makeColor(RED, BLACK),
                        blueOnBlack = makeColor(BLUE, BLACK),
                        magentaOnBlack = makeColor(MAGENTA, BLACK);

    if (!magicNumber)
        return 1 << 1;
    if (!tablePtr)
        return 1 << 1;
    if (!kernelInfoPtr)
        return 1 << 1;

    if (magicNumber != 0x2badb002)
        return 1 << 2;

    puts(whiteOnBlack, "[      ] Booting kernel...\n");

    // load everything there

    // enable paging
    puts(whiteOnBlack, "[      ] Enabling paging...\n");
    enablePaging(kernelInfoPtr->load_addr, kernelInfoPtr->load_end_addr);
    puts(whiteOnBlack, "[");
    puts(greenOnBlack, "  OK  ");
    puts(whiteOnBlack, "] Enabled paging.\n");

    // load more stuff here

    puts(whiteOnBlack, "[");
    puts(greenOnBlack, "  OK  ");
    puts(whiteOnBlack, "] Booted kernel!\n");

    puts(whiteOnBlack, "\nWelcome to ");
    puts(magentaOnBlack, "Oneiric");
    puts(whiteOnBlack, "!\n\n");

    while (1)
        ; // never ending loop, cause we don't want the kernel to just stop

    return 1 << 0;
}
