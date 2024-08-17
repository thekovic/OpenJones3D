#ifndef STD_STDUTIL_H
#define STD_STDUTIL_H
#include <j3dcore/j3d.h>
#include <std/types.h>
#include <std/RTI/addresses.h>

J3D_EXTERN_C_START

int stdUtil_Format(char* aBuf, int bufSize, const char* format, ...);
char* J3DAPI stdUtil_StringSplit(const char* pSource, char* pDest, int destSize, char* pSeparators);
char* J3DAPI stdUtil_ParseLiteral(const char* pSource, char* pDest, unsigned int destSize);
int J3DAPI stdUtil_ToWStringEx(wchar_t* pwString, const char* pString, int maxChars);
void J3DAPI stdUtil_ToAStringEx(char* pString, const wchar_t* pwString, int maxChars);
wchar_t* J3DAPI stdUtil_ToWString(const char* pString);
char* J3DAPI stdUtil_ToAString(wchar_t* pwString);
void J3DAPI stdUtil_ToLower(char* pStr);
int J3DAPI stdUtil_StrCmp(const char* str1, const char* str2);

// Helper hooking functions
void stdUtil_InstallHooks(void);
void stdUtil_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // STD_STDUTIL_H
