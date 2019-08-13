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
extern void puts(unsigned char const color, char const* text);
/**
 * Basically resets the video buffer to its original state
 */
extern void clear();

#endif
