
#include <windows.h>


// The entry point for this DLL.
extern "C" BOOL WINAPI _DllMainCRTStartup(
    HINSTANCE const instance,
    DWORD     const reason,
    LPVOID    const reserved
    )
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        // The /GS security cookie must be initialized before any exception
        // handling targeting the current image is registered.  No function
        // using exception handling can be called in the current image until
        // after this call:
        __security_init_cookie();
    }

    return FALSE;
}