
#include <Windows.h>
#include "internal.h"

#define CHECK_FOR_LATE_COOKIE_INIT


#ifdef _WIN64
#define DEFAULT_SECURITY_COOKIE 0x00002B992DDFA232
#else  /* _WIN64 */
#define DEFAULT_SECURITY_COOKIE 0xBB40E64E
#endif  /* _WIN64 */

/*
 * The global security cookie.  This name is known to the compiler.
 */
extern uintptr_t __security_cookie;
extern uintptr_t __security_cookie_complement;


/***
*__security_init_cookie() - init buffer overrun security cookie.
*
*Purpose:
*       Initialize the global buffer overrun security cookie which is used by
*       the /GS compile switch to detect overwrites to local array variables
*       that potentially corrupt the return address.  This routine is called
*       at EXE/DLL startup.
*
*Entry:
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/

void __cdecl __security_init_cookie(void)
{
    UINT_PTR cookie;

    /*
     * Do nothing if the global cookie has already been initialized.  On x86,
     * reinitialize the cookie if it has been previously initialized to a
     * value with the high word 0x0000.  Some versions of Windows will init
     * the cookie in the loader, but using an older mechanism which forced the
     * high word to zero.
     */

    if (__security_cookie != DEFAULT_SECURITY_COOKIE
#if defined (_M_IX86)
        && (__security_cookie & 0xFFFF0000) != 0
#endif  /* defined (_M_IX86) */
       )
    {
        __security_cookie_complement = ~__security_cookie;
        return;
    }


    /*
     * Initialize the global cookie with an unpredictable value which is
     * different for each module in a process.
     */
    cookie = 0;//__get_entropy();

    /*
     * Make sure the cookie is initialized to a value that will prevent us from
     * reinitializing it if this routine is ever called twice.
     */

    if (cookie == DEFAULT_SECURITY_COOKIE)
    {
        cookie = DEFAULT_SECURITY_COOKIE + 1;
    }
#if defined (_M_IX86)
    else if ((cookie & 0xFFFF0000) == 0)
    {
        cookie |= ( (cookie|0x4711) << 16);
    }
#endif  /* defined (_M_IX86) */

    __security_cookie = cookie;
    __security_cookie_complement = ~cookie;

}
