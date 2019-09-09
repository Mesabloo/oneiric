#include <core/memory/pager.h>
#include <std/io/console.h>
#include <std/stdstr.h>
#include <std/stdmem.h>
#include <utils/logs.h>
#include <std/stdmem.h>

static uint32_t __attribute__((aligned(4096))) pageDir[1024];
static uint32_t __attribute__((aligned(4096))) pageTables[1024 * 1024];

#define DEFAULT_FLAGS 0b10 // supervisor flag, read/write flag

int enable_paging(uint32_t mmap_addr, uint32_t mmap_length)
{
#ifdef ENABLE_LOGGING
    {
        char buf[9], buf2[11];
        memset(buf, 0, 9); memset(buf2, 0, 11);

        info("Memory map: address=0x"
             , uint_to_str(mmap_addr, buf, 16)
             , "\tlength="
             , int_to_str(mmap_length, buf2, 10)
             , ":\n"
             , 0);

        char addr_buf[18], len_buf[23], size_buf[23];
        multiboot_memory_map_t* mmap_entry = (multiboot_memory_map_t*) mmap_addr;
        for(; (uint32_t) mmap_entry + sizeof(multiboot_memory_map_t) <= (uint32_t) mmap_addr + mmap_length
            ; mmap_entry = (multiboot_memory_map_t*) ((uint32_t) mmap_entry + mmap_entry->size + sizeof(mmap_entry->size)))
        {
            memset(addr_buf, 0, 18); memset(len_buf, 0, 23); memset(size_buf, 0, 23);

            info("\t* addr=0x"
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
#endif

    // asm inline(
    //     "movl $1783793664, %ecx\n"
    //     "L5: loop L5\n"
    // );

    // just initialize all the page entries to the default flags

    uint16_t i = 0;
    for (; i < 1024; ++i)
        for (uint16_t j = 0; j < 1024; ++j)
            pageTables[i * 1024 + j] = (0 << 12) | DEFAULT_FLAGS;

    // first let's map our conventional memory
    // ! We need to get it from the `mmap_addr` provided in the function parameters
    // ! And we also need to make sure that we don't remap the physical memory < 0x800000

    uint32_t paging_memory = 0x0;
    multiboot_memory_map_t* mmap_entry = (multiboot_memory_map_t*) mmap_addr;
    for(; (uint32_t) mmap_entry + sizeof(multiboot_memory_map_t) <= (uint32_t) mmap_addr + mmap_length
        ; mmap_entry = (multiboot_memory_map_t*) ((uint32_t) mmap_entry + mmap_entry->size + sizeof(mmap_entry->size)))
    {
        if (mmap_entry->type != MULTIBOOT_MEMORY_AVAILABLE)
            continue;

        uint32_t beginning = mmap_entry->addr;
        uint32_t const ending = beginning + mmap_entry->len;

        for (; beginning < ending; beginning += 4096)
        {
            if (beginning < 0x800000)
                continue;
            
#ifdef ENABLE_LOGGING
            char buf[9], buf2[9];
            memset(buf, 0, 9);
            memset(buf2, 0, 9);
            uint_to_str(paging_memory, buf, 16);
            uint_to_str(beginning, buf2, 16);

            info("Mapped 0x", buf2, " to 0x", buf, "\n", 0);
#endif

            pageTables[paging_memory / 4096] = (beginning << 12) | 0b11;
            paging_memory += 4096;
        }
    }

    // then let's remap the kernel (0x0 -> 0x800000 ==> 0xc0000000 -> 0xc0800000) 
    // ! The kernel must be mapped at the index 768 in the page directory
    // ! And will contain only 2 page tables (8 MiB of memory), since giving more is useless for now

    for (i = 768; i < 770; ++i)
        for (uint16_t j = 0; j < 1024; ++j)
            pageTables[i * 1024 + j] = (((i - 768) * 1024 + j) << 12) | 0b11;


    // next, we register our tables in the page directory
    uint16_t ii = 0;
    for (; ii < 768; ++ii)
        pageDir[ii] = (uint32_t) pageTables[ii * 1024] | DEFAULT_FLAGS;

    for (; ii < 770; ++ii)
        pageDir[ii] = (uint32_t) pageTables[ii * 1024] | 0b11;

    for (; ii < 1024; ++ii)
        pageDir[ii] = (uint32_t) pageTables[ii * 1024] | DEFAULT_FLAGS;

    // and finally we activate the paging with the new page directory

    asm inline(
        "movl %%cr0, %%edx\n"
        "orl $0x80010000, %%edx\n"
        "movl %%cr3, %%ebx\n"
        "movl %%edx, %%cr0\n" :: "b" (&pageDir)
    );

    return 0;
}

uint32_t* get_page_directory()
{
    return pageDir;
}

#undef DEFAULT_FLAGS