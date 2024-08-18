#include "JonesMain.h"
#include <j3dcore/j3dhook.h>
#include <Jones3D/RTI/symbols.h>

#include <sith/DSS/sithGamesave.h>
#include <sith/World/sithWorld.h>

#include <std/General/std.h>
#include <std/General/stdUtil.h>

#define JonesMain_curGamesaveState J3D_DECL_FAR_VAR(JonesMain_curGamesaveState, int)
#define JonesMain_aOpenMenuKeyIds J3D_DECL_FAR_ARRAYVAR(JonesMain_aOpenMenuKeyIds, int(*)[8])
#define JonesMain_introVideoMode J3D_DECL_FAR_VAR(JonesMain_introVideoMode, int)
#define JonesMain_hs J3D_DECL_FAR_VAR(JonesMain_hs, tHostServices)
#define JonesMain_bNoProcessWndEvents J3D_DECL_FAR_VAR(JonesMain_bNoProcessWndEvents, int)
#define JonesMain_circBuf J3D_DECL_FAR_VAR(JonesMain_circBuf, tCircularBuffer)
#define JonesMain_pLogFile J3D_DECL_FAR_VAR(JonesMain_pLogFile, FILE*)
#define JonesMain_bPrintFramerate J3D_DECL_FAR_VAR(JonesMain_bPrintFramerate, int)
#define JonesMain_dword_555488 J3D_DECL_FAR_VAR(JonesMain_dword_555488, int)
#define JonesMain_bGamePaused J3D_DECL_FAR_VAR(JonesMain_bGamePaused, int)
#define JonesMain_bOpen J3D_DECL_FAR_VAR(JonesMain_bOpen, int)
#define JonesMain_pNdsFileName J3D_DECL_FAR_ARRAYVAR(JonesMain_pNdsFileName, char(*)[128])
#define JonesMain_pDisplayEnv J3D_DECL_FAR_VAR(JonesMain_pDisplayEnv, StdDisplayEnvironment*)
#define JonesMain_bRefreshDisplayDevice J3D_DECL_FAR_VAR(JonesMain_bRefreshDisplayDevice, int)
#define JonesMain_bSystemSuspended J3D_DECL_FAR_VAR(JonesMain_bSystemSuspended, int)
#define JonesMain_bMouseLButtomUp J3D_DECL_FAR_VAR(JonesMain_bMouseLButtomUp, int)
#define JonesMain_pIntroVideoBuf J3D_DECL_FAR_VAR(JonesMain_pIntroVideoBuf, void*)
#define JonesMain_bPrintQuickSave J3D_DECL_FAR_VAR(JonesMain_bPrintQuickSave, int)
#define JonesMain_bAppActivated J3D_DECL_FAR_VAR(JonesMain_bAppActivated, int)
#define JonesMain_pfCurProcess J3D_DECL_FAR_VAR(JonesMain_pfCurProcess, JonesMainProcessFunc)
#define JonesMain_bEndCredits J3D_DECL_FAR_VAR(JonesMain_bEndCredits, int)
#define JonesMain_hSndCredits J3D_DECL_FAR_VAR(JonesMain_hSndCredits, int)
#define JonesMain_hCreditsMusic J3D_DECL_FAR_VAR(JonesMain_hCreditsMusic, tSoundChannelHandle)
#define JonesMain_bMenuVisible J3D_DECL_FAR_VAR(JonesMain_bMenuVisible, int)
#define JonesMain_bDisplayError J3D_DECL_FAR_VAR(JonesMain_bDisplayError, int)
#define JonesMain_frameRate J3D_DECL_FAR_VAR(JonesMain_frameRate, float)
#define JonesMain_frameCount J3D_DECL_FAR_VAR(JonesMain_frameCount, int)
#define JonesMain_frameCount0 J3D_DECL_FAR_VAR(JonesMain_frameCount0, int)
#define JonesMain_frameTime J3D_DECL_FAR_VAR(JonesMain_frameTime, int)
#define JonesMain_frameTime0 J3D_DECL_FAR_VAR(JonesMain_frameTime0, int)
#define JonesMain_bEnteredOnce J3D_DECL_FAR_VAR(JonesMain_bEnteredOnce, int)
#define JonesMain_curVideoMode J3D_DECL_FAR_VAR(JonesMain_curVideoMode, StdVideoMode)
#define JonesMain_pStartupDisplayEnv J3D_DECL_FAR_VAR(JonesMain_pStartupDisplayEnv, StdDisplayEnvironment*)

