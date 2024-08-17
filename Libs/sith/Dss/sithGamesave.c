#include "sithGamesave.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithGamesave_wszPlayerName J3D_DECL_FAR_ARRAYVAR(sithGamesave_wszPlayerName, wchar_t(*)[14])
#define sithGamesave_state J3D_DECL_FAR_VAR(sithGamesave_state, int)
#define sithGamesave_aLastFilename J3D_DECL_FAR_ARRAYVAR(sithGamesave_aLastFilename, char(*)[128])
#define sithGamesave_aNdsSaveSectionSizes J3D_DECL_FAR_ARRAYVAR(sithGamesave_aNdsSaveSectionSizes, int(*)[15])
#define sithGamesave_gameStatistics J3D_DECL_FAR_VAR(sithGamesave_gameStatistics, SithGameStatistics)
#define sithGamesave_aPreviousLevelFilename J3D_DECL_FAR_ARRAYVAR(sithGamesave_aPreviousLevelFilename, char(*)[64])
#define sithGamesave_aNdsFilePath J3D_DECL_FAR_ARRAYVAR(sithGamesave_aNdsFilePath, char(*)[128])
#define sithGamesave_bStatisticsLocked J3D_DECL_FAR_VAR(sithGamesave_bStatisticsLocked, int)
#define sithGamesave_pVBufferScreenShot J3D_DECL_FAR_VAR(sithGamesave_pVBufferScreenShot, tVBuffer*)
#define sithGamesave_bScreenShot J3D_DECL_FAR_VAR(sithGamesave_bScreenShot, int)
#define sithGamesave_hBmpScreenShot J3D_DECL_FAR_VAR(sithGamesave_hBmpScreenShot, HBITMAP)
#define sithGamesave_pfSaveGameCallback J3D_DECL_FAR_VAR(sithGamesave_pfSaveGameCallback, SithGameSaveCallback)

void sithGamesave_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithGamesave_GetGameStatistics);
    // J3D_HOOKFUNC(sithGamesave_LockGameStatistics);
    // J3D_HOOKFUNC(sithGamesave_UnlockGameStatistics);
    // J3D_HOOKFUNC(sithGamesave_Save);
    // J3D_HOOKFUNC(sithGamesave_Restore);
    // J3D_HOOKFUNC(sithGamesave_SaveCurrentWorld);
    // J3D_HOOKFUNC(sithGamesave_Process);
    // J3D_HOOKFUNC(sithGamesave_RestoreFile);
    // J3D_HOOKFUNC(sithGamesave_NotifyRestored);
    // J3D_HOOKFUNC(sithGamesave_ReadBlockTypeLength);
    // J3D_HOOKFUNC(sithGamesave_SaveFile);
    // J3D_HOOKFUNC(sithGamesave_ScreenShot);
    // J3D_HOOKFUNC(sithGamesave_GetScreenShotBitmap);
    // J3D_HOOKFUNC(sithGamesave_WriteScreenShot);
    // J3D_HOOKFUNC(sithGamesave_SeekThumbNail);
    // J3D_HOOKFUNC(sithGamesave_LoadThumbnail);
    // J3D_HOOKFUNC(sithGamesave_Startup);
    // J3D_HOOKFUNC(sithGamesave_Shutdown);
    // J3D_HOOKFUNC(sithGamesave_Open);
    // J3D_HOOKFUNC(sithGamesave_CloseRestore);
    // J3D_HOOKFUNC(sithGamesave_Close);
    // J3D_HOOKFUNC(sithGamesave_SetPreviousLevelFilename);
    // J3D_HOOKFUNC(sithGamesave_GetPreviousLevelFilename);
    // J3D_HOOKFUNC(sithGamesave_GetLastFilename);
    // J3D_HOOKFUNC(sithGamesave_LoadLevelFilename);
    // J3D_HOOKFUNC(sithGamesave_GetState);
    // J3D_HOOKFUNC(sithGamesave_SetSaveGameCallback);
}

void sithGamesave_ResetGlobals(void)
{
    wchar_t sithGamesave_wszPlayerName_tmp[14] = { 73u, 110u, 100u, 105u, 97u, 110u, 97u, 32u, 74u, 111u, 110u, 101u, 115u, 0u };
    memcpy(&sithGamesave_wszPlayerName, &sithGamesave_wszPlayerName_tmp, sizeof(sithGamesave_wszPlayerName));
    
    memset(&sithGamesave_state, 0, sizeof(sithGamesave_state));
    memset(&sithGamesave_aLastFilename, 0, sizeof(sithGamesave_aLastFilename));
    memset(&sithGamesave_aNdsSaveSectionSizes, 0, sizeof(sithGamesave_aNdsSaveSectionSizes));
    memset(&sithGamesave_gameStatistics, 0, sizeof(sithGamesave_gameStatistics));
    memset(&sithGamesave_aPreviousLevelFilename, 0, sizeof(sithGamesave_aPreviousLevelFilename));
    memset(&sithGamesave_aNdsFilePath, 0, sizeof(sithGamesave_aNdsFilePath));
    memset(&sithGamesave_bStatisticsLocked, 0, sizeof(sithGamesave_bStatisticsLocked));
    memset(&sithGamesave_pVBufferScreenShot, 0, sizeof(sithGamesave_pVBufferScreenShot));
    memset(&sithGamesave_bScreenShot, 0, sizeof(sithGamesave_bScreenShot));
    memset(&sithGamesave_hBmpScreenShot, 0, sizeof(sithGamesave_hBmpScreenShot));
    memset(&sithGamesave_pfSaveGameCallback, 0, sizeof(sithGamesave_pfSaveGameCallback));
}

