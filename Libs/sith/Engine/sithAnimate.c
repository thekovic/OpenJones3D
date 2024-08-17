#include "sithAnimate.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithAnimate_lastPullItemAnimFrameIdx J3D_DECL_FAR_VAR(sithAnimate_lastPullItemAnimFrameIdx, int)
#define sithAnimate_aPullItemAnimFrames J3D_DECL_FAR_ARRAYVAR(sithAnimate_aPullItemAnimFrames, int(*)[12])
#define sithAnimate_aPullItemDistances J3D_DECL_FAR_ARRAYVAR(sithAnimate_aPullItemDistances, rdVector2(*)[11])
#define sithAnimate_lastPushItemAnimFrameIdx J3D_DECL_FAR_VAR(sithAnimate_lastPushItemAnimFrameIdx, int)
#define sithAnimate_aPushItemAnimFrames J3D_DECL_FAR_ARRAYVAR(sithAnimate_aPushItemAnimFrames, const unsigned int(*)[13])
#define sithAnimate_aPushItemDistances J3D_DECL_FAR_ARRAYVAR(sithAnimate_aPushItemDistances, rdVector2(*)[12])
#define sithAnimate_numFreeAnims J3D_DECL_FAR_VAR(sithAnimate_numFreeAnims, int)
#define sithAnimate_aFreeAnimNums J3D_DECL_FAR_ARRAYVAR(sithAnimate_aFreeAnimNums, int(*)[513])
#define sithAnimate_numUsedAnims J3D_DECL_FAR_VAR(sithAnimate_numUsedAnims, int)
#define sithAnimate_aAnims J3D_DECL_FAR_ARRAYVAR(sithAnimate_aAnims, SithAnimationSlot(*)[512])
#define sithAnimate_bOpen J3D_DECL_FAR_VAR(sithAnimate_bOpen, int)

void sithAnimate_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithAnimate_Open);
    // J3D_HOOKFUNC(sithAnimate_Close);
    // J3D_HOOKFUNC(sithAnimate_Stop);
    // J3D_HOOKFUNC(sithAnimate_GetSurfaceAnimIndex);
    // J3D_HOOKFUNC(sithAnimate_StartScrollSurfaceAnim);
    // J3D_HOOKFUNC(sithAnimate_BuildScrollFaceRotate);
    // J3D_HOOKFUNC(sithAnimate_ExtractUVAngle);
    // J3D_HOOKFUNC(sithAnimate_StartSideSkyAnim);
    // J3D_HOOKFUNC(sithAnimate_StartSpriteAnim);
    // J3D_HOOKFUNC(sithAnimate_StartSurfaceAnim);
    // J3D_HOOKFUNC(sithAnimate_StartMaterialAnim);
    // J3D_HOOKFUNC(sithAnimate_StartSurfaceLightAnim);
    // J3D_HOOKFUNC(sithAnimate_StartSpriteSizeAnim);
    // J3D_HOOKFUNC(sithAnimate_StartSectorLightAnim);
    // J3D_HOOKFUNC(sithAnimate_StartThingLightAnim);
    // J3D_HOOKFUNC(sithAnimate_StartThingMove);
    // J3D_HOOKFUNC(sithAnimate_StartThingMoveToPos);
    // J3D_HOOKFUNC(sithAnimate_StartThingColorAnim);
    // J3D_HOOKFUNC(sithAnimate_CameraZoom);
    // J3D_HOOKFUNC(sithAnimate_PushItem);
    // J3D_HOOKFUNC(sithAnimate_PullItem);
    // J3D_HOOKFUNC(sithAnimate_Update);
    // J3D_HOOKFUNC(sithAnimate_UpdateThingYawRotate);
    // J3D_HOOKFUNC(sithAnimate_GetSurfaceAnim);
    // J3D_HOOKFUNC(sithAnimate_GetSurfaceScrollingDirection);
    // J3D_HOOKFUNC(sithAnimate_GetAnim);
    // J3D_HOOKFUNC(sithAnimate_GetMaterialAnim);
    // J3D_HOOKFUNC(sithAnimate_Save);
    // J3D_HOOKFUNC(sithAnimate_UpdateCameraZoom);
    // J3D_HOOKFUNC(sithAnimate_UpdateSpriteSizeAnim);
    // J3D_HOOKFUNC(sithAnimate_UpdateLightAnim);
    // J3D_HOOKFUNC(sithAnimate_UpdateThingMove);
    // J3D_HOOKFUNC(sithAnimate_UpdateThingMovePos);
    // J3D_HOOKFUNC(sithAnimate_UpdateColorAnim);
    // J3D_HOOKFUNC(sithAnimate_UpdateSurfaceScroll);
    // J3D_HOOKFUNC(sithAnimate_UpdateSlideSky);
    // J3D_HOOKFUNC(sithAnimate_UpdatePageFlipAnim);
    // J3D_HOOKFUNC(sithAnimate_ResetImpl);
    // J3D_HOOKFUNC(sithAnimate_FreeAnim);
    // J3D_HOOKFUNC(sithAnimate_CreateImpl);
    // J3D_HOOKFUNC(sithAnimate_UpdatePushItem);
    // J3D_HOOKFUNC(sithAnimate_UpdatePullItem);
    // J3D_HOOKFUNC(sithAnimate_GetNextFrameIndex);
    // J3D_HOOKFUNC(sithAnimate_GetPuppetTrackCurFrame);
    // J3D_HOOKFUNC(sithAnimate_SearchFloorSurface);
    // J3D_HOOKFUNC(sithAnimate_SendExitSurfaceMessage);
    // J3D_HOOKFUNC(sithAnimate_EnterFloorSurface);
}

