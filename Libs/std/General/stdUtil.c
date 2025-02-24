#include "stdUtil.h"
#include <j3dcore/j3dhook.h>
#include <std/General/std.h>
#include <std/General/stdMemory.h>
#include <std/General/stdPlatform.h>
#include <std/RTI/symbols.h>

#include <string.h>
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
{}

char* J3DAPI stdUtil_StringDuplicate(const char* pSource, tHostServices* pHS)
{
    STD_ASSERTREL(pSource != NULL);
    STD_ASSERTREL(pHS != NULL);

    size_t len = strlen(pSource);
    char* pDupStr = (char*)STDMALLOC(len + 1);
    if ( !pDupStr )
    {
        return NULL;
    }

    stdUtil_StringCopy(pDupStr, len + 1, pSource);
    return pDupStr;
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

char* J3DAPI stdUtil_StringSplit(const char* pSource, char* pFirstToken, size_t maxTokenLenght, const char* pSeparators)
{
    STD_ASSERTREL(pSource != NULL);
    STD_ASSERTREL(pSeparators != NULL);

    if ( pFirstToken )
    {
        *pFirstToken = 0;
    }

    const char* pTokenStart = &pSource[strspn(pSource, pSeparators)]; // Skip any leading separators.
    char* pTokenEnd = strpbrk(pTokenStart, pSeparators); // Find the next occurrence of any separator.

    // Changed: Swap if statements to first check for null pDest
    if ( !pFirstToken )
    {
        return pTokenEnd;
    }

    size_t len = pTokenEnd ? pTokenEnd - pTokenStart : strlen(pTokenStart);
    stdUtil_StringNumCopy(pFirstToken, maxTokenLenght, pTokenStart, len);
    return pTokenEnd;
}

char* J3DAPI stdUtil_ParseLiteral(const char* pSource, char* pDest, size_t destSize)
{
    char* pCur;
    char* pStrBegin;
    char* pStrEnd;
    //unsigned int strSize;

    STD_ASSERTREL(pSource != NULL);
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

int J3DAPI stdUtil_ToWStringEx(wchar_t* pwString, const char* pString, size_t maxChars)
{
    STD_ASSERTREL(pwString != NULL);
    STD_ASSERTREL(pString != NULL);
    STD_ASSERTREL(maxChars >= 0);

    size_t numChars = 0;
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

void J3DAPI stdUtil_ToAStringEx(char* pString, const wchar_t* pwString, size_t maxChars)
{
    STD_ASSERTREL(pString != NULL);
    STD_ASSERTREL(pwString != NULL);
    STD_ASSERTREL(maxChars >= 0);

    size_t numChars = 0;
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
    STD_ASSERTREL(pString != NULL);

    wchar_t* pwString = (wchar_t*)STDMALLOC(sizeof(wchar_t) * strlen(pString) + sizeof(wchar_t)); // Note, extra 2 bytes for storing null
    STD_ASSERTREL(pwString != NULL);

    stdUtil_ToWStringEx(pwString, pString, strlen(pString));
    pwString[strlen(pString)] = 0;
    return pwString;
}

char* J3DAPI stdUtil_ToAString(const wchar_t* pwString)
{
    STD_ASSERTREL(pwString != NULL);
    size_t len = wcslen(pwString);

    char* pString = (char*)STDMALLOC(len + 1); // Note, extra byte for storing null
    STD_ASSERTREL(pString != NULL);

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

bool J3DAPI stdUtil_DirExists(const char* pPath)
{
    return stdPlatform_DirExists(pPath);
}

bool J3DAPI stdUtil_FileExists(const char* pFilename)
{
    tFileHandle fh = std_g_pHS->pFileOpen(pFilename, "r");
    if ( !fh ) {
        return false;
    }
    std_g_pHS->pFileClose(fh);
    return true;
}

uint32_t J3DAPI stdUtil_CalcChecksum(const uint8_t* pData, size_t dataSize, uint32_t seed)
{
    while ( dataSize )
    {
        seed = *pData ^ ((seed >> 31) + 2 * seed);
        --dataSize;
        ++pData;
    }

    return seed;
}
