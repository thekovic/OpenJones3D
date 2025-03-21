#include "sithCamera.h"
#include <j3dcore/j3dhook.h>

#include <rdroid/Engine/rdCamera.h>
#include <rdroid/Math/rdMatrix.h>
#include <rdroid/Math/rdVector.h>

#include <sith/Engine/sithCollision.h>
#include <sith/Engine/sithRender.h>
#include <sith/Gameplay/sithPlayer.h>
#include <sith/RTI/symbols.h>
#include <sith/World/sithWorld.h>

#include <std/General/stdMemory.h>
#include <std/General/stdUtil.h>

#define sithCamera_aCycleCamIndices J3D_DECL_FAR_ARRAYVAR(sithCamera_aCycleCamIndices, size_t(*)[3])
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

#define sithCamera_idleCamOffset J3D_DECL_FAR_VAR(sithCamera_idleCamOffset, rdVector3)

#define sithCamera_vecExtCameraPrevLookOffset J3D_DECL_FAR_VAR(sithCamera_vecExtCameraPrevLookOffset, rdVector3)

#define sithCamera_idleCamOrient J3D_DECL_FAR_VAR(sithCamera_idleCamOrient, rdMatrix34)

#define sithCamera_secFocusThingFadeInTime J3D_DECL_FAR_VAR(sithCamera_secFocusThingFadeInTime, float)
#define sithCamera_bFocusThingInvisible J3D_DECL_FAR_VAR(sithCamera_bFocusThingInvisible, int)
#define sithCamera_bUpdateCameraOffset J3D_DECL_FAR_VAR(sithCamera_bUpdateCameraOffset, int)
#define sithCamera_bStartup J3D_DECL_FAR_VAR(sithCamera_bStartup, int) // TODO: Rename to bStartup 
#define sithCamera_bOpen J3D_DECL_FAR_VAR(sithCamera_bOpen, int)
#define sithCamera_secLookOffsetTranslateDelta J3D_DECL_FAR_VAR(sithCamera_secLookOffsetTranslateDelta, float)

SithSector* J3DAPI sithCamera_SearchSectorInRadius(int a1, SithSector* pSector, const rdVector3* startPos, rdVector3* endPos, float unused, int flags);

void sithCamera_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    J3D_HOOKFUNC(sithCamera_Startup);
    J3D_HOOKFUNC(sithCamera_Shutdown);
    J3D_HOOKFUNC(sithCamera_Open);
    J3D_HOOKFUNC(sithCamera_Close);
    J3D_HOOKFUNC(sithCamera_ResetAllCameras);
    J3D_HOOKFUNC(sithCamera_NewEntry);
    J3D_HOOKFUNC(sithCamera_FreeEntry);
    J3D_HOOKFUNC(sithCamera_SetCameraCanvas);
    J3D_HOOKFUNC(sithCamera_SetCurrentCamera);
    J3D_HOOKFUNC(sithCamera_CycleCamera);
    J3D_HOOKFUNC(sithCamera_SetCurrentToCycleCamera);
    J3D_HOOKFUNC(sithCamera_SetCameraFocus);
    J3D_HOOKFUNC(sithCamera_SetCameraFOV);
    J3D_HOOKFUNC(sithCamera_SetCameraPosition);
    J3D_HOOKFUNC(sithCamera_GetCameraPosition);
    J3D_HOOKFUNC(sithCamera_SetExtCameraOffset);
    J3D_HOOKFUNC(sithCamera_SetExtCameraLookOffset);
    J3D_HOOKFUNC(sithCamera_RestoreExtCamera);
    J3D_HOOKFUNC(sithCamera_GetPrimaryFocus);
    J3D_HOOKFUNC(sithCamera_GetSecondaryFocus);
    // J3D_HOOKFUNC(sithCamera_Update);
    J3D_HOOKFUNC(sithCamera_RenderScene);
    J3D_HOOKFUNC(sithCamera_SetPOVShake);
    J3D_HOOKFUNC(sithCamera_SearchSectorInRadius);
    J3D_HOOKFUNC(sithCamera_SetCameraStateFlags);
    J3D_HOOKFUNC(sithCamera_GetCameraStateFlags);
}

