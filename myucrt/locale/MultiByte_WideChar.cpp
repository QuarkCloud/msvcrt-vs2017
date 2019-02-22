
#include <corecrt_internal.h>



int __cdecl __acrt_MultiByteToWideChar(UINT _CodePage, DWORD _DWFlags, LPCSTR  _LpMultiByteStr,
	int _CbMultiByte,LPWSTR  _LpWideCharStr, int _CchWideChar)
{
	return ::MultiByteToWideChar(_CodePage , _DWFlags , _LpMultiByteStr , _CbMultiByte ,
		_LpWideCharStr , _CchWideChar);
}

int __cdecl __acrt_WideCharToMultiByte(UINT _CodePage, DWORD _DWFlags, LPCWSTR _LpWideCharStr,
	int _CchWideChar, LPSTR _LpMultiByteStr, int _CbMultiByte, LPCSTR _LpDefaultChar, LPBOOL  _LpUsedDefaultChar)
{
	return ::WideCharToMultiByte(_CodePage, _DWFlags, _LpWideCharStr,
		_CchWideChar, _LpMultiByteStr, _CbMultiByte, _LpDefaultChar, _LpUsedDefaultChar);
}