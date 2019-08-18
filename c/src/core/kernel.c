#include <core/kernel.h>
#include <std/io/console.h>
#include <std/stddef.h>
#include <std/stderr.h>
#include <core/multiboot.h>
#include <std/stdstr.h>

static logLine = 0;

/* extern */ void kMain(multiboot_info_t* mb_info)
{
    assert(mb_info);
    if (mb_info->flags & (1 << 12) && mb_info->framebuffer_type == MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT)
        initDisplay(mb_info->framebuffer_width, mb_info->framebuffer_height);

    clear();

    if(mb_info->flags & (1 << 12) && mb_info->framebuffer_type == MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT)
    {
        moveCursorAt(0, logLine++);
        char buf[5], buf1[5];
        memset(buf, 0, 5); memset(buf1, 0, 5);

        putsN("\e\x8C[\e\x01 INFO \e\x8C] Initialized display with size "
             , uint_to_str(mb_info->framebuffer_width, buf, 10)
             , "x", uint_to_str(mb_info->framebuffer_height, buf1, 10)
             , 0);
    }

    moveCursorAt(getDisplaySizeX() - 19, getDisplaySizeY() - 1);
    puts("\e\x8C Booting kernel... ");

    asm inline(
        "movl $500000000000, %ecx\n"
        ".L5: loop .L5\n"
    );
    moveCursorAt(0, logLine++);
    puts("\e\x07[\e\x0A  OK  \e\x07] Nothing to activate right now... (will come soon)\n");

    moveCursorAt(getDisplaySizeX() - 19, getDisplaySizeY() - 1);
    puts("\e\x8A Booted kernel!    ");

    asm inline(
        "movl $1000000000000, %ecx\n"
        ".L6: loop .L6\n"
    );

    //terminate("This kernel is not fully implemented yet!", 0x0);

    asm inline(
        "wait: jmp wait\n"
    );
}