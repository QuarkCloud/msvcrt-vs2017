
#ifdef _DEBUG

#include <vcruntime_string.h>

extern "C" void* _cdecl memset(void* dst, int val, size_t size)
{
    char * start = (char *)dst;
    int count = (int)size;
    while (count--)
        *start++ = (char)val;
    return start;
}

#endif
