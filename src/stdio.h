#pragma once
#ifndef STDIO_H
#define STDIO_H

typedef enum 
{
    BLACK = 0x0,
    BLUE = 0x1,
    GREEN = 0x2,
    CYAN = 0x3,
    RED = 0x4,
    MAGENTA = 0x5,
    BROWN = 0x6,
    LGRAY = 0x7,
    DGRAY = 0x8,
    LBLUE = 0x9,
    LGREEN = 0xA,
    LCYAN = 0xB,
    LRED = 0xC,
    LMAGENTA = 0xD,
    YELLOW = 0xE,
    WHITE = 0xF
} Color;

unsigned char makeColor(Color const foreground, Color const background);
void puts_(short const color, char const* text);
void clear_();

#endif