#define JonesMain_aCndLevelLoadInfos J3D_DECL_FAR_ARRAYVAR(JonesMain_aCndLevelLoadInfos, const JonesLevelInfo(*)[18])


#define JonesMain_aNdyLevelLoadInfos J3D_DECL_FAR_ARRAYVAR(JonesMain_aNdyLevelLoadInfos, const JonesLevelInfo(*)[18])


#define JonesMain_pfProcess J3D_DECL_FAR_VAR(JonesMain_pfProcess, JonesMainProcessFunc)


#define JonesMain_curLevelNum J3D_DECL_FAR_VAR(JonesMain_curLevelNum, int)


#define JonesMain_state J3D_DECL_FAR_VAR(JonesMain_state, JonesState)


void JonesMain_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(JonesMain_Startup);
    // J3D_HOOKFUNC(JonesMain_GameWndProc);
    // J3D_HOOKFUNC(JonesMain_HandleWMGetMinMaxInfo);
    // J3D_HOOKFUNC(JonesMain_HandleWMPaint);
    // J3D_HOOKFUNC(JonesMain_HandleWMTimer);
    // J3D_HOOKFUNC(JonesMain_HandleWMKeydown);
    // J3D_HOOKFUNC(JonesMain_PrintQuickSave);
    // J3D_HOOKFUNC(JonesMain_HandleWMActivateApp);
    // J3D_HOOKFUNC(JonesMain_HandleWMActivate);
    // J3D_HOOKFUNC(JonesMain_OnAppActivate);
    // J3D_HOOKFUNC(JonesMain_HandleWMChar);
    // J3D_HOOKFUNC(JonesMain_HandleWMSysCommand);
    // J3D_HOOKFUNC(JonesMain_HandleWMPowerBroadcast);
    // J3D_HOOKFUNC(JonesMain_Shutdown);
    // J3D_HOOKFUNC(JonesMain_PauseGame);
    // J3D_HOOKFUNC(JonesMain_ResumeGame);
    // J3D_HOOKFUNC(JonesMain_IsGamePaused);
    // J3D_HOOKFUNC(JonesMain_Process);
    // J3D_HOOKFUNC(JonesMain_ProcessWindowEvents);
    // J3D_HOOKFUNC(JonesMain_ProcessGame);
    // J3D_HOOKFUNC(JonesMain_ProcessMenu);
    // J3D_HOOKFUNC(JonesMain_PrintFramerate);
    // J3D_HOOKFUNC(JonesMain_TogglePrintFramerate);
    // J3D_HOOKFUNC(JonesMain_Open);
    // J3D_HOOKFUNC(JonesMain_EnsureFile);
    // J3D_HOOKFUNC(JonesMain_Close);
    // J3D_HOOKFUNC(JonesMain_Restore);
    // J3D_HOOKFUNC(JonesMain_ProcessGamesaveState);
    // J3D_HOOKFUNC(JonesMain_UpdateLevelNum);
    // J3D_HOOKFUNC(JonesMain_ProcessEndLevel);
    // J3D_HOOKFUNC(JonesMain_SetBonusLevel);
    // J3D_HOOKFUNC(JonesMain_ShowEndCredits);
    // J3D_HOOKFUNC(JonesMain_Credits);
    // J3D_HOOKFUNC(JonesMain_IsOpen);
    // J3D_HOOKFUNC(JonesMain_GetDisplayEnvironment);
    // J3D_HOOKFUNC(JonesMain_GetDisplaySettings);
    // J3D_HOOKFUNC(JonesMain_CloseWindow);
    // J3D_HOOKFUNC(JonesMain_FilePrintf);
    // J3D_HOOKFUNC(JonesMain_Printf);
    // J3D_HOOKFUNC(JonesMain_RefreshDisplayDevice);
    // J3D_HOOKFUNC(JonesMain_PlayIntro);
    // J3D_HOOKFUNC(JonesMain_IntroWndProc);
    // J3D_HOOKFUNC(JonesMain_HandleWMLButtonUp);
    // J3D_HOOKFUNC(JonesMain_IntroHandleKeydown);
    // J3D_HOOKFUNC(JonesMain_IntroMovieBll565);
    // J3D_HOOKFUNC(JonesMain_IntroMovieBlt555);
    // J3D_HOOKFUNC(JonesMain_IntroMovieBlt32);
    // J3D_HOOKFUNC(JonesMain_Assert);
    // J3D_HOOKFUNC(JonesMain_BindInventoryControlKeys);
    // J3D_HOOKFUNC(JonesMain_ResetHUD);
    // J3D_HOOKFUNC(JonesMain_SaveHUD);
    // J3D_HOOKFUNC(JonesMain_RestoreHUD);
    // J3D_HOOKFUNC(JonesMain_GetCurrentLevelNum);
    // J3D_HOOKFUNC(JonesMain_LogErrorToFile);
    // J3D_HOOKFUNC(JonesMain_LoadSettings);
    // J3D_HOOKFUNC(JonesMain_ShowDevDialog);
    // J3D_HOOKFUNC(JonesMain_DevDialogProc);
    // J3D_HOOKFUNC(JonesMain_InitDevDialog);
    // J3D_HOOKFUNC(JonesMain_DevDialogHandleCommand);
    // J3D_HOOKFUNC(JonesMain_DevDialogInitDisplayDevices);
    // J3D_HOOKFUNC(JonesMain_DevDialogUpdateRadioButtons);
    // J3D_HOOKFUNC(JonesMain_FindClosestVideoMode);
    // J3D_HOOKFUNC(JonesMain_CurDisplaySupportsBPP);
}

