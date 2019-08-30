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

#pragma once
#ifndef STDMEM_H
#define STDMEM_H

#include <stddef.h>

/**
 * A simple handler for memory copying
 */
extern void memcpy(void* source, unsigned int const size, void* destination);

/**
 * A simple handler for memory setting
 */
extern void memset(void* source, unsigned char value, size_t n);

#endif
