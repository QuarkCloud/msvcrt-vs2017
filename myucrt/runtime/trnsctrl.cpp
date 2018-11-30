/***
*trnsctrl.cpp -  Routines for doing control transfers
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Routines for doing control transfers; written using inline
*       assembly in naked functions.  Contains the public routine
*       _CxxFrameHandler, the entry point for the frame handler
****/

#include <eh.h>
//#include <ehassert.h>
//#include <ehdata.h>
//#include <ehhooks.h>
#include <setjmp.h>
//#include <trnsctrl.h>

//#include "../ehhelpers.h"

#include <Windows.h>
#include <suppress.h>
#include <vcruntime_internal.h>

#pragma warning(disable: 4100)      // unreferenced formal parameter
#pragma warning(disable: 4731)      // ignore EBP mod in inline-asm warning
#pragma warning(disable: 4733)      // ignore unsafe FS:0 modifications
#pragma warning(disable: 4740)      // control flow in asm suppresses global optimization



// copied from ntxcapi.h
#define EXCEPTION_UNWINDING 0x2         // Unwind is in progress
#define EXCEPTION_EXIT_UNWIND 0x4       // Exit unwind is in progress
#define EXCEPTION_STACK_INVALID 0x8     // Stack out of limits or unaligned
#define EXCEPTION_NESTED_CALL 0x10      // Nested exception handler call
#define EXCEPTION_TARGET_UNWIND 0x20    // Target unwind in progress
#define EXCEPTION_COLLIDED_UNWIND 0x40  // Collided exception handler call

#define EXCEPTION_UNWIND (EXCEPTION_UNWINDING | EXCEPTION_EXIT_UNWIND | \
                          EXCEPTION_TARGET_UNWIND | EXCEPTION_COLLIDED_UNWIND)

#define IS_UNWINDING(Flag) ((Flag & EXCEPTION_UNWIND) != 0)
#define IS_DISPATCHING(Flag) ((Flag & EXCEPTION_UNWIND) == 0)
#define IS_TARGET_UNWIND(Flag) (Flag & EXCEPTION_TARGET_UNWIND)

#define pFrameInfoChain   (*((FRAMEINFO **)    &(__vcrt_getptd()->_pFrameInfoChain)))



//
// __CxxFrameHandler3 - Real entry point to the runtime
//                                              __CxxFrameHandler2 is an alias for __CxxFrameHandler3
//                                              since they are compatible in VC version of CRT
//                      These function should be separated out if a change makes
//                                              __CxxFrameHandler3 incompatible with __CxxFrameHandler2
//
extern "C" _VCRTIMP DECLSPEC_GUARD_SUPPRESS EXCEPTION_DISPOSITION __cdecl __CxxFrameHandler3(
/*
    EAX=FuncInfo   *pFuncInfo,          // Static information for this frame
*/
    //EHExceptionRecord  *pExcept,        // Information for this exception
    //EHRegistrationNode *pRN,            // Dynamic information for this frame
    //void               *pContext,       // Context info (we don't care what's in it)
    //DispatcherContext  *pDC             // More dynamic info for this frame (ignored on Intel)
    void * except , void * rn , void * context , void * dc
) 
{
    return ExceptionContinueExecution;
    //
}

