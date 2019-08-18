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
#include <std/stdio.h>
#include <std/stdstr.h>
#include <std/stdmem.h>

static void halt()
{
    asm inline(
        "cli ; hlt\n"
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

/* extern */ void terminate(char const* message)
{
    clear();

    uint32_t address = (uint32_t)__builtin_return_address(0);
    char buf[9];
    size_t const height = 25, width = 80;
    memset(buf, 0, 9);
    uint_to_str(address, buf, 16);

    assert(strlen(message) < width - 12);

    puts("\e\x40");
    for (size_t i = 0; i < 10; ++i)
        for (size_t j = 0; j < width; ++j)
            puts(" ");
    puts("                                    \e\x74 Oneiric \e\x40                                   ");
    for (size_t i = 0; i < 4; ++i)
        for (size_t j = 0; j < width; ++j)
            puts(" ");

    putsN("\e\x47  * What happened: The kernel terminated because of a fatal exception.            * Reason: ", message, 0);
    for (size_t i = 0; i < width - 12 - strlen(message); ++i)
        puts(" ");
    putsN("  * At: 0x", buf, 0);

    for (size_t i = 0; i < width - 10 - strlen(buf); ++i)
        puts(" ");
    for (size_t i = 0; i < 7; ++i)
        for (size_t j = 0; j < width; ++j)
            puts(" ");

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