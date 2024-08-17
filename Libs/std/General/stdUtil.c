#include "stdUtil.h"
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>


void stdUtil_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(stdUtil_Format);
    // J3D_HOOKFUNC(stdUtil_StringSplit);
    // J3D_HOOKFUNC(stdUtil_ParseLiteral);
    // J3D_HOOKFUNC(stdUtil_ToWStringEx);
    // J3D_HOOKFUNC(stdUtil_ToAStringEx);
    // J3D_HOOKFUNC(stdUtil_ToWString);
    // J3D_HOOKFUNC(stdUtil_ToAString);
    // J3D_HOOKFUNC(stdUtil_ToLower);
    // J3D_HOOKFUNC(stdUtil_StrCmp);
}

void stdUtil_ResetGlobals(void)
{

}

int stdUtil_Format(char* aBuf, int bufSize, const char* format, ...)
{
    return J3D_TRAMPOLINE_CALL(stdUtil_Format, aBuf, bufSize, format);
}

char* J3DAPI stdUtil_StringSplit(const char* pSource, char* pDest, int destSize, char* pSeparators)
{
    return J3D_TRAMPOLINE_CALL(stdUtil_StringSplit, pSource, pDest, destSize, pSeparators);
}

char* J3DAPI stdUtil_ParseLiteral(const char* pSource, char* pDest, unsigned int destSize)
{
    return J3D_TRAMPOLINE_CALL(stdUtil_ParseLiteral, pSource, pDest, destSize);
}

int J3DAPI stdUtil_ToWStringEx(wchar_t* pwString, const char* pString, int maxChars)
{
    return J3D_TRAMPOLINE_CALL(stdUtil_ToWStringEx, pwString, pString, maxChars);
}

void J3DAPI stdUtil_ToAStringEx(char* pString, const wchar_t* pwString, int maxChars)
{
    J3D_TRAMPOLINE_CALL(stdUtil_ToAStringEx, pString, pwString, maxChars);
}

wchar_t* J3DAPI stdUtil_ToWString(const char* pString)
{
    return J3D_TRAMPOLINE_CALL(stdUtil_ToWString, pString);
}

char* J3DAPI stdUtil_ToAString(wchar_t* pwString)
{
    return J3D_TRAMPOLINE_CALL(stdUtil_ToAString, pwString);
}

void J3DAPI stdUtil_ToLower(char* pStr)
{
    J3D_TRAMPOLINE_CALL(stdUtil_ToLower, pStr);
}

int J3DAPI stdUtil_StrCmp(const char* str1, const char* str2)
{
    return J3D_TRAMPOLINE_CALL(stdUtil_StrCmp, str1, str2);
}