void sithCamera_ResetGlobals(void)
{
    int sithCamera_aCycleCamIndices_tmp[3] = { SITHCAMERA_INTCAMERANUM, SITHCAMERA_EXTCAMERANUM, SITHCAMERA_ORBCAMERANUM };
    memcpy(&sithCamera_aCycleCamIndices, &sithCamera_aCycleCamIndices_tmp, sizeof(sithCamera_aCycleCamIndices));

    rdVector3 sithCamera_vecExtCameraLookOffset_tmp = { { 0.0f }, { 0.02f }, { 0.02f } };
    memcpy(&sithCamera_vecExtCameraLookOffset, &sithCamera_vecExtCameraLookOffset_tmp, sizeof(sithCamera_vecExtCameraLookOffset));

    rdVector3 sithCamera_vecDefaultExtCamLookOffset_tmp = { { 0.0f }, { 0.02f }, { 0.02f } };
    memcpy(&sithCamera_vecDefaultExtCamLookOffset, &sithCamera_vecDefaultExtCamLookOffset_tmp, sizeof(sithCamera_vecDefaultExtCamLookOffset));

    rdVector3 sithCamera_vecExtCameraOffset_tmp = { { 0.0f }, { -0.2f }, { 0.064999998f } };
    memcpy(&sithCamera_vecExtCameraOffset, &sithCamera_vecExtCameraOffset_tmp, sizeof(sithCamera_vecExtCameraOffset));

    const rdVector3 sithCamera_vecDefaultCameraOffset_tmp = { { 0.0f }, { -0.22f }, { 0.15000001f } };
    memcpy((rdVector3*)&sithCamera_vecDefaultCameraOffset, &sithCamera_vecDefaultCameraOffset_tmp, sizeof(sithCamera_vecDefaultCameraOffset));

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
    memcpy(&sithCamera_idleCamOffset, &sithCamera_vecOffsetCamType20_tmp, sizeof(sithCamera_idleCamOffset));

    memset(&sithCamera_vecExtCameraPrevLookOffset, 0, sizeof(sithCamera_vecExtCameraPrevLookOffset));
    memset(&sithCamera_idleCamOrient, 0, sizeof(sithCamera_idleCamOrient));
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
    memset(&sithCamera_g_orbCamOrient, 0, sizeof(sithCamera_g_orbCamOrient));
    memset(&sithCamera_g_camLookSpot, 0, sizeof(sithCamera_g_camLookSpot));
}