void sithAnimate_ResetGlobals(void)
{
    int sithAnimate_lastPullItemAnimFrameIdx_tmp = 11;
    memcpy(&sithAnimate_lastPullItemAnimFrameIdx, &sithAnimate_lastPullItemAnimFrameIdx_tmp, sizeof(sithAnimate_lastPullItemAnimFrameIdx));
    
    int sithAnimate_aPullItemAnimFrames_tmp[12] = { 0, 0, 29, 38, 54, 72, 110, 120, 128, 135, 155, 163 };
    memcpy(&sithAnimate_aPullItemAnimFrames, &sithAnimate_aPullItemAnimFrames_tmp, sizeof(sithAnimate_aPullItemAnimFrames));
    
    rdVector2 sithAnimate_aPullItemDistances_tmp[11] = {
      { 0.0f, 0.0f },
      { 0.0f, -0.00190222f },
      { -0.01712f, -0.0030881299f },
      { -0.066529997f, 0.0f },
      { -0.066529997f, -0.00282553f },
      { -0.17390001f, 0.0f },
      { -0.17390001f, -0.00110625f },
      { -0.18275f, -0.0026557101f },
      { -0.20134f, 0.0f },
      { -0.20134f, 0.00033499999f },
      { -0.2f, 0.0f }
    };
    memcpy(&sithAnimate_aPullItemDistances, &sithAnimate_aPullItemDistances_tmp, sizeof(sithAnimate_aPullItemDistances));
    
    int sithAnimate_lastPushItemAnimFrameIdx_tmp = 12;
    memcpy(&sithAnimate_lastPushItemAnimFrameIdx, &sithAnimate_lastPushItemAnimFrameIdx_tmp, sizeof(sithAnimate_lastPushItemAnimFrameIdx));
    
    const unsigned int sithAnimate_aPushItemAnimFrames_tmp[13] = { 0u, 0u, 12u, 25u, 35u, 51u, 66u, 85u, 99u, 108u, 121u, 129u, 151u };
    memcpy((unsigned int *)&sithAnimate_aPushItemAnimFrames, &sithAnimate_aPushItemAnimFrames_tmp, sizeof(sithAnimate_aPushItemAnimFrames));
    
    rdVector2 sithAnimate_aPushItemDistances_tmp[12] = {
      { 0.0f, 0.0f },
      { 0.0f, 0.00167f },
      { 0.021709999f, 0.002697f },
      { 0.04868f, 0.0f },
      { 0.04868f, 0.0021413299f },
      { 0.080799997f, 0.0030821001f },
      { 0.13936f, 0.0f },
      { 0.13936f, 0.0021388901f },
      { 0.15861f, 0.0029861501f },
      { 0.19743f, 0.0f },
      { 0.19743f, 0.00012682f },
      { 0.20100001f, 0.0f }
    };
    memcpy(&sithAnimate_aPushItemDistances, &sithAnimate_aPushItemDistances_tmp, sizeof(sithAnimate_aPushItemDistances));
    
    memset(&sithAnimate_numFreeAnims, 0, sizeof(sithAnimate_numFreeAnims));
    memset(&sithAnimate_aFreeAnimNums, 0, sizeof(sithAnimate_aFreeAnimNums));
    memset(&sithAnimate_numUsedAnims, 0, sizeof(sithAnimate_numUsedAnims));
    memset(&sithAnimate_aAnims, 0, sizeof(sithAnimate_aAnims));
    memset(&sithAnimate_bOpen, 0, sizeof(sithAnimate_bOpen));
}

int J3DAPI sithAnimate_Open()
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_Open);
}

void J3DAPI sithAnimate_Close()
{
    J3D_TRAMPOLINE_CALL(sithAnimate_Close);
}

