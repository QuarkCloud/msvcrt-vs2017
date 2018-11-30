/***
*loadcfg.c
*
*       Copyright (c) Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Defines the default load config struct linked into images.
*
*******************************************************************************/

#include <Windows.h>

extern UINT_PTR __security_cookie;  /* /GS security cookie */
extern PVOID __guard_check_icall_fptr;
#if defined(_AMD64_)
extern PVOID __guard_dispatch_icall_fptr;
#endif

#if defined(_M_IX86) || defined(_X86_)
/*
 * The following two names are automatically created by the linker for any
 * image that has the safe exception table present.
 */

extern PVOID __safe_se_handler_table[]; /* base of safe handler entry table */
extern BYTE  __safe_se_handler_count;   /* absolute symbol whose address is
                                           the count of table entries */
#endif
extern PVOID __guard_fids_table[];
extern ULONG __guard_fids_count;
extern ULONG __guard_flags;
extern PVOID __guard_iat_table[];
extern ULONG __guard_iat_count;
extern PVOID __guard_longjmp_table[];
extern ULONG __guard_longjmp_count;
extern PVOID __dynamic_value_reloc_table;
extern PVOID __enclave_config;

#if defined(_CRT_WINDOWS)
// Windows build has the up-to-date SDK and hence does not need this DevDiv workaround for their stale SDK.
#else // _CRT_WINDOWS
typedef struct _RS2_IMAGE_LOAD_CONFIG_DIRECTORY32 {
    ULONG   Size;
    ULONG   TimeDateStamp;
    USHORT  MajorVersion;
    USHORT  MinorVersion;
    ULONG   GlobalFlagsClear;
    ULONG   GlobalFlagsSet;
    ULONG   CriticalSectionDefaultTimeout;
    ULONG   DeCommitFreeBlockThreshold;
    ULONG   DeCommitTotalFreeThreshold;
    ULONG   LockPrefixTable;                // VA
    ULONG   MaximumAllocationSize;
    ULONG   VirtualMemoryThreshold;
    ULONG   ProcessHeapFlags;
    ULONG   ProcessAffinityMask;
    USHORT  CSDVersion;
    USHORT  DependentLoadFlags;
    ULONG   EditList;                       // VA
    ULONG   SecurityCookie;                 // VA
    ULONG   SEHandlerTable;                 // VA
    ULONG   SEHandlerCount;
    ULONG   GuardCFCheckFunctionPointer;    // VA
    ULONG   GuardCFDispatchFunctionPointer; // VA
    ULONG   GuardCFFunctionTable;           // VA
    ULONG   GuardCFFunctionCount;
    ULONG   GuardFlags;
    IMAGE_LOAD_CONFIG_CODE_INTEGRITY CodeIntegrity;
    ULONG   GuardAddressTakenIatEntryTable; // VA
    ULONG   GuardAddressTakenIatEntryCount;
    ULONG   GuardLongJumpTargetTable;       // VA
    ULONG   GuardLongJumpTargetCount;
    ULONG   DynamicValueRelocTable;         // VA
    ULONG   CHPEMetadataPointer;
    ULONG   GuardRFFailureRoutine;          // VA
    ULONG   GuardRFFailureRoutineFunctionPointer; // VA
    ULONG   DynamicValueRelocTableOffset;
    USHORT  DynamicValueRelocTableSection;
    USHORT  Reserved2;
    ULONG   GuardRFVerifyStackPointerFunctionPointer; // VA
    ULONG   HotPatchTableOffset;
    ULONG   Reserved3;
    ULONG   EnclaveConfigurationPointer;    // VA
} RS2_IMAGE_LOAD_CONFIG_DIRECTORY32, *PRS2_IMAGE_LOAD_CONFIG_DIRECTORY32;

