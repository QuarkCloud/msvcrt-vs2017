
#include <vcruntime_string.h>

void*  memmove(void* dst, void const* src, size_t size)
{
    char * to = (char *)dst;
    const char * from = (const char *)src;
    int count = (int)size;

    if (to > from)
    {
        while (count--)
            to[count] = from[count];
    }
    else if (to < from)
    {
        int idx = 0;
        while (idx < count)
        {
            to[idx] = from[idx];
            ++idx;
        }
    }

    return to;
}
