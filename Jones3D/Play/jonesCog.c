#include "jonesCog.h"
#include <j3dcore/j3dhook.h>
#include <Jones3D/RTI/symbols.h>

#define jonesCog_curCutsceneType J3D_DECL_FAR_VAR(jonesCog_curCutsceneType, int)
#define jonesCog_bInterfaceEnabled J3D_DECL_FAR_VAR(jonesCog_bInterfaceEnabled, int)
#define jonesCog_bOverlayMapVisible J3D_DECL_FAR_VAR(jonesCog_bOverlayMapVisible, int)
#define jonesCog_bStartup J3D_DECL_FAR_VAR(jonesCog_bStartup, int)

void jonesCog_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(jonesCog_Startup);
    // J3D_HOOKFUNC(jonesCog_Shutdown);
    // J3D_HOOKFUNC(jonesCog_RegisterFunctions);
    // J3D_HOOKFUNC(jonesCog_HideHealthDisplay);
    // J3D_HOOKFUNC(jonesCog_ShowHealthDisplay);
    // J3D_HOOKFUNC(jonesCog_InventoryItemChanged);
    // J3D_HOOKFUNC(jonesCog_EndLevel);
    // J3D_HOOKFUNC(jonesCog_StartCutsceneImpl);
    // J3D_HOOKFUNC(jonesCog_EndCutscene);
    // J3D_HOOKFUNC(jonesCog_UpdateDifficulty);
    // J3D_HOOKFUNC(jonesCog_EnableInterfaceImpl);
    // J3D_HOOKFUNC(jonesCog_StartCutscene);
    // J3D_HOOKFUNC(jonesCog_EnableInterface);
}

void jonesCog_ResetGlobals(void)
{
    int jonesCog_curCutsceneType_tmp = -1;
    memcpy(&jonesCog_curCutsceneType, &jonesCog_curCutsceneType_tmp, sizeof(jonesCog_curCutsceneType));
    
    int jonesCog_bInterfaceEnabled_tmp = -1;
    memcpy(&jonesCog_bInterfaceEnabled, &jonesCog_bInterfaceEnabled_tmp, sizeof(jonesCog_bInterfaceEnabled));
    
    jonesCog_bOverlayMapVisible = 0;
    jonesCog_bStartup = 0;
    memset(&jonesCog_g_bShowHealthHUD, 0, sizeof(jonesCog_g_bShowHealthHUD));
    memset(&jonesCog_g_bMenuVisible, 0, sizeof(jonesCog_g_bMenuVisible));
    memset(&jonesCog_g_bEnableGamesave, 0, sizeof(jonesCog_g_bEnableGamesave));
    memset(&jonesCog_g_dword_17EFFCC, 0, sizeof(jonesCog_g_dword_17EFFCC));
}

int jonesCog_Startup(void)
{
    return J3D_TRAMPOLINE_CALL(jonesCog_Startup);
}

void jonesCog_Shutdown(void)
{
    J3D_TRAMPOLINE_CALL(jonesCog_Shutdown);
}

int J3DAPI jonesCog_RegisterFunctions()
{
    return J3D_TRAMPOLINE_CALL(jonesCog_RegisterFunctions);
}

void J3DAPI jonesCog_HideHealthDisplay(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(jonesCog_HideHealthDisplay, pCog);
}

void J3DAPI jonesCog_ShowHealthDisplay(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(jonesCog_ShowHealthDisplay, pCog);
}

void J3DAPI jonesCog_InventoryItemChanged(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(jonesCog_InventoryItemChanged, pCog);
}

void jonesCog_EndLevel(void)
{
    J3D_TRAMPOLINE_CALL(jonesCog_EndLevel);
}

void J3DAPI jonesCog_StartCutsceneImpl(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(jonesCog_StartCutsceneImpl, pCog);
}

void J3DAPI jonesCog_EndCutscene(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(jonesCog_EndCutscene, pCog);
}

void J3DAPI jonesCog_UpdateDifficulty(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(jonesCog_UpdateDifficulty, pCog);
}

void J3DAPI jonesCog_EnableInterfaceImpl(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(jonesCog_EnableInterfaceImpl, pCog);
}

void J3DAPI jonesCog_StartCutscene(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(jonesCog_StartCutscene, pCog);
}

void J3DAPI jonesCog_EnableInterface(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(jonesCog_EnableInterface, pCog);
}
