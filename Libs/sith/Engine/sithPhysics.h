#ifndef SITH_SITHPHYSICS_H
#define SITH_SITHPHYSICS_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>

#include <std/types.h>
#include <std/General/stdConffile.h>

J3D_EXTERN_C_START

void J3DAPI sithPhysics_FindFloor(SithThing* pThing, int bNoThingStateUpdate);
void J3DAPI sithPhysics_FindWaterSurface(SithThing* pThing);
void J3DAPI sithPhysics_UpdateThing(SithThing* pThing, float secDeltaTime);
void J3DAPI sithPhysics_ApplyForce(SithThing* pThing, const rdVector3* force);
void J3DAPI sithPhysics_SetThingLook(SithThing* pThing, const rdVector3* pNormal, float secDeltaTime);
void J3DAPI sithPhysics_ApplyDrag(rdVector3* pVelocity, float drag, float mag, float secDeltaTime);
signed int J3DAPI sithPhysics_ParseArg(StdConffileArg* pArg, SithThing* pThing, int adjNum);
void J3DAPI sithPhysics_ResetThingMovement(SithThing* pThing);
float J3DAPI sithPhysics_GetThingHeight(const SithThing* pThing);
// Updates physics include gravity effect on thing
void J3DAPI sithPhysics_UpdateThingPhysics(SithThing* pThing, float secDeltaTime);
// update player physics in the air or water/aeterium
// local variable allocation has failed, the output may be wrong!
void J3DAPI sithPhysics_UpdatePlayerPhysics(SithThing* pThing, float msDeltaTime);
void J3DAPI sithPhysics_UpdateUnderwaterThingPhysics(SithThing* pThing, float secDeltaTime);
void J3DAPI sithPhysics_UpdateClimbingThingPhysics(SithThing* pThing, float secDeltaTime);
void J3DAPI sithPhysics_UpdateAttachedThingPhysics(SithThing* pThing, float secDeltaTime);
int J3DAPI sithPhysics_CreateMineCarUserBlock(SithThing* pMineCar);
void J3DAPI sithPhysics_InitMineCarFxState(SithThing* pThing, SithMineCarFxState* pFxState);
void J3DAPI sithPhysics_InitVehicleFxState(SithThing* pThing, SithVehicleEngineFxState* pFxState);
void J3DAPI sithPhysics_InitDefaultMineCarInfo(SithThing* pThing, void* pInfo);
void J3DAPI sithPhysics_InitMineCarChassis(SithThing* pThing, SithVehicleChassisInfo* pChassisInfo);
void J3DAPI sithPhysics_InitTrackTruckChassis(SithThing* pThing, SithVehicleChassisInfo* pChassisInfo);
void J3DAPI sithPhysics_InitTrackJeepChassis(SithThing* pThing, SithVehicleChassisInfo* pChassisInfo);
void J3DAPI sithPhysics_InitMineCarExhaust(SithThing* pThing, SithVehicleExhaustInfo* pExhaustInfo);
void J3DAPI sithPhysics_InitJeepExhaust(SithThing* pThing, SithVehicleExhaustInfo* pExhaustInfo);
void J3DAPI sithPhysics_InitTrackTruckExhaust(SithThing* pThing, SithVehicleExhaustInfo* pExhaustInfo);
void J3DAPI sithPhysics_InitMineCarState(SithThing* pThing, SithMineCarState* pState);
void J3DAPI sithPhysics_InitTrackTruckState(SithThing* pThing, SithMineCarState* pState);
void J3DAPI sithPhysics_UpdateMineCarPhysics(SithThing* pThing, float secDeltaTime);
void J3DAPI sithPhysics_UpdateTrackVehicleFx(SithThing* pThing, SithMineCarUserBlock* pMineCarUserBlock, float secDeltaTime);
void J3DAPI sithPhysics_UpdateMineCarFx(SithThing* pThing, SithMineCarFxState* pFxState, float secDeltaTime);
void J3DAPI sithPhysics_UpdateTrackJeepFx(SithThing* pThing, SithVehicleEngineFxState* pFxState, float secDeltaTime);
void J3DAPI sithPhysics_UpdateTrackTruckFx(SithThing* pThing, SithVehicleEngineFxState* pFxState, float secDeltaTime);
void J3DAPI sithPhysics_UpdateVehicleChassis(SithThing* pThing, SithVehicleChassisInfo* pChasisInfo, float secDeltaTime);
void J3DAPI sithPhysics_UpdateExhaustFx(SithThing* pThing, SithVehicleExhaustInfo* pExhaustInfo, float secDeltaTime);
// update physics
void J3DAPI sithPhysics_UpdateRaftPhysics(SithThing* pThing, float secDeltaTime);
int J3DAPI sithPhysics_GetWaterNormalAtPos(const SithThing* pThing, float* pOutDistance, rdVector3* pOutNormal, const rdVector3* pPos, float secDeltaTime);
void J3DAPI sithPhysics_GetWaterThrust(SithThing* pThing, rdVector3* a2, rdVector3* pOutThrust, float msDeltaTime);
void J3DAPI sithPhysics_ProcessMineCarTrackMove(SithThing* pThing, float secDeltaTime, float a3, rdVector3* a4);
int J3DAPI sithPhysics_ProcessTrackFace(SithThing* pThing, rdFace* pFace, rdVector3* a3, rdVector3* a4, rdVector3* a5, void* pData);
int J3DAPI sithPhysics_CheckForPointOnTrack(SithThing* pThing, rdVector3* a2, rdFace** ppOutFoundFace, int bUpdateState, rdFace* pPrevFace);
int J3DAPI sithPhysics_sub_487EC0(SithThing* pThing, void* pData, float* secDeltaTime, rdVector3* a4, rdVector3* a5, float a6);
void J3DAPI sithPhysics_UpdateJeepPhysics(SithThing* pThing, float secDeltaTime);
int J3DAPI sithPhysics_Jeep_sub_4892E0(SithThing* pThing, void* a2, float secDeltaTime);
// function might check for jeep surface and thing face collision
void J3DAPI sithPhysics_sub_48A970(SithThing* pThing, void* a2, const rdVector3* a3);
int J3DAPI sithPhysics_sub_48AD20(SithThing* pThing, void* a2, rdVector3* a3, float secDeltaTime);
signed int J3DAPI sithPhysics_CreateJeepUserBlock(SithThing* pThing);
void J3DAPI sithPhysics_Jeep_sub_48B4D0(SithThing* pThing, float* a2);
void J3DAPI sithPhysics_UpdateJeepFx(SithThing* pThing, SithVehicleEngineFxState* pFxState, float a3);

// Helper hooking functions
void sithPhysics_InstallHooks(void);
void sithPhysics_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHPHYSICS_H
