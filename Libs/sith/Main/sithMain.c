#include "sithMain.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithMain_aLevelNdsInfos J3D_DECL_FAR_ARRAYVAR(sithMain_aLevelNdsInfos, const SithMainStartLevelNdsInfo(*)[17])
#define sithMain_aLevelNdsFileNameBuf J3D_DECL_FAR_ARRAYVAR(sithMain_aLevelNdsFileNameBuf, char(*)[512])
#define sithMain_szScreenShotsFileName J3D_DECL_FAR_ARRAYVAR(sithMain_szScreenShotsFileName, char(*)[128])
#define sithMain_aNdsLevelFilenameBuf J3D_DECL_FAR_ARRAYVAR(sithMain_aNdsLevelFilenameBuf, char(*)[512])
#define sithMain_szTmpQuickSavePrefix J3D_DECL_FAR_ARRAYVAR(sithMain_szTmpQuickSavePrefix, char(*)[128])
#define sithMain_szTmpSaveGameDirPath J3D_DECL_FAR_ARRAYVAR(sithMain_szTmpSaveGameDirPath, char(*)[128])
#define sithMain_szTmpAutoSaveFilePrefix J3D_DECL_FAR_ARRAYVAR(sithMain_szTmpAutoSaveFilePrefix, char(*)[128])
#define sithMain_szTmpScreenShotDirPath J3D_DECL_FAR_ARRAYVAR(sithMain_szTmpScreenShotDirPath, char(*)[128])
#define sithMain_dword_56437C J3D_DECL_FAR_VAR(sithMain_dword_56437C, int)
#define sithMain_bDrawPlayerMoveBounds J3D_DECL_FAR_VAR(sithMain_bDrawPlayerMoveBounds, int)
#define sithMain_bDrawThingMoveBounds J3D_DECL_FAR_VAR(sithMain_bDrawThingMoveBounds, int)
#define sithMain_bStartup J3D_DECL_FAR_VAR(sithMain_bStartup, int)
#define sithMain_bOpen J3D_DECL_FAR_VAR(sithMain_bOpen, int)
#define sithMain_performanceLevel J3D_DECL_FAR_VAR(sithMain_performanceLevel, int)
#define sithMain_pfOpenCallback J3D_DECL_FAR_VAR(sithMain_pfOpenCallback, SithOpenCallback)
#define sithMain_somePos2 J3D_DECL_FAR_VAR(sithMain_somePos2, rdVector3)
#define sithMain_somePos J3D_DECL_FAR_VAR(sithMain_somePos, rdVector3)
#define sithMain_flt_17FD1B0 J3D_DECL_FAR_VAR(sithMain_flt_17FD1B0, float)
#define sithMain_flt_17FD1B4 J3D_DECL_FAR_VAR(sithMain_flt_17FD1B4, float)

void sithMain_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithSetServices);
    // J3D_HOOKFUNC(sithClearServices);
    // J3D_HOOKFUNC(sithStartup);
    // J3D_HOOKFUNC(sithShutdown);
    // J3D_HOOKFUNC(sithSetPerformanceLevel);
    // J3D_HOOKFUNC(sithGetPerformanceLevel);
    // J3D_HOOKFUNC(sithOpenStatic);
    // J3D_HOOKFUNC(sithCloseStatic);
    // J3D_HOOKFUNC(sithOpenNormal);
    // J3D_HOOKFUNC(sithOpenPostProcess);
    // J3D_HOOKFUNC(sithOpen);
    // J3D_HOOKFUNC(sithClose);
    // J3D_HOOKFUNC(sithUpdate);
    // J3D_HOOKFUNC(sithDrawScene);
    // J3D_HOOKFUNC(sithSetGameDifficulty);
    // J3D_HOOKFUNC(sithGetGameDifficulty);
    // J3D_HOOKFUNC(sithGetHitAccuarancyScalar);
    // J3D_HOOKFUNC(sithGetCombatDamageScalar);
    // J3D_HOOKFUNC(sithGetIMPDamageScalar);
    // J3D_HOOKFUNC(sithAdvanceRenderTick);
    // J3D_HOOKFUNC(sithMakeDirs);
    // J3D_HOOKFUNC(sithGetAutoSaveFilePrefix);
    // J3D_HOOKFUNC(sithGetPath);
    // J3D_HOOKFUNC(sithGetSaveGamesDir);
    // J3D_HOOKFUNC(sithGetQuickSaveFilePrefix);
    // J3D_HOOKFUNC(sithGetScreenShotsDir);
    // J3D_HOOKFUNC(sithGetScreenShotFileTemplate);
    // J3D_HOOKFUNC(sithSetOpenCallback);
    // J3D_HOOKFUNC(sithGetCurrentWorldSaveName);
    // J3D_HOOKFUNC(sithGetLevelSaveFilename);
}

