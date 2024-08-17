#ifndef STD_STDCONSOLE_H
#define STD_STDCONSOLE_H
#include <j3dcore/j3d.h>
#include <std/types.h>
#include <std/RTI/addresses.h>

J3D_EXTERN_C_START

int J3DAPI stdConsole_Startup(const char* pTitleText, int attributes, int bShowMinimized);
int J3DAPI stdConsole_SetAttributes(WORD wAttributes);
int J3DAPI stdConsole_SetConsoleTextAttribute(WORD wAttributes);
int J3DAPI stdConsole_InitOutputConsole();
int J3DAPI stdConsole_WriteConsole(const char* pStr, uint32_t textAttribute);

// Helper hooking functions
void stdConsole_InstallHooks(void);
void stdConsole_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // STD_STDCONSOLE_H
