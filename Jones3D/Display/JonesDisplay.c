#include "JonesDisplay.h"
#include <j3dcore/j3dhook.h>
#include <Jones3D/RTI/symbols.h>

#define JonesDisplay_wallLineColor J3D_DECL_FAR_VAR(JonesDisplay_wallLineColor, rdVector4)
#define JonesDisplay_primaryDisplayNum J3D_DECL_FAR_VAR(JonesDisplay_primaryDisplayNum, int)
#define JonesDisplay_backBufferWidth J3D_DECL_FAR_VAR(JonesDisplay_backBufferWidth, unsigned int)
#define JonesDisplay_backBufferHeight J3D_DECL_FAR_VAR(JonesDisplay_backBufferHeight, unsigned int)
#define JonesDisplay_pCanvas J3D_DECL_FAR_VAR(JonesDisplay_pCanvas, rdCanvas*)
#define JonesDisplay_bDualMonitor J3D_DECL_FAR_VAR(JonesDisplay_bDualMonitor, int)
#define JonesDisplay_pWallpaper J3D_DECL_FAR_VAR(JonesDisplay_pWallpaper, rdWallpaper*)
#define JonesDisplay_pWallLine J3D_DECL_FAR_VAR(JonesDisplay_pWallLine, rdWallLine*)
#define JonesDisplay_hSndLoadMusic J3D_DECL_FAR_VAR(JonesDisplay_hSndLoadMusic, tSoundHandle)
#define JonesDisplay_hSndChannelLoadMusic J3D_DECL_FAR_VAR(JonesDisplay_hSndChannelLoadMusic, tSoundChannelHandle)
#define JonesDisplay_openLoadScreenCounter J3D_DECL_FAR_VAR(JonesDisplay_openLoadScreenCounter, int)
#define JonesDisplay_bUpdateLoadScreen J3D_DECL_FAR_VAR(JonesDisplay_bUpdateLoadScreen, int)
#define JonesDisplay_loadScreenState J3D_DECL_FAR_VAR(JonesDisplay_loadScreenState, int)
#define JonesDisplay_bPrimaryLoadMusic J3D_DECL_FAR_VAR(JonesDisplay_bPrimaryLoadMusic, int)
#define JonesDisplay_dword_553328 J3D_DECL_FAR_VAR(JonesDisplay_dword_553328, int)
#define JonesDisplay_dword_55332C J3D_DECL_FAR_VAR(JonesDisplay_dword_55332C, int)

void JonesDisplay_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(JonesDisplay_Startup);
    // J3D_HOOKFUNC(JonesDisplay_Shutdown);
    // J3D_HOOKFUNC(JonesDisplay_Restart);
    // J3D_HOOKFUNC(JonesDisplay_UpdateCur3DDevice);
    // J3D_HOOKFUNC(JonesDisplay_Open);
    // J3D_HOOKFUNC(JonesDisplay_Close);
    // J3D_HOOKFUNC(JonesDisplay_EnableDualMonitor);
    // J3D_HOOKFUNC(JonesDisplay_UpdateDualScreenWindowSize);
    // J3D_HOOKFUNC(JonesDisplay_OpenLoadScreen);
    // J3D_HOOKFUNC(JonesDisplay_CloseLoadScreen);
    // J3D_HOOKFUNC(JonesDisplay_UpdateLoadProgress);
}

