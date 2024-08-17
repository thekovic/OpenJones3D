#ifndef SITH_SITHCONSOLE_H
#define SITH_SITHCONSOLE_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

int J3DAPI sithConsole_Startup();
void J3DAPI sithConsole_Shutdown();
int J3DAPI sithConsole_Open(int bufSize, int numCommands);
void sithConsole_Close();
void J3DAPI sithConsole_PrintString(const char* pString);
void J3DAPI sithConsole_PrintWString(wchar_t* pwString);
int J3DAPI sithConsole_ExeCommand(const char* pLine);
void sithConsole_Flush(void);
int J3DAPI sithConsole_RegisterCommand(SithConsoleFunction pfFunc, const char* pName, int flags);
void J3DAPI sithConsole_RegisterPrintFunctions(SithConsoleWriteTextFunc pfWriteText, SithConsoleWriteWideTextFunc pfWriteWText, SithConsoleFlush pfFlush);
int J3DAPI sithConsole_CreateCommandTable(int size);
void J3DAPI sithConsole_FreeCommandTable();

// Helper hooking functions
void sithConsole_InstallHooks(void);
void sithConsole_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHCONSOLE_H
