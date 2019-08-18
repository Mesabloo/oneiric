#include <core/kernel.h>
#include <std/io/console.h>
#include <std/stddef.h>
#include <std/stderr.h>

/* extern */ void kMain()
{
    clear();
    moveCursorAt(80 - 19, 24);
    puts("\e\x8C Booting kernel... ");

    asm inline(
        "movl $500000000000, %ecx\n"
        ".L5: loop .L5\n"
    );
    moveCursorAt(0, 0);
    puts("\e\x07[\e\x0A  OK  \e\x07] Nothing to activate right now... (will come soon)\n");

    moveCursorAt(80 - 19, 24);
    puts("\e\x8A Booted kernel!    ");

    asm inline(
        "movl $1000000000000, %ecx\n"
        ".L6: loop .L6\n"
    );

    //terminate("This kernel is not fully implemented yet!", 0x0);

    while (1);
}