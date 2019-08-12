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