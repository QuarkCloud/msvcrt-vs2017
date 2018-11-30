//
// fcvt.cpp
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// Defines the _ecvt and _fcvt families of functions.
//
#include <corecrt_internal.h>
#include <corecrt_internal_fltintrn.h>
#include <corecrt_internal_securecrt.h>
#include <minmax.h>
#include <stdlib.h>



// Tries to get the pre-thread conversion buffer; returns nullptr on failure.
static char* __cdecl try_get_ptd_buffer()
{
    __acrt_ptd* const ptd = __acrt_getptd_noexit();
    if (!ptd)
        return nullptr;

    if (ptd->_cvtbuf)
        return ptd->_cvtbuf;

    ptd->_cvtbuf = _malloc_crt_t(char, _CVTBUFSIZE).detach();

    return ptd->_cvtbuf;
}



// An internal helper that wraps the call to convert the STRFLT to a string and
// updates all of the data that is used by its callers.
static errno_t __cdecl internal_to_string(
    _Out_writes_z_(buffer_count) char* const buffer,
    size_t                             const buffer_count,
    STRFLT                             const strflt,
    int                                const requested_digits,
    int*                               const decimal_point,
    int*                               const sign
    ) throw()
{
    // Make sure we don't overflow the buffer.  If the user asks for more digits
    // than the buffer can handle, truncate it to the maximum size allowed in
    // the buffer.  The maximum size is two less than the buffer size because we
    // use one character for overflow and one for the null terminator.
    size_t const minimum_buffer_count = static_cast<size_t>((requested_digits > 0 ? requested_digits : 0) + 2);

    _VALIDATE_RETURN_ERRCODE(buffer_count >= minimum_buffer_count, ERANGE);

    int const capped_digits = min(requested_digits, static_cast<int>(buffer_count - 2));

    errno_t const e = __acrt_fp_strflt_to_string(buffer, buffer_count, capped_digits, strflt);
    
    if (e != 0)
        return errno = e;

    *sign          = strflt->sign == '-' ? 1 : 0;
    *decimal_point = strflt->decpt;

    return 0;
}



// The _fcvt functions, like the _ecvt functions, convert a floating point value
// to a narrow character string.  The functions prepare the data for the Fortran
// F-format with the number of digits following the decimal point specified by
// requested_digits.  The position of the decimal point is returned indirectly
// through *decimal_point.  The correct digit for Fortran F-format is rounded.
//
// These functions update either (a) the user-provided string (_s-suffixed
// function) or (b) the per-thread conversion buffer.  The _s-suffixed
// function returns zero on success, or an error code on failure.  The
// *decimal_point and *sign values are updated with the results of the
// conversion.
extern "C" errno_t __cdecl _fcvt_s(
    char*  const buffer,
    size_t const buffer_count,
    double const value,
    int    const requested_digits,
    int*   const decimal_point,
    int*   const sign
    )
{
    _VALIDATE_RETURN_ERRCODE(buffer != nullptr, EINVAL);
    _VALIDATE_RETURN_ERRCODE(buffer_count > 0,  EINVAL);
    _RESET_STRING(buffer, buffer_count);
    _VALIDATE_RETURN_ERRCODE(decimal_point != nullptr, EINVAL);
    _VALIDATE_RETURN_ERRCODE(sign != nullptr,          EINVAL);
    
    char result_string[_CVTBUFSIZE + 1];

    _strflt strflt{};
    __acrt_fltout(
        reinterpret_cast<_CRT_DOUBLE const&>(value),
        _countof(result_string),
        &strflt,
        result_string,
        _countof(result_string));

    int const actual_digits = strflt.decpt + requested_digits;

    bool const buffer_insufficiently_large = 
        requested_digits > 0 && strflt.decpt > 0 &&
        actual_digits < requested_digits;

    int const capped_digits = buffer_insufficiently_large ? INT_MAX : actual_digits;

    return internal_to_string(buffer, buffer_count, &strflt, capped_digits, decimal_point, sign);
}

