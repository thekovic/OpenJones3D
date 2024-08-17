#include "JonesConsole.h"
#include <j3dcore/j3dhook.h>
#include <Jones3D/RTI/symbols.h>

#define JonesConsole_aVersion J3D_DECL_FAR_ARRAYVAR(JonesConsole_aVersion, const char(*)[128])
#define JonesConsole_aCmdLine J3D_DECL_FAR_ARRAYVAR(JonesConsole_aCmdLine, char(*)[128])
#define JonesConsole_aBuffers J3D_DECL_FAR_ARRAYVAR(JonesConsole_aBuffers, JonesConsoleTextLine(*)[15])
#define JonesConsole_nextIndex J3D_DECL_FAR_VAR(JonesConsole_nextIndex, int)
#define JonesConsole_aUnused_552770 J3D_DECL_FAR_ARRAYVAR(JonesConsole_aUnused_552770, char(*)[2304])
#define JonesConsole_cursorPos J3D_DECL_FAR_VAR(JonesConsole_cursorPos, int)
#define JonesConsole_pFont J3D_DECL_FAR_VAR(JonesConsole_pFont, rdFont*)
#define JonesConsole_bOpened J3D_DECL_FAR_VAR(JonesConsole_bOpened, int)
#define JonesConsole_pFuncHashtbl J3D_DECL_FAR_VAR(JonesConsole_pFuncHashtbl, tHashTable*)

void JonesConsole_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(JonesConsole_Startup);
    // J3D_HOOKFUNC(JonesConsole_Shutdown);
    // J3D_HOOKFUNC(JonesConsole_Open);
    // J3D_HOOKFUNC(JonesConsole_Close);
    // J3D_HOOKFUNC(JonesConsole_FlushToDisplay);
    // J3D_HOOKFUNC(JonesConsole_PrintText);
    // J3D_HOOKFUNC(JonesConsole_PrintTextWithID);
    // J3D_HOOKFUNC(JonesConsole_ClearText);
    // J3D_HOOKFUNC(JonesConsole_ExeCommand);
    // J3D_HOOKFUNC(JonesConsole_ShowConsole);
    // J3D_HOOKFUNC(JonesConsole_HandelChar);
    // J3D_HOOKFUNC(JonesConsole_FlushCommandLine);
    // J3D_HOOKFUNC(JonesConsole_HideConsole);
    // J3D_HOOKFUNC(JonesConsole_PrintVersion);
    // J3D_HOOKFUNC(JonesConsole_PrintFramerate);
    // J3D_HOOKFUNC(JonesConsole_PrintPolys);
    // J3D_HOOKFUNC(JonesConsole_ShowEndCredits);
    // J3D_HOOKFUNC(JonesConsole_RemoveExpired);
}

void JonesConsole_ResetGlobals(void)
{
    const char JonesConsole_aVersion_tmp[128] = {
      'O',
      'c',
      't',
      ' ',
      '2',
      '9',
      ' ',
      '1',
      '9',
      '9',
      '9',
      ',',
      '1',
      '2',
      ':',
      '0',
      '9',
      ':',
      '1',
      '4',
      ' ',
      'R',
      'e',
      'l',
      'e',
      'a',
      's',
      'e',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0',
      '\0'
    };
    memcpy((char *)&JonesConsole_aVersion, &JonesConsole_aVersion_tmp, sizeof(JonesConsole_aVersion));
    
    memset(&JonesConsole_aCmdLine, 0, sizeof(JonesConsole_aCmdLine));
    memset(&JonesConsole_aBuffers, 0, sizeof(JonesConsole_aBuffers));
    memset(&JonesConsole_nextIndex, 0, sizeof(JonesConsole_nextIndex));
    memset(&JonesConsole_aUnused_552770, 0, sizeof(JonesConsole_aUnused_552770));
    memset(&JonesConsole_cursorPos, 0, sizeof(JonesConsole_cursorPos));
    memset(&JonesConsole_pFont, 0, sizeof(JonesConsole_pFont));
    memset(&JonesConsole_g_bVisible, 0, sizeof(JonesConsole_g_bVisible));
    memset(&JonesConsole_g_bStarted, 0, sizeof(JonesConsole_g_bStarted));
    memset(&JonesConsole_bOpened, 0, sizeof(JonesConsole_bOpened));
    memset(&JonesConsole_pFuncHashtbl, 0, sizeof(JonesConsole_pFuncHashtbl));
}

int J3DAPI JonesConsole_Startup()
{
    return J3D_TRAMPOLINE_CALL(JonesConsole_Startup);
}

void JonesConsole_Shutdown(void)
{
    J3D_TRAMPOLINE_CALL(JonesConsole_Shutdown);
}

int JonesConsole_Open(void)
{
    return J3D_TRAMPOLINE_CALL(JonesConsole_Open);
}

void JonesConsole_Close(void)
{
    J3D_TRAMPOLINE_CALL(JonesConsole_Close);
}

void JonesConsole_FlushToDisplay(void)
{
    J3D_TRAMPOLINE_CALL(JonesConsole_FlushToDisplay);
}

size_t J3DAPI JonesConsole_PrintText(const char* pText)
{
    return J3D_TRAMPOLINE_CALL(JonesConsole_PrintText, pText);
}

void J3DAPI JonesConsole_PrintTextWithID(int ID, const char* pText)
{
    J3D_TRAMPOLINE_CALL(JonesConsole_PrintTextWithID, ID, pText);
}

void J3DAPI JonesConsole_ClearText(int yourID)
{
    J3D_TRAMPOLINE_CALL(JonesConsole_ClearText, yourID);
}

int J3DAPI JonesConsole_ExeCommand(const char* pLine)
{
    return J3D_TRAMPOLINE_CALL(JonesConsole_ExeCommand, pLine);
}

void J3DAPI JonesConsole_ShowConsole()
{
    J3D_TRAMPOLINE_CALL(JonesConsole_ShowConsole);
}

void J3DAPI JonesConsole_HandelChar(char chr)
{
    J3D_TRAMPOLINE_CALL(JonesConsole_HandelChar, chr);
}

void JonesConsole_FlushCommandLine(void)
{
    J3D_TRAMPOLINE_CALL(JonesConsole_FlushCommandLine);
}

void JonesConsole_HideConsole(void)
{
    J3D_TRAMPOLINE_CALL(JonesConsole_HideConsole);
}

int J3DAPI JonesConsole_PrintVersion(const SithConsoleCommand* pFunc, const char* pArg)
{
    return J3D_TRAMPOLINE_CALL(JonesConsole_PrintVersion, pFunc, pArg);
}

int J3DAPI JonesConsole_PrintFramerate(const SithConsoleCommand* pFunc, const char* pArg)
{
    return J3D_TRAMPOLINE_CALL(JonesConsole_PrintFramerate, pFunc, pArg);
}

int J3DAPI JonesConsole_PrintPolys(const SithConsoleCommand* pFunc, const char* pArg)
{
    return J3D_TRAMPOLINE_CALL(JonesConsole_PrintPolys, pFunc, pArg);
}

int J3DAPI JonesConsole_ShowEndCredits(const SithConsoleCommand* pFunc, const char* pArg)
{
    return J3D_TRAMPOLINE_CALL(JonesConsole_ShowEndCredits, pFunc, pArg);
}

int J3DAPI JonesConsole_RemoveExpired()
{
    return J3D_TRAMPOLINE_CALL(JonesConsole_RemoveExpired);
}