//int sithCamera_Startup(void)
//{
//    return J3D_TRAMPOLINE_CALL(sithCamera_Startup);
//}
//
//void sithCamera_Shutdown(void)
//{
//    J3D_TRAMPOLINE_CALL(sithCamera_Shutdown);
//}
//
//int J3DAPI sithCamera_Open(rdCanvas* pCanvas, float aspect)
//{
//    return J3D_TRAMPOLINE_CALL(sithCamera_Open, pCanvas, aspect);
//}
//
//void J3DAPI sithCamera_Close()
//{
//    J3D_TRAMPOLINE_CALL(sithCamera_Close);
//}
//
//void sithCamera_ResetAllCameras(void)
//{
//    J3D_TRAMPOLINE_CALL(sithCamera_ResetAllCameras);
//}
//
//int J3DAPI sithCamera_NewEntry(SithCamera* pCamera, int a2, SithCameraType type, float fov, float aspect, rdCanvas* pCanvas, SithThing* pPrimaryFocus, SithThing* pSecondaryFocus)
//{
//    return J3D_TRAMPOLINE_CALL(sithCamera_NewEntry, pCamera, a2, type, fov, aspect, pCanvas, pPrimaryFocus, pSecondaryFocus);
//}
//
//void J3DAPI sithCamera_FreeEntry(SithCamera* pCamera)
//{
//    J3D_TRAMPOLINE_CALL(sithCamera_FreeEntry, pCamera);
//}
//
//void J3DAPI sithCamera_SetCameraCanvas(SithCamera* pCamera, float aspect, rdCanvas* pCanvas)
//{
//    J3D_TRAMPOLINE_CALL(sithCamera_SetCameraCanvas, pCamera, aspect, pCanvas);
//}
//
//int J3DAPI sithCamera_SetCurrentCamera(SithCamera* pCamera)
//{
//    return J3D_TRAMPOLINE_CALL(sithCamera_SetCurrentCamera, pCamera);
//}
//
//void sithCamera_CycleCamera(void)
//{
//    J3D_TRAMPOLINE_CALL(sithCamera_CycleCamera);
//}
//
//int sithCamera_SetCurrentToCycleCamera(void)
//{
//    return J3D_TRAMPOLINE_CALL(sithCamera_SetCurrentToCycleCamera);
//}
//
//void J3DAPI sithCamera_SetCameraFocus(SithCamera* pCamera, SithThing* pPrimaryFocusThing, SithThing* pSecondaryFocusThing)
//{
//    J3D_TRAMPOLINE_CALL(sithCamera_SetCameraFocus, pCamera, pPrimaryFocusThing, pSecondaryFocusThing);
//}
//
//void J3DAPI sithCamera_SetCameraFOV(SithCamera* pCamera, float fov)
//{
//    J3D_TRAMPOLINE_CALL(sithCamera_SetCameraFOV, pCamera, fov);
//}
//
//void J3DAPI sithCamera_SetCameraPosition(SithCamera* pCamera, const rdVector3* pPos)
//{
//    J3D_TRAMPOLINE_CALL(sithCamera_SetCameraPosition, pCamera, pPos);
//}
//
//void J3DAPI sithCamera_GetCameraPosition(const SithCamera* pCamera, rdVector3* pDstPos)
//{
//    J3D_TRAMPOLINE_CALL(sithCamera_GetCameraPosition, pCamera, pDstPos);
//}
//
//void J3DAPI sithCamera_SetExtCameraOffset(const rdVector3* pOffset)
//{
//    J3D_TRAMPOLINE_CALL(sithCamera_SetExtCameraOffset, pOffset);
//}
//
//void J3DAPI sithCamera_SetExtCameraLookOffset(const rdVector3* pOffset)
//{
//    J3D_TRAMPOLINE_CALL(sithCamera_SetExtCameraLookOffset, pOffset);
//}
//
//void sithCamera_RestoreExtCamera(void)
//{
//    J3D_TRAMPOLINE_CALL(sithCamera_RestoreExtCamera);
//}
//
//SithThing* J3DAPI sithCamera_GetPrimaryFocus(const SithCamera* pCamera)
//{
//    return J3D_TRAMPOLINE_CALL(sithCamera_GetPrimaryFocus, pCamera);
//}
//
//SithThing* J3DAPI sithCamera_GetSecondaryFocus(const SithCamera* pCamera)
//{
//    return J3D_TRAMPOLINE_CALL(sithCamera_GetSecondaryFocus, pCamera);
//}

void J3DAPI sithCamera_Update(SithCamera* pCamera)
{
    J3D_TRAMPOLINE_CALL(sithCamera_Update, pCamera);
}

//void sithCamera_RenderScene(void)
//{
//    J3D_TRAMPOLINE_CALL(sithCamera_RenderScene);
//}

//void J3DAPI sithCamera_SetPOVShake(const rdVector3* posOffset, const rdVector3* angleOffset, float posDelta, float angleDelta)
//{
//    J3D_TRAMPOLINE_CALL(sithCamera_SetPOVShake, posOffset, angleOffset, posDelta, angleDelta);
//}
//
//SithSector* J3DAPI sithCamera_SearchSectorInRadius(int a1, SithSector* pSector, const rdVector3* startPos, rdVector3* endPos, float unused, int flags)
//{
//    return J3D_TRAMPOLINE_CALL(sithCamera_SearchSectorInRadius, a1, pSector, startPos, endPos, unused, flags);
//}
//
//void J3DAPI sithCamera_SetCameraStateFlags(SithCameraState flags)
//{
//    J3D_TRAMPOLINE_CALL(sithCamera_SetCameraStateFlags, flags);
//}
//
//SithCameraState J3DAPI sithCamera_GetCameraStateFlags()
//{
//    return J3D_TRAMPOLINE_CALL(sithCamera_GetCameraStateFlags);
//}

