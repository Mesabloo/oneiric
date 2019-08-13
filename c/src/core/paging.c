/*
    Oneiric, a small kernel based on how dreams work
    Copyright (C) 2019  Mesabloo

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <core/paging.h>
#include <std/stdmem.h>

/**                                                            11 9 7 5 3 1
 *                                                              ↓ ↓ ↓ ↓ ↓ ↓
 */ static uint32_t pageDirectory[1024]
         __attribute__((aligned(4096))) = {0b0000000000000000000000000000010};
/**                                          ↑                 ↑   ↑ ↑ ↑ ↑ ↑
 *                                          32                12   8 6 4 2 0
 *  
 * ? In the following paragraph, `unset` refers to `== 0` and `set` refers to `== 1` 
 *
 * Each individual field is mapped as follows:
 * - bit #0 -> Presence flag, if unset, the table is not present
 * - bit #1 -> RW flag, if unset, the table is read only, else it has read/write access
 * - bit #2 -> Supervisor flag, if set, table can be accessed by anybody
 * - bit #3 -> Write-Through flag, if set, write-trough caching is enabled
 * - bit #4 -> Cache Disable flag, if set, table will not be cached
 * - bit #5 -> Accessed flag, if set, the page has been written to or read from
 * - bit #6 -> if PAT is supported, indicates the memory type, else must be 0
 * - bit #7 -> Page Size flag, if set, page pointed is 4 MiB in size, else it is 4 kiB
 * - bit #8 -> Ignored flag
 * - bits #9~11 -> Unused (may store specific data in it for the kernel)
 * - bits #12~32 -> Page table address, 4 kiB aligned
 */

/**                                                               11 9 7 5 3 1
 *                                                                 ↓ ↓ ↓ ↓ ↓ ↓
 */ static uint32_t nextTables[1024][1024]
        __attribute__((aligned(4096))); //= {{0b0000000000000000000000000000010}};
/**                                             ↑                 ↑   ↑ ↑ ↑ ↑ ↑
 *                                             32                12   8 6 4 2 0
 *
 * ? In the following paragraph, `unset` refers to `== 0` and `set` refers to `== 1` 
 *
 * Each individual field is mapped as follows:
 * - bit #0 -> @see pageDirectory
 * - bit #1 -> @see pageDirectory
 * - bit #2 -> @see pageDirectory
 * - bit #3 -> @see pageDirectory
 * - bit #4 -> @see pageDirectory#Cache Disable flag
 * - bit #5 -> @see pageDirectory
 * - bit #6 -> Dirty flag, if set, the page has been written to
 * - bit #7 -> @see pageDirectory
 * - bit #8 -> Global flag, if set, prevents the Translation Lookaside Buffer (TLB) from updating the address in its cache (when CR3 is reset)
 *             Note: The page global enable bit must be enabled in CR4
 * - bits #9~11 -> @see pageDirectory
 * - bits #12~32 -> 4 kiB chunk address, 4 kiB aligned
 */

void createPages(uint32_t kernBegin, uint32_t kernEnd)
{
#define DEFAULTFLAGS 0b11 // supervisor flag, read/write flag and present flag
    memset(nextTables, 0, 1024*1024*4);

    /**
     * Let's first map our conventional memory and our kernel
     */
    uint64_t i = 0;
    for (; i < (kernEnd & ~4096) / 4096; ++i)
        nextTables[i / 1024][i % 1024] = (i << 12) | DEFAULTFLAGS;

    /**
     * Let's then map the memory remaining unmapped
     */
    for (; i < 1024 * 1024 /* max entry number */; ++i)
        nextTables[i / 1024][i % 1024] = (i << 12) | DEFAULTFLAGS;

    /**
     * Now put the addresses of the page tables in the page directory
     */
    for (unsigned short j = 0; j < 1024; ++j)
        pageDirectory[j] = (uint32_t)nextTables[j] | DEFAULTFLAGS;

#undef DEFAULTFLAGS
}

void enablePaging(uint32_t loadBeginAddr, uint32_t loadEndAddr)
{
    createPages(loadBeginAddr, loadEndAddr);
    loadPageDirectory(pageDirectory);

    asm inline(
        "movl %cr0, %eax\n"
        "orl $0x80000000, %eax\n"
        "movl %eax, %cr0\n"
    );
}

void loadPageDirectory(uint32_t* pageDir)
{
    asm inline(
        "movl %0, %%cr3\n" :: "a"(pageDir)
    );
}