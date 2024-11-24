#include "JonesMain.h"
#include <j3dcore/j3dhook.h>

#include <Jones3D/Display/JonesHud.h>
#include <Jones3D/Main/jonesString.h>
#include <Jones3D/Play/jonesCog.h>
#include <Jones3D/RTI/symbols.h>

#include <rdroid/Raster/rdCache.h>

#include <sith/DSS/sithDSS.h>
#include <sith/DSS/sithGamesave.h>
#include <sith/Devices/sithComm.h>
#include <sith/Devices/sithSoundMixer.h>
#include <sith/Engine/sithRender.h>
#include <sith/World/sithModel.h>
#include <sith/World/sithWorld.h>

#include <sound/Sound.h>

#include <std/General/std.h>
#include <std/General/stdFileUtil.h>
#include <std/General/stdMath.h>
#include <std/General/stdUtil.h>
#include <std/Win95/std3D.h>
#include <std/Win95/stdControl.h>
#include <std/Win95/stdDisplay.h>

#include <wkernel/wkernel.h>
#include <w32util/wuRegistry.h>

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


#define JonesMain_curLevelNum J3D_DECL_FAR_VAR(JonesMain_curLevelNum, size_t)


#define JonesMain_state J3D_DECL_FAR_VAR(JonesMain_state, JonesState)


INT_PTR CALLBACK JonesMain_DevDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
int J3DAPI JonesMain_InitDevDialog(HWND hDlg, WPARAM wParam, JonesState* pConfig);
void J3DAPI JonesMain_DevDialogHandleCommand(HWND hWnd, int controlId, LPARAM lParam, int hiWParam);
void J3DAPI JonesMain_DevDialogInitDisplayDevices(HWND hDlg, JonesState* pConfig);
void J3DAPI JonesMain_DevDialogUpdateRadioButtons(HWND hDlg, const JonesState* pState);
bool J3DAPI JonesMain_CurDisplaySupportsBPP(const JonesDisplaySettings* pSettings, size_t bpp);

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
    J3D_HOOKFUNC(JonesMain_ShowEndCredits);
    J3D_HOOKFUNC(JonesMain_Credits);
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
    J3D_HOOKFUNC(JonesMain_InitializeHUD);
    J3D_HOOKFUNC(JonesMain_SaveHUD);
    J3D_HOOKFUNC(JonesMain_RestoreHUD);
    J3D_HOOKFUNC(JonesMain_GetCurrentLevelNum);
    J3D_HOOKFUNC(JonesMain_LogErrorToFile);
    J3D_HOOKFUNC(JonesMain_LoadSettings);
    J3D_HOOKFUNC(JonesMain_ShowDevDialog);
    J3D_HOOKFUNC(JonesMain_DevDialogProc);
    J3D_HOOKFUNC(JonesMain_InitDevDialog);
    J3D_HOOKFUNC(JonesMain_DevDialogHandleCommand);
    J3D_HOOKFUNC(JonesMain_DevDialogInitDisplayDevices);
    J3D_HOOKFUNC(JonesMain_DevDialogUpdateRadioButtons);
    J3D_HOOKFUNC(JonesMain_FindClosestVideoMode);
    J3D_HOOKFUNC(JonesMain_CurDisplaySupportsBPP);
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

//void JonesMain_ShowEndCredits(void)
//{
//    J3D_TRAMPOLINE_CALL(JonesMain_ShowEndCredits);
//}

//int JonesMain_Credits(void)
//{
//    return J3D_TRAMPOLINE_CALL(JonesMain_Credits);
//}

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
//
//void J3DAPI JonesMain_InitializeHUD()
//{
//    J3D_TRAMPOLINE_CALL(JonesMain_InitializeHUD);
//}
//
//int J3DAPI JonesMain_SaveHUD(DPID idTo, unsigned int outstream)
//{
//    return J3D_TRAMPOLINE_CALL(JonesMain_SaveHUD, idTo, outstream);
//}
//
//int J3DAPI JonesMain_RestoreHUD(const SithMessage* pMsg)
//{
//    return J3D_TRAMPOLINE_CALL(JonesMain_RestoreHUD, pMsg);
//}
//
//int J3DAPI JonesMain_GetCurrentLevelNum()
//{
//    return J3D_TRAMPOLINE_CALL(JonesMain_GetCurrentLevelNum);
//}
//
//void J3DAPI JonesMain_LogErrorToFile(const char* pErrorText)
//{
//    J3D_TRAMPOLINE_CALL(JonesMain_LogErrorToFile, pErrorText);
//}
//
//void J3DAPI JonesMain_LoadSettings(StdDisplayEnvironment* pDisplayEnv, JonesState* pConfig)
//{
//    J3D_TRAMPOLINE_CALL(JonesMain_LoadSettings, pDisplayEnv, pConfig);
//}
//
//int J3DAPI JonesMain_ShowDevDialog(HWND hWnd, JonesState* pConfig)
//{
//    return J3D_TRAMPOLINE_CALL(JonesMain_ShowDevDialog, hWnd, pConfig);
//}
//
//LRESULT __stdcall JonesMain_DevDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    return J3D_TRAMPOLINE_CALL(JonesMain_DevDialogProc, hDlg, uMsg, wParam, lParam);
//}
//
//int J3DAPI JonesMain_InitDevDialog(HWND hDlg, WPARAM wParam, JonesState* pConfig)
//{
//    return J3D_TRAMPOLINE_CALL(JonesMain_InitDevDialog, hDlg, wParam, pConfig);
//}
//
//void J3DAPI JonesMain_DevDialogHandleCommand(HWND hWnd, int controlId, LPARAM lParam, int hiWParam)
//{
//    J3D_TRAMPOLINE_CALL(JonesMain_DevDialogHandleCommand, hWnd, controlId, lParam, hiWParam);
//}
//
//void J3DAPI JonesMain_DevDialogInitDisplayDevices(HWND hDlg, JonesState* pConfig)
//{
//    J3D_TRAMPOLINE_CALL(JonesMain_DevDialogInitDisplayDevices, hDlg, pConfig);
//}
//
//void J3DAPI JonesMain_DevDialogUpdateRadioButtons(HWND hDlg, JonesState* pState)
//{
//    J3D_TRAMPOLINE_CALL(JonesMain_DevDialogUpdateRadioButtons, hDlg, pState);
//}

