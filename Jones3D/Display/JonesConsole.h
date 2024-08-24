#ifndef JONES3D_JONESCONSOLE_H
#define JONES3D_JONESCONSOLE_H
#include <Jones3D/types.h>
#include <Jones3D/RTI/addresses.h>
#include <j3dcore/j3d.h>

#include <rdroid/types.h>
#include <sith/types.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define JonesConsole_g_bVisible J3D_DECL_FAR_VAR(JonesConsole_g_bVisible, int)
// extern int JonesConsole_g_bVisible;

#define JonesConsole_g_bStarted J3D_DECL_FAR_VAR(JonesConsole_g_bStarted, int)
// extern int JonesConsole_g_bStarted;

int J3DAPI JonesConsole_Startup();
void JonesConsole_Shutdown(void);
int JonesConsole_Open(void);
void JonesConsole_Close(void);
void JonesConsole_FlushToDisplay(void);
size_t J3DAPI JonesConsole_PrintText(const char* pText);
void J3DAPI JonesConsole_PrintTextWithID(int ID, const char* pText);
void J3DAPI JonesConsole_ClearText(int yourID);
int J3DAPI JonesConsole_ExeCommand(const char* pLine);
void J3DAPI JonesConsole_ShowConsole();
void J3DAPI JonesConsole_HandelChar(char chr);
void JonesConsole_FlushCommandLine(void);
void JonesConsole_HideConsole(void);
int J3DAPI JonesConsole_PrintVersion(const SithConsoleCommand* pFunc, const char* pArg);
int J3DAPI JonesConsole_PrintFramerate(const SithConsoleCommand* pFunc, const char* pArg);
int J3DAPI JonesConsole_PrintPolys(const SithConsoleCommand* pFunc, const char* pArg);
int J3DAPI JonesConsole_ShowEndCredits(const SithConsoleCommand* pFunc, const char* pArg);
int J3DAPI JonesConsole_RemoveExpired();

// Helper hooking functions
void JonesConsole_InstallHooks(void);
void JonesConsole_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // JONES3D_JONESCONSOLE_H
