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

typedef enum eSithPhysicsWaterSurfaceType
{
    SITHPHYSICS_WATERSURFACE_NONE    = 0,
    SITHPHYSICS_WATERSURFACE_DEFAULT = 1,
    SITHPHYSICS_WATERSURFACE_ADJOIN  = 3,
    SITHPHYSICS_WATERSURFACE_WATER   = 4,
} SithPhysicsWaterSurfaceType;

void J3DAPI sithPhysics_FindFloor(SithThing* pThing, int bNoThingStateUpdate);
void J3DAPI sithPhysics_FindWaterSurface(SithThing* pThing);

// Main thing physics update function
void J3DAPI sithPhysics_UpdateThing(SithThing* pThing, float secDeltaTime);

// Force, drag and look functions
void J3DAPI sithPhysics_ApplyForce(SithThing* pThing, const rdVector3* force);
void J3DAPI sithPhysics_SetThingLook(SithThing* pThing, const rdVector3* look, float secDeltaTime);
void J3DAPI sithPhysics_ApplyDrag(rdVector3* pVelocity, float drag, float staticDrag, float secDeltaTime);

// Parse function
int J3DAPI sithPhysics_ParseArg(const StdConffileArg* pArg, SithThing* pThing, int adjNum);

void J3DAPI sithPhysics_ResetThingMovement(SithThing* pThing);
float J3DAPI sithPhysics_GetThingHeight(const SithThing* pThing);

// Specific thing physics update functions.
// Note, these are called by sithPhysics_UpdateThing based on the state of the thing.
void J3DAPI sithPhysics_UpdateDetachedThingPhysics(SithThing* pThing, float secDeltaTime);
void J3DAPI sithPhysics_UpdateDetachedPlayerPhysics(SithThing* pThing, float secDeltaTime);
void J3DAPI sithPhysics_UpdateUnderwaterThingPhysics(SithThing* pThing, float secDeltaTime);
void J3DAPI sithPhysics_UpdateClimbingThingPhysics(SithThing* pThing, float secDeltaTime);
void J3DAPI sithPhysics_UpdateAttachedThingPhysics(SithThing* pThing, float secDeltaTime);

// MineCar physics
int J3DAPI sithPhysics_CreateMineCarUserBlock(SithThing* pThing);
void J3DAPI sithPhysics_UpdateMineCarPhysics(SithThing* pThing, float secDeltaTime);

// Raft physics
void J3DAPI sithPhysics_UpdateRaftPhysics(SithThing* pThing, float secDeltaTime);

// Jeep physics
signed int J3DAPI sithPhysics_CreateJeepUserBlock(SithThing* pThing);
void J3DAPI sithPhysics_UpdateJeepPhysics(SithThing* pThing, float secDeltaTime);

// Helper hooking functions
void sithPhysics_InstallHooks(void);
void sithPhysics_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHPHYSICS_H
