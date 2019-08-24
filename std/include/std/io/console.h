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
#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdint.h>
#include <stdarg.h>

/**
 * Just put a string with a color on the screen, nothing fancy
 * Also handles tabulations, new lines, and output scrolling
 */
extern void puts(char const* text);
/**
 * Puts an undefined number N of strings on the screen, all of the same color
 * Be aware that the arguments list must end with `0`
 */
extern void putsN(char const* first,...);
extern void vputsN(va_list args);
/**
 * Basically resets the video buffer to its original state
 */
extern void clear();

extern void moveCursorUp();
extern void moveCursorDown();
extern void moveCursorLeft();
extern void moveCursorRight();
extern void moveCursorAt(uint16_t x, uint16_t y);
extern uint16_t getCursorLine();
extern uint16_t getCursorColumn();

extern void initDisplayBuffer(uint32_t address);
extern void initDisplay(uint16_t sizeX, uint16_t sizeY);
extern uint16_t getDisplaySizeX();
extern uint16_t getDisplaySizeY();

#endif
