/***
*ehhelpers.cpp - Some target-independent helper routines used by the EH frame handler.
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
****/

#include <eh.h>         // User-visible routines for eh
//#include <ehassert.h>   // This project's versions of standard assert macros
//#include <ehdata.h>     // Declarations of all types used for EH
//#include <ehhooks.h>    // Declarations of hook variables and callbacks
//#include <ehstate.h>    // Declarations of state management stuff
//#include <trnsctrl.h>   // Routines to handle transfer of control (trnsctrl.asm)
#include <vcruntime_exception.h>
#include <vcruntime_typeinfo.h>

#include <Unknwn.h>
#include <Windows.h>

//#include "ehhelpers.h"

//////////////////////////////////////////////////////////////////////////////////
// __std_terminate: Helper function referenced by the front-end to assist in
// implementing noexcept. Noexcept termination semantics are generally handled
// by FindHandler() above, when we cross a function with the noexcept bit set
// in the xdata when looking for a handler. When noexcept functions are inlined,
// though, we may no longer cross a noexcept function boundary when searching for
// a handler. In this case the inlined code contains an EH state that will invoke
// this function should an exception occur.
extern "C" __declspec(noreturn) void __cdecl __std_terminate()
{
    terminate();
}

