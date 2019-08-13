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
#ifndef PAGING_H
#define PAGING_H

#include <std/stddef.h>

void enablePaging(uint32_t loadBeginAddr, uint32_t loadEndAddr);
void loadPageDirectory(uint32_t* pageDir);

/**
 * ? Below are marked the physical addresses, their mapped (virtual) addresses.
 * 
 * Memory address paging reference:
 * 
 * ? Conventional memory
 * *    [0x00000000;loadBeginAddr - 1] ⇒ [0x00000000;loadBeginAddr - 1]   (identity mapped)   
 * 
 * ? Kernel memory
 * *    [loadBeginAddr;loadEndAddr] ⇒ [loadBeginAddr;loadEndAddr &~ 4096] (identity mapped)
 * 
 * ? Software memory
 * *    [(loadEndAddr &~ 4096) + 1;0xffffffff] ⇒ [loadEndAddr;0xffffffff] (identity mapped)
 */

#endif