SithGameStatistics* J3DAPI sithGamesave_GetGameStatistics()
{
    return J3D_TRAMPOLINE_CALL(sithGamesave_GetGameStatistics);
}

int sithGamesave_LockGameStatistics(void)
{
    return J3D_TRAMPOLINE_CALL(sithGamesave_LockGameStatistics);
}

int sithGamesave_UnlockGameStatistics(void)
{
    return J3D_TRAMPOLINE_CALL(sithGamesave_UnlockGameStatistics);
}

int J3DAPI sithGamesave_Save(const char* pFilename, int bOverwrite)
{
    return J3D_TRAMPOLINE_CALL(sithGamesave_Save, pFilename, bOverwrite);
}

int J3DAPI sithGamesave_Restore(const char* pFilename, int bNotifyCog)
{
    return J3D_TRAMPOLINE_CALL(sithGamesave_Restore, pFilename, bNotifyCog);
}

int J3DAPI sithGamesave_SaveCurrentWorld(unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithGamesave_SaveCurrentWorld, outstream);
}

int sithGamesave_Process(void)
{
    return J3D_TRAMPOLINE_CALL(sithGamesave_Process);
}

int J3DAPI sithGamesave_RestoreFile(const char* pFilename, int bNotify)
{
    return J3D_TRAMPOLINE_CALL(sithGamesave_RestoreFile, pFilename, bNotify);
}

void J3DAPI sithGamesave_NotifyRestored(const char* pFilePath)
{
    J3D_TRAMPOLINE_CALL(sithGamesave_NotifyRestored, pFilePath);
}

int J3DAPI sithGamesave_ReadBlockTypeLength(uint16_t* pType, unsigned int* pLength)
{
    return J3D_TRAMPOLINE_CALL(sithGamesave_ReadBlockTypeLength, pType, pLength);
}

int J3DAPI sithGamesave_SaveFile(const char* pFilename)
{
    return J3D_TRAMPOLINE_CALL(sithGamesave_SaveFile, pFilename);
}

void J3DAPI sithGamesave_ScreenShot(tVBuffer* pVBuffer)
{
    J3D_TRAMPOLINE_CALL(sithGamesave_ScreenShot, pVBuffer);
}

HBITMAP J3DAPI sithGamesave_GetScreenShotBitmap()
{
    return J3D_TRAMPOLINE_CALL(sithGamesave_GetScreenShotBitmap);
}

int J3DAPI sithGamesave_WriteScreenShot(tFileHandle fh)
{
    return J3D_TRAMPOLINE_CALL(sithGamesave_WriteScreenShot, fh);
}

int J3DAPI sithGamesave_SeekThumbNail(tFileHandle fh)
{
    return J3D_TRAMPOLINE_CALL(sithGamesave_SeekThumbNail, fh);
}

HBITMAP J3DAPI sithGamesave_LoadThumbnail(const char* pFilename)
{
    return J3D_TRAMPOLINE_CALL(sithGamesave_LoadThumbnail, pFilename);
}

void sithGamesave_Startup(void)
{
    J3D_TRAMPOLINE_CALL(sithGamesave_Startup);
}

void J3DAPI sithGamesave_Shutdown()
{
    J3D_TRAMPOLINE_CALL(sithGamesave_Shutdown);
}

void J3DAPI sithGamesave_Open()
{
    J3D_TRAMPOLINE_CALL(sithGamesave_Open);
}

void sithGamesave_CloseRestore(void)
{
    J3D_TRAMPOLINE_CALL(sithGamesave_CloseRestore);
}

void J3DAPI sithGamesave_Close()
{
    J3D_TRAMPOLINE_CALL(sithGamesave_Close);
}

void J3DAPI sithGamesave_SetPreviousLevelFilename(const char* pFilename)
{
    J3D_TRAMPOLINE_CALL(sithGamesave_SetPreviousLevelFilename, pFilename);
}

const char* J3DAPI sithGamesave_GetPreviousLevelFilename()
{
    return J3D_TRAMPOLINE_CALL(sithGamesave_GetPreviousLevelFilename);
}

const char* J3DAPI sithGamesave_GetLastFilename()
{
    return J3D_TRAMPOLINE_CALL(sithGamesave_GetLastFilename);
}

int J3DAPI sithGamesave_LoadLevelFilename(const char* pNdsFilePath, char* pDestFilename)
{
    return J3D_TRAMPOLINE_CALL(sithGamesave_LoadLevelFilename, pNdsFilePath, pDestFilename);
}

int J3DAPI sithGamesave_GetState(char** ppDestNdsFilePath)
{
    return J3D_TRAMPOLINE_CALL(sithGamesave_GetState, ppDestNdsFilePath);
}

void J3DAPI sithGamesave_SetSaveGameCallback(SithGameSaveCallback pfCallback)
{
    J3D_TRAMPOLINE_CALL(sithGamesave_SetSaveGameCallback, pfCallback);
}
