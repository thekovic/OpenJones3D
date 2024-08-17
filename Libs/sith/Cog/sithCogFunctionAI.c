#include "sithCogFunctionAI.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithCogFunctionAI_aThingsInView J3D_DECL_FAR_ARRAYVAR(sithCogFunctionAI_aThingsInView, SithThing*(*)[32])
#define sithCogFunctionAI_numThingsInView J3D_DECL_FAR_VAR(sithCogFunctionAI_numThingsInView, int)
#define sithCogFunctionAI_curThingInView J3D_DECL_FAR_VAR(sithCogFunctionAI_curThingInView, int)

void sithCogFunctionAI_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithCogFunctionAI_RegisterFunctions);
    // J3D_HOOKFUNC(sithCogFunctionAI_AISetMoveSpeed);
    // J3D_HOOKFUNC(sithCogFunctionAI_AISetMovePos);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIGetHomePos);
    // J3D_HOOKFUNC(sithCogFunctionAI_AISetMaxHomeDist);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIGetGoalThing);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIGetGoalLVec);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIJump);
    // J3D_HOOKFUNC(sithCogFunctionAI_AISetMoveFrame);
    // J3D_HOOKFUNC(sithCogFunctionAI_AISetMoveThing);
    // J3D_HOOKFUNC(sithCogFunctionAI_AISetGoalThing);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIEnableHeadTracking);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIDisableHeadTracking);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIEnableBodyTracking);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIDisableBodyTracking);
    // J3D_HOOKFUNC(sithCogFunctionAI_AISetLookPos);
    // J3D_HOOKFUNC(sithCogFunctionAI_AISetLookFrame);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIGetMovePos);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIPauseMove);
    // J3D_HOOKFUNC(sithCogFunctionAI_AISetMode);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIGetMode);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIClearMode);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIGetSubMode);
    // J3D_HOOKFUNC(sithCogFunctionAI_AISetSubMode);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIClearSubMode);
    // J3D_HOOKFUNC(sithCogFunctionAI_FirstThingInView);
    // J3D_HOOKFUNC(sithCogFunctionAI_NextThingInView);
    // J3D_HOOKFUNC(sithCogFunctionAI_ThingViewDot);
    // J3D_HOOKFUNC(sithCogFunctionAI_AISetFireTarget);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIEnableInstinct);
    // J3D_HOOKFUNC(sithCogFunctionAI_AISetCutsceneMode);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIClearCutsceneMode);
    // J3D_HOOKFUNC(sithCogFunctionAI_IsAITargetInSight);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIFlee);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIStopFlee);
    // J3D_HOOKFUNC(sithCogFunctionAI_AISetClass);
    // J3D_HOOKFUNC(sithCogFunctionAI_AISetLookThing);
    // J3D_HOOKFUNC(sithCogFunctionAI_AISetLookThingEyeLevel);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIWaitForStop);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIWaitForHeadTracking);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIGetArmedMode);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIKnockout);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIRunOver);
    // J3D_HOOKFUNC(sithCogFunctionAI_AISetAllowedSurfaceType);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIClearAllowedSurfaceType);
    // J3D_HOOKFUNC(sithCogFunctionAI_AISetWpnt);
    // J3D_HOOKFUNC(sithCogFunctionAI_AISetWpntRank);
    // J3D_HOOKFUNC(sithCogFunctionAI_AISetWpntFlags);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIClearWpntFlags);
    // J3D_HOOKFUNC(sithCogFunctionAI_AISetActiveWpntLayer);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIConnectWpnts);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIConnectWpntsOneWay);
    // J3D_HOOKFUNC(sithCogFunctionAI_AITraverseWpnts);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIClearTraverseWpnts);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIFindNearestWpnt);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIWpntHuntTarget);
    // J3D_HOOKFUNC(sithCogFunctionAI_AISetInstinctWpntMode);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIClearInstinctWpntMode);
    // J3D_HOOKFUNC(sithCogFunctionAI_AIFleeToWpnt);
    // J3D_HOOKFUNC(sithCogFunctionAI_AISpat);
}