//int J3DAPI JonesMain_FindClosestVideoMode(const StdDisplayEnvironment* pList, StdVideoMode* pVideoMOde, size_t deviceNum)
//{
//    return J3D_TRAMPOLINE_CALL(JonesMain_FindClosestVideoMode, pList, pVideoMOde, deviceNum);
//}
//
//int J3DAPI JonesMain_CurDisplaySupportsBPP(JonesDisplaySettings* pSettings, int bpp)
//{
//    return J3D_TRAMPOLINE_CALL(JonesMain_CurDisplaySupportsBPP, pSettings, bpp);
//}

void JonesMain_NextLevel(void)
{
    if ( strcmpi(sithWorld_g_pCurrentWorld->aName, "17_PRU.cnd") )
    {
        STD_STRCPY(JonesMain_state.aCurLevelFilename, sithWorld_g_pCurrentWorld->aName);
    }
    else
    {
        const char* pPreviousLevelName = sithGamesave_GetPreviousLevelFilename();
        STD_STRCPY(JonesMain_state.aCurLevelFilename, pPreviousLevelName);
    }

    JonesMain_state.startMode = 0;

    // Advance level
    JonesMain_UpdateLevelNum();
    STD_STRCPY(JonesMain_state.aCurLevelFilename, JonesMain_aCndLevelLoadInfos[++JonesMain_curLevelNum].pFilename); // Note, the JonesMain_curLevelNum gets incremented here for some reason

    // Set process
    JonesMain_pfProcess = JonesMain_ProcessEndLevel;
}

void JonesMain_ShowEndCredits(void)
{
    Sound_StopAllSounds(); // Added: Stop all sounds before showing end credits. Note, don't call sithSoundMixer_StopAll(), as it clears cur camera sec, which is re-assigned when sithSoundMixer_Update() is called
    JonesMain_pfProcess = JonesMain_Credits;
}

int JonesMain_Credits(void)
{
    bool bFinished = false; // Added: Init. to false

    if ( !JonesMain_bEndCredits )
    {
        JonesMain_hSndCredits = Sound_GetSoundHandle(SITHWORLD_STATICINDEX(2)); // mus_enddemo.wav
        if ( JonesMain_hSndCredits && !JonesMain_hCreditsMusic )
        {
            JonesMain_hCreditsMusic = sithSoundMixer_PlaySound(JonesMain_hSndCredits, 1.0, 0.0, SOUNDPLAY_PLAYONCE | SOUNDPLAY_LOOP);
        }

        stdControl_ReadControls();
        int numEscPressed;
        if ( !JonesMain_bEndCredits && stdControl_ReadKey(DIK_ESCAPE, &numEscPressed) )
        {
            JonesMain_bEndCredits = 1;
        }
    }

    std3D_ClearZBuffer();
    rdCache_AdvanceFrame();
    sithSoundMixer_Update(); // Fixed: Added missing call to sithSoundMixer_Update which updates sound fadeout at the end of credits

    if ( JonesMain_state.displaySettings.bClearBackBuffer )
    {
        stdDisplay_BackBufferFill(0, NULL);
    }

    if ( !std3D_StartScene() )
    {
        sithDrawScene();
        if ( JonesMain_bEndCredits )
        {
            bFinished = JonesHud_DrawCredits(1, JonesMain_hCreditsMusic);
        }
        else
        {
            bFinished = JonesHud_DrawCredits(0, JonesMain_hCreditsMusic);
        }

        rdCache_Flush();
        rdCache_FlushAlpha();
        std3D_EndScene();
        stdDisplay_Update();
    }

    if ( !bFinished )
    {
        return wkernel_PeekProcessEvents();
    }

    if ( JonesMain_hCreditsMusic )
    {
        sithSoundMixer_StopSound(JonesMain_hCreditsMusic);
    }

    JonesMain_pfProcess     = JonesMain_ProcessGame;
    JonesMain_hSndCredits   = 0;
    JonesMain_hCreditsMusic = 0;
    JonesMain_bEndCredits   = 0;
    JonesHud_ShowGameOverDialog(0);
    return wkernel_PeekProcessEvents();
}

void JonesMain_InitializeHUD(void)
{
    JonesHud_EnableMenu(0);
    JonesHud_SetHealthBarAlpha(0.0f);
    jonesCog_g_bShowHealthHUD  = 0;
    jonesCog_g_bEnableGamesave = 1;
}

int J3DAPI JonesMain_SaveHUD(DPID idTo, unsigned int outstream)
{
    SITHDSS_STARTOUT(SITHDSS_HUDSTATE);
    SITHDSS_PUSHUINT8(JonesHud_IsMenuEnabled());
    SITHDSS_PUSHUINT8(jonesCog_g_bShowHealthHUD);
    SITHDSS_PUSHFLOAT(JonesHud_GetHealthBarAlpha());
    SITHDSS_ENDOUT;
    STD_ASSERT(sithMulti_g_message.length == 6);

    //sithMulti_g_message.data[0] = JonesHud_IsMenuEnabled();
    //sithMulti_g_message.data[1] = jonesCog_g_bShowHealthHUD;
    //*(float*)&sithMulti_g_message.data[2] = JonesHud_GetHealthBarAlpha();
    //sithMulti_g_message.type = 47;
    //sithMulti_g_message.length = 6;

    return sithMessage_SendMessage(&sithMulti_g_message, idTo, outstream, 0x01);
}