void J3DAPI sithAnimate_Stop(SithAnimationSlot* pAnim)
{
    J3D_TRAMPOLINE_CALL(sithAnimate_Stop, pAnim);
}

int J3DAPI sithAnimate_GetSurfaceAnimIndex(const SithSurface* pSurf)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_GetSurfaceAnimIndex, pSurf);
}

// local variable allocation has failed, the output may be wrong!
SithAnimationSlot* J3DAPI sithAnimate_StartScrollSurfaceAnim(SithSurface* pSurf, const rdVector3* pDir)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_StartScrollSurfaceAnim, pSurf, pDir);
}

void J3DAPI sithAnimate_BuildScrollFaceRotate(rdMatrix34* pOrient, const rdFace* pFace, SithSurfaceFlag surfflags)
{
    J3D_TRAMPOLINE_CALL(sithAnimate_BuildScrollFaceRotate, pOrient, pFace, surfflags);
}

float J3DAPI sithAnimate_ExtractUVAngle(float v, float u)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_ExtractUVAngle, v, u);
}

SithAnimationSlot* J3DAPI sithAnimate_StartSideSkyAnim(SithSurfaceFlag skyType, rdVector2* pDirection)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_StartSideSkyAnim, skyType, pDirection);
}

SithAnimationSlot* J3DAPI sithAnimate_StartSpriteAnim(SithThing* pSprite, float fps, SithAnimateFlags flags)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_StartSpriteAnim, pSprite, fps, flags);
}

SithAnimationSlot* J3DAPI sithAnimate_StartSurfaceAnim(SithSurface* pSurf, float fps, SithAnimateFlags flags)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_StartSurfaceAnim, pSurf, fps, flags);
}

SithAnimationSlot* J3DAPI sithAnimate_StartMaterialAnim(rdMaterial* pMat, float fps, SithAnimateFlags flags)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_StartMaterialAnim, pMat, fps, flags);
}

SithAnimationSlot* J3DAPI sithAnimate_StartSurfaceLightAnim(SithSurface* pSurface, rdVector3* pColor, float timeDelta)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_StartSurfaceLightAnim, pSurface, pColor, timeDelta);
}

SithAnimationSlot* J3DAPI sithAnimate_StartSpriteSizeAnim(SithThing* pSprite, const rdVector3* start, const rdVector3* end, float time)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_StartSpriteSizeAnim, pSprite, start, end, time);
}

SithAnimationSlot* J3DAPI sithAnimate_StartSectorLightAnim(SithSector* pSector, rdVector3* pNewLightColor, float timeDelta, SithAnimateFlags flags)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_StartSectorLightAnim, pSector, pNewLightColor, timeDelta, flags);
}

SithAnimationSlot* J3DAPI sithAnimate_StartThingLightAnim(SithThing* pThing, rdVector4* color, float timeDelta, SithAnimateFlags flags)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_StartThingLightAnim, pThing, color, timeDelta, flags);
}

SithAnimationSlot* J3DAPI sithAnimate_StartThingMove(SithThing* pThing, rdVector3* pDirection, float distance, float timeDelta)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_StartThingMove, pThing, pDirection, distance, timeDelta);
}

SithAnimationSlot* J3DAPI sithAnimate_StartThingMoveToPos(SithThing* pThing, rdVector3* pPos, float time)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_StartThingMoveToPos, pThing, pPos, time);
}

SithAnimationSlot* J3DAPI sithAnimate_StartThingColorAnim(SithThing* pThing, rdVector4* startColor, rdVector4* endColor, float timeDelta, SithAnimateFlags flags)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_StartThingColorAnim, pThing, startColor, endColor, timeDelta, flags);
}

SithAnimationSlot* J3DAPI sithAnimate_CameraZoom(SithCamera* pCamera, float fov, float timeDelta)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_CameraZoom, pCamera, fov, timeDelta);
}

SithAnimationSlot* J3DAPI sithAnimate_PushItem(SithThing* pActor, SithThing* pThing, rdVector3* pDirection, int trackNum)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_PushItem, pActor, pThing, pDirection, trackNum);
}

SithAnimationSlot* J3DAPI sithAnimate_PullItem(SithThing* pActor, SithThing* pThing, rdVector3* pDirection, int trackNum)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_PullItem, pActor, pThing, pDirection, trackNum);
}

void J3DAPI sithAnimate_Update(float secTimeDelta)
{
    J3D_TRAMPOLINE_CALL(sithAnimate_Update, secTimeDelta);
}

void J3DAPI sithAnimate_UpdateThingYawRotate(SithAnimationSlot* pAnim, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithAnimate_UpdateThingYawRotate, pAnim, secDeltaTime);
}

SithAnimationSlot* J3DAPI sithAnimate_GetSurfaceAnim(const SithSurface* pSurf)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_GetSurfaceAnim, pSurf);
}

