#include "sithAIMove.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>


void sithAIMove_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithAIMove_Update);
    // J3D_HOOKFUNC(sithAIMove_UpdateMineCar);
    // J3D_HOOKFUNC(sithAIMove_sub_4958B0);
    // J3D_HOOKFUNC(sithAIMove_sub_495CD0);
    // J3D_HOOKFUNC(sithAIMove_sub_4961A0);
    // J3D_HOOKFUNC(sithAIMove_sub_496200);
    // J3D_HOOKFUNC(sithAIMove_sub_496550);
    // J3D_HOOKFUNC(sithAIMove_sub_4966D0);
    // J3D_HOOKFUNC(sithAIMove_sub_496820);
    // J3D_HOOKFUNC(sithAIMove_AIGetMoveState);
    // J3D_HOOKFUNC(sithAIMove_sub_496A50);
    // J3D_HOOKFUNC(sithAIMove_UpdateAIMove);
    // J3D_HOOKFUNC(sithAIMove_GetAIMoveModes);
    // J3D_HOOKFUNC(sithAIMove_SetSubMode);
    // J3D_HOOKFUNC(sithAIMove_PuppetCallback);
    // J3D_HOOKFUNC(sithAIMove_AISetLookThing);
    // J3D_HOOKFUNC(sithAIMove_AISetLookPos);
    // J3D_HOOKFUNC(sithAIMove_AISetLookPosEyeLevel);
    // J3D_HOOKFUNC(sithAIMove_AISetMovePos);
    // J3D_HOOKFUNC(sithAIMove_AISetMoveTargetPos);
    // J3D_HOOKFUNC(sithAIMove_sub_497FF0);
    // J3D_HOOKFUNC(sithAIMove_sub_498890);
    // J3D_HOOKFUNC(sithAIMove_AIJump);
    // J3D_HOOKFUNC(sithAIMove_AIStop);
    // J3D_HOOKFUNC(sithAIMove_SetGoalReached);
    // J3D_HOOKFUNC(sithAIMove_Unreachable);
    // J3D_HOOKFUNC(sithAIMove_StopAIMovement);
    // J3D_HOOKFUNC(sithAIMove_ResetAILook);
    // J3D_HOOKFUNC(sithAIMove_UpdateBoss);
    // J3D_HOOKFUNC(sithAIMove_sub_499090);
    // J3D_HOOKFUNC(sithAIMove_sub_4996C0);
    // J3D_HOOKFUNC(sithAIMove_sub_499A80);
    // J3D_HOOKFUNC(sithAIMove_sub_499CA0);
    // J3D_HOOKFUNC(sithAIMove_sub_49A020);
    // J3D_HOOKFUNC(sithAIMove_sub_49A1B0);
    // J3D_HOOKFUNC(sithAIMove_sub_49A450);
    // J3D_HOOKFUNC(sithAIMove_sub_49A630);
    // J3D_HOOKFUNC(sithAIMove_sub_49A810);
    // J3D_HOOKFUNC(sithAIMove_UpdateQuetzTail);
    // J3D_HOOKFUNC(sithAIMove_sub_49AA60);
    // J3D_HOOKFUNC(sithAIMove_sub_49AB80);
    // J3D_HOOKFUNC(sithAIMove_sub_49AC50);
    // J3D_HOOKFUNC(sithAIMove_sub_49AF80);
    // J3D_HOOKFUNC(sithAIMove_sub_49B1B0);
    // J3D_HOOKFUNC(sithAIMove_UpdateMardukTail);
}

void sithAIMove_ResetGlobals(void)
{
    memset(&sithAIMove_g_flt_585464, 0, sizeof(sithAIMove_g_flt_585464));
    memset(&sithAIMove_g_flt_585468, 0, sizeof(sithAIMove_g_flt_585468));
    memset(&sithAIMove_g_flt_58546C, 0, sizeof(sithAIMove_g_flt_58546C));
    memset(&sithAIMove_g_flt_585470, 0, sizeof(sithAIMove_g_flt_585470));
}

void J3DAPI sithAIMove_Update(SithThing* pThing, float secDeltatTime)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_Update, pThing, secDeltatTime);
}

