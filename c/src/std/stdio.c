#include <std/stdio.h>
#include <std/stdint.h>
#include <std/stdmem.h>

static unsigned short* const textBuffer = (unsigned short*) 0xb8000; // graphical buffer is at 0xa0000
static unsigned int textBufferIndex = 0; // offset in text memory

unsigned char makeColor(Color const foreground, Color const background)
{
    return (background << 4) + foreground;
}

void puts_(unsigned char const color, char const* text)
{
    for (unsigned int i = 0; text[i]; ++i)
    {
        switch (text[i]) {
            case '\n': 
            {
                unsigned short actualLine = textBufferIndex++ / 80;
                
                if (actualLine == 24) // if we are on the last line
                {
                    memcpy_(textBuffer + 80, 80*24, textBuffer);
                    /**
                     * Copy the whole screen (except the first line)
                     * to the first line. That way, all lines are
                     * moved on line upwards
                     */
                    for (unsigned int j = 0; j < 80; ++j)
                        textBuffer[80*24 + j] = 0x0f00; // reset the last line, we don't want some old trash
                    textBufferIndex = 80*24; // move the index to the last line
                }
                else
                {
                    while (textBufferIndex / 80 == actualLine)
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
            default:
                textBuffer[textBufferIndex++] = (color << 8) + text[i];
        }
        
    }
}

void clear_()
{
    for (textBufferIndex = 80*25; textBufferIndex > 0; --textBufferIndex)
    {
        textBuffer[textBufferIndex] = (makeColor(WHITE, BLACK) << 8) + '\0';
    }
}
