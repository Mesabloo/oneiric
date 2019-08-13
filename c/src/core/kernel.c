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

#include <core/kernel.h>
#include <std/stdio.h>
#include <core/memory/paging.h>
#include <core/multiboot.h>
#include <std/stdstr.h>
#include <std/stderr.h>

/* extern */ int kMain(uint32_t magicNumber, MultibootInfo* kernelInfoPtr, MultibootTable* tablePtr)
{
    // do some stuff here
    clear();

    unsigned char const whiteOnBlack = makeColor(WHITE, BLACK),
                        greenOnBlack = makeColor(GREEN, BLACK),
                        redOnBlack = makeColor(RED, BLACK),
                        blueOnBlack = makeColor(BLUE, BLACK),
                        magentaOnBlack = makeColor(MAGENTA, BLACK);

    assert(magicNumber);
    assert(tablePtr);
    assert(kernelInfoPtr);

    assert(magicNumber == 0x2badb002);

    puts(whiteOnBlack, "[      ] Booting kernel...\n");

    // load everything there

    // enable paging
    puts(whiteOnBlack, "[      ] Enabling paging...\n");

    puts(blueOnBlack, "\tKernel info: load_begin=0x");
    puts(blueOnBlack, int_to_str(kernelInfoPtr->load_addr, 16));
    puts(blueOnBlack, " ; load_end=0x");
    puts(blueOnBlack, int_to_str(kernelInfoPtr->load_end_addr, 16));
    puts(blueOnBlack, "\n\n");

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
