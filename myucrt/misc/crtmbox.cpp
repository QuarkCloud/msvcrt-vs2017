/***
*crtmbox.c - CRT MessageBoxA wrapper.
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Wrap MessageBoxA.
*
*******************************************************************************/

#include <corecrt_internal.h>
#include <corecrt_internal_traits.h>


extern "C" int __cdecl __acrt_show_narrow_message_box(
    char const* const text,
    char const* const caption,
    unsigned    const type
    )
{
    return 0;
    //return common_show_message_box(text, caption, type);
}

extern "C" int __cdecl __acrt_show_wide_message_box(
    wchar_t const* const text,
    wchar_t const* const caption,
    unsigned       const type
    )
{
    return 0;
    //return common_show_message_box(text, caption, type);
}