int J3DAPI JonesMain_RestoreHUD(const SithMessage* pMsg)
{
    STD_ASSERTREL(pMsg);
    SITHDSS_STARTIN(pMsg);

    JonesHud_EnableMenu(SITHDSS_POPUINT8());
    jonesCog_g_bShowHealthHUD = SITHDSS_POPUINT8();
    JonesHud_SetHealthBarAlpha(SITHDSS_POPFLOAT());
    SITHDSS_ENDIN;

    /*  JonesHud_EnableMenu(pMsg->data[0]);
      jonesCog_g_bShowHealthHUD = pMsg->data[1];
      JonesHud_SetHealthBarAlpha(*(float*)&pMsg->data[2]);*/
    return 1;
}

size_t JonesMain_GetCurrentLevelNum(void)
{
    return JonesMain_curLevelNum;
}

void J3DAPI JonesMain_LogErrorToFile(const char* pErrorText)
{
    char aFilePath[128] = { 0 };

    const char* pFilename = jonesString_GetString("JONES_STR_ERRORFILE");
    if ( pFilename )
    {
        char aInstallPath[128] ={ 0 };
        wuRegistry_GetStr("Install Path", aInstallPath, STD_ARRAYLEN(aInstallPath), "");
        size_t pathLen = strlen(aInstallPath);
        if ( pathLen )
        {
            if ( aInstallPath[pathLen] == '\\' ) // Fixed: before: aFilePath[pathLen + 127] == '\\'
            {
                STD_FORMAT(aFilePath, "%s%s", aInstallPath, pFilename);
            }
            else
            {
                STD_FORMAT(aFilePath, "%s\\%s", aInstallPath, pFilename);
            }
        }
        else
        {
            STD_FORMAT(aFilePath, ".\\\\%s", pFilename);
        }
    }
    else
    {
        STD_FORMAT(aFilePath, ".\\\\%s", "JonesError.txt");
    }

    if ( pErrorText && strlen(pErrorText) )
    {
        FILE* fp = fopen(aFilePath, "wt+");
        if ( fp )
        {
            fprintf(fp, pErrorText);
            fprintf(fp, "\n");
            fclose(fp);
        }
    }
}

void J3DAPI JonesMain_LoadSettings(StdDisplayEnvironment* pDisplayEnv, JonesState* pConfig)
{
    DWORD nSize = STD_ARRAYLEN(pConfig->waPlayerName);
    CHAR aText[128] = { 0 }; // Added: Init to 0
    if ( GetComputerName(aText, &nSize) )
    {
        stdUtil_ToWStringEx(pConfig->waPlayerName, aText, STD_ARRAYLEN(pConfig->waPlayerName) - 1);
    }
    else
    {
        stdUtil_ToWStringEx(pConfig->waPlayerName, "NoName", STD_ARRAYLEN(pConfig->waPlayerName) - 1);
    }

    pConfig->waPlayerName[STD_ARRAYLEN(pConfig->waPlayerName) - 1] = 0;

    // Removed: rdModel3K module not supported 
    //if ( wuRegistry_GetIntEx("Katmai", 1) && rdModel3K_sub_4E2ED0() )
    //{
    //    rdModel3K_sub_4E2F00(1);
    //    rdModel3K_sub_4E1DA0();
    //    rdModel3K_sub_4E2F00(0);
    //}

    // Make sure sith has all required dirs set
    sithMakeDirs();

    wuRegistry_GetStr("StartLevel", pConfig->aCurLevelFilename, STD_ARRAYLEN(pConfig->aCurLevelFilename), "");

    pConfig->displaySettings.bWindowMode  = wuRegistry_GetIntEx("InWindow", 0);
    pConfig->displaySettings.bDualMonitor = wuRegistry_GetIntEx("Dual Monitor", 0);
    pConfig->displaySettings.bBuffering   = wuRegistry_GetIntEx("Buffering", 0);
    pConfig->displaySettings.filter       = wuRegistry_GetInt("Filter", 1); // bilinear

    pConfig->displaySettings.bFog = wuRegistry_GetIntEx("Fog", 1);
    pConfig->fogDensity           = wuRegistry_GetFloat("Fog Density", 1.0f);
    std3D_EnableFog(pConfig->displaySettings.bFog, pConfig->fogDensity);

    sithRender_g_fogDensity = pConfig->fogDensity * 100.0f;

    pConfig->devMode   = wuRegistry_GetIntEx("DevMode", 0);
    pConfig->startMode = wuRegistry_GetInt("Start Mode", 2);
    pConfig->startMode = STDMATH_CLAMP(pConfig->startMode, 0, 4);

    pConfig->debugMode = wuRegistry_GetInt("Debug Mode", 0);
    pConfig->logLevel  = wuRegistry_GetInt("Verbosity", 1);
    pConfig->performanceLevel = wuRegistry_GetInt("Performance Level", 4);

    pConfig->displaySettings.geoMode   = wuRegistry_GetInt("Geometry Mode", RD_GEOMETRY_FULL);
    pConfig->displaySettings.lightMode = wuRegistry_GetInt("Lighting Mode", RD_LIGHTING_GOURAUD);

    int bHiPoly = wuRegistry_GetIntEx("HiPoly", 0);
    sithModel_EnableHiPoly(bHiPoly);

    JonesMain_pStartupDisplayEnv = pDisplayEnv;

    wuRegistry_GetStr("Display", aText, STD_ARRAYLEN(aText), "");

    for ( size_t i = 0; i < JonesMain_pStartupDisplayEnv->numInfos; ++i )
    {
        if ( JonesMain_pStartupDisplayEnv->aDisplayInfos[i].displayDevice.bHAL )
        {
            pConfig->displaySettings.displayDeviceNum = i;
        }

        if ( strcmp(JonesMain_pStartupDisplayEnv->aDisplayInfos[i].displayDevice.aDriverName, aText) == 0 )
        {
            pConfig->displaySettings.displayDeviceNum = i;
            break;
        }
    }

    StdDisplayInfo* pDisplay = &JonesMain_pStartupDisplayEnv->aDisplayInfos[pConfig->displaySettings.displayDeviceNum];
    for ( size_t i = 0; i < pDisplay->numDevices; ++i )
    {
        if ( strstr(pDisplay->aDevices[i].deviceDescription, "HAL") ) // contains "HAL" word
        {
            pConfig->displaySettings.device3DNum = i;
            break;
        }
    }

    wuRegistry_GetStr("3D Device", aText, STD_ARRAYLEN(aText), "");
    for ( size_t i = 0; i < pDisplay->numDevices; ++i )
    {
        if ( !strcmp(pDisplay->aDevices[i].deviceDescription, aText) )
        {
            pConfig->displaySettings.device3DNum = i;
            break;
        }
    }

    JonesMain_curVideoMode.aspectRatio                    = 1.0f;
    JonesMain_curVideoMode.rasterInfo.width               = wuRegistry_GetInt("Width", 640);
    JonesMain_curVideoMode.rasterInfo.height              = wuRegistry_GetInt("Height", 480);
    JonesMain_curVideoMode.rasterInfo.colorInfo.bpp       = wuRegistry_GetInt("BPP", 32);
    JonesMain_curVideoMode.rasterInfo.colorInfo.colorMode = STDCOLOR_RGB;

    pConfig->displaySettings.videoModeNum = JonesMain_FindClosestVideoMode(JonesMain_pStartupDisplayEnv, &JonesMain_curVideoMode, pConfig->displaySettings.displayDeviceNum);

    memcpy(&JonesMain_curVideoMode, &pDisplay->aModes[pConfig->displaySettings.videoModeNum], sizeof(JonesMain_curVideoMode));

    pConfig->displaySettings.width  = JonesMain_curVideoMode.rasterInfo.width;
    pConfig->displaySettings.height = JonesMain_curVideoMode.rasterInfo.height;
    pConfig->displaySettings.bClearBackBuffer = 0;

    pConfig->bSound3D      = wuRegistry_GetIntEx("Sound 3D", 0);
    pConfig->bReverseSound = wuRegistry_GetIntEx("ReverseSound", 0);
}