int sithCamera_Startup(void)
{
    SITH_ASSERTREL(sithCamera_bStartup == 0);

    // 1st person camera
    sithCamera_NewEntry(&sithCamera_g_aCameras[SITHCAMERA_INTCAMERANUM], 0, SITHCAMERA_INTERNAL, SITHCAMERA_FOVDEFAULT, 1.0f, NULL, NULL, NULL);

    // 3rd person camera
    sithCamera_NewEntry(&sithCamera_g_aCameras[SITHCAMERA_EXTCAMERANUM], 0, SITHCAMERA_EXTERNAL, SITHCAMERA_FOVDEFAULT, 1.0f, NULL, NULL, NULL);
    rdVector_Copy3(&sithCamera_g_aCameras[SITHCAMERA_EXTCAMERANUM].offset, &sithCamera_vecExtCameraOffset);
    sithCamera_g_aCameras[SITHCAMERA_EXTCAMERANUM].interpSpeed = 0.34999999f;

    sithCamera_NewEntry(&sithCamera_g_aCameras[SITHCAMERA_CINEMACAMERANUM], 0, SITHCAMERA_CINEMATIC, SITHCAMERA_FOVDEFAULT, 1.0f, NULL, NULL, NULL);
    sithCamera_g_aCameras[SITHCAMERA_CINEMACAMERANUM].interpSpeed = 1.0f;

    // Idle camera
    sithCamera_NewEntry(&sithCamera_g_aCameras[SITHCAMERA_IDLECAMERANUM], 0, SITHCAMERA_IDLE, SITHCAMERA_FOVDEFAULT, 1.0f, NULL, NULL, NULL);
    sithCamera_NewEntry(&sithCamera_g_aCameras[SITHCAMERA_UNKNONWCAMERANUM], 0, SITHCAMERA_UNKNOWN_40, SITHCAMERA_FOVDEFAULT, 1.0f, NULL, NULL, NULL);
    sithCamera_NewEntry(&sithCamera_g_aCameras[SITHCAMERA_ORBCAMERANUM], 0, SITHCAMERA_ORBITAL, SITHCAMERA_FOVDEFAULT, 1.0f, NULL, NULL, NULL);

    sithCamera_bStartup = 1;
    return 1;
}

void sithCamera_Shutdown(void)
{
    if ( sithCamera_bStartup )
    {
        sithCamera_Close(); // Added: Make sure system is closed
        for ( size_t i = 0; i < STD_ARRAYLEN(sithCamera_g_aCameras); ++i )
        {
            sithCamera_FreeEntry(&sithCamera_g_aCameras[i]);
        }

        sithCamera_g_pCurCamera = NULL;
        sithCamera_bStartup     = 0;
    }
}

int J3DAPI sithCamera_Open(rdCanvas* pCanvas, float aspect)
{
    SITH_ASSERTREL(sithCamera_bStartup == 1);
    if ( sithCamera_bOpen )
    {
        // TODO: Maybe add debug log
        return 0;
    }

    sithCamera_SetCameraCanvas(&sithCamera_g_aCameras[SITHCAMERA_INTCAMERANUM], aspect, pCanvas);
    sithCamera_SetCameraCanvas(&sithCamera_g_aCameras[SITHCAMERA_EXTCAMERANUM], aspect, pCanvas);
    sithCamera_SetCameraCanvas(&sithCamera_g_aCameras[SITHCAMERA_CINEMACAMERANUM], aspect, pCanvas);
    sithCamera_SetCameraCanvas(&sithCamera_g_aCameras[SITHCAMERA_IDLECAMERANUM], aspect, pCanvas);
    sithCamera_SetCameraCanvas(&sithCamera_g_aCameras[SITHCAMERA_UNKNONWCAMERANUM], aspect, pCanvas);
    sithCamera_SetCameraCanvas(&sithCamera_g_aCameras[SITHCAMERA_ORBCAMERANUM], aspect, pCanvas);

    sithCamera_ResetAllCameras();
    sithCamera_Update(sithCamera_g_pCurCamera);

    sithCamera_bOpen = 1;
    return 1;
}

