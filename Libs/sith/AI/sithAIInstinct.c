#include "sithAIInstinct.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithAIInstinct_flt_539AB8 J3D_DECL_FAR_VAR(sithAIInstinct_flt_539AB8, float)

void sithAIInstinct_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithAIInstinct_InitInstincts);
    // J3D_HOOKFUNC(sithAIInstinct_Listen);
    // J3D_HOOKFUNC(sithAIInstinct_LookForTarget);
    // J3D_HOOKFUNC(sithAIInstinct_SenseDanger);
    // J3D_HOOKFUNC(sithAIInstinct_FearGunshot);
    // J3D_HOOKFUNC(sithAIInstinct_Hop);
    // J3D_HOOKFUNC(sithAIInstinct_HoverDrift);
    // J3D_HOOKFUNC(sithAIInstinct_Talk);
    // J3D_HOOKFUNC(sithAIInstinct_RandomTurn);
    // J3D_HOOKFUNC(sithAIInstinct_OpenDoors);
    // J3D_HOOKFUNC(sithAIInstinct_Jump);
    // J3D_HOOKFUNC(sithAIInstinct_LobFire);
    // J3D_HOOKFUNC(sithAIInstinct_PrimaryFire);
    // J3D_HOOKFUNC(sithAIInstinct_AlternateFire);
    // J3D_HOOKFUNC(sithAIInstinct_CircleStrafe);
    // J3D_HOOKFUNC(sithAIInstinct_Dodge);
    // J3D_HOOKFUNC(sithAIInstinct_HitAndRun);
    // J3D_HOOKFUNC(sithAIInstinct_Retreat);
    // J3D_HOOKFUNC(sithAIInstinct_RandomMove);
    // J3D_HOOKFUNC(sithAIInstinct_HumanCombatMove);
    // J3D_HOOKFUNC(sithAIInstinct_Roam);
    // J3D_HOOKFUNC(sithAIInstinct_ReturnHome);
    // J3D_HOOKFUNC(sithAIInstinct_Flee);
    // J3D_HOOKFUNC(sithAIInstinct_BasicFallow);
    // J3D_HOOKFUNC(sithAIInstinct_WallCrawl);
    // J3D_HOOKFUNC(sithAIInstinct_sub_494360);
    // J3D_HOOKFUNC(sithAIInstinct_SnakeMungeTestCheck);
    // J3D_HOOKFUNC(sithAIInstinct_SnakeFollow);
    // J3D_HOOKFUNC(sithAIInstinct_sub_494FF0);
}

void sithAIInstinct_ResetGlobals(void)
{
    float sithAIInstinct_flt_539AB8_tmp = 1.0f;
    memcpy(&sithAIInstinct_flt_539AB8, &sithAIInstinct_flt_539AB8_tmp, sizeof(sithAIInstinct_flt_539AB8));
    
}

void J3DAPI sithAIInstinct_InitInstincts()
{
    J3D_TRAMPOLINE_CALL(sithAIInstinct_InitInstincts);
}

int J3DAPI sithAIInstinct_Listen(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_Listen, pLocal, pInstinct, pState, event, pThing);
}

int J3DAPI sithAIInstinct_LookForTarget(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, SithAIMode newMode)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_LookForTarget, pLocal, pInstinct, pState, event, newMode);
}

int J3DAPI sithAIInstinct_SenseDanger(SithAIControlBlock* pLocal, SithAIInstinct* pInstance, SithAIInstinctState* pState, SithAIEventType event, SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_SenseDanger, pLocal, pInstance, pState, event, pThing);
}

signed int J3DAPI sithAIInstinct_FearGunshot(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, void* pObject)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_FearGunshot, pLocal, pInstinct, pState, event, pObject);
}

int J3DAPI sithAIInstinct_Hop(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, void* pObject)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_Hop, pLocal, pInstinct, pState, event, pObject);
}

int J3DAPI sithAIInstinct_HoverDrift(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, void* pObject)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_HoverDrift, pLocal, pInstinct, pState, event, pObject);
}

