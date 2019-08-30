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
#ifndef STDERR_H
#define STDERR_H

#include <stdint.h>

/**
 * Aborts the program, and prints the address of the last function call (which should be `call abort`)
 */
extern void abort();

/**
 * Terminate the program with a beautiful message
 */
extern void terminate(char const *message, uint16_t const error_code);

/**
 * Asserts an expression is true, else aborts the program
 */
#ifdef NDEBUG
#   define assert(e) ;
#else
    void assert(int e);
#endif

#endif