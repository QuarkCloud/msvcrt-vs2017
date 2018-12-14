
#include "compile.h"
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN64
    typedef unsigned __int64 size_t;
    typedef __int64          ptrdiff_t;
    typedef __int64          intptr_t;
    typedef unsigned __int64 uintptr_t;
#else
    typedef unsigned int     size_t;
    typedef int              ptrdiff_t;
    typedef int              intptr_t;
    typedef unsigned int     uintptr_t;
#endif


void __cdecl __security_init_cookie(void);
extern uintptr_t __security_cookie;



#if defined _M_IX86
    #define _VCRT_DECLARE_ALTERNATE_NAME_PREFIX "_"
    #define _VCRT_DECLARE_ALTERNATE_NAME_PREFIX_DATA "_"
#elif defined _M_X64 || defined _M_ARM || defined _M_ARM64
    #define _VCRT_DECLARE_ALTERNATE_NAME_PREFIX ""
    #define _VCRT_DECLARE_ALTERNATE_NAME_PREFIX_DATA ""
#else
    #error Unsupported architecture
#endif

#define _VCRT_DECLARE_ALTERNATE_NAME(name, alternate_name)  \
    __pragma(comment(linker,                                \
        "/alternatename:"                                   \
        _VCRT_DECLARE_ALTERNATE_NAME_PREFIX #name           \
        "="                                                 \
        _VCRT_DECLARE_ALTERNATE_NAME_PREFIX #alternate_name \
        ))

#define _VCRT_DECLARE_ALTERNATE_NAME_DATA(name, alternate_name)     \
    __pragma(comment(linker,                                        \
        "/alternatename:"                                           \
        _VCRT_DECLARE_ALTERNATE_NAME_PREFIX_DATA #name              \
        "="                                                         \
        _VCRT_DECLARE_ALTERNATE_NAME_PREFIX_DATA #alternate_name    \
        ))


// The _VCRT_DEFINE_IAT_SYMBOL macro provides an architecture-neutral way of
// defining IAT symbols (__imp_- or _imp__-prefixed symbols).
#ifdef _M_IX86
#define _VCRT_DEFINE_IAT_SYMBOL_MAKE_NAME(f) _CRT_CONCATENATE(_imp__, f)
#else
#define _VCRT_DEFINE_IAT_SYMBOL_MAKE_NAME(f) _CRT_CONCATENATE(__imp_, f)
#endif

#define _VCRT_DEFINE_IAT_SYMBOL(f)                                                          \
    extern "C" __declspec(selectany) void const* const _VCRT_DEFINE_IAT_SYMBOL_MAKE_NAME(f) \
        = reinterpret_cast<void const*>(f)



int __cdecl main(int    argc,char** argv,char** envp);
BOOL WINAPI DllMain(HINSTANCE hInstance,DWORD fdwReason,LPVOID lpvReserved);

typedef BOOL(WINAPI* __scrt_dllmain_type)(HINSTANCE, DWORD, LPVOID);

enum class __scrt_module_type
{
    dll,
    exe
};


#ifdef __cplusplus
}
#endif

