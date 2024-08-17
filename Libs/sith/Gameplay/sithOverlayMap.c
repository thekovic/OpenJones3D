#include "sithOverlayMap.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithOverlayMap_aHintIconUVs J3D_DECL_FAR_ARRAYVAR(sithOverlayMap_aHintIconUVs, const rdVector2(*)[4])
#define sithOverlayMap_aMarkIconUVs J3D_DECL_FAR_ARRAYVAR(sithOverlayMap_aMarkIconUVs, const rdVector2(*)[4])
#define sithOverlayMap_aPlayerIconNormals J3D_DECL_FAR_ARRAYVAR(sithOverlayMap_aPlayerIconNormals, const rdVector2(*)[4])
#define sithOverlayMap_aPlayerIconUVs J3D_DECL_FAR_ARRAYVAR(sithOverlayMap_aPlayerIconUVs, const rdVector2(*)[4])
#define sithOverlayMap_aMarkIconUVNormals J3D_DECL_FAR_ARRAYVAR(sithOverlayMap_aMarkIconUVNormals, const rdVector2(*)[4])
#define sithOverlayMap_aEncEasterEggCmd J3D_DECL_FAR_ARRAYVAR(sithOverlayMap_aEncEasterEggCmd, const char(*)[8])
#define sithOverlayMap_scaleFactor J3D_DECL_FAR_VAR(sithOverlayMap_scaleFactor, float)
#define sithOverlayMap_aHintIconNames J3D_DECL_FAR_ARRAYVAR(sithOverlayMap_aHintIconNames, const char*(*)[1])
#define sithOverlayMap_aMapIconNames J3D_DECL_FAR_ARRAYVAR(sithOverlayMap_aMapIconNames, const char*(*)[1])
#define sithOverlayMap_aChalkMarkIconNames J3D_DECL_FAR_ARRAYVAR(sithOverlayMap_aChalkMarkIconNames, const char*(*)[1])
#define sithOverlayMap_aMarkBlinkUpdateInterval J3D_DECL_FAR_ARRAYVAR(sithOverlayMap_aMarkBlinkUpdateInterval, int(*)[10])
#define sithOverlayMap_orientMat J3D_DECL_FAR_VAR(sithOverlayMap_orientMat, rdMatrix34)
#define sithOverlayMap_pLocalPlayer J3D_DECL_FAR_VAR(sithOverlayMap_pLocalPlayer, SithThing*)
#define sithOverlayMap_aIndyIcons J3D_DECL_FAR_ARRAYVAR(sithOverlayMap_aIndyIcons, rdMaterial*(*)[10])
#define sithOverlayMap_aMarkIcons J3D_DECL_FAR_ARRAYVAR(sithOverlayMap_aMarkIcons, rdMaterial*(*)[10])
#define sithOverlayMap_canvasPos J3D_DECL_FAR_VAR(sithOverlayMap_canvasPos, rdVector2)
#define sithOverlayMap_config J3D_DECL_FAR_VAR(sithOverlayMap_config, SithOverlayMapConfig)
#define sithOverlayMap_pCurWorld J3D_DECL_FAR_VAR(sithOverlayMap_pCurWorld, SithWorld*)
#define sithOverlayMap_aHintIcons J3D_DECL_FAR_ARRAYVAR(sithOverlayMap_aHintIcons, rdMaterial*(*)[10])
#define sithOverlayMap_vertexScale J3D_DECL_FAR_VAR(sithOverlayMap_vertexScale, float)
#define sithOverlayMap_curHintNum J3D_DECL_FAR_VAR(sithOverlayMap_curHintNum, int)
#define sithOverlayMap_bMapVisible J3D_DECL_FAR_VAR(sithOverlayMap_bMapVisible, int)
#define sithOverlayMap_bNoSolvedHintCount J3D_DECL_FAR_VAR(sithOverlayMap_bNoSolvedHintCount, int)
#define sithOverlayMap_curHintIconNum J3D_DECL_FAR_VAR(sithOverlayMap_curHintIconNum, int)
#define sithOverlayMap_curIndyIconNum J3D_DECL_FAR_VAR(sithOverlayMap_curIndyIconNum, int)
#define sithOverlayMap_curMarkIconNum J3D_DECL_FAR_VAR(sithOverlayMap_curMarkIconNum, int)
#define sithOverlayMap_bOpened J3D_DECL_FAR_VAR(sithOverlayMap_bOpened, int)
#define sithOverlayMap_bShowHints J3D_DECL_FAR_VAR(sithOverlayMap_bShowHints, int)
#define sithOverlayMap_markBlinkStep J3D_DECL_FAR_VAR(sithOverlayMap_markBlinkStep, int)
#define sithOverlayMap_msecLastMarkBlinkUpdate J3D_DECL_FAR_VAR(sithOverlayMap_msecLastMarkBlinkUpdate, unsigned int)

