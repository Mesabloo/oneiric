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

#include <std/stdstr.h>
#include <std/stdmem.h>

static char *symbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char const* int_to_str(int32_t value, char* buffer, short base)
{
    unsigned char isNegative = 0;
    size_t i = 0; // `i` should not get bigger than 32

    if (base > 36)
        base = 36;

    if (value == 0)
    {
        buffer[i++] = '0';
        buffer[i] = 0;
        return buffer;
    }

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

char const* uint_to_str(uint32_t value, char* buffer, short base)
{
    size_t i = 0; // `i` should not get bigger than 32

    if (base > 36)
        base = 36;

    if (value == 0)
    {
        buffer[i++] = '0';
        buffer[i] = 0;
        return buffer;
    }

    while (value != 0)
    {
        buffer[i++] = symbols[value % base];
        value /= base;
    }

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

size_t strlen(char const* str)
{
    size_t i = 0;
    for (; str[i]; ++i)
        ;
    return i;
}