void sithCogFunctionAI_ResetGlobals(void)
{
    memset(&sithCogFunctionAI_aThingsInView, 0, sizeof(sithCogFunctionAI_aThingsInView));
    memset(&sithCogFunctionAI_numThingsInView, 0, sizeof(sithCogFunctionAI_numThingsInView));
    memset(&sithCogFunctionAI_curThingInView, 0, sizeof(sithCogFunctionAI_curThingInView));
}

int J3DAPI sithCogFunctionAI_RegisterFunctions(SithCogSymbolTable* pTable)
{
    return J3D_TRAMPOLINE_CALL(sithCogFunctionAI_RegisterFunctions, pTable);
}

void J3DAPI sithCogFunctionAI_AISetMoveSpeed(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AISetMoveSpeed, pCog);
}

void J3DAPI sithCogFunctionAI_AISetMovePos(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AISetMovePos, pCog);
}

void J3DAPI sithCogFunctionAI_AIGetHomePos(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIGetHomePos, pCog);
}

void J3DAPI sithCogFunctionAI_AISetMaxHomeDist(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AISetMaxHomeDist, pCog);
}

void J3DAPI sithCogFunctionAI_AIGetGoalThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIGetGoalThing, pCog);
}

void J3DAPI sithCogFunctionAI_AIGetGoalLVec(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIGetGoalLVec, pCog);
}

void J3DAPI sithCogFunctionAI_AIJump(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIJump, pCog);
}

void J3DAPI sithCogFunctionAI_AISetMoveFrame(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AISetMoveFrame, pCog);
}

void J3DAPI sithCogFunctionAI_AISetMoveThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AISetMoveThing, pCog);
}

void J3DAPI sithCogFunctionAI_AISetGoalThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AISetGoalThing, pCog);
}

void J3DAPI sithCogFunctionAI_AIEnableHeadTracking(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIEnableHeadTracking, pCog);
}

void J3DAPI sithCogFunctionAI_AIDisableHeadTracking(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIDisableHeadTracking, pCog);
}

void J3DAPI sithCogFunctionAI_AIEnableBodyTracking(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIEnableBodyTracking, pCog);
}

void J3DAPI sithCogFunctionAI_AIDisableBodyTracking(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIDisableBodyTracking, pCog);
}

void J3DAPI sithCogFunctionAI_AISetLookPos(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AISetLookPos, pCog);
}

void J3DAPI sithCogFunctionAI_AISetLookFrame(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AISetLookFrame, pCog);
}

void J3DAPI sithCogFunctionAI_AIGetMovePos(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIGetMovePos, pCog);
}

void J3DAPI sithCogFunctionAI_AIPauseMove(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIPauseMove, pCog);
}

void J3DAPI sithCogFunctionAI_AISetMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AISetMode, pCog);
}

void J3DAPI sithCogFunctionAI_AIGetMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIGetMode, pCog);
}

void J3DAPI sithCogFunctionAI_AIClearMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIClearMode, pCog);
}

void J3DAPI sithCogFunctionAI_AIGetSubMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIGetSubMode, pCog);
}

void J3DAPI sithCogFunctionAI_AISetSubMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AISetSubMode, pCog);
}

void J3DAPI sithCogFunctionAI_AIClearSubMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIClearSubMode, pCog);
}

// Gets a thing in the specified view from a thing. 
// Use : 
//     FirstThingInView(ThingThatFinds, FOV(in angle), Distance(jku), WhatToLookForFlag);
//     Flag is the thing type value. The Type is ThingTypeMask
//     For ie if flag is 0x4, then actor thing should be returned
//     Returns the thing found.
// 
// From:    
//     https://web.archive.org/web/20011212235446/http://www.sfc.keio.ac.jp:80/~t00214ho/millennium/cogverb/
// 
// Forum:
//     https://web.archive.org/web/20200114134644/https://forums.massassi.net/vb3/archive/index.php/t-14421.html
void J3DAPI sithCogFunctionAI_FirstThingInView(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_FirstThingInView, pCog);
}

