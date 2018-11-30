/***
*wsetloca.c - Contains the wsetlocale function
*
*       Copyright (c) Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Contains the wsetlocale() function.
*
****/

#include <corecrt_internal.h>
#include <locale.h>

extern "C" {

static const char _first_127char[] = {
        1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17,
        18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
        35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
        69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
        86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100,101,102,
        103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,
        120,121,122,123,124,125,126,127
};

extern __crt_locale_data __acrt_initial_locale_data;
extern const unsigned short _wctype[];
static const unsigned short *_ctype_loc_style = _wctype + 2;

long __acrt_locale_changed_data = FALSE;

__crt_locale_data* __cdecl _updatetlocinfoEx_nolock(__crt_locale_data**, __crt_locale_data*);

void __cdecl __acrt_set_locale_changed()
{
    _InterlockedExchange(&__acrt_locale_changed_data, TRUE);
}

/***
* _configthreadlocale(int i)
*
* Purpose:
*       To set _own_locale flag on threadinfo sturct. If this flag is set, this thread
*       is going own it's threadlocinfo struct. Setlocale call on other thread will have
*       no effect on this thread's locale. If 0 is passed then nothing is changed, but
*       current status is returned.
* Exit   :
*       Returns the current status - i.e. per thread locale is enabled or not.
*
*******************************************************************************/
int __cdecl _configthreadlocale(int i)
{
    /*
     * ownlocale flag struct:
     * bits: 000000000000000000000000000000P1
     * P is set when _ENABLE_PER_THREAD_LOCALE is called for this thread
     * or _ENABLE_PER_THREAD_LOCALE_NEW was set when this thread was created.
     *
     * __globallocalestatus structure:
     * bits: 11111111111111111111111111111N1G
     * G is set if _ENABLE_PER_THREAD_LOCALE_GLOBAL is set.
     * G is 0 if _ENABLE_PER_THREAD_LOCALE_GLOBAL is not set.
     * N is set if _ENABLE_PER_THREAD_LOCALE_NEW is set.
     * N is 0 if _ENABLE_PER_THREAD_LOCALE_NEW is not set.
     */
    __acrt_ptd* const ptd = __acrt_getptd();
    int retval = (ptd->_own_locale & _PER_THREAD_LOCALE_BIT)==0 ? _DISABLE_PER_THREAD_LOCALE:_ENABLE_PER_THREAD_LOCALE;

    switch(i)
    {
        case _ENABLE_PER_THREAD_LOCALE :
            ptd->_own_locale = ptd->_own_locale | _PER_THREAD_LOCALE_BIT;
            break;

        case _DISABLE_PER_THREAD_LOCALE :
            ptd->_own_locale = ptd->_own_locale & ~_PER_THREAD_LOCALE_BIT;
            break;

        case 0 :
            break;

        /* used only during dll startup for linkopt */
        case -1 :
            __globallocalestatus=-1;
            break;

        default :
            _VALIDATE_RETURN(("Invalid parameter for _configthreadlocale",0),EINVAL,-1);
            break;
    }

    return retval;

}


} // extern "C"
