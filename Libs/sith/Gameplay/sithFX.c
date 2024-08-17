#include "sithFX.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithFX_aChalkMarkNames J3D_DECL_FAR_ARRAYVAR(sithFX_aChalkMarkNames, char*(*)[35])
#define sithFX_rowRippleLastPos J3D_DECL_FAR_VAR(sithFX_rowRippleLastPos, rdVector3)
#define sithFX_msecLastCreatedFairyDustDeluxTime J3D_DECL_FAR_VAR(sithFX_msecLastCreatedFairyDustDeluxTime, unsigned int)
#define sithFX_numChalkMarks J3D_DECL_FAR_VAR(sithFX_numChalkMarks, int)
#define sithFX_fariyDustSizeFactor J3D_DECL_FAR_VAR(sithFX_fariyDustSizeFactor, int)
#define sithFX_newFairyDustDeluxSizeFactor J3D_DECL_FAR_VAR(sithFX_newFairyDustDeluxSizeFactor, int)
#define sithFX_fairyDustDeluxSizeFactor J3D_DECL_FAR_VAR(sithFX_fairyDustDeluxSizeFactor, int)
#define sithFX_secLastCreatedRowRipple J3D_DECL_FAR_VAR(sithFX_secLastCreatedRowRipple, float)

void sithFX_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithFX_Reset);
    // J3D_HOOKFUNC(sithFX_ClearChalkMarks);
    // J3D_HOOKFUNC(sithFX_DestroyFairyDustDeluxe);
    // J3D_HOOKFUNC(sithFX_CreateFairyDust);
    // J3D_HOOKFUNC(sithFX_SetFairyDustSize);
    // J3D_HOOKFUNC(sithFX_UpdateFairyDustUserBlock);
    // J3D_HOOKFUNC(sithFX_CreateFairyDustDelux);
    // J3D_HOOKFUNC(sithFX_CreateFairyDustDeluxDusts);
    // J3D_HOOKFUNC(sithFX_CreateBubble);
    // J3D_HOOKFUNC(sithFX_CreateWaterRipple);
    // J3D_HOOKFUNC(sithFX_CreateRaftRipple);
    // J3D_HOOKFUNC(sithFX_CreateRaftWake);
    // J3D_HOOKFUNC(sithFX_CreatePaddleSplash);
    // J3D_HOOKFUNC(sithFX_CreateRowWaterFx);
    // J3D_HOOKFUNC(sithFX_CreateRipple);
    // J3D_HOOKFUNC(sithFX_CreateMineCarSparks);
    // J3D_HOOKFUNC(sithFX_CreateChalkMark);
    // J3D_HOOKFUNC(sithFX_CreateThingOnSurface);
    // J3D_HOOKFUNC(sithFX_UpdatePolyline);
    // J3D_HOOKFUNC(sithFX_ResetPolylineTexVertOffset);
    // J3D_HOOKFUNC(sithFX_CreateLaserThing);
    // J3D_HOOKFUNC(sithFX_CreateLightningThing);
    // J3D_HOOKFUNC(sithFX_CreatePolylineThing);
}

void sithFX_ResetGlobals(void)
{
    int sithFX_g_lastChalkMarkNum_tmp = -1;
    memcpy(&sithFX_g_lastChalkMarkNum, &sithFX_g_lastChalkMarkNum_tmp, sizeof(sithFX_g_lastChalkMarkNum));
    
    char *sithFX_aChalkMarkNames_tmp[35] = {
      "+1947_mark",
      "+alien_mark",
      "+ankh_mark",
      "+ark_mark",
      "+cccr_mark",
      "+check_mark",
      "+cir_mark",
      "+cross_mark",
      "+eye_mark",
      "+five_mark",
      "+grail_mark",
      "+guy_mark",
      "+happy_mark",
      "+hawk_mark",
      "+here_mark",
      "+indy_mark",
      "+indy2_mark",
      "+la_mark",
      "+love_mark",
      "+portrait_mark",
      "+pound_mark",
      "+pyramid_mark",
      "+question_mark",
      "+r2d2_mark",
      "+skull_mark",
      "+snake_mark",
      "+square_mark",
      "+star_mark",
      "+stones_mark",
      "+sunrise_mark",
      "+tentacle_mark",
      "+tictactoe_mark",
      "+triangle_mark",
      "+usa_mark",
      "+x_mark"
    };
    memcpy(&sithFX_aChalkMarkNames, &sithFX_aChalkMarkNames_tmp, sizeof(sithFX_aChalkMarkNames));
    
    memset(&sithFX_rowRippleLastPos, 0, sizeof(sithFX_rowRippleLastPos));
    memset(&sithFX_msecLastCreatedFairyDustDeluxTime, 0, sizeof(sithFX_msecLastCreatedFairyDustDeluxTime));
    memset(&sithFX_numChalkMarks, 0, sizeof(sithFX_numChalkMarks));
    memset(&sithFX_fariyDustSizeFactor, 0, sizeof(sithFX_fariyDustSizeFactor));
    memset(&sithFX_newFairyDustDeluxSizeFactor, 0, sizeof(sithFX_newFairyDustDeluxSizeFactor));
    memset(&sithFX_fairyDustDeluxSizeFactor, 0, sizeof(sithFX_fairyDustDeluxSizeFactor));
    memset(&sithFX_secLastCreatedRowRipple, 0, sizeof(sithFX_secLastCreatedRowRipple));
    memset(&sithFX_g_aChalkMarks, 0, sizeof(sithFX_g_aChalkMarks));
}