int J3DAPI JonesMain_ShowDevDialog(HWND hWnd, JonesState* pConfig)
{
    HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWL_HINSTANCE);
    return DialogBoxParam(hInstance, (LPCSTR)101, hWnd, JonesMain_DevDialogProc, (LPARAM)pConfig);
}

int J3DAPI JonesMain_ShowDisplayOptions(HWND hWnd, JonesState* pState)
{
    HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWL_HINSTANCE);
    return DialogBoxParam(hInstance, (LPCSTR)106, hWnd, JonesMain_DevDialogProc, (LPARAM)pState);
}

INT_PTR CALLBACK JonesMain_DevDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch ( uMsg )
    {
        case WM_INITDIALOG:
            return JonesMain_InitDevDialog(hDlg, wParam, (JonesState*)lParam);

        case WM_COMMAND:
            JonesMain_DevDialogHandleCommand(hDlg, (uint16_t)wParam, lParam, HIWORD(wParam));
            return 1;
    };

    return 0;
}

int J3DAPI JonesMain_InitDevDialog(HWND hDlg, WPARAM wParam, JonesState* pConfig)
{
    J3D_UNUSED(wParam);

    // Populate display driver combo box list
    HWND hDlgItem = GetDlgItem(hDlg, 1030); // Display driver
    for ( size_t i = 0; i < JonesMain_pStartupDisplayEnv->numInfos; ++i )
    {
        if ( JonesMain_pStartupDisplayEnv->aDisplayInfos[i].displayDevice.bHAL == 1 )
        {
            STD_FORMAT(std_g_genBuffer, "%s", JonesMain_pStartupDisplayEnv->aDisplayInfos[i].displayDevice.aDriverName);
            int itemIdx = SendMessage(hDlgItem, CB_ADDSTRING, 0, (LPARAM)std_g_genBuffer);
            SendMessage(hDlgItem, CB_SETITEMDATA, itemIdx, i);

            // Select diver if matches the one in settings
            if ( i == pConfig->displaySettings.displayDeviceNum )
            {
                SendMessage(hDlgItem, CB_SETCURSEL, itemIdx, 0);
            }
        }
    }

    // Init CB GeometryMOde
    hDlgItem = GetDlgItem(hDlg, 1008);
    int itemIdx = SendMessage(hDlgItem, CB_ADDSTRING, 0, (LPARAM)"Vertex Only");
    SendMessage(hDlgItem, CB_SETITEMDATA, itemIdx, 1);

    int selectedItemIdx = itemIdx;
    itemIdx = SendMessage(hDlgItem, CB_ADDSTRING, 0, (LPARAM)"Wire Frame");
    SendMessage(hDlgItem, CB_SETITEMDATA, itemIdx, 2);
    if ( pConfig->displaySettings.geoMode == RD_GEOMETRY_WIREFRAME )
    {
        selectedItemIdx = itemIdx;
    }

    itemIdx = SendMessage(hDlgItem, CB_ADDSTRING, 0, (LPARAM)"Solid");
    SendMessage(hDlgItem, CB_SETITEMDATA, itemIdx, 3);
    if ( pConfig->displaySettings.geoMode == RD_GEOMETRY_SOLID )
    {
        selectedItemIdx = itemIdx;
    }

    itemIdx = SendMessage(hDlgItem, CB_ADDSTRING, 0, (LPARAM)"Texture");
    SendMessage(hDlgItem, CB_SETITEMDATA, itemIdx, 4);
    if ( pConfig->displaySettings.geoMode == RD_GEOMETRY_FULL )
    {
        selectedItemIdx = itemIdx;
    }

    SendMessage(hDlgItem, CB_SETCURSEL, selectedItemIdx, 0);

    // Init CB Lighting Mode
    hDlgItem = GetDlgItem(hDlg, 1009);
    itemIdx = SendMessage(hDlgItem, CB_ADDSTRING, 0, (LPARAM)"None");
    SendMessage(hDlgItem, CB_SETITEMDATA, itemIdx, 1);

    selectedItemIdx = itemIdx;
    itemIdx = SendMessage(hDlgItem, CB_ADDSTRING, 0, (LPARAM)"Lit");
    SendMessage(hDlgItem, CB_SETITEMDATA, itemIdx, 0);
    if ( pConfig->displaySettings.lightMode == RD_LIGHTING_NONE )
    {
        selectedItemIdx = itemIdx;
    }

    itemIdx = SendMessage(hDlgItem, CB_ADDSTRING, 0, (LPARAM)"Diffuse");
    SendMessage(hDlgItem, CB_SETITEMDATA, itemIdx, 2);
    if ( pConfig->displaySettings.lightMode == RD_LIGHTING_DIFFUSE )
    {
        selectedItemIdx = itemIdx;
    }

    itemIdx = SendMessage(hDlgItem, CB_ADDSTRING, 0, (LPARAM)"Gouraud");
    SendMessage(hDlgItem, CB_SETITEMDATA, itemIdx, 3);
    if ( pConfig->displaySettings.lightMode == RD_LIGHTING_GOURAUD )
    {
        selectedItemIdx = itemIdx;
    }

    SendMessage(hDlgItem, CB_SETCURSEL, selectedItemIdx, 0);

    // Init CB MIp Filter
    hDlgItem = GetDlgItem(hDlg, 1012);
    itemIdx = SendMessage(hDlgItem, CB_ADDSTRING, 0, (LPARAM)"None");
    SendMessage(hDlgItem, CB_SETITEMDATA, itemIdx, 0);

    itemIdx = SendMessage(hDlgItem, CB_ADDSTRING, 0, (LPARAM)"Bilinear");
    SendMessage(hDlgItem, CB_SETCURSEL, itemIdx, 0);// Select bilinear as defult
    SendMessage(hDlgItem, CB_SETITEMDATA, itemIdx, 1);

    itemIdx = SendMessage(hDlgItem, CB_ADDSTRING, 0, (LPARAM)"Trilinear");
    SendMessage(hDlgItem, CB_SETITEMDATA, itemIdx, 2);

    // Setup Display related controls
    JonesMain_DevDialogInitDisplayDevices(hDlg, pConfig);

    // Populate level List box
    hDlgItem = GetDlgItem(hDlg, 1001);
    if ( hDlgItem )
    {
        tFoundFileInfo fileInfo;
        FindFileData* pFileData = stdFileUtil_NewFind("ndy", 3, "ndy");
        while ( stdFileUtil_FindNext(pFileData, &fileInfo) )
        {
            itemIdx = SendMessage(hDlgItem, LB_ADDSTRING, 0, (LPARAM)&fileInfo);
        }

        stdFileUtil_DisposeFind(pFileData);
        pFileData = stdFileUtil_NewFind("ndy", 3, "cnd");
        while ( stdFileUtil_FindNext(pFileData, &fileInfo) )
        {
            itemIdx = SendMessage(hDlgItem, LB_ADDSTRING, 0, (LPARAM)&fileInfo);
        }

        stdFileUtil_DisposeFind(pFileData);

        // Select cur level from config
        int numLevels = SendMessage(hDlgItem, LB_GETCOUNT, 0, 0);
        for ( itemIdx = 0; itemIdx < numLevels; ++itemIdx )
        {
            char aLevelName[128] = { 0 }; // Fixed: Increased string len to 128 from 64
            SendMessage(hDlgItem, LB_GETTEXT, itemIdx, (LPARAM)aLevelName);
            if ( strcmp(aLevelName, pConfig->aCurLevelFilename) == 0 )
            {
                SendMessage(hDlgItem, LB_SETCURSEL, itemIdx, 0);
                break;
            }
        }

        if ( itemIdx == numLevels )
        {
            // Non selected, select level in the middle of the list
            SendMessage(hDlgItem, LB_SETCURSEL, numLevels / 2, 0);
        }
    }

    SetWindowLongPtr(hDlg, DWL_USER, (LONG)pConfig); // Set config to dialog handle

    CheckDlgButton(hDlg, 1007, pConfig->devMode);// Dev mode

    JonesMain_DevDialogUpdateRadioButtons(hDlg, pConfig);
    return 1;
}