void J3DAPI sithAIMove_UpdateMineCar(SithAIControlBlock* pLocal, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_UpdateMineCar, pLocal, secDeltaTime);
}

void J3DAPI sithAIMove_sub_4958B0(SithAIControlBlock* pLocal, float secDeltatTime)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_sub_4958B0, pLocal, secDeltatTime);
}

void J3DAPI sithAIMove_sub_495CD0(SithAIControlBlock* pLocal, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_sub_495CD0, pLocal, secDeltaTime);
}

void J3DAPI sithAIMove_sub_4961A0(SithAIControlBlock* pLocal)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_sub_4961A0, pLocal);
}

double J3DAPI sithAIMove_sub_496200(SithAIControlBlock* pLocal, const rdVector3* a2, rdVector3* a3)
{
    return J3D_TRAMPOLINE_CALL(sithAIMove_sub_496200, pLocal, a2, a3);
}

int J3DAPI sithAIMove_sub_496550(SithAIControlBlock* pLocal, float secDeltaTime)
{
    return J3D_TRAMPOLINE_CALL(sithAIMove_sub_496550, pLocal, secDeltaTime);
}

int J3DAPI sithAIMove_sub_4966D0(SithAIControlBlock* pLocal, float secDeltaTime)
{
    return J3D_TRAMPOLINE_CALL(sithAIMove_sub_4966D0, pLocal, secDeltaTime);
}

int J3DAPI sithAIMove_sub_496820(SithAIControlBlock* pLocal, float secDeltaTime)
{
    return J3D_TRAMPOLINE_CALL(sithAIMove_sub_496820, pLocal, secDeltaTime);
}

int J3DAPI sithAIMove_AIGetMoveState(const SithAIControlBlock* pLocal)
{
    return J3D_TRAMPOLINE_CALL(sithAIMove_AIGetMoveState, pLocal);
}

int J3DAPI sithAIMove_sub_496A50(SithAIControlBlock* pLocal, float angle)
{
    return J3D_TRAMPOLINE_CALL(sithAIMove_sub_496A50, pLocal, angle);
}

float J3DAPI sithAIMove_UpdateAIMove(SithAIControlBlock* pLocal)
{
    return J3D_TRAMPOLINE_CALL(sithAIMove_UpdateAIMove, pLocal);
}

void J3DAPI sithAIMove_GetAIMoveModes(const SithThing* pThing, float moveSpeed, int moveDirection, SithThingMoveStatus* pOutMoveStatus, SithPuppetSubMode* pOutSubmode)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_GetAIMoveModes, pThing, moveSpeed, moveDirection, pOutMoveStatus, pOutSubmode);
}

int J3DAPI sithAIMove_SetSubMode(SithAIControlBlock* pLocal, SithThingMoveStatus moveStatus, SithPuppetSubMode submode)
{
    return J3D_TRAMPOLINE_CALL(sithAIMove_SetSubMode, pLocal, moveStatus, submode);
}

void J3DAPI sithAIMove_PuppetCallback(SithThing* pThing, int trackNum, rdKeyMarkerType marker)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_PuppetCallback, pThing, trackNum, marker);
}

void J3DAPI sithAIMove_AISetLookThing(SithAIControlBlock* pLocal, const SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_AISetLookThing, pLocal, pThing);
}

void J3DAPI sithAIMove_AISetLookPos(SithAIControlBlock* pLocal, const rdVector3* targetPos)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_AISetLookPos, pLocal, targetPos);
}

void J3DAPI sithAIMove_AISetLookPosEyeLevel(SithAIControlBlock* pLocal, const rdVector3* targetPos)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_AISetLookPosEyeLevel, pLocal, targetPos);
}

int J3DAPI sithAIMove_AISetMovePos(SithAIControlBlock* pLocal, const rdVector3* moveToPos, float moveSpeed)
{
    return J3D_TRAMPOLINE_CALL(sithAIMove_AISetMovePos, pLocal, moveToPos, moveSpeed);
}

