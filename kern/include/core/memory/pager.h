#pragma once
#ifndef PAGER_H
#define PAGER_H

#include <stdint.h>
#include <core/multiboot.h>

extern uint32_t* bootPD;
int enable_paging(uint32_t mmap_addr, uint32_t mmap_length);

#endif