extern "C" char* __cdecl _fcvt(
    double const value,
    int    const requested_digits,
    int*   const decimal_point,
    int*   const sign
    )
{
    char* const buffer = try_get_ptd_buffer();
    if (!buffer)
        return nullptr;

    char result_string[_CVTBUFSIZE + 1];

    _strflt strflt{};
    __acrt_fltout(
        reinterpret_cast<_CRT_DOUBLE const&>(value),
        _countof(result_string),
        &strflt,
        result_string,
        _countof(result_string));

    // Make sure we don't overflow the buffer.  If the user asks for more digits
    // than the buffer can handle, truncate it to the maximum size allowed in
    // the buffer.  The maximum size is two less than the buffer size because we
    // use one character for overflow and one for the null terminator.
    int const capped_digits = min(requested_digits, _CVTBUFSIZE - 2 - strflt.decpt);

    errno_t const status = _fcvt_s(buffer, _CVTBUFSIZE, value, capped_digits, decimal_point, sign);
    if (status != 0)
        return nullptr;

    return buffer;
}



// The _ecvt functions, which convert a floating point value to a string.  The
// position of the decimal point relative to the beginning of the string is
// stored indirectly through the decimal_point argument, where a negative value
// means that the decimal point is to the left of the returned digits.  If the
// sign of the result is negative, the word pointed to by sign is nonzero;
// otherwise it is zero.  The low order digit is rounded.
//
// These functions update either (a) the user-provided string (_s-suffixed
// function) or (b) the per-thread conversion buffer.  The _s-suffixed
// function returns zero on success, or an error code on failure.  The
// *decimal_point and *sign values are updated with the results of the
// conversion.
extern "C" errno_t __cdecl _ecvt_s(
    char*  const buffer,
    size_t const buffer_count,
    double const value,
    int    const requested_digits,
    int*   const decimal_point,
    int*   const sign
    )
{
    _VALIDATE_RETURN_ERRCODE(buffer != nullptr, EINVAL);
    _VALIDATE_RETURN_ERRCODE(buffer_count > 0,  EINVAL);
    _RESET_STRING(buffer, buffer_count);
    _VALIDATE_RETURN_ERRCODE(decimal_point != nullptr, EINVAL);
    _VALIDATE_RETURN_ERRCODE(sign != nullptr,          EINVAL);

    char result_string[_CVTBUFSIZE + 1];

    _strflt strflt{};
    __acrt_fltout(
        reinterpret_cast<_CRT_DOUBLE const&>(value),
        _countof(result_string),
        &strflt,
        result_string,
        _countof(result_string));

    errno_t const e = internal_to_string(buffer, buffer_count, &strflt, requested_digits, decimal_point, sign);

    // Make sure we don't overflow the buffer.  If the user asks for more digits
    // than the buffer can handle, truncate it to the maximum size allowed in
    // the buffer.  The maximum size is two less than the buffer size because we
    // use one character for overflow and one for the null terminator.
    int const capped_digits = min(requested_digits, static_cast<int>(buffer_count - 2));

    // The conversion function occasionally returns an extra char in the buffer:
    if (capped_digits >= 0 && buffer[capped_digits])
        buffer[capped_digits] = '\0';

    return e;
}

extern "C" char* __cdecl _ecvt(
    double const value,
    int    const requested_digits,
    int*   const decimal_point,
    int*   const sign
    )
{
    char* const buffer = try_get_ptd_buffer();
    if (!buffer)
        return nullptr;

    // Make sure we don't overflow the buffer.  If the user asks for more digits
    // than the buffer can handle, truncate it to the maximum size allowed in
    // the buffer.  The maximum size is two less than the buffer size because we
    // use one character for overflow and one for the null terminator.
    int const capped_digits = min(requested_digits, _CVTBUFSIZE - 2);

    errno_t const e = _ecvt_s(buffer, _CVTBUFSIZE, value, capped_digits, decimal_point, sign);
    if (e != 0)
        return nullptr;

    return buffer;
}