void sithCamera_Close(void)
{
    if ( sithCamera_bOpen )
    {
        sithCamera_g_pCurCamera = NULL;
        sithCamera_bOpen        = 0;
    }
}

bool sithCamera_IsOpen(void)
{
    return sithCamera_bOpen != 0;
}

void sithCamera_ResetAllCameras(void)
{
    sithCamera_g_bCurCameraSet = 0;
    sithCamera_g_stateFlags &= ~SITHCAMERA_STATE_CUTSCENE;

    sithCamera_SetCameraFocus(&sithCamera_g_aCameras[SITHCAMERA_INTCAMERANUM], sithWorld_g_pCurrentWorld->pCameraFocusThing, NULL);
    sithCamera_SetCameraFocus(&sithCamera_g_aCameras[SITHCAMERA_EXTCAMERANUM], sithWorld_g_pCurrentWorld->pCameraFocusThing, NULL);
    sithCamera_SetCameraFocus(&sithCamera_g_aCameras[SITHCAMERA_IDLECAMERANUM], sithWorld_g_pCurrentWorld->pCameraFocusThing, sithWorld_g_pCurrentWorld->pCameraFocusThing);
    sithCamera_SetCameraFocus(&sithCamera_g_aCameras[SITHCAMERA_UNKNONWCAMERANUM], sithWorld_g_pCurrentWorld->pCameraFocusThing, sithWorld_g_pCurrentWorld->pCameraFocusThing);
    sithCamera_SetCameraFocus(&sithCamera_g_aCameras[SITHCAMERA_ORBCAMERANUM], sithWorld_g_pCurrentWorld->pCameraFocusThing, sithWorld_g_pCurrentWorld->pCameraFocusThing);

    rdVector_Copy3(&sithCamera_vecExtCameraOffset, &sithCamera_vecDefaultExtCamOffset);
    rdVector_Copy3(&sithCamera_vecExtCameraLookOffset, &sithCamera_vecDefaultExtCamLookOffset);

    // Set default FOV for 3rd person camera
    sithCamera_SetCameraFOV(&sithCamera_g_aCameras[SITHCAMERA_EXTCAMERANUM], SITHCAMERA_FOVDEFAULT);

    if ( (sithMain_g_sith_mode.debugModeFlags & SITHDEBUG_INEDITOR) != 0 )
    {
        // Set 1st person camera
        sithCamera_SetCurrentCamera(&sithCamera_g_aCameras[SITHCAMERA_INTCAMERANUM]);
    }
    else if ( sithPlayer_g_pLocalPlayerThing )
    {
        if ( !sithCamera_g_pCurCamera )
        {
            // Set 3rd person camera
            sithCamera_SetCameraFocus(&sithCamera_g_aCameras[SITHCAMERA_EXTCAMERANUM], sithPlayer_g_pLocalPlayerThing, NULL);
            sithCamera_SetCurrentCamera(&sithCamera_g_aCameras[SITHCAMERA_EXTCAMERANUM]);
        }
    }
}

SithCamera* J3DAPI sithCamera_New(SithCameraType type, uint32_t a2, float fov, float aspect, rdCanvas* pCanvas, SithThing* pPrimaryFocus, SithThing* pSecondaryFocus)
{
    SithCamera* pCamera = (SithCamera*)STDMALLOC(sizeof(SithCamera));
    if ( !pCamera )
    {
        SITHLOG_ERROR("Error allocating memory for camera.\n");
        return NULL;
    }

    if ( !sithCamera_NewEntry(pCamera, a2, type, fov, aspect, pCanvas, pPrimaryFocus, pSecondaryFocus) )
    {
        return NULL;
    }

    return pCamera;
}

