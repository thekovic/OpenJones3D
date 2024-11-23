#include "sithFX.h"
#include <j3dcore/j3dhook.h>

#include <sith/Engine/sithAnimate.h>
#include <sith/Engine/sithPhysics.h>
#include <sith/Engine/sithParticle.h>
#include <sith/Gameplay/sithTime.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/symbols.h>
#include <sith/World/sithMaterial.h>
#include <sith/World/sithTemplate.h>
#include <sith/World/sithThing.h>
#include <sith/World/sithWorld.h>

#include <rdroid/Engine/rdThing.h>
#include <rdroid/Math/rdMath.h>
#include <rdroid/Math/rdMatrix.h>
#include <rdroid/Math/rdVector.h>
#include <rdroid/Primitives/rdParticle.h>
#include <rdroid/Primitives/rdPolyline.h>

#include <std/General/stdConffile.h>
#include <std/General/stdMemory.h>
#include <std/General/stdUtil.h>

const char* sithFX_aChalkMarkNames[35] =
{
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

rdVector3 sithFX_rowRippleLastPos    = { 0 }; // Added: Init to 0
float sithFX_secLastCreatedRowRipple = 0.0f;  // Added: Init to 0

rdVector3 sithFx_leftTireStartPosOffset;
rdVector3 sithFx_rightTireStartPosOffset;

size_t sithFX_fariyDustSizeFactor         = 0; // Added: Init to 0
size_t sithFX_newFairyDustDeluxSizeFactor = 0; // Added: Init to 0
size_t sithFX_fairyDustDeluxSizeFactor    = 0; // Added: Init to 0
unsigned int sithFX_msecLastCreatedFairyDustDeluxTime = 0; // Added: Init to 0

void sithFX_InstallHooks(void)
{
    J3D_HOOKFUNC(sithFX_Reset);
    J3D_HOOKFUNC(sithFX_ClearChalkMarks);
    J3D_HOOKFUNC(sithFX_DestroyFairyDustDeluxe);
    J3D_HOOKFUNC(sithFX_CreateFairyDust);
    J3D_HOOKFUNC(sithFX_SetFairyDustSize);
    J3D_HOOKFUNC(sithFX_UpdateFairyDustUserBlock);
    J3D_HOOKFUNC(sithFX_CreateFairyDustDelux);
    J3D_HOOKFUNC(sithFX_CreateFairyDustDeluxDusts);
    J3D_HOOKFUNC(sithFX_CreateBubble);
    J3D_HOOKFUNC(sithFX_CreateWaterRipple);
    J3D_HOOKFUNC(sithFX_CreateRaftRipple);
    J3D_HOOKFUNC(sithFX_CreateRaftWake);
    J3D_HOOKFUNC(sithFX_CreatePaddleSplash);
    J3D_HOOKFUNC(sithFX_CreateRowWaterFx);
    J3D_HOOKFUNC(sithFX_CreateRipple);
    J3D_HOOKFUNC(sithFX_CreateMineCarSparks);
    J3D_HOOKFUNC(sithFX_CreateChalkMark);
    J3D_HOOKFUNC(sithFX_CreateThingOnSurface);
    J3D_HOOKFUNC(sithFX_UpdatePolyline);
    J3D_HOOKFUNC(sithFX_ResetPolylineTexVertOffset);
    J3D_HOOKFUNC(sithFX_CreateLaserThing);
    J3D_HOOKFUNC(sithFX_CreateLightningThing);
    J3D_HOOKFUNC(sithFX_CreatePolylineThing);
}

void sithFX_ResetGlobals(void)
{
    int sithFX_g_lastChalkMarkNum_tmp = -1;
    memcpy(&sithFX_g_lastChalkMarkNum, &sithFX_g_lastChalkMarkNum_tmp, sizeof(sithFX_g_lastChalkMarkNum));

    size_t sithFX_g_numChalkMarks_tmp = 0;
    memcpy(&sithFX_g_numChalkMarks, &sithFX_g_numChalkMarks_tmp, sizeof(sithFX_g_numChalkMarks));

    memset(&sithFX_g_aChalkMarks, 0, sizeof(sithFX_g_aChalkMarks));
}

void sithFX_Reset(void)
{
    sithFX_g_numChalkMarks    = 0;
    sithFX_g_lastChalkMarkNum = -1;
    sithFX_ClearChalkMarks();
}

void sithFX_ClearChalkMarks(void)
{
    int i;

    for ( i = 0; i < STD_ARRAYLEN(sithFX_g_aChalkMarks); ++i )
    {
        sithFX_g_aChalkMarks[i] = NULL;
    }
}

void J3DAPI sithFX_DestroyFairyDustDeluxe(SithThing* pThing)
{
    SithFairyDustUserBlock* pFairydust;
    int i;

    if ( pThing && pThing->userblock.pFairydust )
    {
        pFairydust = pThing->userblock.pFairydust;
        for ( i = 0; i < STD_ARRAYLEN(pFairydust->aDusts); ++i )
        {
            if ( pFairydust->aDusts[i] && pFairydust->aDusts[i]->type != SITH_THING_FREE && (pFairydust->aDusts[i]->flags & SITH_TF_DESTROYED) == 0 )
            {
                sithParticle_DestroyParticle(pFairydust->aDusts[i]);
            }

            pFairydust->aDusts[i] = NULL;
        }

        stdMemory_Free(pThing->userblock.pFairydust);
        pThing->userblock.pFairydust = NULL;
    }
}

void J3DAPI sithFX_CreateFairyDust(const rdVector3* pos, SithSector* pSector)
{
    SithThing* pTemplate = sithTemplate_GetTemplate("+imp2_trail");
    if ( !pTemplate ) {
        return;
    }

    SithThing* pDust = sithThing_CreateThingAtPos(pTemplate, pos, &pTemplate->orient, pSector, NULL); // Fixed: Fixed initing. pDust
    if ( pDust )
    {
        sithFX_fariyDustSizeFactor = sithFX_SetFairyDustSize(pDust->renderData.data.pParticle, sithFX_fariyDustSizeFactor);
    }
}

size_t J3DAPI sithFX_SetFairyDustSize(rdParticle* pParticle, size_t sizeFactor)
{
    if ( sizeFactor > 0 )
    {
        --sizeFactor;
    }
    else
    {
        sizeFactor = 2;
    }

    float size = (float)sizeFactor * 0.0025f + 0.005f;
    pParticle->size = size;
    pParticle->sizeHalf = pParticle->size / 2.0f;
    return sizeFactor;
}

void J3DAPI sithFX_UpdateFairyDustUserBlock(SithThing* pThing)
{
    if ( !pThing )
    {
        return;
    }

    if ( !pThing->pParent )
    {
        return;
    }

    SithFairyDustUserBlock* pFairydust = pThing->pParent->userblock.pFairydust;
    if ( !pFairydust )
    {
        return;
    }

    for ( size_t i = 0; i < STD_ARRAYLEN(pFairydust->aDusts); ++i )
    {
        if ( pFairydust->aDusts[i] && ((pFairydust->aDusts[i]->flags & SITH_TF_DESTROYED) != 0 || pFairydust->aDusts[i]->type == SITH_THING_FREE) )
        {
            pFairydust->aDusts[i] = NULL;
        }
    }

    if ( strcmp(pThing->thingInfo.particleInfo.pMaterial->aName, "aet_4sprite_glow_fairy_dust.mat") == 0 )
    {
        pThing->pos.x = pThing->pParent->pos.x;
        pThing->pos.y = pThing->pParent->pos.y;
    }
}

void J3DAPI sithFX_CreateFairyDustDelux(SithThing* pThing, const rdVector3* pPos)
{
    if ( !pThing )
    {
        return;
    }

    SithFairyDustUserBlock* pFairydust = pThing->userblock.pFairydust;
    if ( pFairydust ) // If exists, update
    {
        if ( pFairydust->bCreateNormalFairyDust )
        {
            if ( pPos )
            {
                sithFX_CreateFairyDust(pPos, pThing->pInSector);
            }
        }

        else if ( sithTime_g_msecGameTime - sithFX_msecLastCreatedFairyDustDeluxTime <= 900 )
        {
            sithFX_CreateFairyDustDeluxDusts(pThing, pFairydust);
        }
        else
        {
            pFairydust->bCreateNormalFairyDust = 1;
        }
    }
    else
    {
        pFairydust = (SithFairyDustUserBlock*)STDMALLOC(sizeof(SithFairyDustUserBlock));
        if ( pFairydust )
        {
            memset(pFairydust, 0, sizeof(SithFairyDustUserBlock));
            if ( sithFX_CreateFairyDustDeluxDusts(pThing, pFairydust) )
            {
                pFairydust->bCreateNormalFairyDust = 0;
                pThing->userblock.pFairydust = pFairydust;
                sithFX_msecLastCreatedFairyDustDeluxTime = sithTime_g_msecGameTime;
            }
            else
            {
                stdMemory_Free(pFairydust);
            }
        }
    }
}

int J3DAPI sithFX_CreateFairyDustDeluxDusts(SithThing* pThing, SithFairyDustUserBlock* pFairydust)
{
    SithThing* pTemplate = sithTemplate_GetTemplate("+imp2_dust");
    if ( !pTemplate )
    {
        return 0;
    }

    rdVector3 pos;
    rdVector_Copy3(&pos, &pThing->pos);

    float size = sithPhysics_GetThingHeight(pThing);
    pos.z = pos.z - size;
    pos.z = (float)pFairydust->numUsedDusts * 0.045000002f + 0.022500001f + pos.z;

    for ( size_t i = 0; i < STD_ARRAYLEN(pFairydust->aDusts); ++i )
    {
        if ( pFairydust->aDusts[i] )
        {
            if ( pFairydust->aDusts[i]->type )
            {
                sithFX_fairyDustDeluxSizeFactor = sithFX_SetFairyDustSize(pFairydust->aDusts[i]->renderData.data.pParticle, sithFX_fairyDustDeluxSizeFactor);
            }
        }
    }

    if ( pFairydust->aDusts[pFairydust->numUsedDusts] && pFairydust->aDusts[pFairydust->numUsedDusts]->type != SITH_THING_FREE )
    {
        return 1;
    }

    SithThing* pDust = sithThing_CreateThingAtPos(pTemplate, &pos, &pTemplate->orient, pThing->pInSector, NULL);
    if ( !pDust )
    {
        return 0;
    }

    pDust->pParent = pThing;
    sithFX_newFairyDustDeluxSizeFactor = sithFX_SetFairyDustSize(pDust->renderData.data.pParticle, sithFX_newFairyDustDeluxSizeFactor);

    pFairydust->aDusts[pFairydust->numUsedDusts++] = pDust;
    if ( pFairydust->numUsedDusts == STD_ARRAYLEN(pFairydust->aDusts) )
    {
        pFairydust->numUsedDusts = 0;
    }

    return 1;
}

void J3DAPI sithFX_CreateBubble(SithThing* pThing)
{
    if ( pThing->type == SITH_THING_PLAYER && (!pThing->pInSector || (pThing->pInSector->flags & SITH_SECTOR_UNDERWATER) != 0) )
    {
        SithThing* pTemplate = sithTemplate_GetTemplate("+bubbles");
        if ( !pTemplate )
        {
            return;
        }

        SithThing* pSprite = sithThing_CreateThingAtPos(pTemplate, &pThing->pos, &pTemplate->orient, pThing->pInSector, NULL);
        if ( !pSprite )
        {
            SITHLOG_ERROR("Couldn't make a bubble thing!\n");
            return;
        }

        pSprite->flags |= SITH_TF_AIRDESTROYED;

        rdVector3 offset;
        rdVector_Scale3(&offset, &pThing->orient.lvec, 0.07f);

        rdVector_Add3Acc(&pSprite->pos, &offset);
        pSprite->pos.z = pSprite->pos.z + pThing->collide.movesize;

        float size = pThing->collide.movesize / 3.0f;
        rdVector_Scale3(&offset, &pThing->orient.rvec, size);

        if ( SITH_RANDF() > 0.5f )
        {
            rdVector_Sub3Acc(&pSprite->pos, &offset);
        }
        else
        {
            rdVector_Add3Acc(&pSprite->pos, &offset);
        }

        rdVector3 start;
        start.x = 0.001f;
        start.y = 0.001f;
        start.z = 1.0f;

        rdVector3 end;
        end.x = 0.02f;
        end.y = 0.02f;
        end.z = 0.0f;
        float time = (SITH_RANDF() - 0.5f) * 2.0f + 4.0f;
        sithAnimate_StartSpriteSizeAnim(pSprite, &start, &end, time);

        rdVector3 vel;
        vel.x = SITH_RANDF() - 0.5f;
        vel.y = SITH_RANDF() - 0.5f;
        vel.z = SITH_RANDF() + 0.55000001f;
        rdVector_Scale3Acc(&vel, 0.02f);
        rdVector_Copy3(&pSprite->moveInfo.physics.velocity, &vel);
    }
}

void J3DAPI sithFX_CreateWaterRipple(SithThing* pThing)
{
    if ( ((pThing->pInSector->flags & SITH_SECTOR_UNDERWATER) == 0 || (pThing->moveInfo.physics.flags & SITH_PF_ONWATERSURFACE) != 0)
      && (pThing->pInSector->flags & SITH_SECTOR_AETHERIUM) == 0 )
    {
        SithThing* pTemplate = sithTemplate_GetTemplate("+ripples");
        if ( !pTemplate )
        {
            return;
        }

        rdVector3 pos, start, end;
        if ( (pThing->moveInfo.physics.flags & SITH_PF_ONWATERSURFACE) != 0 || (pThing->moveInfo.physics.flags & SITH_PF_RAFT) != 0 )
        {
            float size = pThing->collide.movesize;
            start.x = size;
            start.y = size;
            start.z = 1.0f;

            size = pThing->collide.movesize * 4.0f;
            end.x = size;
            end.y = size;
            end.z = 0.0f;

            rdVector_Copy3(&pos, &pThing->pos);
            pos.z += pThing->attach.someAttachDistance + 0.001f;
        }
        else
        {
            float size = pThing->collide.movesize / 4.0f;
            start.x = size;
            start.y = size;
            start.z = 1.0f;

            size = pThing->collide.movesize * 2.0f;
            end.x = size;
            end.y = size;
            end.z = 0.0f;

            rdVector_Copy3(&pos, &pThing->pos);
            pos.z = pos.z - pThing->collide.movesize * 2.0f;
        }

        SithThing* pSprite = sithThing_CreateThingAtPos(pTemplate, &pos, &pTemplate->orient, pThing->pInSector, NULL);
        if ( !pSprite )
        {
            SITHLOG_ERROR("Can't make a ripple, no thing space!\n");
            return;
        }

        pSprite->orient.lvec.x = 0.0f;
        pSprite->orient.lvec.y = 0.0f;
        pSprite->orient.lvec.z = 1.0f;
        float time = SITH_RANDF() + 1.0f;
        sithAnimate_StartSpriteSizeAnim(pSprite, &start, &end, time);
    }
}

void J3DAPI sithFX_CreateRaftRipple(SithThing* pThing, int bCreateSplash)
{
    rdVector3 ripplePos = { 0 }; // Added: Init to 0

    SithThing* pTemplate = sithTemplate_GetTemplate("+ripples");
    if ( pTemplate && pThing->attach.flags )
    {
        float size = pThing->collide.movesize;
        rdVector3 start = { .x=size, .y=size, .z=1.0f };

        size = pThing->collide.movesize * 4.0f;
        rdVector3 end = { .x=size, .y=size, .z=0.0f };

        rdVector_Copy3(&ripplePos, &pThing->pos); // TODO: maybe this should be done outside of this scope

        ripplePos.x  = (SITH_RANDF() - 0.5f) * 0.03f + ripplePos.x;
        ripplePos.y  = (SITH_RANDF() - 0.5f) * 0.03f + ripplePos.y;
        ripplePos.z -= rdMath_DistancePointToPlane(&pThing->pos, &pThing->attach.pFace->normal, &pThing->attach.attachedFaceFirstVert) + 0.0020000001f;

        SithThing* pSprite = sithThing_CreateThingAtPos(pTemplate, &ripplePos, &pTemplate->orient, pThing->pInSector, NULL);
        if ( !pSprite )
        {
            SITHLOG_ERROR("Can't make a ripple, no thing space!\n");
            return;
        }

        pSprite->orient.lvec.x = 0.0f;
        pSprite->orient.lvec.y = 0.0f;
        pSprite->orient.lvec.z = 1.0f;
        float time = SITH_RANDF() + 1.5f;
        sithAnimate_StartSpriteSizeAnim(pSprite, &start, &end, time);
    }

    if ( bCreateSplash )
    {
        pTemplate = sithTemplate_GetTemplate("+raft_splash");
        SithThing* pMistTpl = sithTemplate_GetTemplate("spritlemist");
        if ( !pTemplate || !pMistTpl )
        {
            // TODO: maybe log warning
            return;
        }

        // Sprite sizes
        rdVector3 start;
        start.x = 3.5f;
        start.y = 1.5f;
        start.z = 1.0f;

        rdVector3 end;
        end.x = 3.5f;
        end.y = 1.5f;
        end.z = 1.0f;

        // Create splash thing
        rdVector3 pos;
        pos.x = 0.12f; // right
        pos.y = 0.090000004f;
        pos.z = 0.0099999998f;
        rdMatrix_TransformVector34Acc(&pos, &pThing->orient);
        rdVector_Add3Acc(&pos, &ripplePos);

        rdMatrix34 orient;
        rdMatrix_Copy34(&orient, &pThing->orient);

        rdVector3 pyr;
        pyr.x = 90.0f;
        pyr.y = 90.0f;
        pyr.z = 0.0f;
        rdMatrix_PreRotate34(&orient, &pyr);
        rdVector_Copy3(&orient.uvec, &pThing->attach.pFace->normal);

        SithThing* pSprite = sithThing_CreateThingAtPos(pTemplate, &pos, &orient, pThing->pInSector, NULL);
        if ( pSprite )
        {
            sithAnimate_StartSpriteSizeAnim(pSprite, &start, &end, 0.5f);
        }

        // Create mist thing
        pos.z += 0.050000001f;
        sithThing_CreateThingAtPos(pMistTpl, &pos, &pMistTpl->orient, pThing->pInSector, NULL);

        // Create another splash thing
        pos.x = -0.12f; // left
        pos.y = 0.090000004f;
        pos.z = 0.0099999998f;
        rdMatrix_TransformVector34Acc(&pos, &pThing->orient);
        rdVector_Add3Acc(&pos, &ripplePos);

        rdMatrix_Copy34(&orient, &pThing->orient);

        pyr.x = 90.0f;
        pyr.y = -90.0f;
        pyr.z = 0.0f;
        rdMatrix_PreRotate34(&orient, &pyr);
        rdVector_Copy3(&orient.uvec, &pThing->attach.pFace->normal);

        pSprite = sithThing_CreateThingAtPos(pTemplate, &pos, &orient, pThing->pInSector, NULL);
        if ( pSprite )
        {
            sithAnimate_StartSpriteSizeAnim(pSprite, &start, &end, 0.5f);
        }

        // Create another mist thing
        pos.z += 0.050000001f;
        sithThing_CreateThingAtPos(pMistTpl, &pos, &pMistTpl->orient, pThing->pInSector, NULL);

        rdMaterial* pMat = sithMaterial_Load("riv_a4sprite_rocksplash.mat");
        if ( pMat )
        {
            sithAnimate_StartMaterialAnim(pMat, 16.0f, (SithAnimateFlags)0);
        }
    }
}

void J3DAPI sithFX_CreateRaftWake(SithThing* pThing)
{
    SithThing* pTemplate = sithTemplate_GetTemplate("+raft_wake");
    if ( pTemplate && pThing->attach.flags )
    {
        rdVector3 start;
        start.x = 0.175f;
        start.y = 0.1f;
        start.z = 0.25f;

        rdVector3 end;
        end.x = 0.27500001f;
        end.y = 0.40000001f;
        end.z = 0.0f;

        rdVector3 pos;
        rdVector_Copy3(&pos, &pThing->pos);
        pos.z -= rdMath_DistancePointToPlane(&pThing->pos, &pThing->attach.pFace->normal, &pThing->attach.attachedFaceFirstVert) + 0.0020000001f;

        SithThing* pSprite = sithThing_CreateThingAtPos(pTemplate, &pos, &pTemplate->orient, pThing->pInSector, NULL);
        if ( !pSprite )
        {
            SITHLOG_ERROR("Can't make a wake, no thing space!\n");
            return;
        }

        pSprite->orient.lvec.x = 0.0f;
        pSprite->orient.lvec.y = 0.0f;
        pSprite->orient.lvec.z = 1.0f;

        rdVector3 dirFwd;
        rdVector_Normalize3(&dirFwd, &pThing->moveInfo.physics.velocity);
        const float rollAngle = rdMath_DeltaAngleNormalized(&rdroid_g_xVector3, &dirFwd, &rdroid_g_zVector3);

        pSprite->thingInfo.spriteInfo.rollAngle = rollAngle + 180.0f;

        sithAnimate_StartSpriteSizeAnim(pSprite, &start, &end, 0.5f);
    }
}

void J3DAPI sithFX_CreatePaddleSplash(SithThing* pThing, const rdVector3* pos)
{
    SithThing* pTemplate = sithTemplate_GetTemplate("paddlesplash");
    if ( pTemplate )
    {
        SithThing* pSplash = sithThing_CreateThingAtPos(pTemplate, pos, &pTemplate->orient, pThing->pInSector, NULL);
        if ( !pSplash )
        {
            SITHLOG_ERROR("Can't make a paddle splash, no thing space!\n");
            return;
        }

        pSplash->moveInfo.physics.velocity.z = 0.07f;
    }
}


void J3DAPI sithFX_CreateRowWaterFx(SithThing* pThing, float secTime)
{
    float secDeltaTime = sithTime_g_secGameTime - secTime;
    float secDelatLastCreated = sithTime_g_secGameTime - sithFX_secLastCreatedRowRipple;

    rdVector3 ripplePos;
    switch ( pThing->moveStatus )
    {
        case SITHPLAYERMOVE_RAFT_PADDLE_FORWARD_LEFT:
            ripplePos.x = -0.075000003f - 0.0f * secDeltaTime;
            ripplePos.y = -0.31999999f * secDeltaTime + 0.090000004f;
            ripplePos.z = -sithPhysics_GetThingHeight(pThing);
            break;

        case SITHPLAYERMOVE_RAFT_PADDLE_FORWARD_RIGHT:
            ripplePos.x = 0.0f * secDeltaTime + 0.075000003f;
            ripplePos.y = -0.31999999f * secDeltaTime + 0.090000004f;
            ripplePos.z = -sithPhysics_GetThingHeight(pThing);
            break;

        case SITHPLAYERMOVE_RAFT_TURN_LEFT:
        case SITHPLAYERMOVE_RAFT_PADDLE_BACK_LEFT:
            ripplePos.x = -0.07f - 0.0f * secDeltaTime;
            ripplePos.y = 0.12f * secDeltaTime + -0.039999999f;
            ripplePos.z = -sithPhysics_GetThingHeight(pThing);
            break;

        case SITHPLAYERMOVE_RAFT_TURN_RIGHT:
        case SITHPLAYERMOVE_RAFT_PADDLE_BACK_RIGHT:
            ripplePos.x = 0.0f * secDeltaTime + 0.07f;
            ripplePos.y = 0.12f * secDeltaTime + -0.039999999f;
            ripplePos.z = -sithPhysics_GetThingHeight(pThing);
            break;

        default:
            return;
    }

    rdMatrix_TransformPoint34Acc(&ripplePos, &pThing->orient);
    rdVector_Add3Acc(&ripplePos, &pThing->pos);
    ripplePos.z += 0.001f;

    bool bCreateSplashFx = false;
    if ( secDeltaTime == 0.0f || secDelatLastCreated >= 0.2f )
    {
        bCreateSplashFx = true;
    }
    else
    {
        rdVector3 deltaPos;
        rdVector_Sub3(&deltaPos, &ripplePos, &sithFX_rowRippleLastPos);
        if ( rdVector_Len3(&deltaPos) > 0.0049999999f )
        {
            bCreateSplashFx = true;
        }
    }

    if ( !bCreateSplashFx )
    {
        goto skip;
    }

    if ( (int32_t)pThing->userval != 3 ) // If not underwater sector, set by sithPhysics_GetWaterNormalAtPos. Note 4 is water surface
    {
        goto skip;
    }

    SithThing* pTemplate = sithTemplate_GetTemplate("+ripples");
    if ( !pTemplate )
    {
        goto skip;
    }

    SithThing* pSprite = sithThing_CreateThingAtPos(pTemplate, &ripplePos, &pTemplate->orient, pThing->pInSector, NULL);
    if ( !pSprite )
    {
        SITHLOG_ERROR("Can't make a ripple, no thing space!\n", 0);
        return;
    }

    // Start sprite animation
    rdVector_Copy3(&pSprite->orient.lvec, &pThing->orient.uvec);

    rdVector3 start;
    start.x = 0.0049999999f;
    start.y = 0.0049999999f;
    start.z = 1.0f;

    rdVector3 end;
    end.x = 0.029999999f;
    end.y = 0.029999999f;
    end.z = 0.0f;

    float time = SITH_RANDF() + 1.0f;
    sithAnimate_StartSpriteSizeAnim(pSprite, &start, &end, time);

    rdVector_Copy3(&sithFX_rowRippleLastPos, &ripplePos);
    sithFX_secLastCreatedRowRipple = sithTime_g_secGameTime;

skip:
    if ( bCreateSplashFx )
    {
        ripplePos.z += 0.0080000004f;
        sithFX_CreatePaddleSplash(pThing, &ripplePos);
    }
}

void J3DAPI sithFX_CreateRipple(SithThing* pThing, float size)
{
    SithThing* pTemplate = sithTemplate_GetTemplate("+ripples");
    if ( pTemplate && pThing->attach.flags )
    {

        rdVector3 start;
        start.x = size;
        start.y = size;
        start.z = 1.0f;

        rdVector3 end;
        float endSize = size * 2.0f;
        end.x = endSize;
        end.y = endSize;
        end.z = 0.0f;

        rdVector3 pos;
        pos.x = (SITH_RANDF() - 0.5f) * (size * 0.5f);
        pos.y = (SITH_RANDF() - 0.5f) * (size * 0.5f);
        pos.z = 0.0020000001f;

        rdVector_Add3Acc(&pos, &pThing->pos);
        pos.z -= rdMath_DistancePointToPlane(&pThing->pos, &pThing->attach.pFace->normal, &pThing->attach.attachedFaceFirstVert);

        SithThing* pSprite = sithThing_CreateThingAtPos(pTemplate, &pos, &pTemplate->orient, pThing->pInSector, NULL);
        if ( !pSprite )
        {
            SITHLOG_ERROR("Can't make a ripple, no thing space!\n");
            return;
        }

        pSprite->orient.lvec.x = 0.0f;
        pSprite->orient.lvec.y = 0.0f;
        pSprite->orient.lvec.z = 1.0f;
        sithAnimate_StartSpriteSizeAnim(pSprite, &start, &end, 2.5f);
    }
}

void J3DAPI sithFx_CreateTireFx(SithThing* pThing, const rdVector3* pPosLeft, rdMaterial* pMatLeft, const rdVector3* pPosRigth, rdMaterial* pMatRight)
{

    float a;
    float aa;
    SithThing* pTemplate;
    float v10;
    float yawAngle;
    int bLeft;
    float dot;
    float speed;
    rdVector3 dir;
    SithThing* pLeftParticles;
    rdVector3 pos;
    float v18;
    float v19;
    int bRight;
    SithThing* pRightParticles;

    pLeftParticles = 0;
    pRightParticles = 0;
    bLeft = 0;
    bRight = 0;

    speed = rdVector_Normalize3(&dir, &pThing->moveInfo.physics.velocity);

    dot = rdVector_Dot3(&pThing->orient.rvec, &dir);
    v10 = speed * dot * 1.0f;
    yawAngle = pThing->moveInfo.physics.angularVelocity.y * 0.0099999998f + v10;
    v19 = 0.001f;
    if ( dot < 0.0f )
    {
        dot = -dot;
    }

    v19 = dot * 0.1f + v19;
    v19 = speed * 0.0049999999f + v19;

    a = (pPosLeft->x - sithFx_leftTireStartPosOffset.x) * (pPosLeft->x - sithFx_leftTireStartPosOffset.x)
        + (pPosLeft->y - sithFx_leftTireStartPosOffset.y) * (pPosLeft->y - sithFx_leftTireStartPosOffset.y)
        + (pPosLeft->z - sithFx_leftTireStartPosOffset.z) * (pPosLeft->z - sithFx_leftTireStartPosOffset.z);
    v18 = sqrtf(a);
    if ( v18 >= 0.0049999999f && SITH_RANDF() < v19 )
    {
        bLeft = 1;
    }

    aa = (pPosRigth->x - sithFx_rightTireStartPosOffset.x) * (pPosRigth->x - sithFx_rightTireStartPosOffset.x)
        + (pPosRigth->y - sithFx_rightTireStartPosOffset.y) * (pPosRigth->y - sithFx_rightTireStartPosOffset.y)
        + (pPosRigth->z - sithFx_rightTireStartPosOffset.z) * (pPosRigth->z - sithFx_rightTireStartPosOffset.z);
    if ( sqrtf(aa) >= 0.0049999999f && SITH_RANDF() < v19 )
    {
        bRight = 1;
    }

    pTemplate = sithTemplate_GetTemplate("paddlesplash");
    if ( pTemplate && (bRight || bLeft) )
    {
        if ( pMatLeft )
        {
            memcpy(&pos, pPosLeft, sizeof(pos));
            pos.x = pThing->orient.lvec.x * -0.025f + pos.x;
            pos.y = pThing->orient.lvec.y * -0.025f + pos.y;
            pos.z = pThing->orient.lvec.z * -0.025f + pos.z;

            pos.x = pThing->orient.rvec.x * 0.0070000002f + pos.x;
            pos.y = pThing->orient.rvec.y * 0.0070000002f + pos.y;
            pos.z = pThing->orient.rvec.z * 0.0070000002f + pos.z;

            pos.x = pThing->orient.uvec.x * 0.035f + pos.x;
            pos.y = pThing->orient.uvec.y * 0.035f + pos.y;
            pos.z = pThing->orient.uvec.z * 0.035f + pos.z;

            pLeftParticles = sithThing_CreateThingAtPos(pTemplate, &pos, &pTemplate->orient, pThing->pInSector, NULL);
            if ( !pLeftParticles )
            {
                SITHLOG_ERROR("Can't make a tirefx, no thing space!\n");
                return;
            }

            pLeftParticles->renderData.data.pParticle->pMaterial = pMatLeft;
        }

        if ( pMatRight )
        {
            memcpy(&pos, pPosRigth, sizeof(pos));
            pos.x = pThing->orient.lvec.x * -0.025f + pos.x;
            pos.y = pThing->orient.lvec.y * -0.025f + pos.y;
            pos.z = pThing->orient.lvec.z * -0.025f + pos.z;

            pos.x = pThing->orient.rvec.x * -0.0070000002f + pos.x;
            pos.y = pThing->orient.rvec.y * -0.0070000002f + pos.y;
            pos.z = pThing->orient.rvec.z * -0.0070000002f + pos.z;

            pos.x = pThing->orient.uvec.x * 0.035f + pos.x;
            pos.y = pThing->orient.uvec.y * 0.035f + pos.y;
            pos.z = pThing->orient.uvec.z * 0.035f + pos.z;

            pRightParticles = sithThing_CreateThingAtPos(pTemplate, &pos, &pTemplate->orient, pThing->pInSector, NULL);
            if ( !pRightParticles )
            {
                SITHLOG_ERROR("Can't make a tirefx, no thing space!\n");
                return;
            }

            pRightParticles->renderData.data.pParticle->pMaterial = pMatRight;
        }

        if ( pLeftParticles )
        {
            pLeftParticles->moveInfo.physics.velocity.x = pThing->orient.rvec.x * yawAngle;
            pLeftParticles->moveInfo.physics.velocity.y = pThing->orient.rvec.y * yawAngle;
            pLeftParticles->moveInfo.physics.velocity.z = pThing->orient.rvec.z * yawAngle;
            pLeftParticles->moveInfo.physics.velocity.z = speed * 0.40000001f + pLeftParticles->moveInfo.physics.velocity.z;
            pLeftParticles->msecLifeLeft = 200;
        }

        if ( pRightParticles )
        {
            pRightParticles->moveInfo.physics.velocity.x = pThing->orient.rvec.x * yawAngle;
            pRightParticles->moveInfo.physics.velocity.y = pThing->orient.rvec.y * yawAngle;
            pRightParticles->moveInfo.physics.velocity.z = pThing->orient.rvec.z * yawAngle;
            pRightParticles->moveInfo.physics.velocity.z = speed * 0.40000001f + pRightParticles->moveInfo.physics.velocity.z;
            pRightParticles->msecLifeLeft = 200;
        }
    }
}

SithThing* J3DAPI sithFX_CreateMineCarSparks(SithThing* pThing, const rdVector3* pSparkPos)
{
    SithThing* pSparks = sithTemplate_GetTemplate("minecarsparks");
    if ( !pSparks )
    {
        return pSparks;
    }

    rdVector3 pos;
    rdMatrix_TransformPoint34(&pos, pSparkPos, &pThing->orient);
    rdVector_Add3Acc(&pos, &pThing->pos);

    pSparks = sithThing_CreateThingAtPos(pSparks, &pos, &pSparks->orient, pThing->pInSector, NULL);
    if ( !pSparks )
    {
        SITHLOG_ERROR("Can't make a spark, no thing space!\n");
        return NULL;
    }

    pSparks->moveInfo.physics.velocity.z = 0.5f;
    return pSparks;
}

void J3DAPI sithFX_CreateChalkMark(const rdVector3* pPos, const SithSurface* pAttSurf, SithSector* pSector)
{
    if ( sithFX_g_lastChalkMarkNum + 1 >= STD_ARRAYLEN(sithFX_g_aChalkMarks) )
    {
        sithFX_g_lastChalkMarkNum = -1;
    }

    size_t markNum = sithFX_g_lastChalkMarkNum + 1;
    size_t tplNum  = 0;
    bool bSearch = false; // Added init to false
    do
    {
        tplNum = (size_t)(SITH_RAND() * (float)STD_ARRAYLEN(sithFX_aChalkMarkNames));
        bSearch = false;
        for ( size_t i = 0; i < sithFX_g_numChalkMarks && !bSearch && sithFX_g_aChalkMarks[i]; i++ )
        {
            if ( strcmp(sithFX_g_aChalkMarks[i]->aName, sithFX_aChalkMarkNames[tplNum]) == 0 )
            {
                bSearch = true;
            }
        }
    } while ( bSearch );

    SithThing* pTemplate = sithTemplate_GetTemplate(sithFX_aChalkMarkNames[tplNum]);
    if ( pTemplate )
    {
        if ( sithFX_g_aChalkMarks[markNum] )
        {
            sithThing_RemoveThing(sithWorld_g_pCurrentWorld, sithFX_g_aChalkMarks[markNum]);
            sithFX_g_aChalkMarks[markNum] = NULL;
        }

        sithFX_g_aChalkMarks[markNum] = sithFX_CreateThingOnSurface(pTemplate, pPos, pAttSurf, pSector);
        if ( sithFX_g_aChalkMarks[markNum] )
        {
            ++sithFX_g_lastChalkMarkNum;
            if ( ++sithFX_g_numChalkMarks > STD_ARRAYLEN(sithFX_g_aChalkMarks) )
            {
                sithFX_g_numChalkMarks = STD_ARRAYLEN(sithFX_g_aChalkMarks);
            }
        }
    }
}

SithThing* J3DAPI sithFX_CreateThingOnSurface(const SithThing* pTemplate, const rdVector3* pPos, const SithSurface* pAttSurf, SithSector* pSector)
{
    SITH_ASSERTREL(pTemplate && pAttSurf && pSector);

    rdVector3 offset;
    rdVector_Scale3(&offset, &pAttSurf->face.normal, 0.001f);

    rdVector3 pos;
    rdVector_Add3(&pos, pPos, &offset);

    SithThing* pThing = sithThing_CreateThingAtPos(pTemplate, &pos, &pTemplate->orient, pSector, NULL);
    if ( !pThing )
    {
        return NULL;
    }

    //rdVector_Copy3(&pThing->pos, &pos); // ??
    rdVector_Copy3(&pThing->orient.lvec, &pAttSurf->face.normal);

    // Calculate rvec = lvec X zVector3
    rdVector_Cross3(&pThing->orient.rvec, &pThing->orient.lvec, &rdroid_g_zVector3);
    rdVector_Normalize3Acc(&pThing->orient.rvec);

    // Calculate uvec = rvec X lvec
    rdVector_Cross3(&pThing->orient.uvec, &pThing->orient.rvec, &pThing->orient.lvec);

    return pThing;
}

void J3DAPI sithFX_UpdatePolyline(SithThing* pThing)
{
    if ( pThing->renderData.type == RD_THING_POLYLINE && strcmp(pThing->aName, "+laserbeam") )
    {
        if ( strcmp(pThing->aName, "+lightning") == 0 )
        {
            rdPolyline* pPolyline = pThing->renderData.data.pPolyline;
            pPolyline->face.texVertOffset.y = (SITH_RANDF() - 0.69999999f) * 0.079999998f + pPolyline->face.texVertOffset.y;
            size_t numCels = pThing->renderData.data.pPolyline->face.pMaterial->numCels;
            if ( numCels > 1 && (((uint8_t)sithMain_g_frameNumber + (uint8_t)pThing->idx) & 3) == 0 )
            {
                pThing->renderData.data.pPolyline->face.matCelNum = (int32_t)(SITH_RAND() * (double)numCels);
            }
        }
        else if ( strcmp(pThing->aName, "+plcogend") == 0 )
        {
            rdVector3 look;
            rdVector_Sub3(&look, &pThing->pParent->pos, &pThing->pos);
            float lineLen = rdVector_Normalize3Acc(&look);

            rdMatrix_BuildFromLook34(&pThing->orient, &look);
            pThing->renderData.data.pPolyline->length = lineLen;
        }
        else if ( strcmp(pThing->aName, "+plcog") == 0 )
        {
            rdVector3 look;
            rdVector_Sub3(&look, &pThing->forceMoveStartPos, &pThing->pos);
            float lineLen = rdVector_Normalize3Acc(&look);

            rdMatrix_BuildFromLook34(&pThing->orient, &look);
            pThing->renderData.data.pPolyline->length = lineLen;
        }
    }
}

void J3DAPI sithFX_ResetPolylineTexVertOffset(SithThing* pThing)
{
    if ( pThing->renderData.type == RD_THING_POLYLINE )
    {
        pThing->renderData.data.pPolyline->face.texVertOffset.x = 0.0f;
        pThing->renderData.data.pPolyline->face.texVertOffset.y = 0.0f;
    }
}

SithThing* J3DAPI sithFX_CreateLaserThing(const SithThing* pSourceThing, const rdVector3* vecOffset, const rdVector3* vecEnd, float baseRadius, float tipRadius, float duration)
{
    SithThing* pThing = sithThing_Create(SITH_THING_POLYLINE);
    if ( !pThing )
    {
        SITHLOG_ERROR("Could not create sithThing for Laser\n");
        return NULL;
    }

    SithThing* pTemplate = sithTemplate_GetTemplate("+laserbeam");
    if ( !pTemplate )
    {
        // Maybe add log
        return NULL;
    }

    sithThing_SetThingBasedOn(pThing, pTemplate);
    pThing->userval = 0.0f;
    pThing->msecLifeLeft = (int32_t)(duration * 1000.0f);

    rdVector3 startPos;
    rdVector_Add3(&startPos, &pSourceThing->pos, vecOffset);

    rdVector3 look;
    rdVector_Sub3(&look, vecEnd, &startPos);
    float length = rdVector_Normalize3Acc(&look);
    rdMatrix_BuildFromLook34(&pThing->orient, &look);

    rdVector4 color = { .red= 1.0f, .green=0.40000001f, .blue=0.2f, .alpha=0.89999998f };
    rdPolyline* pPolyline = rdPolyline_New("+laserbeam", "gen_a4sfx_rbbeam_b.mat", "gen_a4sfx_rbbeam_b.mat", length, baseRadius, tipRadius, RD_GEOMETRY_FULL, RD_LIGHTING_GOURAUD, &color);
    if ( !pPolyline )
    {
        sithThing_RemoveThing(sithWorld_g_pCurrentWorld, pThing);
        SITHLOG_ERROR("Could not create polyline for laser.\n");
        return NULL;
    }

    rdThing_NewEntry(&pThing->renderData, NULL);
    rdThing_SetPolyline(&pThing->renderData, pPolyline);

    // Maybe should call sithFX_ResetPolylineTexVertOffset
    pThing->renderData.data.pPolyline->face.texVertOffset.x = 0.0f;
    pThing->renderData.data.pPolyline->face.texVertOffset.y = 0.0f;

    memset(&pThing->orient.dvec, 0, sizeof(pThing->orient.dvec)); // Reset orientation
    rdVector_Copy3(&pThing->pos, &startPos);
    sithThing_EnterSector(pThing, pSourceThing->pInSector, 1, 1);
    return pThing;
}

SithThing* J3DAPI sithFX_CreateLightningThing(const SithThing* pSourceThing, const rdVector3* offset, const rdVector3* endPos, float baseRadius, float tipRadius, float duration)
{
    SithThing* pThing = sithThing_Create(SITH_THING_POLYLINE);
    if ( !pThing )
    {
        SITHLOG_ERROR("Could not create sithThing for Lightning\n");
        return NULL;
    }

    SithThing* pTemplate = sithTemplate_GetTemplate("+lightning");
    if ( !pTemplate )
    {
        return NULL;
    }

    sithThing_SetThingBasedOn(pThing, pTemplate);

    pThing->flags |= SITH_TF_EMITLIGHT;
    pThing->light.color.red   = 0.0f;
    pThing->light.color.green = 0.0f;
    pThing->light.color.blue  = 0.89999998f;
    pThing->light.color.alpha = 1.0f;

    pThing->msecLifeLeft = (int32_t)(duration * 1000.0f);

    rdVector3 startPos;
    rdVector_Add3(&startPos, &pSourceThing->pos, offset);

    rdVector3 look;
    rdVector_Sub3(&look, endPos, &startPos);
    float length = rdVector_Normalize3Acc(&look);

    pThing->light.minRadius = length * 2.0f;
    pThing->light.maxRadius = pThing->light.minRadius;

    rdMatrix_BuildFromLook34(&pThing->orient, &look);

    rdVector4 color = { .red= 1.0f, .green=0.40000001f, .blue=0.2f, .alpha=0.89999998f };

    rdPolyline* pPolyline = rdPolyline_New("+lightning", "gen_a4sfx_lightning.mat", "gen_a4sfx_lightning.mat", length, baseRadius, tipRadius, RD_GEOMETRY_FULL, RD_LIGHTING_GOURAUD, &color);
    if ( !pPolyline )
    {
        sithThing_RemoveThing(sithWorld_g_pCurrentWorld, pThing);
        SITHLOG_ERROR("Could not create polyline for lightning.\n");
        return NULL;
    }

    rdThing_NewEntry(&pThing->renderData, NULL);
    rdThing_SetPolyline(&pThing->renderData, pPolyline);

    memset(&pThing->orient.dvec, 0, sizeof(pThing->orient.dvec)); // Reset orientation
    rdVector_Copy3(&pThing->pos, &startPos);
    sithThing_EnterSector(pThing, pSourceThing->pInSector, 1, 1);
    return pThing;
}

SithThing* J3DAPI sithFX_CreatePolylineThing(const SithThing* pSourceThing, SithThing* pEndThing, const rdVector3* pEndPos, const rdMaterial* pMaterial, float baseRadius, float tipRadius, float duration)
{
    SithThing* pThing = sithThing_Create(SITH_THING_POLYLINE);
    if ( !pThing )
    {
        SITHLOG_ERROR("Could not create sithThing for CreatePolylineThing\n");
        return NULL;
    }

    if ( !pMaterial )
    {
        SITHLOG_ERROR("NULL Material pointer passed to CreatePolylineThing\n");
        sithThing_RemoveThing(sithWorld_g_pCurrentWorld, pThing);
        return NULL;
    }

    rdVector3 endPos;
    if ( pEndThing )
    {
        SithThing* pTemplate = sithTemplate_GetTemplate("+plcogend");
        if ( !pTemplate )
        {
            return NULL;
        }

        sithThing_SetThingBasedOn(pThing, pTemplate);
        rdVector_Copy3(&endPos, &pEndThing->pos);
        pThing->pParent = pEndThing;
    }
    else
    {
        SithThing* pTemplate = sithTemplate_GetTemplate("+plcog");
        if ( !pTemplate )
        {
            return NULL;
        }

        sithThing_SetThingBasedOn(pThing, pTemplate);
        rdVector_Copy3(&endPos, pEndPos);
        rdVector_Copy3(&pThing->forceMoveStartPos, &endPos);
    }

    if ( duration > 0.0f )
    {
        pThing->msecLifeLeft = (int32_t)(duration * 1000.0f);
    }

    rdVector3 startPos;
    rdVector_Copy3(&startPos, &pSourceThing->pos);

    rdVector3 look;
    rdVector_Sub3(&look, &endPos, &startPos);
    float length = rdVector_Normalize3Acc(&look);
    rdMatrix_BuildFromLook34(&pThing->orient, &look);

    rdVector4 color = { .red=0.1f, .green=0.1f, .blue=0.1f, .alpha=1.0f };

    rdPolyline* pPolyline = rdPolyline_New(pThing->aName, pMaterial->aName, pMaterial->aName, length, baseRadius, tipRadius, RD_GEOMETRY_FULL, RD_LIGHTING_GOURAUD, &color);
    if ( !pPolyline )
    {
        sithThing_RemoveThing(sithWorld_g_pCurrentWorld, pThing);
        SITHLOG_ERROR("Could not create polyline for CreatePolylineThing.\n");
        return NULL;
    }

    rdThing_NewEntry(&pThing->renderData, NULL);
    rdThing_SetPolyline(&pThing->renderData, pPolyline);

    memset(&pThing->orient.dvec, 0, sizeof(pThing->orient.dvec)); // Reset orientation
    rdVector_Copy3(&pThing->pos, &startPos);
    sithThing_EnterSector(pThing, pSourceThing->pInSector, 1, 1);

    pThing->alpha = 1.0f;
    return pThing;
}
