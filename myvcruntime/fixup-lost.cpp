
#include <vcruntime.h>
#include <corecrt.h>

extern "C" errno_t __cdecl _controlfp_s(unsigned int *_CurrentState, unsigned int _NewValue, unsigned int _Mask)
{
    return 0;
}


extern "C" void __cdecl __setusermatherr(void*)
{
    //
}