void J3DAPI sithAnimate_GetSurfaceScrollingDirection(const SithSurface* pSurf, rdVector3* result)
{
    J3D_TRAMPOLINE_CALL(sithAnimate_GetSurfaceScrollingDirection, pSurf, result);
}

SithAnimationSlot* J3DAPI sithAnimate_GetAnim(int animID)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_GetAnim, animID);
}

SithAnimationSlot* J3DAPI sithAnimate_GetMaterialAnim(const rdMaterial* pMaterial)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_GetMaterialAnim, pMaterial);
}

int J3DAPI sithAnimate_Save(unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_Save, outstream);
}

void J3DAPI sithAnimate_UpdateCameraZoom(SithAnimationSlot* pAnim, float secTimeDelta)
{
    J3D_TRAMPOLINE_CALL(sithAnimate_UpdateCameraZoom, pAnim, secTimeDelta);
}

void J3DAPI sithAnimate_UpdateSpriteSizeAnim(SithAnimationSlot* pAnim, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithAnimate_UpdateSpriteSizeAnim, pAnim, secDeltaTime);
}

void J3DAPI sithAnimate_UpdateLightAnim(SithAnimationSlot* pAnim, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithAnimate_UpdateLightAnim, pAnim, secDeltaTime);
}

void J3DAPI sithAnimate_UpdateThingMove(SithAnimationSlot* pAnim, float secTimeDelta)
{
    J3D_TRAMPOLINE_CALL(sithAnimate_UpdateThingMove, pAnim, secTimeDelta);
}

void J3DAPI sithAnimate_UpdateThingMovePos(SithAnimationSlot* pAnim, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithAnimate_UpdateThingMovePos, pAnim, secDeltaTime);
}

void J3DAPI sithAnimate_UpdateColorAnim(SithAnimationSlot* pAnim, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithAnimate_UpdateColorAnim, pAnim, secDeltaTime);
}

void J3DAPI sithAnimate_UpdateSurfaceScroll(SithAnimationSlot* pAnim, float secDeltaTime, int animNum)
{
    J3D_TRAMPOLINE_CALL(sithAnimate_UpdateSurfaceScroll, pAnim, secDeltaTime, animNum);
}

void J3DAPI sithAnimate_UpdateSlideSky(SithAnimationSlot* pAnim, int skyType, float secDeltaTime, int animNum)
{
    J3D_TRAMPOLINE_CALL(sithAnimate_UpdateSlideSky, pAnim, skyType, secDeltaTime, animNum);
}

void J3DAPI sithAnimate_UpdatePageFlipAnim(SithAnimationSlot* pAnim)
{
    J3D_TRAMPOLINE_CALL(sithAnimate_UpdatePageFlipAnim, pAnim);
}

void J3DAPI sithAnimate_ResetImpl()
{
    J3D_TRAMPOLINE_CALL(sithAnimate_ResetImpl);
}

void J3DAPI sithAnimate_FreeAnim(SithAnimationSlot* pAnim)
{
    J3D_TRAMPOLINE_CALL(sithAnimate_FreeAnim, pAnim);
}

SithAnimationSlot* J3DAPI sithAnimate_CreateImpl()
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_CreateImpl);
}

void J3DAPI sithAnimate_UpdatePushItem(SithAnimationSlot* pAnim)
{
    J3D_TRAMPOLINE_CALL(sithAnimate_UpdatePushItem, pAnim);
}

void J3DAPI sithAnimate_UpdatePullItem(SithAnimationSlot* pAnim)
{
    J3D_TRAMPOLINE_CALL(sithAnimate_UpdatePullItem, pAnim);
}

int J3DAPI sithAnimate_GetNextFrameIndex(float frame, int size, const unsigned int* aAnimFrames)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_GetNextFrameIndex, frame, size, aAnimFrames);
}

float J3DAPI sithAnimate_GetPuppetTrackCurFrame(SithThing* pThing, int trackNum)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_GetPuppetTrackCurFrame, pThing, trackNum);
}

SithSurface* J3DAPI sithAnimate_SearchFloorSurface(const SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithAnimate_SearchFloorSurface, pThing);
}

void J3DAPI sithAnimate_SendExitSurfaceMessage(const SithThing* pThing, const SithSurface* pSurface)
{
    J3D_TRAMPOLINE_CALL(sithAnimate_SendExitSurfaceMessage, pThing, pSurface);
}

void J3DAPI sithAnimate_EnterFloorSurface(const SithThing* pSrcThing, const SithSurface* pSurf)
{
    J3D_TRAMPOLINE_CALL(sithAnimate_EnterFloorSurface, pSrcThing, pSurf);
}
