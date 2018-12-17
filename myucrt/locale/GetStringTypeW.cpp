
#include <corecrt_internal.h>
#include <locale.h>


extern "C" BOOL __cdecl __acrt_GetStringTypeW(
	_In_                DWORD       _DWInfoType,
	_In_NLS_string_(_CchSrc) PCWCH  _LpSrcStr,
	_In_                int         _CchSrc,
	_Out_               LPWORD      _LpCharType
)
{
	return FALSE;
}