void JonesMain_ResetGlobals(void)
{
    const JonesLevelInfo JonesMain_g_aCndLevelLoadInfos_tmp[18] = {
      { NULL, "mat\\teo_amap", { -5.0f, 358.0f }, { 366.0f, 221.0f }, 0, NULL },
      {
        "00_CYN.cnd",
        "mat\\cyn_amap",
        { -5.0f, 187.0f },
        { 345.0f, 344.0f },
        1,
        "CANYONLANDS"
      },
      {
        "01_BAB.cnd",
        "mat\\bab_amap",
        { -5.0f, 163.0f },
        { 419.0f, 251.0f },
        1,
        "BABYLON"
      },
      {
        "02_RIV.cnd",
        "mat\\riv_amap",
        { -5.0f, 344.0f },
        { 423.0f, 130.0f },
        0,
        "TIAN SHAN RIVER"
      },
      {
        "03_SHS.cnd",
        "mat\\shs_amap",
        { 150.0f, 512.0f },
        { 397.0f, 274.0f },
        0,
        "SHAMBALA SANCTUARY"
      },
      {
        "05_LAG.cnd",
        "mat\\lag_amap",
        { -5.0f, 147.0f },
        { 435.0f, 380.0f },
        1,
        "PALAWAN LAGOON"
      },
      {
        "06_VOL.cnd",
        "mat\\vol_amap",
        { -5.0f, 184.0f },
        { 330.0f, 269.0f },
        0,
        "PALAWAN VOLCANO"
      },
      {
        "07_TEM.cnd",
        "mat\\tem_amap",
        { -5.0f, 127.0f },
        { 349.0f, 312.0f },
        0,
        "PALAWAN TEMPLE"
      },
      {
        "16_JEP.cnd",
        "mat\\jep_amap",
        { -5.0f, 223.0f },
        { 370.0f, 309.0f },
        1,
        "JEEP"
      },
      {
        "08_TEO.cnd",
        "mat\\teo_amap",
        { -5.0f, 358.0f },
        { 365.0f, 221.0f },
        1,
        "TEOTIAACAN"
      },
      {
        "09_OLV.cnd",
        "mat\\olv_amap",
        { -5.0f, 277.0f },
        { 413.0f, 257.0f },
        0,
        "OLMEC VALLEY"
      },
      {
        "10_SEA.cnd",
        "mat\\sea_amap",
        { -5.0f, 252.0f },
        { 380.0f, 199.0f },
        0,
        "PUDOVKIN SHIP"
      },
      {
        "11_PYR.cnd",
        "mat\\pyr_amap",
        { -5.0f, 243.0f },
        { 421.0f, 391.0f },
        1,
        "MEROE PYRAMIDS"
      },
      {
        "12_SOL.cnd",
        "mat\\sol_amap",
        { -5.0f, 208.0f },
        { 348.0f, 266.0f },
        1,
        "SOLOMON'S MINES"
      },
      {
        "13_NUB.cnd",
        "mat\\nub_amap",
        { -5.0f, 237.0f },
        { 383.0f, 245.0f },
        0,
        "NUB'S TOMB"
      },
      {
        "14_INF.cnd",
        "mat\\inf_amap",
        { 85.0f, 485.0f },
        { 395.0f, 224.0f },
        0,
        "INFERNAL MACHINE"
      },
      {
        "15_AET.cnd",
        "mat\\aet_amap",
        { 329.0f, -5.0f },
        { 329.0f, 316.0f },
        1,
        "AETHERIUM"
      },
      {
        "17_PRU.cnd",
        "mat\\pru_amap",
        { 565.0f, -5.0f },
        { 176.0f, 341.0f },
        1,
        "RETURN TO PERU"
      }
    };
    memcpy((JonesLevelInfo*)&JonesMain_aCndLevelLoadInfos, &JonesMain_g_aCndLevelLoadInfos_tmp, sizeof(JonesMain_aCndLevelLoadInfos));

    const JonesLevelInfo JonesMain_g_aNdyLevelLoadInfos_tmp[18] = {
      { NULL, "mat\\teo_amap", { -5.0f, 358.0f }, { 366.0f, 221.0f }, 1, NULL },
      {
        "00_CYN.ndy",
        "mat\\cyn_amap",
        { -5.0f, 187.0f },
        { 345.0f, 344.0f },
        1,
        "CANYONLANDS"
      },
      {
        "01_BAB.ndy",
        "mat\\bab_amap",
        { -5.0f, 163.0f },
        { 419.0f, 251.0f },
        1,
        "BABYLON"
      },
      {
        "02_RIV.ndy",
        "mat\\riv_amap",
        { -5.0f, 344.0f },
        { 423.0f, 130.0f },
        1,
        "TIAN SHAN RIVER"
      },
      {
        "03_SHS.ndy",
        "mat\\shs_amap",
        { 150.0f, 512.0f },
        { 397.0f, 274.0f },
        1,
        "SHAMBALA SANCTUARY"
      },
      {
        "05_LAG.ndy",
        "mat\\lag_amap",
        { -5.0f, 147.0f },
        { 435.0f, 380.0f },
        1,
        "PALAWAN LAGOON"
      },
      {
        "06_VOL.ndy",
        "mat\\vol_amap",
        { -5.0f, 184.0f },
        { 330.0f, 267.0f },
        1,
        "PALAWAN VOLCANO"
      },
      {
        "07_TEM.ndy",
        "mat\\tem_amap",
        { -5.0f, 127.0f },
        { 349.0f, 312.0f },
        1,
        "PALAWAN TEMPLE"
      },
      {
        "16_JEP.ndy",
        "mat\\jep_amap",
        { -5.0f, 223.0f },
        { 370.0f, 308.0f },
        1,
        "JEEP"
      },
      {
        "08_TEO.ndy",
        "mat\\teo_amap",
        { -5.0f, 358.0f },
        { 365.0f, 221.0f },
        1,
        "TEOTIAACAN"
      },
      {
        "09_OLV.ndy",
        "mat\\olv_amap",
        { -5.0f, 277.0f },
        { 413.0f, 257.0f },
        1,
        "OLMEC VALLEY"
      },
      {
        "10_SEA.ndy",
        "mat\\sea_amap",
        { -5.0f, 252.0f },
        { 380.0f, 199.0f },
        1,
        "PUDOVKIN SHIP"
      },
      {
        "11_PYR.ndy",
        "mat\\pyr_amap",
        { -5.0f, 243.0f },
        { 421.0f, 391.0f },
        1,
        "MEROE PYRAMIDS"
      },
      {
        "12_SOL.ndy",
        "mat\\sol_amap",
        { -5.0f, 208.0f },
        { 348.0f, 266.0f },
        1,
        "SOLOMON'S MINES"
      },
      {
        "13_NUB.ndy",
        "mat\\nub_amap",
        { -5.0f, 237.0f },
        { 383.0f, 245.0f },
        1,
        "NUB'S TOMB"
      },
      {
        "14_INF.ndy",
        "mat\\inf_amap",
        { 85.0f, 485.0f },
        { 395.0f, 224.0f },
        1,
        "INFERNAL MACHINE"
      },
      {
        "15_AET.ndy",
        "mat\\aet_amap",
        { 327.0f, -5.0f },
        { 327.0f, 316.0f },
        1,
        "AETHERIUM"
      },
      {
        "17_PRU.ndy",
        "mat\\pru_amap",
        { 565.0f, -5.0f },
        { 176.0f, 340.0f },
        1,
        "RETURN TO PERU"
      }
    };
    memcpy((JonesLevelInfo*)&JonesMain_aNdyLevelLoadInfos, &JonesMain_g_aNdyLevelLoadInfos_tmp, sizeof(JonesMain_aNdyLevelLoadInfos));

    JonesMainProcessFunc JonesMain_g_pfProcess_tmp = &JonesMain_ProcessGame;
    memcpy(&JonesMain_pfProcess, &JonesMain_g_pfProcess_tmp, sizeof(JonesMain_pfProcess));

    char JonesMain_g_aErrorBuffer_tmp[1024] = "Unknown error";
    memcpy(&JonesMain_g_aErrorBuffer, &JonesMain_g_aErrorBuffer_tmp, sizeof(JonesMain_g_aErrorBuffer));

    memset(&JonesMain_curLevelNum, 0, sizeof(JonesMain_curLevelNum));
    memset(&JonesMain_curGamesaveState, 0, sizeof(JonesMain_curGamesaveState));
    memset(&JonesMain_aOpenMenuKeyIds, 0, sizeof(JonesMain_aOpenMenuKeyIds));
    memset(&JonesMain_introVideoMode, 0, sizeof(JonesMain_introVideoMode));
    memset(&JonesMain_state, 0, sizeof(JonesMain_state));
    memset(&JonesMain_hs, 0, sizeof(JonesMain_hs));
    memset(&JonesMain_bNoProcessWndEvents, 0, sizeof(JonesMain_bNoProcessWndEvents));
    memset(&JonesMain_circBuf, 0, sizeof(JonesMain_circBuf));
    memset(&JonesMain_pLogFile, 0, sizeof(JonesMain_pLogFile));
    memset(&JonesMain_g_mainMutex, 0, sizeof(JonesMain_g_mainMutex));
    memset(&JonesMain_bPrintFramerate, 0, sizeof(JonesMain_bPrintFramerate));
    memset(&JonesMain_dword_555488, 0, sizeof(JonesMain_dword_555488));
    memset(&JonesMain_bGamePaused, 0, sizeof(JonesMain_bGamePaused));
    memset(&JonesMain_bOpen, 0, sizeof(JonesMain_bOpen));
    memset(&JonesMain_pNdsFileName, 0, sizeof(JonesMain_pNdsFileName));
    memset(&JonesMain_pDisplayEnv, 0, sizeof(JonesMain_pDisplayEnv));
    memset(&JonesMain_bRefreshDisplayDevice, 0, sizeof(JonesMain_bRefreshDisplayDevice));
    memset(&JonesMain_bSystemSuspended, 0, sizeof(JonesMain_bSystemSuspended));
    memset(&JonesMain_bMouseLButtomUp, 0, sizeof(JonesMain_bMouseLButtomUp));
    memset(&JonesMain_pIntroVideoBuf, 0, sizeof(JonesMain_pIntroVideoBuf));
    memset(&JonesMain_bPrintQuickSave, 0, sizeof(JonesMain_bPrintQuickSave));
    memset(&JonesMain_bAppActivated, 0, sizeof(JonesMain_bAppActivated));
    memset(&JonesMain_pfCurProcess, 0, sizeof(JonesMain_pfCurProcess));
    memset(&JonesMain_bEndCredits, 0, sizeof(JonesMain_bEndCredits));
    memset(&JonesMain_hSndCredits, 0, sizeof(JonesMain_hSndCredits));
    memset(&JonesMain_hCreditsMusic, 0, sizeof(JonesMain_hCreditsMusic));
    memset(&JonesMain_bMenuVisible, 0, sizeof(JonesMain_bMenuVisible));
    memset(&JonesMain_bDisplayError, 0, sizeof(JonesMain_bDisplayError));
    memset(&JonesMain_frameRate, 0, sizeof(JonesMain_frameRate));
    memset(&JonesMain_frameCount, 0, sizeof(JonesMain_frameCount));
    memset(&JonesMain_frameCount0, 0, sizeof(JonesMain_frameCount0));
    memset(&JonesMain_frameTime, 0, sizeof(JonesMain_frameTime));
    memset(&JonesMain_frameTime0, 0, sizeof(JonesMain_frameTime0));
    memset(&JonesMain_bEnteredOnce, 0, sizeof(JonesMain_bEnteredOnce));
    memset(&JonesMain_curVideoMode, 0, sizeof(JonesMain_curVideoMode));
    memset(&JonesMain_pStartupDisplayEnv, 0, sizeof(JonesMain_pStartupDisplayEnv));
}

