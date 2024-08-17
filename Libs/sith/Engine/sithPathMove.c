#include "sithPathMove.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>


void sithPathMove_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithPathMove_SkipToFrame);
    // J3D_HOOKFUNC(sithPathMove_MoveToFrame);
    // J3D_HOOKFUNC(sithPathMove_RotatePivot);
    // J3D_HOOKFUNC(sithPathMove_FollowNextPath);
    // J3D_HOOKFUNC(sithPathMove_MoveToPos);
    // J3D_HOOKFUNC(sithPathMove_RotateToPYR);
    // J3D_HOOKFUNC(sithPathMove_Update);
    // J3D_HOOKFUNC(sithPathMove_ParseArg);
    // J3D_HOOKFUNC(sithPathMove_SendMessageBlocked);
    // J3D_HOOKFUNC(sithPathMove_UpdatePath);
    // J3D_HOOKFUNC(sithPathMove_Finish);
    // J3D_HOOKFUNC(sithPathMove_PathMovePause);
    // J3D_HOOKFUNC(sithPathMove_PathMoveResume);
    // J3D_HOOKFUNC(sithPathMove_Create);
}

void sithPathMove_ResetGlobals(void)
{

}

void J3DAPI sithPathMove_SkipToFrame(SithThing* pThing, int frame, float velocity)
{
    J3D_TRAMPOLINE_CALL(sithPathMove_SkipToFrame, pThing, frame, velocity);
}

int J3DAPI sithPathMove_MoveToFrame(SithThing* pThing, int frame, float velocity)
{
    return J3D_TRAMPOLINE_CALL(sithPathMove_MoveToFrame, pThing, frame, velocity);
}

void J3DAPI sithPathMove_RotatePivot(SithThing* pThing, const rdVector3* pOffset, const rdVector3* pRot, float rotTime)
{
    J3D_TRAMPOLINE_CALL(sithPathMove_RotatePivot, pThing, pOffset, pRot, rotTime);
}

void J3DAPI sithPathMove_FollowNextPath(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPathMove_FollowNextPath, pThing);
}

double J3DAPI sithPathMove_MoveToPos(SithThing* pThing, SithPathFrame* pos)
{
    return J3D_TRAMPOLINE_CALL(sithPathMove_MoveToPos, pThing, pos);
}

void J3DAPI sithPathMove_RotateToPYR(SithThing* pThing, rdVector3* pyr, float time)
{
    J3D_TRAMPOLINE_CALL(sithPathMove_RotateToPYR, pThing, pyr, time);
}

void J3DAPI sithPathMove_Update(SithThing* pThing, float simTime)
{
    J3D_TRAMPOLINE_CALL(sithPathMove_Update, pThing, simTime);
}

signed int J3DAPI sithPathMove_ParseArg(StdConffileArg* pArg, SithThing* pThing, int adjNum)
{
    return J3D_TRAMPOLINE_CALL(sithPathMove_ParseArg, pArg, pThing, adjNum);
}

void J3DAPI sithPathMove_SendMessageBlocked(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPathMove_SendMessageBlocked, pThing);
}

void J3DAPI sithPathMove_UpdatePath(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPathMove_UpdatePath, pThing);
}

void J3DAPI sithPathMove_Finish(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPathMove_Finish, pThing);
}

signed int J3DAPI sithPathMove_PathMovePause(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithPathMove_PathMovePause, pThing);
}

signed int J3DAPI sithPathMove_PathMoveResume(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithPathMove_PathMoveResume, pThing);
}

void J3DAPI sithPathMove_Create(SithThing* pNewThing, const SithThing* pMarker, const rdVector3* pOffset)
{
    J3D_TRAMPOLINE_CALL(sithPathMove_Create, pNewThing, pMarker, pOffset);
}
