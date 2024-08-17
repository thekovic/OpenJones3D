#ifndef JONES3D_JONESCOG_H
#define JONES3D_JONESCOG_H
#include <Jones3D/types.h>
#include <Jones3D/RTI/addresses.h>
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define jonesCog_g_bShowHealthHUD J3D_DECL_FAR_VAR(jonesCog_g_bShowHealthHUD, int)
// extern int jonesCog_g_bShowHealthHUD;

#define jonesCog_g_bMenuVisible J3D_DECL_FAR_VAR(jonesCog_g_bMenuVisible, int)
// extern int jonesCog_g_bMenuVisible;

#define jonesCog_g_bEnableGamesave J3D_DECL_FAR_VAR(jonesCog_g_bEnableGamesave, int)
// extern int jonesCog_g_bEnableGamesave;

#define jonesCog_g_dword_17EFFCC J3D_DECL_FAR_VAR(jonesCog_g_dword_17EFFCC, int)
// extern int jonesCog_g_dword_17EFFCC;

int jonesCog_Startup(void);
void jonesCog_Shutdown(void);
int J3DAPI jonesCog_RegisterFunctions();
void J3DAPI jonesCog_HideHealthDisplay(SithCog* pCog);
void J3DAPI jonesCog_ShowHealthDisplay(SithCog* pCog);
void J3DAPI jonesCog_InventoryItemChanged(SithCog* pCog);
void jonesCog_EndLevel(void);
void J3DAPI jonesCog_StartCutsceneImpl(SithCog* pCog);
void J3DAPI jonesCog_EndCutscene(SithCog* pCog);
void J3DAPI jonesCog_UpdateDifficulty(SithCog* pCog);
void J3DAPI jonesCog_EnableInterfaceImpl(SithCog* pCog);
void J3DAPI jonesCog_StartCutscene(SithCog* pCog);
void J3DAPI jonesCog_EnableInterface(SithCog* pCog);

// Helper hooking functions
void jonesCog_InstallHooks(void);
void jonesCog_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // JONES3D_JONESCOG_H
