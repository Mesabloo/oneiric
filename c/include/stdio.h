#pragma once
#ifndef STDIO_H
#define STDIO_H

/**
 * Represents all the color codes available for printing
 */
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

/**
 * A simple way to convert two colors into a special code
 */
unsigned char makeColor(Color const foreground, Color const background);
/**
 * Just put a string with a color on the screen, nothing fancy
 * Also handles tabulations, new lines, and output scrolling
 */
void puts_(unsigned char const color, char const* text);
/**
 * Basically resets the video buffer to its original state
 */
void clear_();

#endif
