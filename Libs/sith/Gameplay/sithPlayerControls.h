#ifndef SITH_SITHPLAYERCONTROLS_H
#define SITH_SITHPLAYERCONTROLS_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Gameplay/sithTime.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define sithPlayerControls_g_bCutsceneMode J3D_DECL_FAR_VAR(sithPlayerControls_g_bCutsceneMode, int)
// extern int sithPlayerControls_g_bCutsceneMode;

extern bool sithPlayerControls_bActionKeyActive;

void J3DAPI sithPlayerControls_PuppetCallback(SithThing* pThing, int track, rdKeyMarkerType markerType);
int J3DAPI sithPlayerControls_Process(SithThing* pPlayerThing, float secDeltaTime);

int J3DAPI sithPlayerControls_BoardVehicle(SithThing* pThing, int bBoard);
void J3DAPI sithPlayerControls_ExitVehicle(SithThing* pThing);

void J3DAPI sithPlayerControls_RotateAimJoints(SithThing* pThing, float pitch, float yaw);
void J3DAPI sithPlayerControls_ResetAimJoints(SithThing* pThing);

SithThing* sithPlayerControls_GetTargetThing(void);

SithThing* J3DAPI sithPlayerControls_GetVehicleBoardedThing();
void J3DAPI sithPlayerControls_SetVehicleBoardedThing(SithThing* pThing);

/*
* Calculates yaw angular velocity based on actor max rotation velocity
* @param pActor      - Actor info
* @param direction   - Direction factor. Should be negative for right turn
* @param speedFactor - Extra speed factor. Should be <= 1.0f
*/
inline float sithPlayerControls_CalculateYawVelocity(SithActorInfo* pActor, float direction, float speedFactor)
{
    speedFactor = J3DMIN(speedFactor, 1.0f);
    return (direction * sithTime_g_fps) + (pActor->maxRotVelocity * direction * speedFactor);
}

// Helper hooking functions
void sithPlayerControls_InstallHooks(void);
void sithPlayerControls_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHPLAYERCONTROLS_H
