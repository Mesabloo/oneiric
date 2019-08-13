#pragma once
#ifndef STDSTR_H
#define STDSTR_H

#include <std/stddef.h>

/**
 * A converter from int to string
 */
char const* int_to_str(int32_t value, short base);
/**
 * In simple words: just reverses a string
 */
void reverse(char* str, size_t length);

#endif