void sithOverlayMap_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithOverlayMap_ConsoleCallback);
    // J3D_HOOKFUNC(sithOverlayMap_Open);
    // J3D_HOOKFUNC(sithOverlayMap_Close);
    // J3D_HOOKFUNC(sithOverlayMap_IsMapVisible);
    // J3D_HOOKFUNC(sithOverlayMap_ToggleMap);
    // J3D_HOOKFUNC(sithOverlayMap_ZoomIn);
    // J3D_HOOKFUNC(sithOverlayMap_ZoomOut);
    // J3D_HOOKFUNC(sithOverlayMap_Draw);
    // J3D_HOOKFUNC(sithOverlayMap_SetShowHints);
    // J3D_HOOKFUNC(sithOverlayMap_EnableMapRotation);
    // J3D_HOOKFUNC(sithOverlayMap_GetMapRotation);
    // J3D_HOOKFUNC(sithOverlayMap_GetShowHints);
    // J3D_HOOKFUNC(sithOverlayMap_UpdateHints);
    // J3D_HOOKFUNC(sithOverlayMap_SetHintSolved);
    // J3D_HOOKFUNC(sithOverlayMap_SetHintUnsolved);
    // J3D_HOOKFUNC(sithOverlayMap_GetNumSeenHints);
    // J3D_HOOKFUNC(sithOverlayMap_RenderSectors);
    // J3D_HOOKFUNC(sithOverlayMap_RenderSector);
    // J3D_HOOKFUNC(sithOverlayMap_DrawPlayer);
    // J3D_HOOKFUNC(sithOverlayMap_DrawMark);
    // J3D_HOOKFUNC(sithOverlayMap_CanRenderSurface);
}