void J3DAPI sithCogFunctionAI_NextThingInView(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_NextThingInView, pCog);
}

void J3DAPI sithCogFunctionAI_ThingViewDot(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_ThingViewDot, pCog);
}

void J3DAPI sithCogFunctionAI_AISetFireTarget(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AISetFireTarget, pCog);
}

void J3DAPI sithCogFunctionAI_AIEnableInstinct(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIEnableInstinct, pCog);
}

void J3DAPI sithCogFunctionAI_AISetCutsceneMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AISetCutsceneMode, pCog);
}

void J3DAPI sithCogFunctionAI_AIClearCutsceneMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIClearCutsceneMode, pCog);
}

void J3DAPI sithCogFunctionAI_IsAITargetInSight(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_IsAITargetInSight, pCog);
}

void J3DAPI sithCogFunctionAI_AIFlee(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIFlee, pCog);
}

void J3DAPI sithCogFunctionAI_AIStopFlee(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIStopFlee, pCog);
}

void J3DAPI sithCogFunctionAI_AISetClass(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AISetClass, pCog);
}

void J3DAPI sithCogFunctionAI_AISetLookThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AISetLookThing, pCog);
}

void J3DAPI sithCogFunctionAI_AISetLookThingEyeLevel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AISetLookThingEyeLevel, pCog);
}

void J3DAPI sithCogFunctionAI_AIWaitForStop(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIWaitForStop, pCog);
}

void J3DAPI sithCogFunctionAI_AIWaitForHeadTracking(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIWaitForHeadTracking, pCog);
}

void J3DAPI sithCogFunctionAI_AIGetArmedMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIGetArmedMode, pCog);
}

void J3DAPI sithCogFunctionAI_AIKnockout(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIKnockout, pCog);
}

void J3DAPI sithCogFunctionAI_AIRunOver(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIRunOver, pCog);
}

void J3DAPI sithCogFunctionAI_AISetAllowedSurfaceType(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AISetAllowedSurfaceType, pCog);
}

void J3DAPI sithCogFunctionAI_AIClearAllowedSurfaceType(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIClearAllowedSurfaceType, pCog);
}

void J3DAPI sithCogFunctionAI_AISetWpnt(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AISetWpnt, pCog);
}

void J3DAPI sithCogFunctionAI_AISetWpntRank(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AISetWpntRank, pCog);
}

void J3DAPI sithCogFunctionAI_AISetWpntFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AISetWpntFlags, pCog);
}

void J3DAPI sithCogFunctionAI_AIClearWpntFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIClearWpntFlags, pCog);
}

void J3DAPI sithCogFunctionAI_AISetActiveWpntLayer(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AISetActiveWpntLayer, pCog);
}

void J3DAPI sithCogFunctionAI_AIConnectWpnts(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIConnectWpnts, pCog);
}

void J3DAPI sithCogFunctionAI_AIConnectWpntsOneWay(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIConnectWpntsOneWay, pCog);
}

void J3DAPI sithCogFunctionAI_AITraverseWpnts(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AITraverseWpnts, pCog);
}

void J3DAPI sithCogFunctionAI_AIClearTraverseWpnts(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIClearTraverseWpnts, pCog);
}

void J3DAPI sithCogFunctionAI_AIFindNearestWpnt(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIFindNearestWpnt, pCog);
}

void J3DAPI sithCogFunctionAI_AIWpntHuntTarget(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIWpntHuntTarget, pCog);
}

void J3DAPI sithCogFunctionAI_AISetInstinctWpntMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AISetInstinctWpntMode, pCog);
}

void J3DAPI sithCogFunctionAI_AIClearInstinctWpntMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIClearInstinctWpntMode, pCog);
}

void J3DAPI sithCogFunctionAI_AIFleeToWpnt(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AIFleeToWpnt, pCog);
}

void J3DAPI sithCogFunctionAI_AISpat(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionAI_AISpat, pCog);
}