int J3DAPI sithAIMove_AISetMoveTargetPos(SithAIControlBlock* pLocal, const rdVector3* moveToPos, float moveSpeed)
{
    return J3D_TRAMPOLINE_CALL(sithAIMove_AISetMoveTargetPos, pLocal, moveToPos, moveSpeed);
}

int J3DAPI sithAIMove_sub_497FF0(SithAIControlBlock* pLocal, int armedModeState)
{
    return J3D_TRAMPOLINE_CALL(sithAIMove_sub_497FF0, pLocal, armedModeState);
}

void J3DAPI sithAIMove_sub_498890(SithAIControlBlock* pLocal, int type)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_sub_498890, pLocal, type);
}

void J3DAPI sithAIMove_AIJump(SithAIControlBlock* pLocal, rdVector3* movePos, float a3)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_AIJump, pLocal, movePos, a3);
}

void J3DAPI sithAIMove_AIStop(SithAIControlBlock* pLocal)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_AIStop, pLocal);
}

void J3DAPI sithAIMove_SetGoalReached(SithAIControlBlock* pLocal)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_SetGoalReached, pLocal);
}

void J3DAPI sithAIMove_Unreachable(SithAIControlBlock* pLocal)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_Unreachable, pLocal);
}

void J3DAPI sithAIMove_StopAIMovement(SithAIControlBlock* pLocal)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_StopAIMovement, pLocal);
}

void J3DAPI sithAIMove_ResetAILook(SithAIControlBlock* pLocal)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_ResetAILook, pLocal);
}

void J3DAPI sithAIMove_UpdateBoss(SithAIControlBlock* pLocal, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_UpdateBoss, pLocal, secDeltaTime);
}

void J3DAPI sithAIMove_sub_499090(SithAIControlBlock* pLocal, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_sub_499090, pLocal, secDeltaTime);
}

void J3DAPI sithAIMove_sub_4996C0(SithAIControlBlock* pLocal, float a2)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_sub_4996C0, pLocal, a2);
}

void J3DAPI sithAIMove_sub_499A80(SithAIControlBlock* pLocal, float* pDestAngle, float* a3, float* a4, float* a5)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_sub_499A80, pLocal, pDestAngle, a3, a4, a5);
}

void J3DAPI sithAIMove_sub_499CA0(SithAIControlBlock* pLocal, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_sub_499CA0, pLocal, secDeltaTime);
}

void J3DAPI sithAIMove_sub_49A020(SithAIControlBlock* pLocal, float* angle, float* a3, float* a4, float* a5)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_sub_49A020, pLocal, angle, a3, a4, a5);
}

void J3DAPI sithAIMove_sub_49A1B0(SithAIControlBlock* pLocal, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_sub_49A1B0, pLocal, secDeltaTime);
}

void J3DAPI sithAIMove_sub_49A450(SithAIControlBlock* pLocal, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_sub_49A450, pLocal, secDeltaTime);
}

void J3DAPI sithAIMove_sub_49A630(SithAIControlBlock* pLocal, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_sub_49A630, pLocal, secDeltaTime);
}

void J3DAPI sithAIMove_sub_49A810(SithAIControlBlock* pLocal, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_sub_49A810, pLocal, secDeltaTime);
}

void J3DAPI sithAIMove_UpdateQuetzTail(SithAIControlBlock* pLocal, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_UpdateQuetzTail, pLocal, secDeltaTime);
}

void J3DAPI sithAIMove_sub_49AA60(SithAIControlBlock* pLocal)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_sub_49AA60, pLocal);
}

void J3DAPI sithAIMove_sub_49AB80(SithAIControlBlock* pLocal)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_sub_49AB80, pLocal);
}

void J3DAPI sithAIMove_sub_49AC50(SithAIControlBlock* pLocal)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_sub_49AC50, pLocal);
}

void J3DAPI sithAIMove_sub_49AF80(SithAIControlBlock* pLocal)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_sub_49AF80, pLocal);
}

void J3DAPI sithAIMove_sub_49B1B0(SithAIControlBlock* pLocal)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_sub_49B1B0, pLocal);
}

void J3DAPI sithAIMove_UpdateMardukTail(SithThing* pThing, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithAIMove_UpdateMardukTail, pThing, secDeltaTime);
}