void sithMain_ResetGlobals(void)
{
    const SithMainStartLevelNdsInfo sithMain_aLevelNdsInfos_tmp[17] = {
      { "SITHSTRING_STARTCYN", "00_CYN" },
      { "SITHSTRING_STARTBAB", "01_BAB" },
      { "SITHSTRING_STARTRIV", "02_RIV" },
      { "SITHSTRING_STARTSHS", "03_SHS" },
      { "SITHSTRING_STARTLAG", "05_LAG" },
      { "SITHSTRING_STARTVOL", "06_VOL" },
      { "SITHSTRING_STARTTEM", "07_TEM" },
      { "SITHSTRING_STARTJEP", "16_JEP" },
      { "SITHSTRING_STARTTEO", "08_TEO" },
      { "SITHSTRING_STARTOLV", "09_OLV" },
      { "SITHSTRING_STARTSEA", "10_SEA" },
      { "SITHSTRING_STARTPYR", "11_PYR" },
      { "SITHSTRING_STARTSOL", "12_SOL" },
      { "SITHSTRING_STARTNUB", "13_NUB" },
      { "SITHSTRING_STARTINF", "14_INF" },
      { "SITHSTRING_STARTAET", "15_AET" },
      { "SITHSTRING_STARTPRU", "17_PRU" }
    };
    memcpy((SithMainStartLevelNdsInfo*)&sithMain_aLevelNdsInfos, &sithMain_aLevelNdsInfos_tmp, sizeof(sithMain_aLevelNdsInfos));

    memset(&sithMain_aLevelNdsFileNameBuf, 0, sizeof(sithMain_aLevelNdsFileNameBuf));
    memset(&sithMain_szScreenShotsFileName, 0, sizeof(sithMain_szScreenShotsFileName));
    memset(&sithMain_aNdsLevelFilenameBuf, 0, sizeof(sithMain_aNdsLevelFilenameBuf));
    memset(&sithMain_szTmpQuickSavePrefix, 0, sizeof(sithMain_szTmpQuickSavePrefix));
    memset(&sithMain_szTmpSaveGameDirPath, 0, sizeof(sithMain_szTmpSaveGameDirPath));
    memset(&sithMain_szTmpAutoSaveFilePrefix, 0, sizeof(sithMain_szTmpAutoSaveFilePrefix));
    memset(&sithMain_szTmpScreenShotDirPath, 0, sizeof(sithMain_szTmpScreenShotDirPath));
    memset(&sith_g_pHS, 0, sizeof(sith_g_pHS));
    memset(&sithMain_dword_56437C, 0, sizeof(sithMain_dword_56437C));
    memset(&sithMain_bDrawPlayerMoveBounds, 0, sizeof(sithMain_bDrawPlayerMoveBounds));
    memset(&sithMain_bDrawThingMoveBounds, 0, sizeof(sithMain_bDrawThingMoveBounds));
    memset(&sithMain_bStartup, 0, sizeof(sithMain_bStartup));
    memset(&sithMain_bOpen, 0, sizeof(sithMain_bOpen));
    memset(&sithMain_performanceLevel, 0, sizeof(sithMain_performanceLevel));
    memset(&sithMain_pfOpenCallback, 0, sizeof(sithMain_pfOpenCallback));
    memset(&sithMain_somePos2, 0, sizeof(sithMain_somePos2));
    memset(&sithMain_somePos, 0, sizeof(sithMain_somePos));
    memset(&sithMain_g_frameNumber, 0, sizeof(sithMain_g_frameNumber));
    memset(&sithMain_flt_17FD1B0, 0, sizeof(sithMain_flt_17FD1B0));
    memset(&sithMain_flt_17FD1B4, 0, sizeof(sithMain_flt_17FD1B4));
    memset(&sithMain_g_sith_mode, 0, sizeof(sithMain_g_sith_mode));
    memset(&sithMain_g_curRenderTick, 0, sizeof(sithMain_g_curRenderTick));
}

void J3DAPI sithSetServices(tHostServices* pHS)
{
    J3D_TRAMPOLINE_CALL(sithSetServices, pHS);
}