void J3DAPI JonesMain_DevDialogHandleCommand(HWND hWnd, int controlId, LPARAM lParam, int hiWParam)
{
    J3D_UNUSED(lParam);

    JonesState* pState = (JonesState*)GetWindowLongPtr(hWnd, DWL_USER);
    if ( controlId > 1001 )
    {
        switch ( controlId )
        {
            case 1013: // error output normal
                pState->debugMode = 0;
                JonesMain_DevDialogUpdateRadioButtons(hWnd, pState);
                break;

            case 1014: // error output console
                pState->debugMode = 1;
                JonesMain_DevDialogUpdateRadioButtons(hWnd, pState);
                break;

            case 1015: // error output file
                pState->debugMode = 2;
                JonesMain_DevDialogUpdateRadioButtons(hWnd, pState);
                break;

            case 1016: // debug output normal
                pState->logLevel = 1;
                JonesMain_DevDialogUpdateRadioButtons(hWnd, pState);
                break;

            case 1017: // debug output verbose
                pState->logLevel = 2;
                JonesMain_DevDialogUpdateRadioButtons(hWnd, pState);
                break;

            case 1018: // debug output quiet
                pState->logLevel = 0;
                JonesMain_DevDialogUpdateRadioButtons(hWnd, pState);
                break;

            case 1029: // display mode
                if ( hiWParam == 1 )
                {
                    HWND hCBDisplayMode = GetDlgItem(hWnd, 1029);
                    int curSelIdx = SendMessage(hCBDisplayMode, CB_GETCURSEL, 0, 0);
                    pState->displaySettings.videoModeNum = SendMessage(hCBDisplayMode, CB_GETITEMDATA, curSelIdx, 0);
                }
                break;

            case 1030: // Display settings
                if ( hiWParam == 1 )
                {
                    HWND CBDisplayDriver = GetDlgItem(hWnd, 1030);
                    int curSelIdx = SendMessage(CBDisplayDriver, CB_GETCURSEL, 0, 0);
                    pState->displaySettings.displayDeviceNum = SendMessage(CBDisplayDriver, CB_GETITEMDATA, curSelIdx, 0);
                    JonesMain_DevDialogInitDisplayDevices(hWnd, pState);
                }
                break;

            case 1031: // 3D Driver
                if ( hiWParam == 1 )
                {
                    HWND hCB3DDriver = GetDlgItem(hWnd, 1031);
                    int curSelIdx = SendMessage(hCB3DDriver, CB_GETCURSEL, 0, 0);
                    pState->displaySettings.device3DNum = SendMessage(hCB3DDriver, CB_GETITEMDATA, curSelIdx, 0);
                    JonesMain_DevDialogInitDisplayDevices(hWnd, pState);
                }
                break;

            case 1176: // performance level 0
                pState->performanceLevel = 0;
                JonesMain_DevDialogUpdateRadioButtons(hWnd, pState);
                break;

            case 1177: // performance level 1
                pState->performanceLevel = 1;
                JonesMain_DevDialogUpdateRadioButtons(hWnd, pState);
                break;

            case 1178: // performance level 2
                pState->performanceLevel = 2;
                JonesMain_DevDialogUpdateRadioButtons(hWnd, pState);
                break;

            case 1179: // performance level 3
                pState->performanceLevel = 3;
                JonesMain_DevDialogUpdateRadioButtons(hWnd, pState);
                break;

            case 1180: // performance level 4
                pState->performanceLevel = 4;
                JonesMain_DevDialogUpdateRadioButtons(hWnd, pState);
                break;

            default:
                return;
        }
    }
    else
    {
        switch ( controlId )
        {
            case 1001: // select level list
                if ( hiWParam != 2 )
                {
                    return;
                }

                controlId = 1; // start game
                break;

            case 1: // start the game
                break;

            case 2: // exit
                EndDialog(hWnd, controlId);
                return;

            default:
                return;
        }

        // Start game logic

        // Get 3D driver
        HWND hCB3DDriver = GetDlgItem(hWnd, 1031);
        int curSelIdx = SendMessage(hCB3DDriver, CB_GETCURSEL, 0, 0);
        pState->displaySettings.device3DNum = SendMessage(hCB3DDriver, CB_GETITEMDATA, curSelIdx, 0);

        // Get Display mode
        HWND hCBDisplayMode = GetDlgItem(hWnd, 1029);
        curSelIdx = SendMessage(hCBDisplayMode, CB_GETCURSEL, 0, 0);
        pState->displaySettings.videoModeNum = SendMessage(hCBDisplayMode, CB_GETITEMDATA, curSelIdx, 0);

        // Geometry mode
        HWND hCBGeometryMode = GetDlgItem(hWnd, 1008);
        curSelIdx = SendMessage(hCBGeometryMode, CB_GETCURSEL, 0, 0);
        pState->displaySettings.geoMode = SendMessage(hCBGeometryMode, CB_GETITEMDATA, curSelIdx, 0);

        if ( pState->displaySettings.geoMode == RD_GEOMETRY_WIREFRAME || pState->displaySettings.geoMode == RD_GEOMETRY_VERTEX )
        {
            pState->displaySettings.bClearBackBuffer = 1;
        }

        // Light mode
        HWND hCBLightMode = GetDlgItem(hWnd, 1009);
        curSelIdx = SendMessage(hCBLightMode, CB_GETCURSEL, 0, 0);
        pState->displaySettings.lightMode = SendMessage(hCBLightMode, CB_GETITEMDATA, curSelIdx, 0);

        // Filter mode
        HWND hCBFilterMode = GetDlgItem(hWnd, 1012);
        curSelIdx = SendMessage(hCBFilterMode, CB_GETCURSEL, 0, 0);
        pState->displaySettings.filter = SendMessage(hCBFilterMode, CB_GETITEMDATA, curSelIdx, 0);

        pState->displaySettings.bWindowMode = IsDlgButtonChecked(hWnd, 1002) == 1;// window mode
        pState->devMode = IsDlgButtonChecked(hWnd, 1007) == 1;// devmode

        pState->displaySettings.width = JonesMain_pStartupDisplayEnv->aDisplayInfos[pState->displaySettings.displayDeviceNum].aModes[pState->displaySettings.videoModeNum].rasterInfo.width;
        pState->displaySettings.height = JonesMain_pStartupDisplayEnv->aDisplayInfos[pState->displaySettings.displayDeviceNum].aModes[pState->displaySettings.videoModeNum].rasterInfo.height;

        // Get selected level & Save settings
        HWND hCBLevelList = GetDlgItem(hWnd, 1001);
        curSelIdx = SendMessage(hCBLevelList, LB_GETCURSEL, 0, 0);
        if ( SendMessage(hCBLevelList, LB_GETTEXT, curSelIdx, (LPARAM)pState->aCurLevelFilename) != -1 )
        {
            wuRegistry_SaveStr("Display", JonesMain_pStartupDisplayEnv->aDisplayInfos[pState->displaySettings.displayDeviceNum].displayDevice.aDriverName);
            wuRegistry_SaveStr("3D Device", JonesMain_pStartupDisplayEnv->aDisplayInfos[pState->displaySettings.displayDeviceNum].aDevices[pState->displaySettings.device3DNum].deviceDescription);
            wuRegistry_SaveInt("Width", pState->displaySettings.width);
            wuRegistry_SaveInt("Height", pState->displaySettings.height);
            wuRegistry_SaveInt("BPP", JonesMain_pStartupDisplayEnv->aDisplayInfos[pState->displaySettings.displayDeviceNum].aModes[pState->displaySettings.videoModeNum].rasterInfo.colorInfo.bpp);
            wuRegistry_SaveInt("Filter", pState->displaySettings.filter);

            wuRegistry_SaveStr("StartLevel", pState->aCurLevelFilename);

            wuRegistry_SaveIntEx("InWindow", pState->displaySettings.bWindowMode);
            wuRegistry_SaveIntEx("Dual Monitor", pState->displaySettings.bDualMonitor);

            wuRegistry_SaveIntEx("DevMode", pState->devMode);

            wuRegistry_SaveIntEx("Sound 3D", pState->bSound3D);

            wuRegistry_SaveInt("Debug Mode", pState->debugMode);
            wuRegistry_SaveInt("Verbosity", pState->logLevel);

            wuRegistry_SaveStr("User Path", pState->aInstallPath);
            wuRegistry_SaveInt("Performance Level", pState->performanceLevel);

            wuRegistry_SaveInt("Geometry Mode", pState->displaySettings.geoMode);
            wuRegistry_SaveInt("Lighting Mode", pState->displaySettings.lightMode);

            EndDialog(hWnd, controlId); // Close dialog
        }
    }
}

