#include "sithCamera.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithCamera_aCycleCamIndices J3D_DECL_FAR_ARRAYVAR(sithCamera_aCycleCamIndices, int(*)[3])
#define sithCamera_vecExtCameraLookOffset J3D_DECL_FAR_VAR(sithCamera_vecExtCameraLookOffset, rdVector3)
#define sithCamera_vecDefaultExtCamLookOffset J3D_DECL_FAR_VAR(sithCamera_vecDefaultExtCamLookOffset, rdVector3)
#define sithCamera_vecExtCameraOffset J3D_DECL_FAR_VAR(sithCamera_vecExtCameraOffset, rdVector3)
#define sithCamera_vecDefaultCameraOffset J3D_DECL_FAR_VAR(sithCamera_vecDefaultCameraOffset, const rdVector3)
#define sithCamera_vecDefaultExtCamOffset J3D_DECL_FAR_VAR(sithCamera_vecDefaultExtCamOffset, rdVector3)
#define sithCamera_vecDefaulExtCameraOffset J3D_DECL_FAR_VAR(sithCamera_vecDefaulExtCameraOffset, rdVector3)
#define sithCamera_vecCameraOffsetClimbingUp J3D_DECL_FAR_VAR(sithCamera_vecCameraOffsetClimbingUp, rdVector3)
#define sithCamera_vecExtCameraClimbDownOffset J3D_DECL_FAR_VAR(sithCamera_vecExtCameraClimbDownOffset, rdVector3)
#define sithCamera_vecCameraOffsetClimbingLeft J3D_DECL_FAR_VAR(sithCamera_vecCameraOffsetClimbingLeft, rdVector3)
#define sithCamera_vecCameraOffsetClimbingRight J3D_DECL_FAR_VAR(sithCamera_vecCameraOffsetClimbingRight, rdVector3)
#define sithCamera_vecCameraOffsetSlideForward J3D_DECL_FAR_VAR(sithCamera_vecCameraOffsetSlideForward, rdVector3)
#define sithCamera_vecCameraOffsetSlideBackward J3D_DECL_FAR_VAR(sithCamera_vecCameraOffsetSlideBackward, rdVector3)
#define sithCamera_vecCameraOffsetJumpRollback J3D_DECL_FAR_VAR(sithCamera_vecCameraOffsetJumpRollback, rdVector3)
#define sithCamera_vecOffsetCamType40 J3D_DECL_FAR_VAR(sithCamera_vecOffsetCamType40, rdVector3)
#define sithCamera_vecOffsetCamType20 J3D_DECL_FAR_VAR(sithCamera_vecOffsetCamType20, rdVector3)
#define sithCamera_vecExtCameraPrevLookOffset J3D_DECL_FAR_VAR(sithCamera_vecExtCameraPrevLookOffset, rdVector3)
#define sithCamera_orientCamType20 J3D_DECL_FAR_VAR(sithCamera_orientCamType20, rdMatrix34)
#define sithCamera_secFocusThingFadeInTime J3D_DECL_FAR_VAR(sithCamera_secFocusThingFadeInTime, float)
#define sithCamera_bFocusThingInvisible J3D_DECL_FAR_VAR(sithCamera_bFocusThingInvisible, int)
#define sithCamera_bUpdateCameraOffset J3D_DECL_FAR_VAR(sithCamera_bUpdateCameraOffset, int)
#define sithCamera_bStartup J3D_DECL_FAR_VAR(sithCamera_bStartup, int)
#define sithCamera_bOpen J3D_DECL_FAR_VAR(sithCamera_bOpen, int)
#define sithCamera_secLookOffsetTranslateDelta J3D_DECL_FAR_VAR(sithCamera_secLookOffsetTranslateDelta, float)

