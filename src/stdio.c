#include "stdio.h"

unsigned char makeColor(Color const foreground, Color const background)
{
    return (background << 4) + foreground;
}

void puts_(short const color, char const* text)
{
    unsigned short* videoBuffer = (unsigned short*) 0xb8000;
    
    for (int i = 0; text[i] != '\0'; ++i)
    {
        *videoBuffer++ = (color << 8) + text[i];
    }
}

void clear_()
{
    unsigned short* videoBuffer = (unsigned short*) 0xb8000;
    
    for (int i = 0; i < 80*25; ++i)
    {
        *videoBuffer++ = (makeColor(WHITE, BLACK) << 8) + ' ';
    }
}
