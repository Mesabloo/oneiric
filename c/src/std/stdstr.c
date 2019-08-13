#include <std/stdstr.h>
#include <std/stdmem.h>

static char buffer[33];
char const* int_to_str(int32_t value, short base)
{
    char* symbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    unsigned char isNegative = 0;
    size_t i = 0; // `i` should not get bigger than 32

    memset(buffer, 0, 33);

    if (base > 36)
        base = 36;

    if (value == 0)
        return "0";

    if (value < 0 && base == 10)
    {
        isNegative = 1;
        value = -value;
    }

    while (value != 0)
    {
        buffer[i++] = symbols[value % base];
        value /= base;
    }

    if (isNegative)
        buffer[i++] = '-';

    buffer[i] = 0;

    reverse(buffer, i);

    return buffer;
}

void reverse(char* str, size_t length)
{
    for (size_t start = 0, end = length - 1; start < end; start++, end--)
    {
        char tmp = *(str + end);
        *(str + end) = *(str + start);
        *(str + start) = tmp;
    }
}