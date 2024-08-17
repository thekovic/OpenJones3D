#include "stdConffile.h"
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>

#define stdConffile_aWriteFilename J3D_DECL_FAR_ARRAYVAR(stdConffile_aWriteFilename, char(*)[128])
#define stdConffile_aFilenameStack J3D_DECL_FAR_ARRAYVAR(stdConffile_aFilenameStack, char(*)[20][128])
#define stdConffile_apBufferStack J3D_DECL_FAR_ARRAYVAR(stdConffile_apBufferStack, char*(*)[20])
#define stdConffile_linenumStack J3D_DECL_FAR_ARRAYVAR(stdConffile_linenumStack, size_t(*)[20])
#define stdConffile_pFilename J3D_DECL_FAR_ARRAYVAR(stdConffile_pFilename, char(*)[128])
#define stdConffile_aEntryStack J3D_DECL_FAR_ARRAYVAR(stdConffile_aEntryStack, StdConffileEntry(*)[20])
#define stdConffile_openFileStack J3D_DECL_FAR_ARRAYVAR(stdConffile_openFileStack, tFileHandle(*)[20])
#define stdConffile_linenum J3D_DECL_FAR_VAR(stdConffile_linenum, size_t)
#define stdConffile_bOpen J3D_DECL_FAR_VAR(stdConffile_bOpen, int)
#define stdConffile_openFile J3D_DECL_FAR_VAR(stdConffile_openFile, tFileHandle)
#define stdConffile_writeFile J3D_DECL_FAR_VAR(stdConffile_writeFile, tFileHandle)
#define stdConffile_stackLevel J3D_DECL_FAR_VAR(stdConffile_stackLevel, size_t)

void stdConffile_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(stdConffile_Open);
    // J3D_HOOKFUNC(stdConffile_OpenWrite);
    // J3D_HOOKFUNC(stdConffile_OpenMode);
    // J3D_HOOKFUNC(stdConffile_Close);
    // J3D_HOOKFUNC(stdConffile_CloseWrite);
    // J3D_HOOKFUNC(stdConffile_Write);
    // J3D_HOOKFUNC(stdConffile_Read);
    // J3D_HOOKFUNC(stdConffile_ReadArgsFromStr);
    // J3D_HOOKFUNC(stdConffile_ReadArgs);
    // J3D_HOOKFUNC(stdConffile_ReadLine);
    // J3D_HOOKFUNC(stdConffile_GetFileHandle);
    // J3D_HOOKFUNC(stdConffile_GetLineNumber);
    // J3D_HOOKFUNC(stdConffile_GetFilename);
    // J3D_HOOKFUNC(stdConffile_PushStack);
    // J3D_HOOKFUNC(stdConffile_PopStack);
}

void stdConffile_ResetGlobals(void)
{
    memset(&stdConffile_aWriteFilename, 0, sizeof(stdConffile_aWriteFilename));
    memset(&stdConffile_aFilenameStack, 0, sizeof(stdConffile_aFilenameStack));
    memset(&stdConffile_apBufferStack, 0, sizeof(stdConffile_apBufferStack));
    memset(&stdConffile_linenumStack, 0, sizeof(stdConffile_linenumStack));
    memset(&stdConffile_pFilename, 0, sizeof(stdConffile_pFilename));
    memset(&stdConffile_aEntryStack, 0, sizeof(stdConffile_aEntryStack));
    memset(&stdConffile_openFileStack, 0, sizeof(stdConffile_openFileStack));
    memset(&stdConffile_linenum, 0, sizeof(stdConffile_linenum));
    memset(&stdConffile_bOpen, 0, sizeof(stdConffile_bOpen));
    memset(&stdConffile_openFile, 0, sizeof(stdConffile_openFile));
    memset(&stdConffile_writeFile, 0, sizeof(stdConffile_writeFile));
    memset(&stdConffile_stackLevel, 0, sizeof(stdConffile_stackLevel));
    memset(&stdConffile_g_entry, 0, sizeof(stdConffile_g_entry));
    memset(&stdConffile_g_aLine, 0, sizeof(stdConffile_g_aLine));
}

int J3DAPI stdConffile_Open(const char* pFilename)
{
    return J3D_TRAMPOLINE_CALL(stdConffile_Open, pFilename);
}

int J3DAPI stdConffile_OpenWrite(const char* pFilename)
{
    return J3D_TRAMPOLINE_CALL(stdConffile_OpenWrite, pFilename);
}

int J3DAPI stdConffile_OpenMode(const char* pFilename, const char* openMode)
{
    return J3D_TRAMPOLINE_CALL(stdConffile_OpenMode, pFilename, openMode);
}

void stdConffile_Close(void)
{
    J3D_TRAMPOLINE_CALL(stdConffile_Close);
}

void stdConffile_CloseWrite(void)
{
    J3D_TRAMPOLINE_CALL(stdConffile_CloseWrite);
}

int J3DAPI stdConffile_Write(const void* pData, int size)
{
    return J3D_TRAMPOLINE_CALL(stdConffile_Write, pData, size);
}

int J3DAPI stdConffile_Read(void* pData, size_t size)
{
    return J3D_TRAMPOLINE_CALL(stdConffile_Read, pData, size);
}

int J3DAPI stdConffile_ReadArgsFromStr(char* pStr)
{
    return J3D_TRAMPOLINE_CALL(stdConffile_ReadArgsFromStr, pStr);
}

int stdConffile_ReadArgs(void)
{
    return J3D_TRAMPOLINE_CALL(stdConffile_ReadArgs);
}

int stdConffile_ReadLine(void)
{
    return J3D_TRAMPOLINE_CALL(stdConffile_ReadLine);
}

tFileHandle stdConffile_GetFileHandle(void)
{
    return J3D_TRAMPOLINE_CALL(stdConffile_GetFileHandle);
}

int stdConffile_GetLineNumber(void)
{
    return J3D_TRAMPOLINE_CALL(stdConffile_GetLineNumber);
}

const char* stdConffile_GetFilename(void)
{
    return J3D_TRAMPOLINE_CALL(stdConffile_GetFilename);
}

void stdConffile_PushStack(void)
{
    J3D_TRAMPOLINE_CALL(stdConffile_PushStack);
}

void stdConffile_PopStack(void)
{
    J3D_TRAMPOLINE_CALL(stdConffile_PopStack);
}