void sithFX_Reset(void)
{
    J3D_TRAMPOLINE_CALL(sithFX_Reset);
}

void sithFX_ClearChalkMarks(void)
{
    J3D_TRAMPOLINE_CALL(sithFX_ClearChalkMarks);
}

void J3DAPI sithFX_DestroyFairyDustDeluxe(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithFX_DestroyFairyDustDeluxe, pThing);
}

void J3DAPI sithFX_CreateFairyDust(rdVector3* pos, SithSector* pSector)
{
    J3D_TRAMPOLINE_CALL(sithFX_CreateFairyDust, pos, pSector);
}

int J3DAPI sithFX_SetFairyDustSize(rdParticle* pParticle, int sizeFactor)
{
    return J3D_TRAMPOLINE_CALL(sithFX_SetFairyDustSize, pParticle, sizeFactor);
}

void J3DAPI sithFX_UpdateFairyDustUserBlock(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithFX_UpdateFairyDustUserBlock, pThing);
}

void J3DAPI sithFX_CreateFairyDustDelux(SithThing* pThing, rdVector3* pPos)
{
    J3D_TRAMPOLINE_CALL(sithFX_CreateFairyDustDelux, pThing, pPos);
}

int J3DAPI sithFX_CreateFairyDustDeluxDusts(SithThing* pThing, SithFairyDustUserBlock* pUserBlock)
{
    return J3D_TRAMPOLINE_CALL(sithFX_CreateFairyDustDeluxDusts, pThing, pUserBlock);
}

void J3DAPI sithFX_CreateBubble(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithFX_CreateBubble, pThing);
}

void J3DAPI sithFX_CreateWaterRipple(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithFX_CreateWaterRipple, pThing);
}

void J3DAPI sithFX_CreateRaftRipple(SithThing* pThing, int bCreateSplash)
{
    J3D_TRAMPOLINE_CALL(sithFX_CreateRaftRipple, pThing, bCreateSplash);
}

void J3DAPI sithFX_CreateRaftWake(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithFX_CreateRaftWake, pThing);
}

void J3DAPI sithFX_CreatePaddleSplash(SithThing* pThing, rdVector3* pos)
{
    J3D_TRAMPOLINE_CALL(sithFX_CreatePaddleSplash, pThing, pos);
}

void J3DAPI sithFX_CreateRowWaterFx(SithThing* pThing, float secTime)
{
    J3D_TRAMPOLINE_CALL(sithFX_CreateRowWaterFx, pThing, secTime);
}

void J3DAPI sithFX_CreateRipple(SithThing* pThing, float size)
{
    J3D_TRAMPOLINE_CALL(sithFX_CreateRipple, pThing, size);
}

SithThing* J3DAPI sithFX_CreateMineCarSparks(SithThing* pThing, rdVector3* pSparkPos)
{
    return J3D_TRAMPOLINE_CALL(sithFX_CreateMineCarSparks, pThing, pSparkPos);
}

void J3DAPI sithFX_CreateChalkMark(rdVector3* pPos, SithSurface* pAttSurf, SithSector* pSector)
{
    J3D_TRAMPOLINE_CALL(sithFX_CreateChalkMark, pPos, pAttSurf, pSector);
}

SithThing* J3DAPI sithFX_CreateThingOnSurface(SithThing* pTemplate, rdVector3* pPos, SithSurface* pAttSurf, SithSector* pSector)
{
    return J3D_TRAMPOLINE_CALL(sithFX_CreateThingOnSurface, pTemplate, pPos, pAttSurf, pSector);
}

void J3DAPI sithFX_UpdatePolyline(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithFX_UpdatePolyline, pThing);
}

void J3DAPI sithFX_ResetPolylineTexVertOffset(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithFX_ResetPolylineTexVertOffset, pThing);
}

SithThing* J3DAPI sithFX_CreateLaserThing(const SithThing* pSourceThing, const rdVector3* vecOffset, const rdVector3* vecEnd, float baseRadius, float tipRadius, float duration)
{
    return J3D_TRAMPOLINE_CALL(sithFX_CreateLaserThing, pSourceThing, vecOffset, vecEnd, baseRadius, tipRadius, duration);
}

SithThing* J3DAPI sithFX_CreateLightningThing(const SithThing* pSourceThing, const rdVector3* offset, const rdVector3* endPos, float baseRadius, float tipRadius, float duration)
{
    return J3D_TRAMPOLINE_CALL(sithFX_CreateLightningThing, pSourceThing, offset, endPos, baseRadius, tipRadius, duration);
}

// Crates polyline from pStartThing to pEndThing or endPos if pEndThing is null
SithThing* J3DAPI sithFX_CreatePolylineThing(const SithThing* pSourceThing, SithThing* pEndThing, const rdVector3* endPos, rdMaterial* pMaterial, float baseRadius, float tipRadius, float duration)
{
    return J3D_TRAMPOLINE_CALL(sithFX_CreatePolylineThing, pSourceThing, pEndThing, endPos, pMaterial, baseRadius, tipRadius, duration);
}