void J3DAPI JonesMain_DevDialogInitDisplayDevices(HWND hDlg, JonesState* pConfig)
{
    HWND hBTNStart      = GetDlgItem(hDlg, 1);
    HWND hCBWindowMode  = GetDlgItem(hDlg, 1002);
    HWND hCB3DDriver    = GetDlgItem(hDlg, 1031);

    HWND hCBDisplayMode = GetDlgItem(hDlg, 1029);
    SendMessage(hCBDisplayMode, CB_RESETCONTENT, 0, 0);

    StdDisplayInfo* pDisplay = &JonesMain_pStartupDisplayEnv->aDisplayInfos[pConfig->displaySettings.displayDeviceNum];
    if ( !pDisplay->displayDevice.bHAL )
    {
        EnableWindow(hBTNStart, 0);
        EnableWindow(hCBWindowMode, 0);
        EnableWindow(hCBDisplayMode, 0);
        EnableWindow(hCB3DDriver, 0);
        return;
    }

    EnableWindow(hBTNStart, 1);
    EnableWindow(hCBWindowMode, pDisplay->displayDevice.bWindowRenderNotSupported == 0);

    if ( pDisplay->displayDevice.bWindowRenderNotSupported )
    {
        pConfig->displaySettings.bWindowMode = 0;
    }

    EnableWindow(hCBDisplayMode, 1);
    EnableWindow(hCB3DDriver, 1);
    CheckDlgButton(hDlg, 1002, pConfig->displaySettings.bWindowMode);// CB window mode

    // Init 3D driver combo box list
    bool bDriverSet = false;

    CHAR aDriverName[128] = { 0 };
    GetWindowText(hCB3DDriver, aDriverName, STD_ARRAYLEN(aDriverName));

    SendMessage(hCB3DDriver, CB_RESETCONTENT, 0, 0);
    for ( size_t deviceNum = 0; deviceNum < pDisplay->numDevices; ++deviceNum )
    {
        STD_FORMAT(std_g_genBuffer, "%s", pDisplay->aDevices[deviceNum].deviceDescription);

        int itemIdx = SendMessage(hCB3DDriver, CB_ADDSTRING, 0, (LPARAM)std_g_genBuffer);
        SendMessage(hCB3DDriver, CB_SETITEMDATA, itemIdx, deviceNum);

        // Select item in cb list
        if ( strcmp(aDriverName, std_g_genBuffer) == 0 || pConfig->displaySettings.device3DNum == deviceNum )
        {
            SendMessage(hCB3DDriver, CB_SETCURSEL, itemIdx, 0);
            pConfig->displaySettings.device3DNum = deviceNum;
            bDriverSet = true;
        }
    }

    if ( !bDriverSet )
    {
        pConfig->displaySettings.device3DNum = 0;
        SendMessage(hCB3DDriver, CB_SETCURSEL, 0, 0);
    }

    // Populate display mode combo box list (resolutions) and select 

    // JonesMain_curVideoMode.rasterInfo.colorInfo.bpp = 16; // Removed: This prevents getting stored 32 BPP resolution from config

    bDriverSet = false;
    for ( size_t modeNum = 0; modeNum < JonesMain_pStartupDisplayEnv->aDisplayInfos[pConfig->displaySettings.displayDeviceNum].numModes; ++modeNum )
    {
        if ( pDisplay->aModes[modeNum].aspectRatio == 1.0f
          && pDisplay->aModes[modeNum].rasterInfo.width >= 512
          && pDisplay->aModes[modeNum].rasterInfo.height >= 384 )
        {
            if ( JonesMain_CurDisplaySupportsBPP(&pConfig->displaySettings, pDisplay->aModes[modeNum].rasterInfo.colorInfo.bpp) )
            {
                STD_FORMAT(std_g_genBuffer, "%dx%d %dbpp", pDisplay->aModes[modeNum].rasterInfo.width, pDisplay->aModes[modeNum].rasterInfo.height, pDisplay->aModes[modeNum].rasterInfo.colorInfo.bpp);  // Changed: Moved in this scope
                int itemIdx = SendMessage(hCBDisplayMode, CB_ADDSTRING, 0, (LPARAM)std_g_genBuffer);
                SendMessage(hCBDisplayMode, CB_SETITEMDATA, itemIdx, modeNum);

                // Select mode
                if ( pDisplay->aModes[modeNum].rasterInfo.width == JonesMain_curVideoMode.rasterInfo.width
                  && pDisplay->aModes[modeNum].rasterInfo.height == JonesMain_curVideoMode.rasterInfo.height
                  && pDisplay->aModes[modeNum].rasterInfo.colorInfo.bpp == JonesMain_curVideoMode.rasterInfo.colorInfo.bpp )
                {
                    SendMessage(hCBDisplayMode, CB_SETCURSEL, itemIdx, 0);
                    bDriverSet = true;
                }
            }
        }
    }

    if ( !bDriverSet )
    {
        SendMessage(hCBDisplayMode, CB_SETCURSEL, 0, 0);
    }
}

