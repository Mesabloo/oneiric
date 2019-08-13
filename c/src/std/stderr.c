#include <std/stderr.h>
#include <std/stddef.h>
#include <std/stdio.h>
#include <std/stdstr.h>

/* extern */ void abort()
{
    uint32_t address = (uint32_t) __builtin_return_address(0);

    unsigned char rB = makeColor(RED, BLACK);
    puts(rB, "Calling abort() on address 0x");
    puts(rB, int_to_str(address, 16));
    puts(rB, ".\n");

    asm inline(
        "cli\n"
        "hlt\n"
    );
}

#ifndef DNDEBUG
    void assert(int e)
    {
        if (!e)
        {
            uint32_t address = (uint32_t)__builtin_return_address(0);

            unsigned char rB = makeColor(RED, BLACK);
            puts(rB, "Assertion failed at 0x");
            puts(rB, int_to_str(address, 16));
            puts(rB, ".\n");

            abort();
        }
    }
#endif