void sithOverlayMap_ResetGlobals(void)
{
    const rdVector2 sithOverlayMap_aHintIconUVs_tmp[4] = {
      { -0.075000003f, -0.075000003f },
      { 0.075000003f, -0.075000003f },
      { 0.075000003f, 0.075000003f },
      { -0.075000003f, 0.075000003f }
    };
    memcpy((rdVector2 *)&sithOverlayMap_aHintIconUVs, &sithOverlayMap_aHintIconUVs_tmp, sizeof(sithOverlayMap_aHintIconUVs));
    
    const rdVector2 sithOverlayMap_aMarkIconUVs_tmp[4] = {
      { -0.075000003f, -0.075000003f },
      { 0.075000003f, -0.075000003f },
      { 0.075000003f, 0.075000003f },
      { -0.075000003f, 0.075000003f }
    };
    memcpy((rdVector2 *)&sithOverlayMap_aMarkIconUVs, &sithOverlayMap_aMarkIconUVs_tmp, sizeof(sithOverlayMap_aMarkIconUVs));
    
    const rdVector2 sithOverlayMap_aPlayerIconNormals_tmp[4] = { { -0.1f, -0.1f }, { 0.1f, -0.1f }, { 0.1f, 0.1f }, { -0.1f, 0.1f } };
    memcpy((rdVector2 *)&sithOverlayMap_aPlayerIconNormals, &sithOverlayMap_aPlayerIconNormals_tmp, sizeof(sithOverlayMap_aPlayerIconNormals));
    
    const rdVector2 sithOverlayMap_aPlayerIconUVs_tmp[4] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
    memcpy((rdVector2 *)&sithOverlayMap_aPlayerIconUVs, &sithOverlayMap_aPlayerIconUVs_tmp, sizeof(sithOverlayMap_aPlayerIconUVs));
    
    const rdVector2 sithOverlayMap_aMarkIconUVNormals_tmp[4] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
    memcpy((rdVector2 *)&sithOverlayMap_aMarkIconUVNormals, &sithOverlayMap_aMarkIconUVNormals_tmp, sizeof(sithOverlayMap_aMarkIconUVNormals));
    
    const char sithOverlayMap_aEncEasterEggCmd_tmp[8] = { '\0', '\x06', '\xFF', '\x01', '\x05', '\xFF', '\t', '\a' };
    memcpy((char *)&sithOverlayMap_aEncEasterEggCmd, &sithOverlayMap_aEncEasterEggCmd_tmp, sizeof(sithOverlayMap_aEncEasterEggCmd));
    
    float sithOverlayMap_scaleFactor_tmp = 75.0f;
    memcpy(&sithOverlayMap_scaleFactor, &sithOverlayMap_scaleFactor_tmp, sizeof(sithOverlayMap_scaleFactor));
    
    const char *sithOverlayMap_aHintIconNames_tmp[1] = { "hinticon.mat" };
    memcpy((char **)&sithOverlayMap_aHintIconNames, &sithOverlayMap_aHintIconNames_tmp, sizeof(sithOverlayMap_aHintIconNames));
    
    const char *sithOverlayMap_aMapIconNames_tmp[1] = { "indyicon.mat" };
    memcpy((char **)&sithOverlayMap_aMapIconNames, &sithOverlayMap_aMapIconNames_tmp, sizeof(sithOverlayMap_aMapIconNames));
    
    const char *sithOverlayMap_aChalkMarkIconNames_tmp[1] = { "gen_4icon_chalk_diamond.mat" };
    memcpy((char **)&sithOverlayMap_aChalkMarkIconNames, &sithOverlayMap_aChalkMarkIconNames_tmp, sizeof(sithOverlayMap_aChalkMarkIconNames));
    
    int sithOverlayMap_aMarkBlinkUpdateInterval_tmp[10] = { 135, 55, 40, 20, 8, 4, 2, 1, 0, 75 };
    memcpy(&sithOverlayMap_aMarkBlinkUpdateInterval, &sithOverlayMap_aMarkBlinkUpdateInterval_tmp, sizeof(sithOverlayMap_aMarkBlinkUpdateInterval));
    
    memset(&sithOverlayMap_orientMat, 0, sizeof(sithOverlayMap_orientMat));
    memset(&sithOverlayMap_pLocalPlayer, 0, sizeof(sithOverlayMap_pLocalPlayer));
    memset(&sithOverlayMap_aIndyIcons, 0, sizeof(sithOverlayMap_aIndyIcons));
    memset(&sithOverlayMap_aMarkIcons, 0, sizeof(sithOverlayMap_aMarkIcons));
    memset(&sithOverlayMap_canvasPos, 0, sizeof(sithOverlayMap_canvasPos));
    memset(&sithOverlayMap_config, 0, sizeof(sithOverlayMap_config));
    memset(&sithOverlayMap_pCurWorld, 0, sizeof(sithOverlayMap_pCurWorld));
    memset(&sithOverlayMap_aHintIcons, 0, sizeof(sithOverlayMap_aHintIcons));
    memset(&sithOverlayMap_vertexScale, 0, sizeof(sithOverlayMap_vertexScale));
    memset(&sithOverlayMap_curHintNum, 0, sizeof(sithOverlayMap_curHintNum));
    memset(&sithOverlayMap_bMapVisible, 0, sizeof(sithOverlayMap_bMapVisible));
    memset(&sithOverlayMap_bNoSolvedHintCount, 0, sizeof(sithOverlayMap_bNoSolvedHintCount));
    memset(&sithOverlayMap_curHintIconNum, 0, sizeof(sithOverlayMap_curHintIconNum));
    memset(&sithOverlayMap_curIndyIconNum, 0, sizeof(sithOverlayMap_curIndyIconNum));
    memset(&sithOverlayMap_curMarkIconNum, 0, sizeof(sithOverlayMap_curMarkIconNum));
    memset(&sithOverlayMap_bOpened, 0, sizeof(sithOverlayMap_bOpened));
    memset(&sithOverlayMap_bShowHints, 0, sizeof(sithOverlayMap_bShowHints));
    memset(&sithOverlayMap_markBlinkStep, 0, sizeof(sithOverlayMap_markBlinkStep));
    memset(&sithOverlayMap_msecLastMarkBlinkUpdate, 0, sizeof(sithOverlayMap_msecLastMarkBlinkUpdate));
}

