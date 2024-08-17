#ifndef SITH_SITHVEHICLECONTROLS_H
#define SITH_SITHVEHICLECONTROLS_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define sithVehicleControls_g_bJeepForceStopped J3D_DECL_FAR_VAR(sithVehicleControls_g_bJeepForceStopped, int)
// extern int sithVehicleControls_g_bJeepForceStopped;

#define sithVehicleControls_g_bJeepAccMoveSndFxPlayed J3D_DECL_FAR_VAR(sithVehicleControls_g_bJeepAccMoveSndFxPlayed, int)
// extern int sithVehicleControls_g_bJeepAccMoveSndFxPlayed;

SithMineCarControlState* J3DAPI sithVehicleControls_GetMineCarControlState();
void J3DAPI sithVehicleControls_SetMineCarControlState(SithMineCarControlState* pState);
SithRaftControlState* J3DAPI sithVehicleControls_GetRaftControlState();
void J3DAPI sithVehicleControls_SetRaftControlState(SithRaftControlState* pState);
void J3DAPI sithVehicleControls_PuppetCallback(SithThing* pThing, int track, rdKeyMarkerType markerType);
void J3DAPI sithVehicleControls_ProcessMineCarPlayerMove(SithThing* pThing, float secDeltaTime);
void J3DAPI sithVehicleControls_ProcessJeepPlayerMove(SithThing* pThing, float secDeltaTime);
void J3DAPI sithVehicleControls_PlayPuppetMode(SithThing* pThing, SithPuppetSubMode submode);
void J3DAPI sithVehicleControls_ProcessRaftPlayerMove(SithThing* pThing, float secDeltaTime);
int J3DAPI sithVehicleControls_FindRaftExitSurfacePos(SithThing* pThing, float moveDist, rdVector3* pOutPos, rdVector3* pOutPYR);
void J3DAPI sithVehicleControls_sub_4A5AE0(SithThing* pThing, void* a2, float moveDist);
void J3DAPI sithVehicleControls_FadeJeepMoveSounds(SithThing* pThing);
int J3DAPI sithVehicleControls_CanMoveInDirection(SithThing* pThing, rdVector3* pDir);
void J3DAPI sithVehicleControls_ExitRaft(SithThing* pRaftPlayer);
void J3DAPI sithVehicleControls_UpdateRaftPaddleSoundFx(SithThing* pThing);
int J3DAPI sithVehicleControls_SendMessageUser0(SithThing* pThing);
void J3DAPI sithVehicleControls_SendMessageUser1(SithThing* pThing);

// Helper hooking functions
void sithVehicleControls_InstallHooks(void);
void sithVehicleControls_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHVEHICLECONTROLS_H