int J3DAPI sithCamera_NewEntry(SithCamera* pCamera, uint32_t a2, SithCameraType type, float fov, float aspect, rdCanvas* pCanvas, SithThing* pPrimaryFocus, SithThing* pSecondaryFocus)
{
    pCamera->type                 = type;
    pCamera->unknown1             = a2;
    pCamera->fov                  = fov;
    pCamera->aspectRatio          = aspect;
    pCamera->pPrimaryFocusThing   = pPrimaryFocus;
    pCamera->pSecondaryFocusThing = pSecondaryFocus;
    pCamera->posInterpState       = -1;
    pCamera->lookInterpState      = -1;
    pCamera->focusInterpState     = -1;

    rdCamera_NewEntry(&pCamera->rdCamera, fov, 0, 0.015625f, 64.0f, aspect);
    rdCamera_SetAttenuation(&pCamera->rdCamera, SITHCAMERA_ATTENUATIONMIN, SITHCAMERA_ATTENUATIONMAX);

    if ( pCanvas )
    {
        rdCamera_SetCanvas(&pCamera->rdCamera, pCanvas);
    }

    memset(&pCamera->lookPos, 0, sizeof(pCamera->lookPos));
    memset(&pCamera->lookPYR, 0, sizeof(pCamera->lookPYR));

    rdMatrix_Copy34(&pCamera->orient, &rdroid_g_identMatrix34);

    memset(&pCamera->offset, 0, sizeof(pCamera->offset));
    memset(&pCamera->vecUnknown1, 0, sizeof(pCamera->vecUnknown1));

    pCamera->bLookInterp = 0;
    pCamera->bPosInterp = 0;
    return 1;
}

void J3DAPI sithCamera_Free(SithCamera* pCamera)
{
    if ( !pCamera )
    {
        SITHLOG_ERROR("Warning: attempt to free NULL camera ptr.\n");
        return;
    }

    sithCamera_FreeEntry(pCamera);
    stdMemory_Free(pCamera);
}

void J3DAPI sithCamera_FreeEntry(SithCamera* pCamera)
{
    SITH_ASSERTREL(pCamera != NULL);
    rdCamera_FreeEntry(&pCamera->rdCamera);
}

void J3DAPI sithCamera_SetCameraCanvas(SithCamera* pCamera, float aspect, rdCanvas* pCanvas)
{
    rdCamera_SetCanvas(&pCamera->rdCamera, pCanvas);
    rdCamera_SetAspectRatio(&pCamera->rdCamera, aspect);
    rdCamera_SetAttenuation(&pCamera->rdCamera, SITHCAMERA_ATTENUATIONMIN, SITHCAMERA_ATTENUATIONMAX);
}

int J3DAPI sithCamera_SetCurrentCamera(SithCamera* pCamera)
{
    SITH_ASSERTREL(pCamera != NULL);

    sithCamera_g_pCurCamera   = pCamera;
    sithCamera_g_bCurCameraSet = 1;

    rdCamera_SetCurrent(&pCamera->rdCamera);
    switch ( pCamera->type )
    {
        case SITHCAMERA_INTERNAL:
            sithCamera_g_curCycleCamNum = 0;
            break;

        case SITHCAMERA_EXTERNAL:
            sithCamera_g_curCycleCamNum = 1;
            break;

        case SITHCAMERA_IDLE:
        {
            rdMatrix_Copy34(&sithCamera_idleCamOrient, &sithCamera_g_pCurCamera->pPrimaryFocusThing->orient);

            rdVector3 vecPYR = { 0 };
            vecPYR.y = -45.0f;
            rdMatrix_PostRotate34(&sithCamera_idleCamOrient, &vecPYR);
        } break;

        case SITHCAMERA_ORBITAL:
            sithCamera_g_curCycleCamNum = 2;
            break;

        default:
            break;
    }

    sithCamera_Update(sithCamera_g_pCurCamera);
    return 1;
}

void sithCamera_CycleCamera(void)
{
    if ( ++sithCamera_g_curCycleCamNum >= STD_ARRAYLEN(sithCamera_aCycleCamIndices) )
    {
        sithCamera_g_curCycleCamNum = 0;
    }

    sithCamera_SetCurrentCamera(&sithCamera_g_aCameras[sithCamera_aCycleCamIndices[sithCamera_g_curCycleCamNum]]);
}

int sithCamera_SetCurrentToCycleCamera(void)
{
    return sithCamera_SetCurrentCamera(&sithCamera_g_aCameras[sithCamera_aCycleCamIndices[sithCamera_g_curCycleCamNum]]);
}

