#include <core/interrupts/handler.h>
#include <utils/logs.h>
#include <std/stdmem.h>
#include <std/stdstr.h>
#include <std/io/console.h>

/* extern */ void interrupt_handler(reg_dump_t dump)
{
    char buf[9], buf2[9];
    memset(buf, 0, 9);
    memset(buf2, 0, 9);
    warn("Received interrupt code: 0x", uint_to_str(dump.int_no, buf, 16), " at 0x", uint_to_str(dump.eip, buf2, 16), 0);
    if (!dump.err_code)
    {
        char buf3[23];
        memset(buf3, 0, 9);
        putsN(" with code ", uint_to_str(dump.err_code, buf3, 10), 0);
    }
    puts("\n");
}