int J3DAPI sithAIInstinct_Talk(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, void* pObject)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_Talk, pLocal, pInstinct, pState, event, pObject);
}

int J3DAPI sithAIInstinct_RandomTurn(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, void* pObject)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_RandomTurn, pLocal, pInstinct, pState, event, pObject);
}

int J3DAPI sithAIInstinct_OpenDoors(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, void* pObject)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_OpenDoors, pLocal, pInstinct, pState, event, pObject);
}

int J3DAPI sithAIInstinct_Jump(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, void* pObject)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_Jump, pLocal, pInstinct, pState, event, pObject);
}

int J3DAPI sithAIInstinct_LobFire(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, void* pObject)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_LobFire, pLocal, pInstinct, pState, event, pObject);
}

int J3DAPI sithAIInstinct_PrimaryFire(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, void* pObject)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_PrimaryFire, pLocal, pInstinct, pState, event, pObject);
}

int J3DAPI sithAIInstinct_AlternateFire(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, void* pObject)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_AlternateFire, pLocal, pInstinct, pState, event, pObject);
}

int J3DAPI sithAIInstinct_CircleStrafe(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_CircleStrafe, pLocal, pInstinct, pState, event, pThing);
}

int J3DAPI sithAIInstinct_Dodge(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_Dodge, pLocal, pInstinct, pState, event, pThing);
}

int J3DAPI sithAIInstinct_HitAndRun(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, void* pObject)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_HitAndRun, pLocal, pInstinct, pState, event, pObject);
}

int J3DAPI sithAIInstinct_Retreat(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, void* pObject)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_Retreat, pLocal, pInstinct, pState, event, pObject);
}

int J3DAPI sithAIInstinct_RandomMove(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, void* pObject)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_RandomMove, pLocal, pInstinct, pState, event, pObject);
}

// local variable allocation has failed, the output may be wrong!
int J3DAPI sithAIInstinct_HumanCombatMove(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, void* pObject)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_HumanCombatMove, pLocal, pInstinct, pState, event, pObject);
}

int J3DAPI sithAIInstinct_Roam(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_Roam, pLocal, pInstinct, pState, event, pThing);
}

int J3DAPI sithAIInstinct_ReturnHome(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, void* pObject)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_ReturnHome, pLocal, pInstinct, pState, event, pObject);
}

int J3DAPI sithAIInstinct_Flee(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_Flee, pLocal, pInstinct, pState, event, pThing);
}

int J3DAPI sithAIInstinct_BasicFallow(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, void* pObject)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_BasicFallow, pLocal, pInstinct, pState, event, pObject);
}

int J3DAPI sithAIInstinct_WallCrawl(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, SithSurface* pSurface)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_WallCrawl, pLocal, pInstinct, pState, event, pSurface);
}

void J3DAPI sithAIInstinct_sub_494360(SithAIControlBlock* pLocal, rdVector3* moveToPosLeft, rdVector3* moveToPosRight)
{
    J3D_TRAMPOLINE_CALL(sithAIInstinct_sub_494360, pLocal, moveToPosLeft, moveToPosRight);
}

int J3DAPI sithAIInstinct_SnakeMungeTestCheck(SithAIControlBlock* pLocal, rdVector3* pDirection, float distance, rdVector3* pOutPoint)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_SnakeMungeTestCheck, pLocal, pDirection, distance, pOutPoint);
}

signed int J3DAPI sithAIInstinct_SnakeFollow(SithAIControlBlock* pLocal, SithAIInstinct* pInstinct, SithAIInstinctState* pState, SithAIEventType event, SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithAIInstinct_SnakeFollow, pLocal, pInstinct, pState, event, pThing);
}

void J3DAPI sithAIInstinct_sub_494FF0(const SithThing* pThing, float a2)
{
    J3D_TRAMPOLINE_CALL(sithAIInstinct_sub_494FF0, pThing, a2);
}
