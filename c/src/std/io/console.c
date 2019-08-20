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

#include <std/io/console.h>
#include <stdint.h>
#include <stddef.h>
#include <std/stdmem.h>
#include <stdarg.h>
#include <std/stderr.h>

static unsigned short* textBuffer = (unsigned short*) 0xb8000; // graphical buffer is at 0x0xa0000
static unsigned int textBufferIndex = 0; // offset in text memory
static uint16_t displaySizeX = 80, displaySizeY = 25; // default values

/* extern */ void initDisplayBuffer(uint32_t address)
{
    textBuffer = (unsigned short*) address;
}

/* extern */ void initDisplay(uint16_t sizeX, uint16_t sizeY)
{
    displaySizeX = sizeX;
    displaySizeY = sizeY;
}

/* extern */ uint16_t getDisplaySizeX()
{
    return displaySizeX;
}

/* extern */ uint16_t getDisplaySizeY()
{
    return displaySizeY;
}

static unsigned char color = '\x07';
/* extern */ void puts(char const* text)
{
    for (unsigned int i = 0; text[i]; ++i)
    {
        switch (text[i]) {
            case '\n': 
            {
                unsigned short actualLine = textBufferIndex++ / displaySizeX;
                
                if (actualLine == displaySizeY - 1) // if we are on the last line
                {
                    memcpy(textBuffer + displaySizeX, displaySizeX * (displaySizeY - 1) * 2, textBuffer);
                    /**
                     * Copy the whole screen (except the first line)
                     * to the first line. That way, all lines are
                     * moved on line upwards
                     */
                    for (unsigned int j = 0; j < displaySizeX; ++j)
                        textBuffer[displaySizeX * (displaySizeY - 1) + j] = 0x0f00; // reset the last line, we don't want some old trash
                    textBufferIndex = displaySizeX * (displaySizeY - 1); // move the index to the last line
                }
                else
                {
                    while (textBufferIndex / displaySizeX == actualLine)
                        textBufferIndex++; // Move the cursor until we are on a new line (at the beginning)
                }
                break;
            }
            case '\t':
            {
                for (int j = 0; j < 4; j++)
                {
                    textBuffer[textBufferIndex++] = (color << 8) + ' ';
                } // output 4 spaces instead of a tabulation, because they are evil
                break;
            }
            case '\e':
                color = text[++i];
                break;
            case '\0':
                break;
            default:
            {
                if (textBufferIndex == displaySizeX * displaySizeY)
                {
                    memcpy(textBuffer + displaySizeX, displaySizeX * (displaySizeY - 1) * 2, textBuffer);
                    /**
                     * Copy the whole screen (except the first line)
                     * to the first line. That way, all lines are
                     * moved on line upwards
                     */
                    for (unsigned int j = 0; j < displaySizeX; ++j)
                        textBuffer[displaySizeX * (displaySizeY - 1) + j] = 0x0f00; // reset the last line, we don't want some old trash
                    textBufferIndex = displaySizeX * (displaySizeY - 1);            // move the index to the last line
                }

                textBuffer[textBufferIndex++] = (color << 8) + text[i];
                break;
            }
        }
        
    }
}

/* extern */ void putsN(char const* first, ...)
{
    va_list args;
    char const* arg = first;

    va_start(args, first);
    while (arg != 0)
    {
        puts(arg);
        arg = va_arg(args, char const *);
    }
    va_end(args);
}

/* extern */ void clear()
{
    textBufferIndex = 0;
    memset(textBuffer, 0, displaySizeX * displaySizeY * 2);
}

/* extern */ void moveCursorLeft()
{
    if (textBufferIndex % displaySizeX != 0)
        textBufferIndex--;
}

/* extern */ void moveCursorRight()
{
    if (textBufferIndex % displaySizeX != displaySizeX - 1)
        textBufferIndex++;
}

/* extern */ void moveCursorUp()
{
    if (textBufferIndex / displaySizeX != 0)
        textBufferIndex -= displaySizeX;
}

/* extern */ void moveCursorDown()
{
    if (textBufferIndex / displaySizeX != displaySizeY - 1)
        textBufferIndex += displaySizeX;
}

/* extern */ void moveCursorAt(uint16_t x, uint16_t y)
{
    assert(x < displaySizeX);
    assert(y < displaySizeY);

    textBufferIndex = y * displaySizeX + x;
}

/* extern */ uint16_t getCursorLine()
{
    return textBufferIndex / displaySizeX;
}

/* extern */ uint16_t getCursorColumn()
{
    return textBufferIndex % displaySizeX;
}