// Found in dbg version
int J3DAPI SithCamera_sub_44ACCA(SithCamera* pTargetCamera, float time)
{
    SITH_ASSERTREL(pTargetCamera != NULL);
    SITH_ASSERTREL(time >= 0.0f);
    if ( sithCamera_g_pCurCamera && pTargetCamera->unknown1 < (unsigned int)sithCamera_g_pCurCamera->unknown1 )
    {
        return 0;
    }

    sithCamera_g_bCurCameraSet = 2;
    return 1;
}

void J3DAPI sithCamera_SetCameraFocus(SithCamera* pCamera, SithThing* pPrimaryFocusThing, SithThing* pSecondaryFocusThing)
{
    SITH_ASSERTREL(pCamera);
    if ( pPrimaryFocusThing && pCamera->pPrimaryFocusThing != pPrimaryFocusThing )
    {
        pCamera->pPrimaryFocusThing = pPrimaryFocusThing;
    }

    if ( pSecondaryFocusThing )
    {
        if ( pCamera->pSecondaryFocusThing != pSecondaryFocusThing )
        {
            pCamera->pSecondaryFocusThing = pSecondaryFocusThing;
        }
    }
}

void J3DAPI SithCamera_IncrementFOV(SithCamera* pCamera)
{
    SITH_ASSERTREL(pCamera);
    pCamera->fov = pCamera->fov + 1.0f;
    if ( pCamera->fov > SITHCAMERA_FOVMAX )
    {
        pCamera->fov = SITHCAMERA_FOVMAX;
    }

    rdCamera_SetFOV(&pCamera->rdCamera, pCamera->fov);
}

void J3DAPI sithCamera_DecrementFOV(SithCamera* pCamera)
{
    SITH_ASSERTREL(pCamera);
    pCamera->fov = pCamera->fov - 1.0f;
    if ( pCamera->fov < SITHCAMERA_FOVMIN )
    {
        pCamera->fov = SITHCAMERA_FOVMIN;
    }

    rdCamera_SetFOV(&pCamera->rdCamera, pCamera->fov);
}

void J3DAPI sithCamera_SetCameraFOV(SithCamera* pCamera, float fov)
{
    SITH_ASSERTREL(pCamera);
    if ( fov >= SITHCAMERA_FOVMIN && fov <= SITHCAMERA_FOVMAX )
    {
        pCamera->fov = fov;
        rdCamera_SetFOV(&pCamera->rdCamera, pCamera->fov);
    }
}

void J3DAPI sithCamera_SetCameraPosition(SithCamera* pCamera, const rdVector3* pPos)
{
    SITH_ASSERTREL(pCamera);
    rdVector_Copy3(&pCamera->pos, pPos);
    pCamera->posInterpState   = 0;
    pCamera->focusInterpState = 0;
}


void J3DAPI sithCamera_GetCameraPosition(const SithCamera* pCamera, rdVector3* pDstPos)
{
    SITH_ASSERTREL(pCamera);
    rdVector_Copy3(pDstPos, &pCamera->orient.dvec);
}

void J3DAPI sithCamera_SetExtCameraOffset(const rdVector3* pOffset)
{
    if ( sithCamera_g_pCurCamera->type == SITHCAMERA_EXTERNAL )
    {
        rdVector_Copy3(&sithCamera_vecExtCameraOffset, pOffset);
        sithCamera_bUpdateCameraOffset = 1;
    }
}

void J3DAPI sithCamera_SetExtCameraLookOffset(const rdVector3* pOffset)
{
    if ( sithCamera_g_pCurCamera->type == SITHCAMERA_EXTERNAL )
    {
        rdVector_Copy3(&sithCamera_vecExtCameraPrevLookOffset, &sithCamera_vecExtCameraLookOffset);

        sithCamera_secLookOffsetTranslateDelta = 0.5f;
        rdVector_Copy3(&sithCamera_vecExtCameraLookOffset, pOffset);
    }
}

