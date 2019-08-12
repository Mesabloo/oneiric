#pragma once
#ifndef STDMEM_H
#define STDMEM_H

#include <std/stddef.h>

/**
 * A simple handler for memory copying
 */
void memcpy(void* source, unsigned int const size, void* destination);

/**
 * A simple handler for memory setting
 */
void memset(void* source, unsigned char value, size_t n);

#endif
