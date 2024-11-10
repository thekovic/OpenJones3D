#include "stdUtil.h"
#include <j3dcore/j3dhook.h>
#include <std/General/std.h>
#include <std/General/stdMemory.h>
#include <std/RTI/symbols.h>

#include <wchar.h>

void stdUtil_InstallHooks(void)
{
    J3D_HOOKFUNC(stdUtil_Format);
    J3D_HOOKFUNC(stdUtil_StringSplit);
    J3D_HOOKFUNC(stdUtil_ParseLiteral);
    J3D_HOOKFUNC(stdUtil_ToWStringEx);
    J3D_HOOKFUNC(stdUtil_ToAStringEx);
    J3D_HOOKFUNC(stdUtil_ToWString);
    J3D_HOOKFUNC(stdUtil_ToAString);
    J3D_HOOKFUNC(stdUtil_ToLower);
    J3D_HOOKFUNC(stdUtil_StrCmp);
}

void stdUtil_ResetGlobals(void)
{
}

int stdUtil_Format(char* pStr, size_t size, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    int result = vsnprintf_s(pStr, size, size - 1, format, args); // TODO: make conversion to C11 vsnprintf_s
    va_end(args);
    return result;
}

int stdUtil_WFormat(wchar_t* pStr, size_t size, const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    int result = _vsnwprintf_s(pStr, size, size - 1, format, args); // TODO: make conversion to C11 vsnwprintf_s
    va_end(args);
    return result;
}

char* J3DAPI stdUtil_StringSplit(const char* pSource, char* pDest, unsigned int destSize, char* pSeparators)
{
    const char* pBegin;
    char* pEnd;
    size_t len;

    STD_ASSERTREL(pSource != ((void*)0));
    STD_ASSERTREL(pSeparators != ((void*)0));
    if ( pDest )
    {
        *pDest = 0;
    }

    pBegin = &pSource[strspn(pSource, pSeparators)];
    pEnd = strpbrk(pBegin, pSeparators);
    if ( pEnd )
    {
        len = pEnd - pBegin;
    }
    else
    {
        len = strlen(pBegin);
    }

    if ( !pDest )
    {
        return pEnd;
    }

    stdUtil_StringNumCopy(pDest, destSize, pBegin, len);
    return pEnd;
}

char* J3DAPI stdUtil_ParseLiteral(const char* pSource, char* pDest, unsigned int destSize)
{
    char* pCur;
    char* pStrBegin;
    char* pStrEnd;
    //unsigned int strSize;

    STD_ASSERTREL(pSource != ((void*)0));
    if ( pDest )
    {
        *pDest = 0;
    }

    pCur = strchr(pSource, '"');
    if ( !pCur )
    {
        return pCur;
    }

    pStrBegin = pCur + 1;
    pCur = strchr(pCur + 1, '"');
    pStrEnd = pCur;
    if ( !pCur )
    {
        return pCur;
    }

    if ( !pDest )
    {
        return pStrEnd + 1;
    }

    STD_ASSERTREL(destSize > 0);
    stdUtil_StringNumCopy(pDest, destSize, pStrBegin, pCur - pStrBegin);
    return pStrEnd + 1;
}

int J3DAPI stdUtil_ToWStringEx(wchar_t* pwString, const char* pString, unsigned int maxChars)
{
    STD_ASSERTREL(pwString != ((void*)0));
    STD_ASSERTREL(pString != ((void*)0));
    STD_ASSERTREL(maxChars >= 0);

    unsigned int numChars = 0;
    while ( numChars < maxChars && *pString )
    {
        *pwString++ = *(uint8_t*)pString++;
        ++numChars;
    }

    if ( numChars < maxChars ) {
        *pwString = 0;
    }

    return numChars;
}

void J3DAPI stdUtil_ToAStringEx(char* pString, const wchar_t* pwString, unsigned int maxChars)
{
    STD_ASSERTREL(pString != ((void*)0));
    STD_ASSERTREL(pwString != ((void*)0));
    STD_ASSERTREL(maxChars >= 0);

    unsigned int numChars = 0;
    while ( numChars < maxChars && *pwString )
    {
        *pString = (*pwString <= 255u) ? *(uint8_t*)pwString : '?';
        ++pwString;
        ++pString;
        ++numChars;
    }

    if ( numChars < maxChars )
    {
        *pString = 0;
    }
}

wchar_t* J3DAPI stdUtil_ToWString(const char* pString)
{
    STD_ASSERTREL(pString != ((void*)0));

    wchar_t* pwString = (wchar_t*)STDMALLOC(sizeof(wchar_t) * strlen(pString) + sizeof(wchar_t)); // Note, extra 2 bytes for storing null
    STD_ASSERTREL(pwString != ((void*)0));

    stdUtil_ToWStringEx(pwString, pString, strlen(pString));
    pwString[strlen(pString)] = 0;
    return pwString;
}

char* J3DAPI stdUtil_ToAString(const wchar_t* pwString)
{
    STD_ASSERTREL(pwString != ((void*)0));
    size_t len = wcslen(pwString);

    char* pString = (char*)STDMALLOC(len + 1); // Note, extra byte for storing null
    STD_ASSERTREL(pString != ((void*)0));

    stdUtil_ToAStringEx(pString, pwString, len);
    pString[wcslen(pwString)] = 0;
    return pString;
}

void J3DAPI stdUtil_ToLower(char* pStr)
{
    for ( char* pCur = pStr; *pCur; ++pCur ) {
        *pCur = (char)tolower(*pCur);
    }
}

void J3DAPI stdUtil_ToUpper(char* pStr)
{
    for ( char* pCur = pStr; *pCur; ++pCur ) {
        *pCur = (char)toupper(*pCur);
    }
}

int J3DAPI stdUtil_StrCmp(const char* str1, const char* str2)
{
    while ( 1 )
    {
        int c1 = tolower(*str1);
        int c2 = tolower(*str2);
        if ( !c1 && !c2 )
        {
            return 0;
        }

        if ( c2 > c1 )
        {
            return -1;
        }

        if ( c2 < c1 )
        {
            break;
        }

        ++str1;
        ++str2;
    }

    return 1;
}