int J3DAPI JonesMain_Startup(const char* lpCmdLine)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_Startup, lpCmdLine);
}

int J3DAPI JonesMain_GameWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_GameWndProc, hWnd, uMsg, wParam, lParam);
}

void J3DAPI JonesMain_HandleWMGetMinMaxInfo(HWND hwnd, LPMINMAXINFO pMinMaxInfo)
{
    J3D_TRAMPOLINE_CALL(JonesMain_HandleWMGetMinMaxInfo, hwnd, pMinMaxInfo);
}

void J3DAPI JonesMain_HandleWMPaint(HWND hWnd)
{
    J3D_TRAMPOLINE_CALL(JonesMain_HandleWMPaint, hWnd);
}

int J3DAPI JonesMain_HandleWMTimer(HWND hWnd)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_HandleWMTimer, hWnd);
}

void J3DAPI JonesMain_HandleWMKeydown(HWND hWnd, WPARAM vk, int a3, unsigned int lParam, int exkeyflags)
{
    J3D_TRAMPOLINE_CALL(JonesMain_HandleWMKeydown, hWnd, vk, a3, lParam, exkeyflags);
}

void JonesMain_PrintQuickSave(void)
{
    J3D_TRAMPOLINE_CALL(JonesMain_PrintQuickSave);
}