void sithCamera_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithCamera_Startup);
    // J3D_HOOKFUNC(sithCamera_Shutdown);
    // J3D_HOOKFUNC(sithCamera_Open);
    // J3D_HOOKFUNC(sithCamera_Close);
    // J3D_HOOKFUNC(sithCamera_ResetAllCameras);
    // J3D_HOOKFUNC(sithCamera_NewEntry);
    // J3D_HOOKFUNC(sithCamera_FreeEntry);
    // J3D_HOOKFUNC(sithCamera_SetCameraCanvas);
    // J3D_HOOKFUNC(sithCamera_SetCurrentCamera);
    // J3D_HOOKFUNC(sithCamera_CycleCamera);
    // J3D_HOOKFUNC(sithCamera_SetCurrentToCycleCamera);
    // J3D_HOOKFUNC(sithCamera_SetCameraFocus);
    // J3D_HOOKFUNC(sithCamera_SetCameraFOV);
    // J3D_HOOKFUNC(sithCamera_SetCameraPosition);
    // J3D_HOOKFUNC(sithCamera_GetCameraPosition);
    // J3D_HOOKFUNC(sithCamera_SetExtCameraOffset);
    // J3D_HOOKFUNC(sithCamera_SetExtCameraLookOffset);
    // J3D_HOOKFUNC(sithCamera_RestoreExtCamera);
    // J3D_HOOKFUNC(sithCamera_GetPrimaryFocus);
    // J3D_HOOKFUNC(sithCamera_GetSecondaryFocus);
    // J3D_HOOKFUNC(sithCamera_Update);
    // J3D_HOOKFUNC(sithCamera_RenderScene);
    // J3D_HOOKFUNC(sithCamera_SetPOVShake);
    // J3D_HOOKFUNC(sithCamera_SearchSectorInRadius);
    // J3D_HOOKFUNC(sithCamera_SetCameraStateFlags);
    // J3D_HOOKFUNC(sithCamera_GetCameraStateFlags);
}

