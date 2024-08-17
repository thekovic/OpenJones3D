#include "std.h"
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>

#define std_printBuffer J3D_DECL_FAR_ARRAYVAR(std_printBuffer, char(*)[2048])
#define std_bStdStartup J3D_DECL_FAR_VAR(std_bStdStartup, int)

void std_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(stdStartup);
    // J3D_HOOKFUNC(stdShutdown);
    // J3D_HOOKFUNC(stdPrintf);
    // J3D_HOOKFUNC(stdConsolePrintf);
    // J3D_HOOKFUNC(stdFileFromPath);
    // J3D_HOOKFUNC(stdCalcBitPos);
    // J3D_HOOKFUNC(stdFileOpen);
    // J3D_HOOKFUNC(stdFileClose);
    // J3D_HOOKFUNC(stdFileRead);
    // J3D_HOOKFUNC(stdFileWrite);
    // J3D_HOOKFUNC(stdFileGets);
    // J3D_HOOKFUNC(stdFileGetws);
    // J3D_HOOKFUNC(stdFileEof);
    // J3D_HOOKFUNC(stdFileTell);
    // J3D_HOOKFUNC(stdFileSize);
    // J3D_HOOKFUNC(stdFilePrintf);
    // J3D_HOOKFUNC(stdFileSeek);
}

void std_ResetGlobals(void)
{
    memset((char *)&std_g_aEmptyString, 0, sizeof(std_g_aEmptyString));
    memset(&std_printBuffer, 0, sizeof(std_printBuffer));
    memset(&std_bStdStartup, 0, sizeof(std_bStdStartup));
    memset(&std_g_genBuffer, 0, sizeof(std_g_genBuffer));
    memset(&std_g_pHS, 0, sizeof(std_g_pHS));
}

void J3DAPI stdStartup(tHostServices* pHS)
{
    J3D_TRAMPOLINE_CALL(stdStartup, pHS);
}

void stdShutdown(void)
{
    J3D_TRAMPOLINE_CALL(stdShutdown);
}

void stdPrintf(tPrintfFunc pfPrint, const char* pFilePath, unsigned int linenum, const char* format, ...)
{
    J3D_TRAMPOLINE_CALL(stdPrintf, pfPrint, pFilePath, linenum, format);
}

signed int stdConsolePrintf(const char* pFormat, ...)
{
    return J3D_TRAMPOLINE_CALL(stdConsolePrintf, pFormat);
}

const char* J3DAPI stdFileFromPath(const char* pPath)
{
    return J3D_TRAMPOLINE_CALL(stdFileFromPath, pPath);
}

int J3DAPI stdCalcBitPos(int a1)
{
    return J3D_TRAMPOLINE_CALL(stdCalcBitPos, a1);
}

tFileHandle J3DAPI stdFileOpen(const char* pFilename, const char* mode)
{
    return J3D_TRAMPOLINE_CALL(stdFileOpen, pFilename, mode);
}

int J3DAPI stdFileClose(tFileHandle fh)
{
    return J3D_TRAMPOLINE_CALL(stdFileClose, fh);
}

size_t J3DAPI stdFileRead(tFileHandle fh, void* pOutData, size_t size)
{
    return J3D_TRAMPOLINE_CALL(stdFileRead, fh, pOutData, size);
}

size_t J3DAPI stdFileWrite(tFileHandle fh, const void* pData, size_t size)
{
    return J3D_TRAMPOLINE_CALL(stdFileWrite, fh, pData, size);
}

char* J3DAPI stdFileGets(tFileHandle fh, char* pStr, size_t size)
{
    return J3D_TRAMPOLINE_CALL(stdFileGets, fh, pStr, size);
}

wchar_t* J3DAPI stdFileGetws(tFileHandle fh, wchar_t* pOutStr, size_t size)
{
    return J3D_TRAMPOLINE_CALL(stdFileGetws, fh, pOutStr, size);
}

int J3DAPI stdFileEof(tFileHandle fh)
{
    return J3D_TRAMPOLINE_CALL(stdFileEof, fh);
}

int J3DAPI stdFileTell(tFileHandle fh)
{
    return J3D_TRAMPOLINE_CALL(stdFileTell, fh);
}

size_t J3DAPI stdFileSize(const char* pFilePath)
{
    return J3D_TRAMPOLINE_CALL(stdFileSize, pFilePath);
}

int stdFilePrintf(tFileHandle fh, const char* pFormat, ...)
{
    return J3D_TRAMPOLINE_CALL(stdFilePrintf, fh, pFormat);
}

int J3DAPI stdFileSeek(tFileHandle pFile, int offset, int origin)
{
    return J3D_TRAMPOLINE_CALL(stdFileSeek, pFile, offset, origin);
}