int J3DAPI JonesMain_HandleWMActivateApp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_HandleWMActivateApp, hWnd, wParam, lParam);
}

LRESULT J3DAPI JonesMain_HandleWMActivate(HWND hWnd, int wParam, LPARAM lParamLo, int lParamHi)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_HandleWMActivate, hWnd, wParam, lParamLo, lParamHi);
}

void J3DAPI JonesMain_OnAppActivate(HWND hWnd, int bActivated)
{
    J3D_TRAMPOLINE_CALL(JonesMain_OnAppActivate, hWnd, bActivated);
}

void J3DAPI JonesMain_HandleWMChar(HWND hwnd, char chr)
{
    J3D_TRAMPOLINE_CALL(JonesMain_HandleWMChar, hwnd, chr);
}

void J3DAPI JonesMain_HandleWMSysCommand(HWND hWnd, WPARAM wParam)
{
    J3D_TRAMPOLINE_CALL(JonesMain_HandleWMSysCommand, hWnd, wParam);
}

void J3DAPI JonesMain_HandleWMPowerBroadcast(HWND hWnd, WPARAM wParam)
{
    J3D_TRAMPOLINE_CALL(JonesMain_HandleWMPowerBroadcast, hWnd, wParam);
}

void JonesMain_Shutdown(void)
{
    J3D_TRAMPOLINE_CALL(JonesMain_Shutdown);
}