void JonesDisplay_ResetGlobals(void)
{
    rdVector4 JonesDisplay_wallLineColor_tmp = { { 1.0f }, { 0.0f }, { 0.0f }, { 1.0f } };
    memcpy(&JonesDisplay_wallLineColor, &JonesDisplay_wallLineColor_tmp, sizeof(JonesDisplay_wallLineColor));
    
    int JonesDisplay_primaryDisplayNum_tmp = 1;
    memcpy(&JonesDisplay_primaryDisplayNum, &JonesDisplay_primaryDisplayNum_tmp, sizeof(JonesDisplay_primaryDisplayNum));
    
    memset(&JonesDisplay_backBufferWidth, 0, sizeof(JonesDisplay_backBufferWidth));
    memset(&JonesDisplay_backBufferHeight, 0, sizeof(JonesDisplay_backBufferHeight));
    memset(&JonesDisplay_pCanvas, 0, sizeof(JonesDisplay_pCanvas));
    memset(&JonesDisplay_bDualMonitor, 0, sizeof(JonesDisplay_bDualMonitor));
    memset(&JonesDisplay_pWallpaper, 0, sizeof(JonesDisplay_pWallpaper));
    memset(&JonesDisplay_pWallLine, 0, sizeof(JonesDisplay_pWallLine));
    memset(&JonesDisplay_hSndLoadMusic, 0, sizeof(JonesDisplay_hSndLoadMusic));
    memset(&JonesDisplay_hSndChannelLoadMusic, 0, sizeof(JonesDisplay_hSndChannelLoadMusic));
    memset(&JonesDisplay_openLoadScreenCounter, 0, sizeof(JonesDisplay_openLoadScreenCounter));
    memset(&JonesDisplay_bUpdateLoadScreen, 0, sizeof(JonesDisplay_bUpdateLoadScreen));
    memset(&JonesDisplay_loadScreenState, 0, sizeof(JonesDisplay_loadScreenState));
    memset(&JonesDisplay_bPrimaryLoadMusic, 0, sizeof(JonesDisplay_bPrimaryLoadMusic));
    memset(&JonesDisplay_dword_553328, 0, sizeof(JonesDisplay_dword_553328));
    memset(&JonesDisplay_dword_55332C, 0, sizeof(JonesDisplay_dword_55332C));
}

// Returns 0 for success and 1 indecating error
int J3DAPI JonesDisplay_Startup(JonesDisplaySettings* pSettings)
{
    return J3D_TRAMPOLINE_CALL(JonesDisplay_Startup, pSettings);
}

void JonesDisplay_Shutdown(void)
{
    J3D_TRAMPOLINE_CALL(JonesDisplay_Shutdown);
}

int J3DAPI JonesDisplay_Restart(JonesDisplaySettings* pSettings)
{
    return J3D_TRAMPOLINE_CALL(JonesDisplay_Restart, pSettings);
}

void J3DAPI JonesDisplay_UpdateCur3DDevice(const StdDisplayEnvironment* pEnv, JonesDisplaySettings* pDisplaySettings)
{
    J3D_TRAMPOLINE_CALL(JonesDisplay_UpdateCur3DDevice, pEnv, pDisplaySettings);
}

int J3DAPI JonesDisplay_Open(JonesDisplaySettings* pSettings)
{
    return J3D_TRAMPOLINE_CALL(JonesDisplay_Open, pSettings);
}

void JonesDisplay_Close(void)
{
    J3D_TRAMPOLINE_CALL(JonesDisplay_Close);
}

void J3DAPI JonesDisplay_EnableDualMonitor(int bEnable)
{
    J3D_TRAMPOLINE_CALL(JonesDisplay_EnableDualMonitor, bEnable);
}

int J3DAPI JonesDisplay_UpdateDualScreenWindowSize(const JonesDisplaySettings* pSettings)
{
    return J3D_TRAMPOLINE_CALL(JonesDisplay_UpdateDualScreenWindowSize, pSettings);
}

void J3DAPI JonesDisplay_OpenLoadScreen(const char* pMatFilePath, float wlStartX, float wlStartY, float wlEndX, float wlEndY, int bPrimaryMusicTheme)
{
    J3D_TRAMPOLINE_CALL(JonesDisplay_OpenLoadScreen, pMatFilePath, wlStartX, wlStartY, wlEndX, wlEndY, bPrimaryMusicTheme);
}

void JonesDisplay_CloseLoadScreen(void)
{
    J3D_TRAMPOLINE_CALL(JonesDisplay_CloseLoadScreen);
}

void J3DAPI JonesDisplay_UpdateLoadProgress(float progress)
{
    J3D_TRAMPOLINE_CALL(JonesDisplay_UpdateLoadProgress, progress);
}