void sithCamera_RestoreExtCamera(void)
{
    if ( sithCamera_g_pCurCamera->type == SITHCAMERA_EXTERNAL )
    {
        rdVector_Copy3(&sithCamera_vecExtCameraOffset, &sithCamera_vecDefaultExtCamOffset);
        rdVector_Copy3(&sithCamera_vecExtCameraLookOffset, &sithCamera_vecDefaultExtCamLookOffset);

        sithCamera_g_pCurCamera->interpSpeed = 0.34999999f;
        sithCamera_bUpdateCameraOffset = 0;

        if ( !sithCamera_g_bExtCameraLookMode )
        {
            sithCamera_bFocusThingInvisible = 0;
        }
    }
}

SithThing* J3DAPI sithCamera_GetPrimaryFocus(const SithCamera* pCamera)
{
    SITH_ASSERTREL(pCamera != NULL);
    return pCamera->pPrimaryFocusThing;
}

SithThing* J3DAPI sithCamera_GetSecondaryFocus(const SithCamera* pCamera)
{
    SITH_ASSERTREL(pCamera != NULL);
    return pCamera->pSecondaryFocusThing;
}

void sithCamera_RenderScene(void)
{
    if ( sithCamera_g_pCurCamera )
    {
        rdCamera_SetCurrent(&sithCamera_g_pCurCamera->rdCamera);
        rdCamera_Update(&sithCamera_g_pCurCamera->orient);
        sithRender_RenderScene();
    }
}

void J3DAPI sithCamera_SetPOVShake(const rdVector3* posOffset, const rdVector3* angleOffset, float posDelta, float angleDelta)
{
    rdVector_Copy3(&sithCamera_g_vecCameraPosOffset, posOffset);
    rdVector_Copy3(&sithCamera_g_vecCameraAngleOffset, angleOffset);

    sithCamera_g_cameraPosDelta   = posDelta;
    sithCamera_g_cameraAngleDelta = angleDelta;
}

SithSector* J3DAPI sithCamera_SearchSectorInRadius(int a1, SithSector* pSector, const rdVector3* startPos, rdVector3* endPos, float unused, int flags)
{
    /* Function searches for collision that blocks camera movement */

    J3D_UNUSED(a1);
    J3D_UNUSED(unused);

    rdVector3 moveNorm;
    rdVector_Sub3(&moveNorm, endPos, startPos);
    /*  moveNorm.x = endPos->x - startPos->x;
      moveNorm.y = endPos->y - startPos->y;
      moveNorm.z = endPos->z - startPos->z;*/
    float moveDist = rdVector_Normalize3Acc(&moveNorm);

    SithSector* pFoundSector = pSector;
    sithCollision_SearchForCollisions(pSector, NULL, startPos, &moveNorm, moveDist, 0.014f, flags | 0x800);
    while ( 1 )
    {
        SithCollision* pCollision = sithCollision_PopStack();
        if ( !pCollision )
        {
            break;
        }

        if ( (pCollision->type & SITHCOLLISION_ADJOINTOUCH) != 0 )
        {
            SITH_ASSERTREL(pCollision->pSurfaceCollided->pAdjoin != NULL);
            pFoundSector = pCollision->pSurfaceCollided->pAdjoin->pAdjoinSector;
        }

        else if ( ((pCollision->type & SITHCOLLISION_THING) == 0
            || pCollision->pThingCollided->type != SITH_THING_ITEM
            && pCollision->pThingCollided->type != SITH_THING_CORPSE
            && pCollision->distance != 0.0f
            && pCollision->pThingCollided->type != SITH_THING_WEAPON)
            && ((pCollision->type & SITHCOLLISION_THING) == 0 || pCollision->pThingCollided != sithPlayer_g_pLocalPlayerThing) )
        {
            /*endPos->x = pCollision->distance * moveNorm.x + startPos->x;
            endPos->y = pCollision->distance * moveNorm.y + startPos->y;
            endPos->z = pCollision->distance * moveNorm.z + startPos->z;*/
            rdVector_ScaleAdd3(endPos, &moveNorm, pCollision->distance, startPos);
            break;
        }
    }

    sithCollision_DecreaseStackLevel();
    return pFoundSector;
}

void J3DAPI sithCamera_SetCameraStateFlags(SithCameraState flags)
{
    sithCamera_g_stateFlags = flags;
}

SithCameraState sithCamera_GetCameraStateFlags(void)
{
    return sithCamera_g_stateFlags;
}