void J3DAPI JonesMain_PauseGame()
{
    J3D_TRAMPOLINE_CALL(JonesMain_PauseGame);
}

void J3DAPI JonesMain_ResumeGame()
{
    J3D_TRAMPOLINE_CALL(JonesMain_ResumeGame);
}

int J3DAPI JonesMain_IsGamePaused()
{
    return J3D_TRAMPOLINE_CALL(JonesMain_IsGamePaused);
}

int JonesMain_Process(void)
{
    // Call return JonesMain_pfProcess();
    return J3D_TRAMPOLINE_CALL(JonesMain_Process);
}

int JonesMain_ProcessWindowEvents(void)
{
    // Call return wkernel_ProcessEvents();
    return J3D_TRAMPOLINE_CALL(JonesMain_ProcessWindowEvents);
}

int JonesMain_ProcessGame(void)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_ProcessGame);
}

void JonesMain_ProcessMenu(void)
{
    J3D_TRAMPOLINE_CALL(JonesMain_ProcessMenu);
}

void J3DAPI JonesMain_PrintFramerate()
{
    J3D_TRAMPOLINE_CALL(JonesMain_PrintFramerate);
}

int J3DAPI JonesMain_TogglePrintFramerate()
{
    return J3D_TRAMPOLINE_CALL(JonesMain_TogglePrintFramerate);
}