void sithClearServices(void)
{
    J3D_TRAMPOLINE_CALL(sithClearServices);
}

int J3DAPI sithStartup()
{
    return J3D_TRAMPOLINE_CALL(sithStartup);
}

void sithShutdown(void)
{
    J3D_TRAMPOLINE_CALL(sithShutdown);
}

int J3DAPI sithSetPerformanceLevel(int level)
{
    return J3D_TRAMPOLINE_CALL(sithSetPerformanceLevel, level);
}

int sithGetPerformanceLevel(void)
{
    return J3D_TRAMPOLINE_CALL(sithGetPerformanceLevel);
}

int J3DAPI sithOpenStatic(const char* pFilename)
{
    return J3D_TRAMPOLINE_CALL(sithOpenStatic, pFilename);
}

void sithCloseStatic(void)
{
    J3D_TRAMPOLINE_CALL(sithCloseStatic);
}

// NOTE: there is debug info that originally this function was named: sithOpenNormal
int J3DAPI sithOpenNormal(char* pWorldName, const wchar_t* wszPlayerName)
{
    return J3D_TRAMPOLINE_CALL(sithOpenNormal, pWorldName, wszPlayerName);
}

void J3DAPI sithOpenPostProcess()
{
    J3D_TRAMPOLINE_CALL(sithOpenPostProcess);
}

int J3DAPI sithOpen(const wchar_t* wszPlayerName)
{
    return J3D_TRAMPOLINE_CALL(sithOpen, wszPlayerName);
}

void sithClose(void)
{
    J3D_TRAMPOLINE_CALL(sithClose);
}

void sithUpdate(void)
{
    J3D_TRAMPOLINE_CALL(sithUpdate);
}

void sithDrawScene(void)
{
    J3D_TRAMPOLINE_CALL(sithDrawScene);
}

void J3DAPI sithSetGameDifficulty(int difficulty)
{
    J3D_TRAMPOLINE_CALL(sithSetGameDifficulty, difficulty);
}

int J3DAPI sithGetGameDifficulty()
{
    return J3D_TRAMPOLINE_CALL(sithGetGameDifficulty);
}

float J3DAPI sithGetHitAccuarancyScalar()
{
    return J3D_TRAMPOLINE_CALL(sithGetHitAccuarancyScalar);
}

float J3DAPI sithGetCombatDamageScalar()
{
    return J3D_TRAMPOLINE_CALL(sithGetCombatDamageScalar);
}

float sithGetIMPDamageScalar(void)
{
    return J3D_TRAMPOLINE_CALL(sithGetIMPDamageScalar);
}

void J3DAPI sithAdvanceRenderTick()
{
    J3D_TRAMPOLINE_CALL(sithAdvanceRenderTick);
}

void sithMakeDirs(void)
{
    J3D_TRAMPOLINE_CALL(sithMakeDirs);
}

const char* J3DAPI sithGetAutoSaveFilePrefix()
{
    return J3D_TRAMPOLINE_CALL(sithGetAutoSaveFilePrefix);
}

const char* J3DAPI sithGetPath(char* aOutPath, char* pKey, int bPrependInstallDirPath)
{
    return J3D_TRAMPOLINE_CALL(sithGetPath, aOutPath, pKey, bPrependInstallDirPath);
}

const char* J3DAPI sithGetSaveGamesDir()
{
    return J3D_TRAMPOLINE_CALL(sithGetSaveGamesDir);
}

const char* J3DAPI sithGetQuickSaveFilePrefix()
{
    return J3D_TRAMPOLINE_CALL(sithGetQuickSaveFilePrefix);
}

const char* J3DAPI sithGetScreenShotsDir()
{
    return J3D_TRAMPOLINE_CALL(sithGetScreenShotsDir);
}

const char* J3DAPI sithGetScreenShotFileTemplate()
{
    return J3D_TRAMPOLINE_CALL(sithGetScreenShotFileTemplate);
}

void J3DAPI sithSetOpenCallback(SithOpenCallback pfCallback)
{
    J3D_TRAMPOLINE_CALL(sithSetOpenCallback, pfCallback);
}

const char* J3DAPI sithGetCurrentWorldSaveName()
{
    return J3D_TRAMPOLINE_CALL(sithGetCurrentWorldSaveName);
}

const char* J3DAPI sithGetLevelSaveFilename(unsigned int levelNum)
{
    return J3D_TRAMPOLINE_CALL(sithGetLevelSaveFilename, levelNum);
}
