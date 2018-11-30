//
// mktime.cpp
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// The mktime and mkgmtime families of functions, which convert a time value in
// a (possibly incomplete) tm structure into a time_t value, then update all of
// the tm structure fields with the "normalized" values.
//
#include <corecrt_internal_time.h>


// ChkAdd evaluates to TRUE if dest = src1 + src2 has overflowed
#define ChkAdd(dest, src1, src2)  \
    (((src1 >= 0L) && (src2 >= 0L) && (dest <  0L)) || \
     ((src1 <  0L) && (src2 <  0L) && (dest >= 0L)))

// ChkMul evaluates to TRUE if dest = src1 * src2 has overflowed
#define ChkMul(dest, src1, src2) ( src1 ? (dest / src1 != src2) : 0 )



// The implementation of the _mktime and _mkgmtime functions.  If 'use_local_time'
// is true, the time is assumed to be in local time; otherwise, the time is
// assumed to be in UTC.
template <typename TimeType>
static TimeType __cdecl common_mktime(
    tm*  const tb,
    bool const use_local_time
    ) throw()
{


    TimeType tmptm1 = 0;

    return tmptm1;
}



// Converts a tm structure value into a time_t value.  These functions also
// update the tm structure to normalize it and populate any missing fields.
// There are three practical uses for these functions:
//
// (1) To convert a broken-down time to the internal time format (time_t)
// (2) To complete the tm value with the correct tm_wday, tm_yday, or tm_isdst
//     values given the rest of the contents of the tm.
// (3) To pass in a time structure with "out of range" values for some fields
//     and get back a "normalized" tm structure (e.g., to pass in 1/35/1987
//     and get back 2/4/1987).
//
// Returns the resulting time_t value on success; returns -1 on failure.
extern "C" __time32_t __cdecl _mktime32(tm* const tb)
{
    return common_mktime<__time32_t>(tb, true);
}

extern "C" __time64_t __cdecl _mktime64(tm* const tb)
{
    return common_mktime<__time64_t>(tb, true);
}



// Converts a UTC time stored in a tm structure into a time_t value.  These
// functions also update the tm structure to normalize it and populate any
// missing fields.  Returns the resulting time_t value on success; returns
// -1 on failure.
extern "C"  __time32_t __cdecl _mkgmtime32(tm* const tb)
{
    return common_mktime<__time32_t>(tb, false);
}

extern "C"  __time64_t __cdecl _mkgmtime64(tm* const tb)
{
    return common_mktime<__time64_t>(tb, false);
}