void sithCamera_ResetGlobals(void)
{
    int sithCamera_aCycleCamIndices_tmp[3] = { 0, 1, 6 };
    memcpy(&sithCamera_aCycleCamIndices, &sithCamera_aCycleCamIndices_tmp, sizeof(sithCamera_aCycleCamIndices));
    
    rdVector3 sithCamera_vecExtCameraLookOffset_tmp = { { 0.0f }, { 0.02f }, { 0.02f } };
    memcpy(&sithCamera_vecExtCameraLookOffset, &sithCamera_vecExtCameraLookOffset_tmp, sizeof(sithCamera_vecExtCameraLookOffset));
    
    rdVector3 sithCamera_vecDefaultExtCamLookOffset_tmp = { { 0.0f }, { 0.02f }, { 0.02f } };
    memcpy(&sithCamera_vecDefaultExtCamLookOffset, &sithCamera_vecDefaultExtCamLookOffset_tmp, sizeof(sithCamera_vecDefaultExtCamLookOffset));
    
    rdVector3 sithCamera_vecExtCameraOffset_tmp = { { 0.0f }, { -0.2f }, { 0.064999998f } };
    memcpy(&sithCamera_vecExtCameraOffset, &sithCamera_vecExtCameraOffset_tmp, sizeof(sithCamera_vecExtCameraOffset));
    
    const rdVector3 sithCamera_vecDefaultCameraOffset_tmp = { { 0.0f }, { -0.22f }, { 0.15000001f } };
    memcpy((rdVector3 *)&sithCamera_vecDefaultCameraOffset, &sithCamera_vecDefaultCameraOffset_tmp, sizeof(sithCamera_vecDefaultCameraOffset));
    
    rdVector3 sithCamera_vecDefaultExtCamOffset_tmp = { { 0.0f }, { -0.2f }, { 0.064999998f } };
    memcpy(&sithCamera_vecDefaultExtCamOffset, &sithCamera_vecDefaultExtCamOffset_tmp, sizeof(sithCamera_vecDefaultExtCamOffset));
    
    rdVector3 sithCamera_vecDefaulExtCameraOffset_tmp = { { 0.0f }, { -0.2f }, { 0.14f } };
    memcpy(&sithCamera_vecDefaulExtCameraOffset, &sithCamera_vecDefaulExtCameraOffset_tmp, sizeof(sithCamera_vecDefaulExtCameraOffset));
    
    rdVector3 sithCamera_vecCameraOffsetClimbingUp_tmp = { { 0.0f }, { -0.2f }, { -0.0099999998f } };
    memcpy(&sithCamera_vecCameraOffsetClimbingUp, &sithCamera_vecCameraOffsetClimbingUp_tmp, sizeof(sithCamera_vecCameraOffsetClimbingUp));
    
    rdVector3 sithCamera_vecExtCameraClimbDownOffset_tmp = { { 0.0f }, { -0.2f }, { 0.16500001f } };
    memcpy(&sithCamera_vecExtCameraClimbDownOffset, &sithCamera_vecExtCameraClimbDownOffset_tmp, sizeof(sithCamera_vecExtCameraClimbDownOffset));
    
    rdVector3 sithCamera_vecCameraOffsetClimbingLeft_tmp = { { 0.1f }, { -0.2f }, { 0.064999998f } };
    memcpy(&sithCamera_vecCameraOffsetClimbingLeft, &sithCamera_vecCameraOffsetClimbingLeft_tmp, sizeof(sithCamera_vecCameraOffsetClimbingLeft));
    
    rdVector3 sithCamera_vecCameraOffsetClimbingRight_tmp = { { -0.1f }, { -0.2f }, { 0.064999998f } };
    memcpy(&sithCamera_vecCameraOffsetClimbingRight, &sithCamera_vecCameraOffsetClimbingRight_tmp, sizeof(sithCamera_vecCameraOffsetClimbingRight));
    
    rdVector3 sithCamera_vecCameraOffsetSlideForward_tmp = { { 0.16500001f }, { 0.0099999998f }, { 0.17f } };
    memcpy(&sithCamera_vecCameraOffsetSlideForward, &sithCamera_vecCameraOffsetSlideForward_tmp, sizeof(sithCamera_vecCameraOffsetSlideForward));
    
    rdVector3 sithCamera_vecCameraOffsetSlideBackward_tmp = { { 0.16500001f }, { -0.2f }, { 0.029999999f } };
    memcpy(&sithCamera_vecCameraOffsetSlideBackward, &sithCamera_vecCameraOffsetSlideBackward_tmp, sizeof(sithCamera_vecCameraOffsetSlideBackward));
    
    rdVector3 sithCamera_vecCameraOffsetJumpRollback_tmp = { { 0.0f }, { -0.30000001f }, { 0.064999998f } };
    memcpy(&sithCamera_vecCameraOffsetJumpRollback, &sithCamera_vecCameraOffsetJumpRollback_tmp, sizeof(sithCamera_vecCameraOffsetJumpRollback));
    
    rdVector3 sithCamera_vecOffsetCamType40_tmp = { { 0.0f }, { 1.0f }, { 1.0f } };
    memcpy(&sithCamera_vecOffsetCamType40, &sithCamera_vecOffsetCamType40_tmp, sizeof(sithCamera_vecOffsetCamType40));
    
    rdVector3 sithCamera_vecOffsetCamType20_tmp = { { 0.0f }, { -0.2f }, { 0.064999998f } };
    memcpy(&sithCamera_vecOffsetCamType20, &sithCamera_vecOffsetCamType20_tmp, sizeof(sithCamera_vecOffsetCamType20));
    
    memset(&sithCamera_vecExtCameraPrevLookOffset, 0, sizeof(sithCamera_vecExtCameraPrevLookOffset));
    memset(&sithCamera_orientCamType20, 0, sizeof(sithCamera_orientCamType20));
    memset(&sithCamera_g_pCurCamera, 0, sizeof(sithCamera_g_pCurCamera));
    memset(&sithCamera_g_bExtCameraLookMode, 0, sizeof(sithCamera_g_bExtCameraLookMode));
    memset(&sithCamera_secFocusThingFadeInTime, 0, sizeof(sithCamera_secFocusThingFadeInTime));
    memset(&sithCamera_bFocusThingInvisible, 0, sizeof(sithCamera_bFocusThingInvisible));
    memset(&sithCamera_bUpdateCameraOffset, 0, sizeof(sithCamera_bUpdateCameraOffset));
    memset(&sithCamera_bStartup, 0, sizeof(sithCamera_bStartup));
    memset(&sithCamera_bOpen, 0, sizeof(sithCamera_bOpen));
    memset(&sithCamera_secLookOffsetTranslateDelta, 0, sizeof(sithCamera_secLookOffsetTranslateDelta));
    memset(&sithCamera_g_camSpot, 0, sizeof(sithCamera_g_camSpot));
    memset(&sithCamera_g_aCameras, 0, sizeof(sithCamera_g_aCameras));
    memset(&sithCamera_g_bCurCameraSet, 0, sizeof(sithCamera_g_bCurCameraSet));
    memset(&sithCamera_g_stateFlags, 0, sizeof(sithCamera_g_stateFlags));
    memset(&sithCamera_g_curCycleCamNum, 0, sizeof(sithCamera_g_curCycleCamNum));
    memset(&sithCamera_g_vecCameraPosOffset, 0, sizeof(sithCamera_g_vecCameraPosOffset));
    memset(&sithCamera_g_vecCameraAngleOffset, 0, sizeof(sithCamera_g_vecCameraAngleOffset));
    memset(&sithCamera_g_cameraPosDelta, 0, sizeof(sithCamera_g_cameraPosDelta));
    memset(&sithCamera_g_cameraAngleDelta, 0, sizeof(sithCamera_g_cameraAngleDelta));
    memset(&sithCamera_g_orientCamType80, 0, sizeof(sithCamera_g_orientCamType80));
    memset(&sithCamera_g_camLookSpot, 0, sizeof(sithCamera_g_camLookSpot));
}