int J3DAPI sithOverlayMap_ConsoleCallback(const SithConsoleCommand* pFunc, const char* pArg)
{
    return J3D_TRAMPOLINE_CALL(sithOverlayMap_ConsoleCallback, pFunc, pArg);
}

int J3DAPI sithOverlayMap_Open(SithOverlayMapConfig* pConfig)
{
    return J3D_TRAMPOLINE_CALL(sithOverlayMap_Open, pConfig);
}

void sithOverlayMap_Close(void)
{
    J3D_TRAMPOLINE_CALL(sithOverlayMap_Close);
}

int sithOverlayMap_IsMapVisible(void)
{
    return J3D_TRAMPOLINE_CALL(sithOverlayMap_IsMapVisible);
}

int sithOverlayMap_ToggleMap(void)
{
    return J3D_TRAMPOLINE_CALL(sithOverlayMap_ToggleMap);
}

void J3DAPI sithOverlayMap_ZoomIn()
{
    J3D_TRAMPOLINE_CALL(sithOverlayMap_ZoomIn);
}

void J3DAPI sithOverlayMap_ZoomOut()
{
    J3D_TRAMPOLINE_CALL(sithOverlayMap_ZoomOut);
}

void sithOverlayMap_Draw(void)
{
    J3D_TRAMPOLINE_CALL(sithOverlayMap_Draw);
}

void J3DAPI sithOverlayMap_SetShowHints(int bShow)
{
    J3D_TRAMPOLINE_CALL(sithOverlayMap_SetShowHints, bShow);
}

void J3DAPI sithOverlayMap_EnableMapRotation(int bEnable)
{
    J3D_TRAMPOLINE_CALL(sithOverlayMap_EnableMapRotation, bEnable);
}

int J3DAPI sithOverlayMap_GetMapRotation()
{
    return J3D_TRAMPOLINE_CALL(sithOverlayMap_GetMapRotation);
}

int sithOverlayMap_GetShowHints(void)
{
    return J3D_TRAMPOLINE_CALL(sithOverlayMap_GetShowHints);
}

int sithOverlayMap_UpdateHints(void)
{
    return J3D_TRAMPOLINE_CALL(sithOverlayMap_UpdateHints);
}

int J3DAPI sithOverlayMap_SetHintSolved(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithOverlayMap_SetHintSolved, pThing);
}

int J3DAPI sithOverlayMap_SetHintUnsolved(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithOverlayMap_SetHintUnsolved, pThing);
}

void J3DAPI sithOverlayMap_GetNumSeenHints(int* pOutNumSeenHints, int* pOutNumHints)
{
    J3D_TRAMPOLINE_CALL(sithOverlayMap_GetNumSeenHints, pOutNumSeenHints, pOutNumHints);
}

void J3DAPI sithOverlayMap_RenderSectors(SithSector* pSector)
{
    J3D_TRAMPOLINE_CALL(sithOverlayMap_RenderSectors, pSector);
}

int J3DAPI sithOverlayMap_RenderSector(SithSector* pSector)
{
    return J3D_TRAMPOLINE_CALL(sithOverlayMap_RenderSector, pSector);
}

void J3DAPI sithOverlayMap_DrawPlayer()
{
    J3D_TRAMPOLINE_CALL(sithOverlayMap_DrawPlayer);
}

void J3DAPI sithOverlayMap_DrawMark(const SithThing* pMark, const rdMaterial* pIcon, const rdVector2* aVertices, int bZLevelColor, int bBlink)
{
    J3D_TRAMPOLINE_CALL(sithOverlayMap_DrawMark, pMark, pIcon, aVertices, bZLevelColor, bBlink);
}

int J3DAPI sithOverlayMap_CanRenderSurface(SithSurface* pSurface, int vertIdx, int nextVertIdx)
{
    return J3D_TRAMPOLINE_CALL(sithOverlayMap_CanRenderSurface, pSurface, vertIdx, nextVertIdx);
}
