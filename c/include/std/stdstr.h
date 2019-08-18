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
#ifndef STDSTR_H
#define STDSTR_H

#include <std/stddef.h>

/**
 * A converter from int to string
 * ? The buffer must be at least 33 char long to handle any value converted to any base (32 chars + the trailing 0)
 */
char const* int_to_str(int32_t value, char* buffer, short base);
/**
 * A converter from uint to string
 * ? The buffer must be at least 33 char long to handle any value converted to any base (32 chars + the trailing 0)
 */
char const* uint_to_str(uint32_t value, char* buffer, short base);
/**
 * In simple words: just reverses a string
 */
void reverse(char* str, size_t length);
/**
 * Gets the length of a string (its number of characters)
 */
size_t strlen(char const* str);

#endif