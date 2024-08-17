#ifndef SITH_SITHPLAYERACTIONS_H
#define SITH_SITHPLAYERACTIONS_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define sithPlayerActions_g_jewelFlyingPuppetTrackNum J3D_DECL_FAR_VAR(sithPlayerActions_g_jewelFlyingPuppetTrackNum, int)
// extern int sithPlayerActions_g_jewelFlyingPuppetTrackNum ;

#define sithPlayerActions_g_pCurCollidedSurface J3D_DECL_FAR_VAR(sithPlayerActions_g_pCurCollidedSurface, SithSurface*)
// extern SithSurface *sithPlayerActions_g_pCurCollidedSurface;

#define sithPlayerActions_g_pCurCollidedModelFace J3D_DECL_FAR_VAR(sithPlayerActions_g_pCurCollidedModelFace, rdFace*)
// extern rdFace *sithPlayerActions_g_pCurCollidedModelFace;

#define sithPlayerActions_g_pCurCollidedModel J3D_DECL_FAR_VAR(sithPlayerActions_g_pCurCollidedModel, rdModel3*)
// extern rdModel3 *sithPlayerActions_g_pCurCollidedModel;

#define sithPlayerActions_g_pPlasma J3D_DECL_FAR_VAR(sithPlayerActions_g_pPlasma, SithThing*)
// extern SithThing *sithPlayerActions_g_pPlasma;

#define sithPlayerActions_g_bJewelFlying J3D_DECL_FAR_VAR(sithPlayerActions_g_bJewelFlying, int)
// extern int sithPlayerActions_g_bJewelFlying;

#define sithPlayerActions_g_bPlayerInvisible J3D_DECL_FAR_VAR(sithPlayerActions_g_bPlayerInvisible, int)
// extern int sithPlayerActions_g_bPlayerInvisible;

#define sithPlayerActions_g_pChalkWriteSurf J3D_DECL_FAR_VAR(sithPlayerActions_g_pChalkWriteSurf, SithSurface*)
// extern SithSurface *sithPlayerActions_g_pChalkWriteSurf;

#define sithPlayerActions_g_posChalkMarkWrite J3D_DECL_FAR_VAR(sithPlayerActions_g_posChalkMarkWrite, rdVector3)
// extern rdVector3 sithPlayerActions_g_posChalkMarkWrite;

#define sithPlayerActions_g_pChalkWriteSector J3D_DECL_FAR_VAR(sithPlayerActions_g_pChalkWriteSector, SithSector*)
// extern SithSector *sithPlayerActions_g_pChalkWriteSector;

int J3DAPI sithPlayerActions_Activate(SithThing* pPlayer);
void J3DAPI sithPlayerActions_Jump(SithThing* pThing, float a2, int jumpDirection);
void J3DAPI sithPlayerActions_MoveToPlayerPosition(SithThing* pThing, unsigned int playerNum);
void J3DAPI sithPlayerActions_PushItem(SithThing* pThing, SithThing* pItem, rdVector3* pDirection);
void J3DAPI sithPlayerActions_PullItem(SithThing* pThing, SithThing* pItem, rdVector3* pDirection);
SithInventoryItem* J3DAPI sithPlayerActions_ClimbPullUp(SithThing* pThing);
void J3DAPI sithPlayerActions_ClimbMove(SithThing* pThing, SithSurface* pSurf, int direction);
void J3DAPI sithPlayerActions_UnmountWall(SithThing* pThing, int trackNum);
void J3DAPI sithPlayerActions_ClimbOn1m(SithThing* pThing);
void J3DAPI sithPlayerActions_ClimbOn2m(SithThing* pThing);
void J3DAPI sithPlayerActions_LeapForward(SithThing* pThing);
void J3DAPI sithPlayerActions_JumpForward(SithThing* pThing);
void J3DAPI sithPlayerActions_JumpLeft(SithThing* pThing);
void J3DAPI sithPlayerActions_JumpRight(SithThing* pThing);
void J3DAPI sithPlayerActions_JumpRollBack(SithThing* pThing);
void J3DAPI sithPlayerActions_JumpRollForward(SithThing* pThing);
void J3DAPI sithPlayerActions_StrafeLeft(SithThing* pThing);
void J3DAPI sithPlayerActions_StrafeRight(SithThing* pThing);
void J3DAPI sithPlayerActions_HopBack(SithThing* pThing);
void J3DAPI sithPlayerActions_Stand2Crawl(SithThing* pThing);
void J3DAPI sithPlayerActions_Crawl2Stand(SithThing* pThing);
int J3DAPI sithPlayerActions_JumpStart(SithThing* pThing);
int J3DAPI sithPlayerActions_HasActiveWeapon(SithThing* pThing);
void J3DAPI sithPlayerActions_ClimbToClimb(SithThing* pThing, int bLedge);
void J3DAPI sithPlayerActions_ClimbToHang(SithThing* pThing);
int J3DAPI sithPlayerActions_CanMoveToPos(SithThing* pThing, rdVector3* pPos, int* a3);
double J3DAPI sithPlayerActions_SearchForCollision(SithThing* pThing, const rdVector3* pPYR, SithSurface** pHitSurf, rdFace** pHitFace, rdModel3Mesh** pHitMesh, SithThing** pHitThing);
int J3DAPI sithPlayerActions_CanClimbOn1m(SithThing* pThing);
int J3DAPI sithPlayerActions_CanClimbOn2m(SithThing* pThing);
int J3DAPI sithPlayerActions_SearchClimbSurface(SithThing* pThing);
int J3DAPI sithPlayerActions_ActorGrabLedge(SithThing* pThing, float distance, SithSurface* pHitSurf, rdFace* pHitFace, const rdModel3Mesh* pHitMesh, SithThing* pHitThing);
int J3DAPI sithPlayerActions_ClimbDownToIdle(SithThing* pThing);
int J3DAPI sithPlayerActions_CanPullUp(SithThing* pThing);
float J3DAPI sithPlayerActions_GetFaceTopZ(const SithThing* pThing, const rdFace* pFace, const rdModel3Mesh* pMesh);
void J3DAPI sithPlayerActions_StartInvisibility();
void J3DAPI sithPlayerActions_EndInvisibility();
int J3DAPI sithPlayerActions_IsInvisible();
int J3DAPI sithPlayerActions_StartJewelFlying();
int J3DAPI sithPlayerActions_EnableJewelFlying(SithThing* pPlasma);
SithThing* J3DAPI sithPlayerActions_DisableJewelFlying();
void J3DAPI sithPlayerActions_MoveToClimbSector(SithThing* pThing, SithSurface* pSurface);
void J3DAPI sithPlayerActions_Crawl(SithThing* pThing);

// Helper hooking functions
void sithPlayerActions_InstallHooks(void);
void sithPlayerActions_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHPLAYERACTIONS_H