int sithCamera_Startup(void)
{
    return J3D_TRAMPOLINE_CALL(sithCamera_Startup);
}

void sithCamera_Shutdown(void)
{
    J3D_TRAMPOLINE_CALL(sithCamera_Shutdown);
}

int J3DAPI sithCamera_Open(rdCanvas* pCanvas, float aspect)
{
    return J3D_TRAMPOLINE_CALL(sithCamera_Open, pCanvas, aspect);
}

void J3DAPI sithCamera_Close()
{
    J3D_TRAMPOLINE_CALL(sithCamera_Close);
}

void sithCamera_ResetAllCameras(void)
{
    J3D_TRAMPOLINE_CALL(sithCamera_ResetAllCameras);
}

int J3DAPI sithCamera_NewEntry(SithCamera* pCamera, int a2, SithCameraType type, float fov, float aspect, rdCanvas* pCanvas, SithThing* pPrimaryFocus, SithThing* pSecondaryFocus)
{
    return J3D_TRAMPOLINE_CALL(sithCamera_NewEntry, pCamera, a2, type, fov, aspect, pCanvas, pPrimaryFocus, pSecondaryFocus);
}

void J3DAPI sithCamera_FreeEntry(SithCamera* pCamera)
{
    J3D_TRAMPOLINE_CALL(sithCamera_FreeEntry, pCamera);
}

void J3DAPI sithCamera_SetCameraCanvas(SithCamera* pCamera, float aspect, rdCanvas* pCanvas)
{
    J3D_TRAMPOLINE_CALL(sithCamera_SetCameraCanvas, pCamera, aspect, pCanvas);
}

