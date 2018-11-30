
#ifdef _DEBUG

#include <vcruntime_string.h>

void* memcpy(void * dst , void const * src , size_t size)
{
    char * to = (char *)dst;
    const char * from = (const char *)src;
    int count = (int)size;
    while (count--)
        to[count] = from[count];

    return to;
}
#endif 
