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
 * Just put a string with a color on the screen, nothing fancy
 * Also handles tabulations, new lines, and output scrolling
 */
extern void puts(char const* text);
/**
 * Puts an undefined number N of strings on the screen, all of the same color
 * Be aware that the arguments list must end with `0`
 */
extern void putsN(char const* first,...);
/**
 * Basically resets the video buffer to its original state
 */
extern void clear();

#endif