int JonesMain_Open(void)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_Open);
}

int J3DAPI JonesMain_EnsureFile(const char* pFilename)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_EnsureFile, pFilename);
}

int JonesMain_Close(void)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_Close);
}

int J3DAPI JonesMain_Restore(const char* pNdsFilePath)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_Restore, pNdsFilePath);
}

int JonesMain_ProcessGamesaveState(void)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_ProcessGamesaveState);
}

void JonesMain_UpdateLevelNum(void)
{
    J3D_TRAMPOLINE_CALL(JonesMain_UpdateLevelNum);
}

int JonesMain_ProcessEndLevel(void)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_ProcessEndLevel);
}

void JonesMain_SetBonusLevel(void)
{
    J3D_TRAMPOLINE_CALL(JonesMain_SetBonusLevel);
}

void JonesMain_ShowEndCredits(void)
{
    J3D_TRAMPOLINE_CALL(JonesMain_ShowEndCredits);
}

int JonesMain_Credits(void)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_Credits);
}

int JonesMain_IsOpen(void)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_IsOpen);
}

StdDisplayEnvironment* JonesMain_GetDisplayEnvironment(void)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_GetDisplayEnvironment);
}

JonesDisplaySettings* JonesMain_GetDisplaySettings(void)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_GetDisplaySettings);
}

int J3DAPI JonesMain_CloseWindow()
{
    return J3D_TRAMPOLINE_CALL(JonesMain_CloseWindow);
}

int JonesMain_FilePrintf(const char* pFormat, ...)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_FilePrintf, pFormat);
}

int JonesMain_Printf(const char* pFormat, ...)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_Printf, pFormat);
}

void JonesMain_RefreshDisplayDevice(void)
{
    J3D_TRAMPOLINE_CALL(JonesMain_RefreshDisplayDevice);
}

int J3DAPI JonesMain_PlayIntro()
{
    return J3D_TRAMPOLINE_CALL(JonesMain_PlayIntro);
}

int J3DAPI JonesMain_IntroWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_IntroWndProc, hWnd, uMsg, wParam, lParam);
}

