#include "stdConsole.h"
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>

#define stdConsole_hOutput J3D_DECL_FAR_VAR(stdConsole_hOutput, HANDLE)
#define stdConsole_textAttribute J3D_DECL_FAR_VAR(stdConsole_textAttribute, int)
#define stdConsole_wAttributes J3D_DECL_FAR_VAR(stdConsole_wAttributes, WORD)
#define stdConsole_dword_5DCCCC J3D_DECL_FAR_VAR(stdConsole_dword_5DCCCC, int)
#define stdConsole_hInput J3D_DECL_FAR_VAR(stdConsole_hInput, HANDLE)
#define stdConsole_dword_5DCCD8 J3D_DECL_FAR_VAR(stdConsole_dword_5DCCD8, int)
#define stdConsole_dword_5DCCDC J3D_DECL_FAR_VAR(stdConsole_dword_5DCCDC, int)

void stdConsole_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(stdConsole_Startup);
    // J3D_HOOKFUNC(stdConsole_SetAttributes);
    // J3D_HOOKFUNC(stdConsole_SetConsoleTextAttribute);
    // J3D_HOOKFUNC(stdConsole_InitOutputConsole);
    // J3D_HOOKFUNC(stdConsole_WriteConsole);
}

void stdConsole_ResetGlobals(void)
{
    memset(&stdConsole_hOutput, 0, sizeof(stdConsole_hOutput));
    memset(&stdConsole_textAttribute, 0, sizeof(stdConsole_textAttribute));
    memset(&stdConsole_wAttributes, 0, sizeof(stdConsole_wAttributes));
    memset(&stdConsole_dword_5DCCCC, 0, sizeof(stdConsole_dword_5DCCCC));
    memset(&stdConsole_hInput, 0, sizeof(stdConsole_hInput));
    memset(&stdConsole_dword_5DCCD8, 0, sizeof(stdConsole_dword_5DCCD8));
    memset(&stdConsole_dword_5DCCDC, 0, sizeof(stdConsole_dword_5DCCDC));
}

int J3DAPI stdConsole_Startup(const char* pTitleText, int attributes, int bShowMinimized)
{
    return J3D_TRAMPOLINE_CALL(stdConsole_Startup, pTitleText, attributes, bShowMinimized);
}

int J3DAPI stdConsole_SetAttributes(WORD wAttributes)
{
    return J3D_TRAMPOLINE_CALL(stdConsole_SetAttributes, wAttributes);
}

int J3DAPI stdConsole_SetConsoleTextAttribute(WORD wAttributes)
{
    return J3D_TRAMPOLINE_CALL(stdConsole_SetConsoleTextAttribute, wAttributes);
}

int J3DAPI stdConsole_InitOutputConsole()
{
    return J3D_TRAMPOLINE_CALL(stdConsole_InitOutputConsole);
}

int J3DAPI stdConsole_WriteConsole(const char* pStr, uint32_t textAttribute)
{
    return J3D_TRAMPOLINE_CALL(stdConsole_WriteConsole, pStr, textAttribute);
}
