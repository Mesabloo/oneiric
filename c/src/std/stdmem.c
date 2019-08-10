#include <std/stdmem.h>

void memcpy_(void* src, unsigned int const size, void* dest)
{    
    asm inline("rep movsd" // movsd copies from %(e)si to %(e)di
        :
        : "S" (src),
          "D" (dest),
          "c" (size) /* `rep` uses %ecx */
    );
}
