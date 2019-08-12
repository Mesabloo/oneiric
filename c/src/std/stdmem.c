#include <std/stdmem.h>

void memcpy(void* src, unsigned int const size, void* dest)
{    
    asm inline("rep movsd\n" // movsd copies from %(e)si to %(e)di
        :
        : "S" (src),
          "D" (dest),
          "c" (size) /* `rep` uses %(e)cx */
    );
}

void memset(void* src, unsigned char value, size_t n)
{
    asm inline(
        "rep stosb"
        :: "D" (src),
           "a" (value),
           "c" (n) /* `rep` uses %(e)cx */
    );
}