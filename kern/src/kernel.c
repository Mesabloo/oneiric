#include <core/kernel.h>
#include <std/io/console.h>
#include <stdint.h>
#include <std/stderr.h>
#include <core/multiboot.h>
#include <std/stdstr.h>
#include <std/stdmem.h>
#include <core/memory/pager.h>
#include <utils/logs.h>
#include <std/io/cursor.h>

/* extern */ void kMain(multiboot_info_t* mb_info)
{
    disable_cursor();

    assert(mb_info);
    if (mb_info->flags & (1 << 12) && mb_info->framebuffer_type == MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT)
        initDisplay(mb_info->framebuffer_width, mb_info->framebuffer_height);

    { // Draw two colored lines at the top and the bottom:
        char const *header = "Oneiric v0.0.1 - Copyright (c) 2019 Mesabloo";
        unsigned short const beginning_header = getDisplaySizeX() / 2 - (strlen(header) / 2 + 1);
        unsigned short i = 0;
        puts("\e\x70");
        for (; i < beginning_header; ++i)
            puts(" ");
        puts(header);
        for (i += strlen(header); i < getDisplaySizeX(); ++i)
            puts(" ");

        moveCursorAt(0, getDisplaySizeY() - 1);
        char const* footer = "Status: booting...";
        unsigned short const beginning_footer = getDisplaySizeX() / 2 - (strlen(footer) / 2 + 1);
        puts("\e\x70");
        for (i = 0; i < beginning_footer; ++i)
            puts(" ");
        puts(footer);
        for (i += strlen(footer); i < getDisplaySizeX(); ++i)
            puts(" ");

        initDisplayBuffer(0xc00b8000 + getDisplaySizeX() * 2);
        initDisplay(getDisplaySizeX(), getDisplaySizeY() - 2);
    }

    clear();

#ifdef ENABLE_LOGGING
    {
        moveCursorAt(0, 0);
        char sizeXBuf[23], sizeYBuf[23];
        memset(sizeXBuf, 0, 23); memset(sizeYBuf, 0, 23);

        info("Screen size: "
             , uint_to_str(getDisplaySizeX(), sizeXBuf, 10)
             , "x"
             , uint_to_str(getDisplaySizeY(), sizeYBuf, 10)
             , "\n"
             , 0);
    }
#endif

    // asm inline(
    //     "movl $1783793664, %ecx\n"
    //     "L5: loop L5\n"
    // );

    puts("\e\x07         Paging available memory...\n");

    if (mb_info->flags & (1 << 6))
    {
        if (!enable_paging(mb_info->mmap_addr, mb_info->mmap_length))
            ok("Paged available memory.\n", 0);
        else
            terminate("Failed paging the available memory. Halting system...", 0x1763);
    }
    else
        terminate("Could not page available memory. (unavailable memory map)", 0x1111);

    asm inline(
        "movl $1783793664, %ecx\n"
        "L5: loop L5\n"
    );

    puts("\e\x07         Activating memory allocator...\n");

    // activate the memory allocator here

    terminate("Memory allocator not yet implemented.", 0x5505);

    //puts("\e\x07[\e\x0A  OK  \e\x07] Nothing to activate right now... (will come soon)\n");

    {
        initDisplay(getDisplaySizeX(), getDisplaySizeY() + 1);
        moveCursorAt(0, getDisplaySizeY() - 1);
        char const *footer = "Status: booted!";
        unsigned short const beginning_footer = getDisplaySizeX() / 2 - (strlen(footer) / 2 + 1);
        puts("\e\x70");
        unsigned short i;
        for (i = 0; i < beginning_footer; ++i)
            puts(" ");
        puts(footer);
        for (i += strlen(footer); i < getDisplaySizeX(); ++i)
            puts(" ");

        initDisplay(getDisplaySizeX(), getDisplaySizeY() - 1);
    }

    asm inline(
        "movl $3567587328, %ecx\n"
        "L6: loop L6\n"
    );

    terminate("This kernel is not fully implemented yet!", 0x1234);

    asm inline(
        "wait: jmp wait\n"
    );
}