void J3DAPI JonesMain_DevDialogUpdateRadioButtons(HWND hDlg, const JonesState* pState)
{
    switch ( pState->debugMode )
    {
        case 0:
            CheckRadioButton(hDlg, 1013, 1015, 1013); // Normal
            break;
        case 1:
            CheckRadioButton(hDlg, 1013, 1015, 1014); // Console
            break;
        case 2:
            CheckRadioButton(hDlg, 1013, 1015, 1015); // Log file
            break;
    };

    switch ( pState->logLevel )
    {
        case 0:
            CheckRadioButton(hDlg, 1016, 1018, 1018); // Quite
            break;
        case 1:
            CheckRadioButton(hDlg, 1016, 1018, 1016); // Normal
            break;
        case 2:
            CheckRadioButton(hDlg, 1016, 1018, 1017); // Verbose
            break;
    };

    switch ( pState->performanceLevel )
    {
        case 0:
            CheckRadioButton(hDlg, 1176, 1180, 1176);
            break;

        case 1:
            CheckRadioButton(hDlg, 1176, 1180, 1177);
            break;

        case 2:
            CheckRadioButton(hDlg, 1176, 1180, 1178);
            break;

        case 3:
            CheckRadioButton(hDlg, 1176, 1180, 1179);
            break;

        case 4:
            CheckRadioButton(hDlg, 1176, 1180, 1180);
            break;

        default:
            return;
    }
}

