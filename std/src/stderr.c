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

#include <std/stderr.h>
#include <stdint.h>
#include <std/io/console.h>
#include <std/stdstr.h>
#include <std/stdmem.h>

static void halt()
{
    asm inline(
        "halt1: cli ; hlt\n"
        "jmp halt1\n"
    );
}

/* extern */ void abort()
{
    uint32_t address = (uint32_t) __builtin_return_address(0);
    char buf[9];
    memset(buf, 0, 9);

    putsN("\e\x04"
         , "Calling abort() on address 0x"
         , uint_to_str(address, buf, 16)
         , ".\n"
         , 0);

    halt();
}

/* extern */ void terminate(char const* message, uint16_t const error_code)
{
    uint32_t address = (uint32_t)__builtin_return_address(0);
    char buf[9];
    size_t const height = getDisplaySizeY(), width = getDisplaySizeX();
    memset(buf, 0, 9);
    puts("\e\x40");

        moveCursorAt(0, 0);
    for (size_t i = 0; i < height * width; ++i)
        puts(" ");

    char const* title = " Oneiric ";
    unsigned short beginning_title = width / 2 - (strlen(title) / 2 + 1);

    moveCursorAt(beginning_title, 8);
    putsN("\e\x74", title, 0);

    puts("\e\x47");
    moveCursorAt(0, height - 10);
    puts("    * What happened: the kernel had to stop its execution because a fatal error occurred!\n");
    putsN("    * Reason: ", message, "\n", 0);
    putsN("    * At: 0x", uint_to_str(address, buf, 16), "\n\n", 0);
    putsN("    * Error code: 0x", int_to_str(error_code, buf, 16), 0);

    halt();
}

#ifndef DNDEBUG
    void assert(int e)
    {
        if (!e)
        {
            uint32_t address = (uint32_t)__builtin_return_address(0);
            char buf[9];
            memset(buf, 0, 9);

            putsN("\e\x04"
                 , "Assertion failed at 0x"
                 , uint_to_str(address, buf, 16)
                 , ".\n"
                 , 0);

            abort();
        }
    }
#endif