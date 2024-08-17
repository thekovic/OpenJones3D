#ifndef SITH_SITHCOGFUNCTIONAI_H
#define SITH_SITHCOGFUNCTIONAI_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

int J3DAPI sithCogFunctionAI_RegisterFunctions(SithCogSymbolTable* pTable);
void J3DAPI sithCogFunctionAI_AISetMoveSpeed(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AISetMovePos(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIGetHomePos(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AISetMaxHomeDist(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIGetGoalThing(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIGetGoalLVec(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIJump(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AISetMoveFrame(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AISetMoveThing(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AISetGoalThing(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIEnableHeadTracking(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIDisableHeadTracking(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIEnableBodyTracking(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIDisableBodyTracking(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AISetLookPos(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AISetLookFrame(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIGetMovePos(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIPauseMove(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AISetMode(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIGetMode(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIClearMode(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIGetSubMode(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AISetSubMode(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIClearSubMode(SithCog* pCog);
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
void J3DAPI sithCogFunctionAI_FirstThingInView(SithCog* pCog);
void J3DAPI sithCogFunctionAI_NextThingInView(SithCog* pCog);
void J3DAPI sithCogFunctionAI_ThingViewDot(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AISetFireTarget(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIEnableInstinct(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AISetCutsceneMode(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIClearCutsceneMode(SithCog* pCog);
void J3DAPI sithCogFunctionAI_IsAITargetInSight(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIFlee(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIStopFlee(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AISetClass(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AISetLookThing(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AISetLookThingEyeLevel(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIWaitForStop(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIWaitForHeadTracking(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIGetArmedMode(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIKnockout(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIRunOver(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AISetAllowedSurfaceType(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIClearAllowedSurfaceType(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AISetWpnt(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AISetWpntRank(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AISetWpntFlags(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIClearWpntFlags(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AISetActiveWpntLayer(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIConnectWpnts(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIConnectWpntsOneWay(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AITraverseWpnts(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIClearTraverseWpnts(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIFindNearestWpnt(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIWpntHuntTarget(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AISetInstinctWpntMode(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIClearInstinctWpntMode(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AIFleeToWpnt(SithCog* pCog);
void J3DAPI sithCogFunctionAI_AISpat(SithCog* pCog);

// Helper hooking functions
void sithCogFunctionAI_InstallHooks(void);
void sithCogFunctionAI_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHCOGFUNCTIONAI_H
