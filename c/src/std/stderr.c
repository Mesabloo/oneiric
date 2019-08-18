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
#include <std/stddef.h>
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
    size_t const height = 25, width = 80;
    memset(buf, 0, 9);
    
    moveCursorAt(0, 0);
    for (size_t i = 0; i < height * width; ++i)
        puts("\e\x40 ");

    moveCursorAt(40 - 4, 8);
    puts("\e\x74 Oneiric ");

    moveCursorAt(4, 15);
    putsN("\e\x47", "* What happened: the kernel had to stop its execution because a fatal error occurred!", 0);
    moveCursorAt(4, getCursorLine() + 1);
    putsN("\e\x47", "* Reason: ", message, 0);
    moveCursorAt(4, getCursorLine() + 1);
    putsN("\e\x47", "* At: 0x", uint_to_str(address, buf, 16), 0);
    moveCursorAt(4, getCursorLine() + 2);
    putsN("\e\x47", "* Error code: 0x", int_to_str(error_code, buf, 16), 0);

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