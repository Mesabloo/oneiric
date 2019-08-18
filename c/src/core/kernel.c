#include <core/kernel.h>
#include <std/stdio.h>
#include <std/stddef.h>
#include <std/stderr.h>

/* extern */ void kMain()
{
    clear();
    puts("\e\x08         Booting kernel...\n");

    puts("[\e\x0A  OK  \e\x08] Booted kernel!\n");

    puts("\n\e\x08         Welcome to \e\x0DOneiric\e\x08!\n\n");

    asm inline(
        "movl $1000000000000, %ecx\n"
        ".L1: loop .L1\n"
    );

    terminate("This kernel is not fully implemented yet! lollollollollollollollollollollollollollollollollollollollollol");

    while (1);
}