typedef struct _RS2_IMAGE_LOAD_CONFIG_DIRECTORY64 {
    ULONG      Size;
    ULONG      TimeDateStamp;
    USHORT     MajorVersion;
    USHORT     MinorVersion;
    ULONG      GlobalFlagsClear;
    ULONG      GlobalFlagsSet;
    ULONG      CriticalSectionDefaultTimeout;
    ULONGLONG  DeCommitFreeBlockThreshold;
    ULONGLONG  DeCommitTotalFreeThreshold;
    ULONGLONG  LockPrefixTable;                // VA
    ULONGLONG  MaximumAllocationSize;
    ULONGLONG  VirtualMemoryThreshold;
    ULONGLONG  ProcessAffinityMask;
    ULONG      ProcessHeapFlags;
    USHORT     CSDVersion;
    USHORT     DependentLoadFlags;
    ULONGLONG  EditList;                       // VA
    ULONGLONG  SecurityCookie;                 // VA
    ULONGLONG  SEHandlerTable;                 // VA
    ULONGLONG  SEHandlerCount;
    ULONGLONG  GuardCFCheckFunctionPointer;    // VA
    ULONGLONG  GuardCFDispatchFunctionPointer; // VA
    ULONGLONG  GuardCFFunctionTable;           // VA
    ULONGLONG  GuardCFFunctionCount;
    ULONG      GuardFlags;
    IMAGE_LOAD_CONFIG_CODE_INTEGRITY CodeIntegrity;
    ULONGLONG  GuardAddressTakenIatEntryTable; // VA
    ULONGLONG  GuardAddressTakenIatEntryCount;
    ULONGLONG  GuardLongJumpTargetTable;       // VA
    ULONGLONG  GuardLongJumpTargetCount;
    ULONGLONG  DynamicValueRelocTable;         // VA
    ULONGLONG  CHPEMetadataPointer;            // VA
    ULONGLONG  GuardRFFailureRoutine;          // VA
    ULONGLONG  GuardRFFailureRoutineFunctionPointer; // VA
    ULONG      DynamicValueRelocTableOffset;
    USHORT     DynamicValueRelocTableSection;
    USHORT     Reserved2;
    ULONGLONG  GuardRFVerifyStackPointerFunctionPointer; // VA
    ULONG      HotPatchTableOffset;
    ULONG      Reserved3;
    ULONGLONG  EnclaveConfigurationPointer;     // VA
} RS2_IMAGE_LOAD_CONFIG_DIRECTORY64, *PRS2_IMAGE_LOAD_CONFIG_DIRECTORY64;

// TRANSITION: VSO#365272
static_assert(sizeof(IMAGE_LOAD_CONFIG_DIRECTORY32) == 152, "IMAGE_LOAD_CONFIG_DIRECTORY32 has changed");
static_assert(sizeof(IMAGE_LOAD_CONFIG_DIRECTORY64) == 244, "IMAGE_LOAD_CONFIG_DIRECTORY64 has changed");

#ifdef _WIN64
typedef RS2_IMAGE_LOAD_CONFIG_DIRECTORY64     RS2_IMAGE_LOAD_CONFIG_DIRECTORY;
typedef PRS2_IMAGE_LOAD_CONFIG_DIRECTORY64    PRS2_IMAGE_LOAD_CONFIG_DIRECTORY;
#else
typedef RS2_IMAGE_LOAD_CONFIG_DIRECTORY32     RS2_IMAGE_LOAD_CONFIG_DIRECTORY;
typedef PRS2_IMAGE_LOAD_CONFIG_DIRECTORY32    PRS2_IMAGE_LOAD_CONFIG_DIRECTORY;
#endif

#endif // _CRT_WINDOWS

#if defined(_CHPE_X86_ARM64_)

extern const PVOID __chpe_metadata;

#endif

const
DECLSPEC_SELECTANY
#if defined(_CRT_WINDOWS)
IMAGE_LOAD_CONFIG_DIRECTORY
#else
RS2_IMAGE_LOAD_CONFIG_DIRECTORY
#endif
_load_config_used = {
    sizeof(_load_config_used),
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    (SIZE_T)&__security_cookie,

#if defined(_M_IX86) || defined(_X86_)

    (SIZE_T)__safe_se_handler_table,
    (SIZE_T)&__safe_se_handler_count,

#else

    0,
    0,

#endif

    (SIZE_T)&__guard_check_icall_fptr,

#if defined(_AMD64_)

    (SIZE_T)&__guard_dispatch_icall_fptr,

#else

    0,

#endif

    (SIZE_T)&__guard_fids_table,
    (SIZE_T)&__guard_fids_count,

    (ULONG)(SIZE_T)&__guard_flags,

    { 0, 0, 0, 0 },

    (SIZE_T)&__guard_iat_table,
    (SIZE_T)&__guard_iat_count,

    (SIZE_T)&__guard_longjmp_table,
    (SIZE_T)&__guard_longjmp_count,

    0,

#if defined(_CHPE_X86_ARM64_)

    (SIZE_T)&__chpe_metadata,

#else

    0,

#endif

    0,
    0,

    0,      // DynamicValueRelocTableOffset
    0,      // DynamicValueRelocTableSection
    0,      // Reserved2

    0,

    0,      // HotPatchTableOffset
    0,      // Reserved3
    (SIZE_T)&__enclave_config,
};