void J3DAPI JonesMain_HandleWMLButtonUp()
{
    J3D_TRAMPOLINE_CALL(JonesMain_HandleWMLButtonUp);
}

void J3DAPI JonesMain_IntroHandleKeydown(HWND hwnd, int wParam)
{
    J3D_TRAMPOLINE_CALL(JonesMain_IntroHandleKeydown, hwnd, wParam);
}

signed int J3DAPI JonesMain_IntroMovieBll565(void* a1)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_IntroMovieBll565, a1);
}

signed int J3DAPI JonesMain_IntroMovieBlt555(void* a1)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_IntroMovieBlt555, a1);
}

int J3DAPI JonesMain_IntroMovieBlt32(void* a1)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_IntroMovieBlt32, a1);
}

J3DNORETURN void J3DAPI JonesMain_Assert(const char* pErrorText, const char* pSrcFile, int line)
{
    J3D_TRAMPOLINE_CALL(JonesMain_Assert, pErrorText, pSrcFile, line);
}

void J3DAPI JonesMain_BindInventoryControlKeys(const int* a1, int numKeys)
{
    J3D_TRAMPOLINE_CALL(JonesMain_BindInventoryControlKeys, a1, numKeys);
}

void J3DAPI JonesMain_ResetHUD()
{
    J3D_TRAMPOLINE_CALL(JonesMain_ResetHUD);
}

int J3DAPI JonesMain_SaveHUD(DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_SaveHUD, idTo, outstream);
}

int J3DAPI JonesMain_RestoreHUD(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_RestoreHUD, pMsg);
}

int J3DAPI JonesMain_GetCurrentLevelNum()
{
    return J3D_TRAMPOLINE_CALL(JonesMain_GetCurrentLevelNum);
}

void J3DAPI JonesMain_LogErrorToFile(const char* pErrorText)
{
    J3D_TRAMPOLINE_CALL(JonesMain_LogErrorToFile, pErrorText);
}

void J3DAPI JonesMain_LoadSettings(StdDisplayEnvironment* pDisplayEnv, JonesState* pConfig)
{
    J3D_TRAMPOLINE_CALL(JonesMain_LoadSettings, pDisplayEnv, pConfig);
}

int J3DAPI JonesMain_ShowDevDialog(HWND hWnd, JonesState* pConfig)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_ShowDevDialog, hWnd, pConfig);
}

LRESULT __stdcall JonesMain_DevDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_DevDialogProc, hDlg, uMsg, wParam, lParam);
}

int J3DAPI JonesMain_InitDevDialog(HWND hDlg, WPARAM wParam, JonesState* pConfig)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_InitDevDialog, hDlg, wParam, pConfig);
}

void J3DAPI JonesMain_DevDialogHandleCommand(HWND hWnd, int controlId, LPARAM lParam, int hiWParam)
{
    J3D_TRAMPOLINE_CALL(JonesMain_DevDialogHandleCommand, hWnd, controlId, lParam, hiWParam);
}

void J3DAPI JonesMain_DevDialogInitDisplayDevices(HWND hDlg, JonesState* pConfig)
{
    J3D_TRAMPOLINE_CALL(JonesMain_DevDialogInitDisplayDevices, hDlg, pConfig);
}

void J3DAPI JonesMain_DevDialogUpdateRadioButtons(HWND hDlg, JonesState* pState)
{
    J3D_TRAMPOLINE_CALL(JonesMain_DevDialogUpdateRadioButtons, hDlg, pState);
}

int J3DAPI JonesMain_FindClosestVideoMode(const StdDisplayEnvironment* pList, StdVideoMode* pVideoMOde, size_t deviceNum)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_FindClosestVideoMode, pList, pVideoMOde, deviceNum);
}

int J3DAPI JonesMain_CurDisplaySupportsBPP(JonesDisplaySettings* pSettings, int bpp)
{
    return J3D_TRAMPOLINE_CALL(JonesMain_CurDisplaySupportsBPP, pSettings, bpp);
}
