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

#include <std/stdmem.h>

void memcpy(void* src, unsigned int const size, void* dest)
{    
    asm inline("rep movsb\n" // movsd copies from %(e)si to %(e)di
        :
        : "S" (src),
          "D" (dest),
          "c" (size) /* `rep` uses %(e)cx */
    );
}

void memset(void* src, unsigned char value, size_t n)
{
    asm inline(
        "rep stosb"
        :: "D" (src),
           "a" (value),
           "c" (n) /* `rep` uses %(e)cx */
    );
}