#ifndef SITH_SITHANIMATE_H
#define SITH_SITHANIMATE_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

void sithAnimate_Startup(void);
void sithAnimate_Shutdown(void); // Added

int sithAnimate_Open(void);
void sithAnimate_Close(void);

void J3DAPI sithAnimate_Stop(SithAnimationSlot* pAnim);
int J3DAPI sithAnimate_GetSurfaceAnimIndex(const SithSurface* pSurf);
// local variable allocation has failed, the output may be wrong!
SithAnimationSlot* J3DAPI sithAnimate_StartScrollSurfaceAnim(SithSurface* pSurf, const rdVector3* pDir);
void J3DAPI sithAnimate_BuildScrollFaceRotate(rdMatrix34* pOrient, const rdFace* pFace, SithSurfaceFlag surfflags);
float J3DAPI sithAnimate_ExtractUVAngle(float v, float u);
SithAnimationSlot* J3DAPI sithAnimate_StartSideSkyAnim(SithSurfaceFlag skyType, rdVector2* pDirection);
SithAnimationSlot* J3DAPI sithAnimate_StartSpriteAnim(SithThing* pSprite, float fps, SithAnimateFlags flags);
SithAnimationSlot* J3DAPI sithAnimate_StartSurfaceAnim(SithSurface* pSurf, float fps, SithAnimateFlags flags);
SithAnimationSlot* J3DAPI sithAnimate_StartMaterialAnim(rdMaterial* pMat, float fps, SithAnimateFlags flags);
SithAnimationSlot* J3DAPI sithAnimate_StartSurfaceLightAnim(SithSurface* pSurface, rdVector3* pColor, float timeDelta);
SithAnimationSlot* J3DAPI sithAnimate_StartSpriteSizeAnim(SithThing* pSprite, const rdVector3* start, const rdVector3* end, float time);
SithAnimationSlot* J3DAPI sithAnimate_StartSectorLightAnim(SithSector* pSector, rdVector3* pNewLightColor, float timeDelta, SithAnimateFlags flags);
SithAnimationSlot* J3DAPI sithAnimate_StartThingLightAnim(SithThing* pThing, rdVector4* color, float timeDelta, SithAnimateFlags flags);
SithAnimationSlot* J3DAPI sithAnimate_StartThingMove(SithThing* pThing, rdVector3* pDirection, float distance, float timeDelta);
SithAnimationSlot* J3DAPI sithAnimate_StartThingMoveToPos(SithThing* pThing, rdVector3* pPos, float time);
SithAnimationSlot* J3DAPI sithAnimate_StartThingColorAnim(SithThing* pThing, rdVector4* startColor, rdVector4* endColor, float timeDelta, SithAnimateFlags flags);
SithAnimationSlot* J3DAPI sithAnimate_CameraZoom(SithCamera* pCamera, float fov, float timeDelta);
SithAnimationSlot* J3DAPI sithAnimate_PushItem(SithThing* pActor, SithThing* pThing, rdVector3* pDirection, int trackNum);
SithAnimationSlot* J3DAPI sithAnimate_PullItem(SithThing* pActor, SithThing* pThing, rdVector3* pDirection, int trackNum);
void J3DAPI sithAnimate_Update(float secTimeDelta);
void J3DAPI sithAnimate_UpdateThingYawRotate(SithAnimationSlot* pAnim, float secDeltaTime);
SithAnimationSlot* J3DAPI sithAnimate_GetSurfaceAnim(const SithSurface* pSurf);
void J3DAPI sithAnimate_GetSurfaceScrollingDirection(const SithSurface* pSurf, rdVector3* result);
SithAnimationSlot* J3DAPI sithAnimate_GetAnim(int animID);
SithAnimationSlot* J3DAPI sithAnimate_GetMaterialAnim(const rdMaterial* pMaterial);
int J3DAPI sithAnimate_Save(unsigned int outstream);
void J3DAPI sithAnimate_UpdateCameraZoom(SithAnimationSlot* pAnim, float secTimeDelta);
void J3DAPI sithAnimate_UpdateSpriteSizeAnim(SithAnimationSlot* pAnim, float secDeltaTime);
void J3DAPI sithAnimate_UpdateLightAnim(SithAnimationSlot* pAnim, float secDeltaTime);
void J3DAPI sithAnimate_UpdateThingMove(SithAnimationSlot* pAnim, float secTimeDelta);
void J3DAPI sithAnimate_UpdateThingMovePos(SithAnimationSlot* pAnim, float secDeltaTime);
void J3DAPI sithAnimate_UpdateColorAnim(SithAnimationSlot* pAnim, float secDeltaTime);
void J3DAPI sithAnimate_UpdateSurfaceScroll(SithAnimationSlot* pAnim, float secDeltaTime, int animNum);
void J3DAPI sithAnimate_UpdateSlideSky(SithAnimationSlot* pAnim, int skyType, float secDeltaTime, int animNum);
void J3DAPI sithAnimate_UpdatePageFlipAnim(SithAnimationSlot* pAnim);
void J3DAPI sithAnimate_ResetImpl();
void J3DAPI sithAnimate_FreeAnim(SithAnimationSlot* pAnim);
SithAnimationSlot* J3DAPI sithAnimate_CreateImpl();
void J3DAPI sithAnimate_UpdatePushItem(SithAnimationSlot* pAnim);
void J3DAPI sithAnimate_UpdatePullItem(SithAnimationSlot* pAnim);
int J3DAPI sithAnimate_GetNextFrameIndex(float frame, int size, const unsigned int* aAnimFrames);
float J3DAPI sithAnimate_GetPuppetTrackCurFrame(SithThing* pThing, int trackNum);
SithSurface* J3DAPI sithAnimate_SearchFloorSurface(const SithThing* pThing);
void J3DAPI sithAnimate_SendExitSurfaceMessage(const SithThing* pThing, const SithSurface* pSurface);
void J3DAPI sithAnimate_EnterFloorSurface(const SithThing* pSrcThing, const SithSurface* pSurf);

// Helper hooking functions
void sithAnimate_InstallHooks(void);
void sithAnimate_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHANIMATE_H
