#include <core/kernel.h>
#include <std/io/console.h>
#include <stdint.h>
#include <std/stderr.h>
#include <core/multiboot.h>
#include <std/stdstr.h>
#include <std/stdmem.h>

/* extern */ void kMain(multiboot_info_t* mb_info)
{
    assert(mb_info);
    if (mb_info->flags & (1 << 12) && mb_info->framebuffer_type == MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT)
        initDisplay(mb_info->framebuffer_width, mb_info->framebuffer_height);

    clear();

    moveCursorAt(getDisplaySizeX() - 19, getDisplaySizeY() - 1);
    puts("\e\x74 Booting kernel... ");

    {
        moveCursorAt(0, 0);
        char sizeXBuf[23], sizeYBuf[23];
        memset(sizeXBuf, 0, 23); memset(sizeYBuf, 0, 23);

        putsN("\e\x07[\e\x01 INFO \e\x07] Screen size: "
             , uint_to_str(getDisplaySizeX(), sizeXBuf, 10)
             , "x"
             , uint_to_str(getDisplaySizeY(), sizeYBuf, 10)
             , "\n"
             , 0);
    }

    asm inline(
        "movl $1783793664, %ecx\n"
        "L7: loop L7\n"
    );

    if (mb_info->flags & (1 << 6))
    {
        // print the memory map information
        char buf[9], buf2[11];
        memset(buf, 0, 9); memset(buf2, 0, 11);

        putsN("\e\x07[\e\x01 INFO \e\x07] Memory map: address=0x"
             , uint_to_str(mb_info->mmap_addr, buf, 16)
             , "\tlength="
             , int_to_str(mb_info->mmap_length, buf2, 10)
             , ":\n"
             , 0);

        char addr_buf[18], len_buf[23], size_buf[23];
        multiboot_memory_map_t* mmap_entry = (multiboot_memory_map_t*) mb_info->mmap_addr;
        for(; (uint32_t) mmap_entry + sizeof(multiboot_memory_map_t) <= (uint32_t) mb_info->mmap_addr + mb_info->mmap_length
            ; mmap_entry = (multiboot_memory_map_t*) ((uint32_t) mmap_entry + mmap_entry->size + sizeof(mmap_entry->size)))
        {
            memset(addr_buf, 0, 18); memset(len_buf, 0, 23); memset(size_buf, 0, 23);

            putsN("\e\x07[\e\x01 INFO \e\x07] \t* addr=0x"
                 , uint_to_str(mmap_entry->addr, addr_buf, 16)
                 , "\t len="
                 , uint_to_str(mmap_entry->len, len_buf, 10)
                 , " B\t type="
                 , 0);

            switch (mmap_entry->type)
            {
                case MULTIBOOT_MEMORY_ACPI_RECLAIMABLE:
                    puts("ACPI"); break;
                case MULTIBOOT_MEMORY_AVAILABLE:
                    puts("AVAILABLE"); break;
                case MULTIBOOT_MEMORY_BADRAM:
                    puts("BAD"); break;
                case MULTIBOOT_MEMORY_NVS:
                    puts("NVS"); break;
                case MULTIBOOT_MEMORY_RESERVED:
                    puts("RESERVED"); break;
                default:
                    puts("UNKNOWN"); break;
            }

            putsN("\tsize=", int_to_str(mmap_entry->size, size_buf, 10), "\n", 0);
        }
    }

    asm inline(
        "movl $1783793664, %ecx\n"
        "L5: loop L5\n"
    );

    puts("\e\x07         Paging available memory...\n");
    putsN("\e\x07[\e\x04", "FAILED\e\x07] Paging not yet implemented.\n", 0);

    puts("\e\x07         Activating memory allocator...\n");

    // activate the memory allocator here

    putsN("\e\x07[\e\x04", "FAILED\e\x07] Memory allocator not yet implemented.\n", 0);

    //puts("\e\x07[\e\x0A  OK  \e\x07] Nothing to activate right now... (will come soon)\n");

    moveCursorAt(getDisplaySizeX() - 19, getDisplaySizeY() - 1);
    puts("\e\x72 Booted kernel!    ");

    asm inline(
        "movl $3567587328, %ecx\n"
        "L6: loop L6\n"
    );

    //terminate("This kernel is not fully implemented yet!", 0x0);

    asm inline(
        "wait: jmp wait\n"
    );
}