int J3DAPI sithCamera_SetCurrentCamera(SithCamera* pCamera)
{
    return J3D_TRAMPOLINE_CALL(sithCamera_SetCurrentCamera, pCamera);
}

void sithCamera_CycleCamera(void)
{
    J3D_TRAMPOLINE_CALL(sithCamera_CycleCamera);
}

int sithCamera_SetCurrentToCycleCamera(void)
{
    return J3D_TRAMPOLINE_CALL(sithCamera_SetCurrentToCycleCamera);
}

void J3DAPI sithCamera_SetCameraFocus(SithCamera* pCamera, SithThing* pPrimaryFocusThing, SithThing* pSecondaryFocusThing)
{
    J3D_TRAMPOLINE_CALL(sithCamera_SetCameraFocus, pCamera, pPrimaryFocusThing, pSecondaryFocusThing);
}

void J3DAPI sithCamera_SetCameraFOV(SithCamera* pCamera, float fov)
{
    J3D_TRAMPOLINE_CALL(sithCamera_SetCameraFOV, pCamera, fov);
}

void J3DAPI sithCamera_SetCameraPosition(SithCamera* pCamera, const rdVector3* pPos)
{
    J3D_TRAMPOLINE_CALL(sithCamera_SetCameraPosition, pCamera, pPos);
}

void J3DAPI sithCamera_GetCameraPosition(const SithCamera* pCamera, rdVector3* pDstPos)
{
    J3D_TRAMPOLINE_CALL(sithCamera_GetCameraPosition, pCamera, pDstPos);
}

void J3DAPI sithCamera_SetExtCameraOffset(const rdVector3* pOffset)
{
    J3D_TRAMPOLINE_CALL(sithCamera_SetExtCameraOffset, pOffset);
}

void J3DAPI sithCamera_SetExtCameraLookOffset(const rdVector3* pOffset)
{
    J3D_TRAMPOLINE_CALL(sithCamera_SetExtCameraLookOffset, pOffset);
}

void sithCamera_RestoreExtCamera(void)
{
    J3D_TRAMPOLINE_CALL(sithCamera_RestoreExtCamera);
}

SithThing* J3DAPI sithCamera_GetPrimaryFocus(const SithCamera* pCamera)
{
    return J3D_TRAMPOLINE_CALL(sithCamera_GetPrimaryFocus, pCamera);
}

SithThing* J3DAPI sithCamera_GetSecondaryFocus(const SithCamera* pCamera)
{
    return J3D_TRAMPOLINE_CALL(sithCamera_GetSecondaryFocus, pCamera);
}

void J3DAPI sithCamera_Update(SithCamera* pCamera)
{
    J3D_TRAMPOLINE_CALL(sithCamera_Update, pCamera);
}

void sithCamera_RenderScene(void)
{
    J3D_TRAMPOLINE_CALL(sithCamera_RenderScene);
}

void J3DAPI sithCamera_SetPOVShake(const rdVector3* posOffset, const rdVector3* angleOffset, float posDelta, float angleDelta)
{
    J3D_TRAMPOLINE_CALL(sithCamera_SetPOVShake, posOffset, angleOffset, posDelta, angleDelta);
}

SithSector* J3DAPI sithCamera_SearchSectorInRadius(int a1, SithSector* pSector, const rdVector3* startPos, rdVector3* endPos, float unused, int flags)
{
    return J3D_TRAMPOLINE_CALL(sithCamera_SearchSectorInRadius, a1, pSector, startPos, endPos, unused, flags);
}

void J3DAPI sithCamera_SetCameraStateFlags(SithCameraState flags)
{
    J3D_TRAMPOLINE_CALL(sithCamera_SetCameraStateFlags, flags);
}

SithCameraState J3DAPI sithCamera_GetCameraStateFlags()
{
    return J3D_TRAMPOLINE_CALL(sithCamera_GetCameraStateFlags);
}