size_t J3DAPI JonesMain_FindClosestVideoMode(const StdDisplayEnvironment* pList, const StdVideoMode* pVideoMode, size_t deviceNum)
{
    size_t videoMode = 0;
    StdDisplayInfo* pDisplay = &pList->aDisplayInfos[deviceNum];
    for ( size_t i = 0; i < pList->aDisplayInfos[deviceNum].numModes; ++i )
    {
        if ( pDisplay->aModes[i].rasterInfo.colorInfo.bpp == pVideoMode->rasterInfo.colorInfo.bpp ) // Fixed: Changed hardcoded 16 BPP check to pVideoMode BPP compare
        {
            if ( pDisplay->aModes[i].rasterInfo.width == pVideoMode->rasterInfo.width && pDisplay->aModes[i].rasterInfo.height == pVideoMode->rasterInfo.height )
            {
                return i; // exact
            }

            videoMode = i; // closest
        }
    }

    return videoMode;
}

bool J3DAPI JonesMain_CurDisplaySupportsBPP(const JonesDisplaySettings* pSettings, size_t bpp)
{
    StdDisplayInfo* pDisplay = &JonesMain_pStartupDisplayEnv->aDisplayInfos[pSettings->displayDeviceNum];
    switch ( bpp )
    {
        case 8:
            return(pDisplay->aDevices[pSettings->device3DNum].d3dDesc.dwDeviceRenderBitDepth & DDBD_8) != 0;
        case 16:
            return (pDisplay->aDevices[pSettings->device3DNum].d3dDesc.dwDeviceRenderBitDepth & DDBD_16) != 0;
        case 24:
            return (pDisplay->aDevices[pSettings->device3DNum].d3dDesc.dwDeviceRenderBitDepth & DDBD_24) != 0;
        case 32:
            return (pDisplay->aDevices[pSettings->device3DNum].d3dDesc.dwDeviceRenderBitDepth & DDBD_32) != 0;
    }

    return false;
}