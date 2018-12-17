
#include <corecrt_internal.h>


int __cdecl memcmp(const void * pv1, const void * pv2, size_t cb) 
{
    if (!cb) {
        return 0;
        }

    while ( --cb && *(char *)pv1 == *(char *)pv2 ) {
        pv1 = (char *)pv1 + 1;
        pv2 = (char *)pv2 + 1;
        }

    return  *((unsigned char *)pv1) - *((unsigned char *)pv2);
}
	