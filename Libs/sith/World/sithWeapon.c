#include "sithWeapon.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#include <rdroid/Math/rdMatrix.h>
#include <rdroid/Math/rdVector.h>

#include <sith/AI/sithAI.h>
#include <sith/AI/sithAIAwareness.h>
#include <sith/AI/sithAIUtil.h>
#include <sith/Cog/sithCog.h>
#include <sith/Devices/sithComm.h>
#include <sith/Devices/sithConsole.h>
#include <sith/Devices/sithControl.h>
#include <sith/Devices/sithSound.h>
#include <sith/Devices/sithSoundMixer.h>
#include <sith/Dss/sithDSSThing.h>
#include <sith/Engine/sithAnimate.h>
#include <sith/Engine/sithCamera.h>
#include <sith/Engine/sithCollision.h>
#include <sith/Engine/sithPhysics.h>
#include <sith/Engine/sithPuppet.h>
#include <sith/Gameplay/sithInventory.h>
#include <sith/Gameplay/sithPlayer.h>
#include <sith/Gameplay/sithPlayerActions.h>
#include <sith/Gameplay/sithPlayerControls.h>
#include <sith/Gameplay/sithTime.h>
#include <sith/Gameplay/sithWhip.h>
#include <sith/World/sithMaterial.h>
#include <sith/World/sithModel.h>
#include <sith/World/sithSector.h>
#include <sith/World/sithSoundClass.h>
#include <sith/World/sithSurface.h>
#include <sith/World/sithTemplate.h>
#include <sith/World/sithThing.h>
#include <sith/World/sithWorld.h>

#include <std/General/stdMath.h>
#include <std/General/stdUtil.h>
#include <std/Win95/stdComm.h>

#define SITHWEAPON_MAX_PROJECTILE_RICOCHETS 6

static bool sithWeapon_bGenBloodsplort = true;

static const float sithWeapon_aMaxAimDistances[25] = { // up to SITHWEAPON_COMSHOTGUN
    0.0f, 0.0f, 0.0f, 1.0f, 1.5f, 1.5f, 2.5f, 0.0f, 1.5f, 1.0f,
    3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    1.5f, 1.5f, 2.5f, 1.5f, 1.0f
};

static SithWeaponId sithWeapon_lastPlayerWeaponID;

static int sithWeapon_bPlayerWeaponActivated;
static int sithWeapon_bLocalPlayerAiming;

static int sithWeapon_deactivatedPlayerWeaponID;

static float sithWeapon_secMountWait;
static float sithWeapon_secWeaponActivationWaitEndTime;
static float sithWeapon_secPlayerWeaponDeactivationTime;

static int sithWeapon_playerWhipHolsterSwapRefNum;
static int sithWeapon_playerPistolHolsterSwapRefNum;
static int sithWeapon_playerBackHolsterSwapRefNum;


static SithControlFunction sithWeapon_bufferedWaponKeyId;
static SithWeaponActorKilledCallback sithWeapon_pfActorKilledCallback;

void J3DAPI sithWeapon_HandleImpact(SithThing* pWeapon);
int sithWeapon_IsLocalPlayerUnableToUseWeapon(void);

void sithWeapon_InstallHooks(void)
{
    J3D_HOOKFUNC(sithWeapon_Open);
    J3D_HOOKFUNC(sithWeapon_InitalizeActor);
    J3D_HOOKFUNC(sithWeapon_UpdateActorWeaponState);
    J3D_HOOKFUNC(sithWeapon_Update);
    J3D_HOOKFUNC(sithWeapon_SelectWeapon);
    J3D_HOOKFUNC(sithWeapon_HandleImpact);
    J3D_HOOKFUNC(sithWeapon_ParseArg);
    J3D_HOOKFUNC(sithWeapon_WeaponFire);
    J3D_HOOKFUNC(sithWeapon_WeaponFireProjectile);
    J3D_HOOKFUNC(sithWeapon_DamageWeapon);
    J3D_HOOKFUNC(sithWeapon_ThingCollisionHandler);
    J3D_HOOKFUNC(sithWeapon_SurfaceCollisionHandler);
    J3D_HOOKFUNC(sithWeapon_DestroyWeapon);
    J3D_HOOKFUNC(sithWeapon_CreateWeaponExplosion);
    J3D_HOOKFUNC(sithWeapon_GetMountWait);
    J3D_HOOKFUNC(sithWeapon_SetMountWait);
    J3D_HOOKFUNC(sithWeapon_SetFireWait);
    J3D_HOOKFUNC(sithWeapon_SetAimWait);
    J3D_HOOKFUNC(sithWeapon_ActivateWeapon);
    J3D_HOOKFUNC(sithWeapon_DeactivateWeapon);
    J3D_HOOKFUNC(sithWeapon_ProcessWeaponControls);
    J3D_HOOKFUNC(sithWeapon_DeselectWeapon);
    J3D_HOOKFUNC(sithWeapon_IsMountingWeapon);
    J3D_HOOKFUNC(sithWeapon_HasWeaponSelected);
    J3D_HOOKFUNC(sithWeapon_GetAimOrient);
    J3D_HOOKFUNC(sithWeapon_FireProjectile);
    J3D_HOOKFUNC(sithWeapon_DeactivateCurrentWeapon);
    J3D_HOOKFUNC(sithWeapon_SelectNextWeapon);
    J3D_HOOKFUNC(sithWeapon_SelectPreviousWeapon);
    J3D_HOOKFUNC(sithWeapon_SetWeaponModel);
    J3D_HOOKFUNC(sithWeapon_ResetWeaponModel);
    J3D_HOOKFUNC(sithWeapon_SetHolsterModel);
    J3D_HOOKFUNC(sithWeapon_ResetHolsterModel);
    J3D_HOOKFUNC(sithWeapon_SendMessageAim);
    J3D_HOOKFUNC(sithWeapon_SetActorKilledCallback);
    J3D_HOOKFUNC(sithWeapon_IsAiming);
    J3D_HOOKFUNC(sithWeapon_GenBloodsplort);
    J3D_HOOKFUNC(sithWeapon_GetLastWeapon);
    J3D_HOOKFUNC(sithWeapon_SetLastWeapon);
    J3D_HOOKFUNC(sithWeapon_GetWeaponMaxAimDistance);
    J3D_HOOKFUNC(sithWeapon_GetWeaponCollideSize);
    J3D_HOOKFUNC(sithWeapon_IsLocalPlayerUnableToUseWeapon);
    J3D_HOOKFUNC(sithWeapon_Save);
    J3D_HOOKFUNC(sithWeapon_Restore);
    J3D_HOOKFUNC(sithWeapon_GetWeaponForControlKey);
    J3D_HOOKFUNC(sithWeapon_FireProjectileEx);
    J3D_HOOKFUNC(sithWeapon_CreateWeaponFireFx);
    J3D_HOOKFUNC(sithWeapon_ActivateWhip);
}

void sithWeapon_ResetGlobals(void)
{}

void sithWeapon_Open(void)
{
    sithWeapon_secWeaponActivationWaitEndTime = 0.0f;
}

void sithWeapon_Close(void)
{}

void J3DAPI sithWeapon_InitalizeActor(SithThing* pThing)
{
    SITH_ASSERTREL((pThing->type == SITH_THING_ACTOR) || (pThing->type == SITH_THING_PLAYER));

    pThing->thingInfo.actorInfo.secWeaponActivationStartTime   = -1.0f;
    pThing->thingInfo.actorInfo.secTimeLastRapidFired          = -1.0f;
    pThing->thingInfo.actorInfo.secWeaponActivationWaitEndTime = -1.0f;
    pThing->thingInfo.actorInfo.secWeaponActivationWaitTime    = -1.0f;
    pThing->thingInfo.actorInfo.secAimWaitEndTime              = 0.0f;
    pThing->thingInfo.actorInfo.secWeaponSwapTime              = -1.0f;
    pThing->thingInfo.actorInfo.selectedWeaponID               = -1;
    pThing->thingInfo.actorInfo.curWeaponID                    = 0;
    pThing->thingInfo.actorInfo.deselectedWeaponID             = -1;
    pThing->thingInfo.actorInfo.weaponSwapRefNum               = -1;

    rdVector_Set3(&pThing->thingInfo.actorInfo.vecUnknown0, 0, 0, 0);

    sithWeapon_secWeaponActivationWaitEndTime = 0.0f;

    if ( pThing->type == SITH_THING_PLAYER )
    {
        sithWeapon_lastPlayerWeaponID              = SITHWEAPON_PISTOL;
        sithWeapon_bufferedWaponKeyId              = -1;
        sithWeapon_deactivatedPlayerWeaponID       = -1;
        sithWeapon_playerWhipHolsterSwapRefNum     = -1;
        sithWeapon_playerPistolHolsterSwapRefNum   = -1;
        sithWeapon_playerBackHolsterSwapRefNum     = -1;
        sithWeapon_secMountWait                    = 0.0f;
        sithWeapon_secPlayerWeaponDeactivationTime = 0.0f;
        sithWeapon_bPlayerWeaponActivated          = 0;
        sithWeapon_bLocalPlayerAiming              = 0;
    }
}

void J3DAPI sithWeapon_UpdateActorWeaponState(SithThing* pThing)
{
    if ( pThing->thingInfo.actorInfo.secWeaponSwapTime > 0.0f && sithTime_g_secGameTime >= (double)pThing->thingInfo.actorInfo.secWeaponSwapTime )
    {
        pThing->thingInfo.actorInfo.secWeaponSwapTime = -1.0f;
        sithWeapon_SetWeaponModel(pThing, (SithWeaponId)pThing->thingInfo.actorInfo.curWeaponID);
    }

    if ( sithWeapon_deactivatedPlayerWeaponID == -1 || pThing->type != SITH_THING_PLAYER )
    {
        if ( pThing->type == SITH_THING_PLAYER && sithWeapon_IsLocalPlayerUnableToUseWeapon() )
        {
            if ( sithWeapon_bPlayerWeaponActivated == 1 )
            {
                sithWeapon_bPlayerWeaponActivated    = 0;
                sithWeapon_deactivatedPlayerWeaponID = pThing->thingInfo.actorInfo.curWeaponID;
                sithWeapon_secPlayerWeaponDeactivationTime = sithTime_g_secGameTime;
            }
        }
        else if ( pThing->thingInfo.actorInfo.deselectedWeaponID == -1 )
        {
            if ( pThing->thingInfo.actorInfo.selectedWeaponID == -1 )
            {
                if ( pThing->thingInfo.actorInfo.secWeaponActivationWaitTime <= 0.0f )
                {
                    if ( pThing->type == SITH_THING_PLAYER && pThing->thingInfo.actorInfo.curWeaponID == SITHWEAPON_WHIP )
                    {
                        if ( (pThing->attach.flags & SITH_ATTACH_SURFACE) != 0
                            && (pThing->attach.attachedToStructure.pSurfaceAttached->flags & SITH_SURFACE_WHIPAIM) != 0
                            || (pThing->attach.flags & SITH_ATTACH_THINGFACE) != 0 && (pThing->attach.pFace->flags & RD_FF_3DO_WHIP_AIM) != 0 )
                        {
                            sithWhip_UpdateWhipAim(pThing);
                        }
                        else if ( sithWeapon_bLocalPlayerAiming )
                        {
                            sithWeapon_SendMessageAim(pThing, 0);
                        }
                    }
                }
                else if ( sithTime_g_secGameTime >= (double)pThing->thingInfo.actorInfo.secWeaponActivationWaitEndTime )
                {
                    SithInventoryType* pItem = sithInventory_GetType(pThing->thingInfo.actorInfo.curWeaponID);
                    if ( pItem->pCog )
                    {
                        sithCog_SendMessage(pItem->pCog, SITHCOG_MSG_FIRE, SITHCOG_SYM_REF_NONE, 0, SITHCOG_SYM_REF_THING, pThing->idx, 0);
                        pThing->thingInfo.actorInfo.secWeaponActivationWaitEndTime = sithTime_g_secGameTime
                            + pThing->thingInfo.actorInfo.secWeaponActivationWaitTime;
                    }

                    if ( pThing->type == SITH_THING_PLAYER && sithWeapon_bPlayerWeaponActivated != 1 )
                    {
                        sithWeapon_bPlayerWeaponActivated = 1;
                        sithWeapon_DeactivateCurrentWeapon(pThing);
                    }
                }
            }
            else if ( (pThing->type != SITH_THING_PLAYER || sithTime_g_secGameTime >= (double)sithWeapon_secMountWait)
                && sithTime_g_secGameTime >= (double)pThing->thingInfo.actorInfo.secAimWaitEndTime )
            {
                SithInventoryType* pItem = sithInventory_GetType(pThing->thingInfo.actorInfo.selectedWeaponID);
                if ( (pItem->flags & SITHINVENTORY_TYPE_WEAPON) != 0 && pItem->pCog )
                {
                    pThing->thingInfo.actorInfo.secTimeLastRapidFired = -1.0f;
                    sithCog_SendMessage(pItem->pCog, SITHCOG_MSG_SELECTED, SITHCOG_SYM_REF_NONE, 0, SITHCOG_SYM_REF_THING, pThing->idx, 0);
                }

                if ( pThing->type == SITH_THING_PLAYER )
                {
                    sithInventory_SetCurrentWeapon(pThing, (SithWeaponId)pThing->thingInfo.actorInfo.selectedWeaponID);
                }

                pThing->thingInfo.actorInfo.curWeaponID = pThing->thingInfo.actorInfo.selectedWeaponID;
                pThing->thingInfo.actorInfo.selectedWeaponID = -1;
            }
        }
        else if ( sithTime_g_secGameTime >= (double)pThing->thingInfo.actorInfo.secAimWaitEndTime )
        {
            if ( pThing->type == SITH_THING_PLAYER && sithWeapon_bPlayerWeaponActivated == 1 )
            {
                sithWeapon_DeactivateCurrentWeapon(pThing);
            }
            else
            {
                SithInventoryType* pItem = sithInventory_GetType(pThing->thingInfo.actorInfo.deselectedWeaponID);
                if ( pItem->pCog )
                {
                    sithCog_SendMessage(pItem->pCog, SITHCOG_MSG_DESELECTED, SITHCOG_SYM_REF_INT, pThing->thingInfo.actorInfo.selectedWeaponID, SITHCOG_SYM_REF_THING, pThing->idx, 0);
                }

                if ( pThing->type == SITH_THING_PLAYER )
                {
                    sithWeapon_bLocalPlayerAiming = 0;
                    sithInventory_SetCurrentWeapon(pThing, SITHWEAPON_NO_WEAPON);
                    if ( (pItem->flags & SITHINVENTORY_TYPE_PLAYERWEAPON) != 0 )
                    {
                        sithWeapon_lastPlayerWeaponID = pThing->thingInfo.actorInfo.deselectedWeaponID;
                    }
                }

                pThing->thingInfo.actorInfo.curWeaponID        = SITHWEAPON_NO_WEAPON;
                pThing->thingInfo.actorInfo.deselectedWeaponID = -1;
            }
        }
    }
    else if ( sithTime_g_secGameTime >= (double)sithWeapon_secPlayerWeaponDeactivationTime )
    {
        SithInventoryType* pItem = sithInventory_GetType(pThing->thingInfo.actorInfo.curWeaponID);
        if ( pItem->pCog )
        {
            sithCog_SendMessage(pItem->pCog, SITHCOG_MSG_DEACTIVATED, SITHCOG_SYM_REF_NONE, 0, SITHCOG_SYM_REF_THING, pThing->idx, 0);
        }

        sithWeapon_deactivatedPlayerWeaponID = -1;
    }
}

void J3DAPI sithWeapon_Update(SithThing* pThing, float secDeltaTime)
{
    SITH_ASSERTREL(pThing);

    if ( (pThing->thingInfo.weaponInfo.flags & SITH_WF_INSTANTIMPACT) != 0 )
    {
        sithWeapon_HandleImpact(pThing);
        return;
    }

    if ( (pThing->thingInfo.weaponInfo.flags & SITH_WF_DAMAGEDECAY) != 0 && pThing->thingInfo.weaponInfo.damage > pThing->thingInfo.weaponInfo.minDamage )
    {
        pThing->thingInfo.weaponInfo.damage -= pThing->thingInfo.weaponInfo.rate * secDeltaTime;
        if ( pThing->thingInfo.weaponInfo.damage < pThing->thingInfo.weaponInfo.minDamage ) {
            pThing->thingInfo.weaponInfo.damage = pThing->thingInfo.weaponInfo.minDamage;
        }
    }

    if ( (pThing->thingInfo.weaponInfo.flags & SITH_WF_DECAYEMITSOUNDAWARENESSEVENT) != 0 && (((uint8_t)sithMain_g_frameNumber + (uint8_t)pThing->idx) & 7) == 0 )
    {
        sithAIAwareness_CreateTransmittingEvent(pThing->pInSector, &pThing->pos, 2, 0.5f, pThing);
    }
}

int J3DAPI sithWeapon_SelectWeapon(SithThing* pThing, SithWeaponId typeId)
{
    SITH_ASSERTREL(pThing && ((pThing->type == SITH_THING_PLAYER) || (pThing->type == SITH_THING_ACTOR))); // Fixed: Move to begining of the scope

    if ( pThing->type == SITH_THING_PLAYER )
    {
        pThing->thingInfo.actorInfo.curWeaponID = sithInventory_GetCurrentWeapon(pThing);
    }

    if ( typeId == pThing->thingInfo.actorInfo.curWeaponID || pThing->thingInfo.actorInfo.selectedWeaponID != -1 )
    {
        return 0;
    }

    bool bHasWeapon = true;
    if ( pThing->type == SITH_THING_PLAYER )
    {
        bHasWeapon = sithInventory_GetInventory(pThing, typeId) != 0.0f && sithInventory_IsInventoryAvailable(pThing, typeId);
    }
    else
    {
        bHasWeapon = true;
        sithPlayerControls_CenterActorOrientation(pThing);
    }

    if ( !bHasWeapon )
    {
        return 0;
    }

    if ( pThing->thingInfo.actorInfo.secWeaponActivationStartTime != -1.0f && pThing->type == SITH_THING_PLAYER )
    {
        sithWeapon_deactivatedPlayerWeaponID = pThing->thingInfo.actorInfo.curWeaponID;
        sithWeapon_secPlayerWeaponDeactivationTime = pThing->thingInfo.actorInfo.secWeaponActivationWaitEndTime;
    }

    pThing->thingInfo.actorInfo.deselectedWeaponID = pThing->thingInfo.actorInfo.curWeaponID;
    pThing->thingInfo.actorInfo.selectedWeaponID   = typeId;
    return 1;
}

void J3DAPI sithWeapon_HandleImpact(SithThing* pWeapon)
{
    SithWeaponInfo* pWeaponInfo = &pWeapon->thingInfo.weaponInfo;
    float damage = pWeapon->thingInfo.actorInfo.maxHealth;

    int searchFlags = 0;
    if ( (pWeapon->thingInfo.weaponInfo.damageType & SITH_DAMAGE_MACHETE) != 0 )
    {
        searchFlags = 0x200;
    }

    rdVector3 moveNorm;
    rdVector_Copy3(&moveNorm, &pWeapon->orient.lvec);
    sithCollision_SearchForCollisions(pWeapon->pInSector, pWeapon, &pWeapon->pos, &moveNorm, pWeaponInfo->range, pWeapon->collide.movesize, searchFlags);

    while ( 1 )
    {
        SithCollision* pCollision = sithCollision_PopStack();
        if ( !pCollision )
        {
            break;
        }

        if ( (pWeaponInfo->flags & SITH_WF_DAMAGEDECAY) != 0 )
        {
            damage -= pWeaponInfo->rate * pCollision->distance;
            if ( damage < pWeaponInfo->minDamage ) {
                damage = pWeaponInfo->minDamage;
            }
        }

        if ( (pCollision->type & SITHCOLLISION_THING) != 0 )
        {
            SithThing* pVictim = pCollision->pThingCollided;
            sithThing_DamageThing(pVictim, pWeapon, damage, pWeaponInfo->damageType);

            if ( pVictim->type == SITH_THING_ACTOR )
            {
                // Call actor killed cb if actor is killed
                if ( sithThing_GetThingParent(pWeapon) == sithPlayer_g_pLocalPlayerThing
                    && sithWeapon_pfActorKilledCallback
                    && pVictim->thingInfo.actorInfo.health == 0.0f )
                {
                    sithWeapon_pfActorKilledCallback(sithGetGameDifficulty());
                }

                // Generate bloodsplort anf destroy projectile or explode projectile
                if ( pVictim->thingInfo.actorInfo.health == 0.0f
                    && (pWeaponInfo->flags & SITH_WF_ACTORKILLDESTROY) != 0
                    && (pVictim->thingInfo.actorInfo.flags & SITH_AF_DROID) == 0
                    && pVictim->type != SITH_THING_PLAYER
                    && sithWeapon_bGenBloodsplort )
                {
                    sithWeapon_GenBloodsplort(pVictim);
                    sithThing_DestroyThing(pWeapon);
                }
                else {
                    sithWeapon_CreateWeaponExplosion(pWeapon, pWeaponInfo->pExplosionTemplate, NULL, /*bRotate=*/0);
                }
            }
            else {
                sithWeapon_CreateWeaponExplosion(pWeapon, pWeaponInfo->pExplosionTemplate, NULL, /*bRotate=*/0);
            }

            if ( pWeaponInfo->force != 0.0f && pVictim->moveType == SITH_MT_PHYSICS )
            {
                rdVector3 force;
                rdVector_Scale3(&force, &moveNorm, pWeaponInfo->force);
                /* force.x = pInfo->weaponInfo.force * moveNorm.x;
                 force.y   = pInfo->weaponInfo.force * moveNorm.y;
                 force.z   = pInfo->weaponInfo.force * moveNorm.z;*/
                sithPhysics_ApplyForce(pVictim, &force);
            }

            break;
        }

        if ( (pCollision->type & SITHCOLLISION_ADJOINCROSS) != 0 )
        {
            sithWeapon_CreateWeaponExplosion(pWeapon, pWeaponInfo->pExplosionTemplate, NULL, /*bRotate=*/0);
            sithSurface_HandleThingImpact(pCollision->pSurfaceCollided, pWeapon, damage, pWeaponInfo->damageType);
            break;
        }
    }

    sithCollision_DecreaseStackLevel();

    if ( (pWeapon->flags & SITH_TF_COGLINKED) != 0 && (pWeapon->flags & SITH_TF_REMOTE) == 0 )
    {
        sithCog_ThingSendMessage(pWeapon, NULL, SITHCOG_MSG_REMOVED);
    }

    sithThing_RemoveThing(sithWorld_g_pCurrentWorld, pWeapon);
}

int J3DAPI sithWeapon_ParseArg(StdConffileArg* pArg, SithThing* pThing, int adjNum)
{
    switch ( adjNum )
    {
        case SITHTHING_ARG_TYPEFLAGS:
        {
            if ( sscanf_s(pArg->argValue, "%x", &pThing->thingInfo.weaponInfo.flags) != 1 ) {
                goto syntax_error;
            }
            return 1;
        }
        case SITHTHING_ARG_DAMAGE:
        {
            float damage = strtof(pArg->argValue, NULL); // Changed: Use strtof instead atof
            if ( errno == ERANGE ) { // Added
                goto syntax_error;
            }
            pThing->thingInfo.weaponInfo.damage = damage;
            return 1;
        }
        case SITHTHING_ARG_MINDAMAGE:
        {
            float minDamage = strtof(pArg->argValue, NULL); // Changed: Use strtof instead atof
            if ( errno == ERANGE ) { // Added
                goto syntax_error;
            }
            pThing->thingInfo.weaponInfo.minDamage = minDamage;
            return 1;
        }
        case SITHTHING_ARG_DAMAGECLASS:
        {
            if ( sscanf_s(pArg->argValue, "%x", &pThing->thingInfo.weaponInfo.damageType) != 1 ) {
                goto syntax_error;
            }
            return 1;
        }
        case SITHTHING_ARG_EXPLODE:
        {
            pThing->thingInfo.weaponInfo.pExplosionTemplate = sithTemplate_GetTemplate(pArg->argValue);
            return 1;
        }
        case SITHTHING_ARG_FORCE:
        {
            float force = strtof(pArg->argValue, NULL); // Changed: Use strtof instead atof
            if ( errno == ERANGE ) { // Added
                goto syntax_error;
            }
            pThing->thingInfo.weaponInfo.force = force;
            return 1;
        }
        case SITHTHING_ARG_RANGE:
        {
            float range = strtof(pArg->argValue, NULL); // Changed: Use strtof instead atof
            if ( errno == ERANGE ) { // Added
                goto syntax_error;
            }
            pThing->thingInfo.weaponInfo.range = range;
            return 1;
        }
        case SITHTHING_ARG_RATE:
        {
            float rate = strtof(pArg->argValue, NULL); // Changed: Use strtof instead atof
            if ( errno == ERANGE ) { // Added
                goto syntax_error;
            }
            pThing->thingInfo.weaponInfo.rate = rate;
            return 1;
        }
        default:
            return 0;
    }

syntax_error:
    SITHLOG_ERROR("Bad argument pair %s=%s line %d.  Skipped.\n", pArg->argName, pArg->argValue, stdConffile_GetLineNumber());
    return 1;
}

SithThing* J3DAPI sithWeapon_WeaponFire(SithThing* pShooter, const SithThing* pProjectileTemplate, const rdVector3* pFireDir, rdVector3* pFirePos, tSoundHandle hFireSnd, SithPuppetSubMode submode, float extra, SithFireProjectileFlags projectileFlags, float secDeltaTime)
{
    SITH_ASSERTREL(pShooter);

    if ( hFireSnd )
    {
        sithAIAwareness_CreateTransmittingEvent(pShooter->pInSector, &pShooter->pos, 0, 3.0f, pShooter);
    }

    if ( pShooter->type == SITH_THING_PLAYER && (pProjectileTemplate->thingInfo.weaponInfo.damageType & (SITH_DAMAGE_ELECTROWHIP | SITH_DAMAGE_WHIP | SITH_DAMAGE_MACHETE | SITH_DAMAGE_FISTS)) == 0 )// 0x838 - SITH_DAMAGE_ELECTROWHIP | SITH_DAMAGE_WHIP | SITH_DAMAGE_MACHETE | SITH_DAMAGE_FISTS
    {
        sithAIAwareness_CreateTransmittingEvent(pShooter->pInSector, &pShooter->pos, 3, 1.5f, pShooter);
    }

    SithThing* pProjectile = sithWeapon_WeaponFireProjectile(pShooter, pProjectileTemplate, pFireDir, pFirePos, hFireSnd, submode, extra, projectileFlags, secDeltaTime);
    if ( pProjectile && sithMessage_g_outputstream )
    {
        sithDSSThing_Fire(pShooter, pProjectileTemplate, pFireDir, pFirePos, hFireSnd, submode, extra, projectileFlags, secDeltaTime, pProjectile->guid, SITHMESSAGE_SENDTOALL, 0xFFu);
    }

    return pProjectile;
}

SithThing* J3DAPI sithWeapon_WeaponFireProjectile(SithThing* pShooter, const SithThing* pProjectileTemplate, const rdVector3* pFireDir, rdVector3* pFirePos, tSoundHandle hFireSnd, SithPuppetSubMode submode, float extra, SithFireProjectileFlags flags, float secDeltaTime)
{
    if ( !pShooter || !pFireDir )
    {
        SITHLOG_ERROR("Bad arguments passed.\n");
        return NULL;
    }

    SithThing* pProjectile = NULL;
    if ( pProjectileTemplate )
    {
        rdMatrix34 projectileOrient;
        rdMatrix_BuildFromLook34(&projectileOrient, pFireDir);

        if ( (pShooter->thingInfo.actorInfo.fireOffset.x != 0.0f
            || pShooter->thingInfo.actorInfo.fireOffset.y != 0.0f
            || pShooter->thingInfo.actorInfo.fireOffset.z != 0.0f)
            && pShooter->controlType != SITH_CT_AI )
        {
            rdVector3 fireOffset;
            rdVector_Copy3(&fireOffset, &pShooter->thingInfo.actorInfo.fireOffset);
            if ( ((uint8_t)flags & (uint8_t)SITHFIREPROJECTILE_RIGHTHAND_FIRE) != 0 )
            {
                int jointIdx = sithThing_GetThingJointIndex(pShooter, "inrhand");
                if ( jointIdx != -1 )
                {
                    rdMatrix_TransformVector34Acc(&fireOffset, &pShooter->renderData.paJointMatrices[jointIdx]);
                }
            }

            else if ( (flags & SITHFIREPROJECTILE_TORSO_FIRE) != 0 )
            {
                int jointIdx = sithThing_GetThingJointIndex(pShooter, "intorso");
                if ( jointIdx != -1 )
                {
                    rdMatrix_TransformVector34Acc(&fireOffset, &pShooter->renderData.paJointMatrices[jointIdx]);
                }
            }
            else
            {
                rdMatrix_TransformVector34Acc(&fireOffset, &pShooter->orient);
            }

            rdVector_Add3Acc(pFirePos, &fireOffset);
            /*pFirePos->x = pFirePos->x + fireOffset.x;
            pFirePos->y = pFirePos->y + fireOffset.y;
            pFirePos->z = pFirePos->z + fireOffset.z;*/
        }

        rdVector3 offsetPos;
        rdVector_Copy3(&offsetPos, &pShooter->pos);

        // Find offset sector
        rdVector3 shooterOffset;
        shooterOffset.x = 0.022f;
        shooterOffset.y = 0.0f;
        shooterOffset.z = 0.050000001f;
        rdMatrix_TransformVector34Acc(&shooterOffset, &pShooter->orient);

        rdVector_Add3Acc(&offsetPos, &shooterOffset);
        /*offsetPos.x = offsetPos.x + shooterOffset.x;
        offsetPos.y = offsetPos.y + shooterOffset.y;
        offsetPos.z = offsetPos.z + shooterOffset.z;*/

        SithSector* pSector = sithCollision_FindSectorInRadius(pShooter->pInSector, &pShooter->pos, &offsetPos, 0.0f);
        if ( !pSector )
        {
            SITHLOG_ERROR("Uh-oh.  Failed to find offset sector.  Weapon fire failed.\n");
            return NULL;
        }

        // Find Fire point sector
        pSector = sithCollision_FindSectorAtThing(pShooter, pSector, &offsetPos, pFirePos, 0.0f);
        if ( !pSector )
        {
            SITHLOG_ERROR("Uh-oh.  Failed to find fire point sector.  Weapon fire failed.\n");
            return NULL;
        }

        pProjectile = sithThing_CreateThingAtPos(pProjectileTemplate, pFirePos, &projectileOrient, pSector, pShooter);
        if ( !pProjectile )
        {
            return NULL;
        }

        if ( pProjectileTemplate->pCog )
        {
            sithCog_SendMessage(pProjectileTemplate->pCog, SITHCOG_MSG_FIRE, SITHCOG_SYM_REF_THING, pProjectile->idx, SITHCOG_SYM_REF_THING, pShooter->idx, 0);
        }

        if ( (flags & SITHFIREPROJECTILE_SCALE_VELOCITY) != 0 )
        {
            pProjectile->moveInfo.physics.velocity.x = pProjectile->moveInfo.physics.velocity.x * extra;
            pProjectile->moveInfo.physics.velocity.y = pProjectile->moveInfo.physics.velocity.y * extra;
            pProjectile->moveInfo.physics.velocity.z = pProjectile->moveInfo.physics.velocity.z * extra;
        }

        if ( (flags & SITHFIREPROJECTILE_SCALE_DAMAGE) != 0 )
        {
            pProjectile->thingInfo.weaponInfo.damage = pProjectile->thingInfo.weaponInfo.damage * extra;
        }

        if ( (flags & SITHFIREPROJECTILE_UNKNOWN_4) != 0 )
        {
            pProjectile->thingInfo.weaponInfo.unknown8 = pProjectile->thingInfo.weaponInfo.unknown8 * extra;
        }

        if ( (flags & SITHFIREPROJECTILE_UNKNOWN_8) != 0 )
        {
            pProjectile->thingInfo.weaponInfo.unknown7 = pProjectile->thingInfo.weaponInfo.unknown7 * extra;
        }

        rdVector3 moveNorm;
        if ( secDeltaTime > 0.02f )
        {
            sithPhysics_UpdateThing(pProjectile, secDeltaTime);
            float moveDist = rdVector_Normalize3(&moveNorm, &pProjectile->moveInfo.physics.deltaVelocity);
            if ( moveDist > 0.0f )
            {
                sithCollision_MoveThing(pProjectile, &moveNorm, moveDist, pProjectile->moveInfo.physics.flags);// // TODO: [BUG] Using physics.flags here is probably wrong???
            }
        }

        // Now search for projectile target
        float speed = rdVector_Normalize3(&moveNorm, &pProjectile->moveInfo.physics.velocity);
        float moveDist = J3DMIN(speed * 3.0f, 5.0f);
        //if ( speed * 3.0f >= 5.0f )
        //{
        //    v12 = 5.0f;
        //}
        //else
        //{
        //    v12 = v19 * 3.0f;
        //}

        //moveDist = v12;

        sithCollision_SearchForCollisions(pProjectile->pInSector, pProjectile, &pProjectile->pos, &moveNorm, moveDist, pProjectile->collide.movesize, 2);
        SithCollision* pCollision = sithCollision_PopStack();
        sithCollision_DecreaseStackLevel();

        if ( pCollision && (pCollision->type & SITHCOLLISION_THING) != 0 )
        {
            if ( !stdComm_IsGameActive()
                && pShooter == sithPlayer_g_pLocalPlayerThing
                && (pProjectile->thingInfo.weaponInfo.flags & SITH_WF_EMITAITARGETEDEVENT) != 0
                && pCollision->pThingCollided->controlType == SITH_CT_AI )
            {
                sithAI_EmitEvent(pCollision->pThingCollided->controlInfo.aiControl.pLocal, SITHAI_EVENT_TARGETED, pProjectile);
            }
        }
        else
        {
            sithCog_ThingSendMessageEx(pShooter, NULL, SITHCOG_MSG_MISSED, (int32_t)pProjectile->thingInfo.weaponInfo.damage, pProjectile->thingInfo.weaponInfo.damageType, 0, 0);
        }
    }

    if ( (flags & SITHFIREPROJECTILE_FIRE_EFFECT) != 0 )
    {
        sithWeapon_CreateWeaponFireFx(pShooter, pFirePos);
    }

    if ( hFireSnd )
    {
        sithSoundMixer_PlaySoundThing(hFireSnd, pShooter, 1.0f, 1.0f, 10.0f, SOUNDPLAY_HIGH_PRIORITY | SOUNDPLAY_THING_POS);
    }

    if ( submode <= 0 )
    {
        return pProjectile;
    }

    if ( pShooter->pPuppetClass )
    {
        sithPuppet_PlayMode(pShooter, submode, NULL);
    }

    return pProjectile;
}

void J3DAPI sithWeapon_DamageWeapon(SithThing* pThing, const SithThing* pPurpetrator, float damage)
{
    J3D_UNUSED(pPurpetrator);
    if ( (pThing->thingInfo.weaponInfo.flags & SITH_WF_DAMAGEDESTROY) != 0 && damage > 1.0f && (!pThing->msecLifeLeft || pThing->msecLifeLeft > 250) )
    {
        pThing->msecLifeLeft = 250;
    }
}

int J3DAPI sithWeapon_ThingCollisionHandler(SithThing* pWeapon, SithThing* pThing, SithCollision* pCollision, int a5)
{

    if ( (pThing->flags & 4) != 0 )
    {
        return 0;
    }

    if ( (pWeapon->thingInfo.weaponInfo.flags & SITH_WF_MOPHIABOMB) != 0 && pThing->type == SITH_THING_PLAYER )
    {
        if ( pThing->thingInfo.actorInfo.curWeaponID == SITHWEAPON_MIRROR )
        {
            SithThing* pTemplate = sithTemplate_GetTemplate("+mardukhit");
            if ( pTemplate )
            {
                bool bNoProjectile = true;
                SithThing* pReboundProjectile =NULL;
                if ( sithWeapon_IsAiming(pThing) )
                {
                    pReboundProjectile = sithThing_CreateThing(pTemplate, pWeapon);
                    if ( pReboundProjectile )
                    {
                        rdVector3 projectDir;
                        /*projectDir.x = pWeapon->pParent->pos.x - pWeapon->pos.x;
                        projectDir.y = pWeapon->pParent->pos.y - pWeapon->pos.y;
                        projectDir.z = pWeapon->pParent->pos.z - pWeapon->pos.z;*/
                        rdVector_Sub3(&projectDir, &pWeapon->pParent->pos, &pWeapon->pos);
                        rdVector_Normalize3Acc(&projectDir);

                        // Set projectile LVect
                        rdVector_Copy3(&pReboundProjectile->orient.lvec, &projectDir);

                        // Set projectile RVect
                        /*pReboundProjectile->orient.rvec.x = pReboundProjectile->orient.lvec.y * pReboundProjectile->orient.uvec.z - pReboundProjectile->orient.lvec.z * pReboundProjectile->orient.uvec.y;
                        pReboundProjectile->orient.rvec.y = pReboundProjectile->orient.lvec.z * pReboundProjectile->orient.uvec.x - pReboundProjectile->orient.lvec.x * pReboundProjectile->orient.uvec.z;
                        pReboundProjectile->orient.rvec.z = pReboundProjectile->orient.lvec.x * pReboundProjectile->orient.uvec.y - pReboundProjectile->orient.lvec.y * pReboundProjectile->orient.uvec.x;*/
                        rdVector_Cross3(&pReboundProjectile->orient.rvec, &pReboundProjectile->orient.lvec, &pReboundProjectile->orient.uvec);
                        rdVector_Normalize3Acc(&pReboundProjectile->orient.rvec);

                        // Set projectile UVect
                        /*pReboundProjectile->orient.uvec.x = pReboundProjectile->orient.lvec.y * pReboundProjectile->orient.rvec.z - pReboundProjectile->orient.lvec.z * pReboundProjectile->orient.rvec.y;
                        pReboundProjectile->orient.uvec.y = pReboundProjectile->orient.lvec.z * pReboundProjectile->orient.rvec.x - pReboundProjectile->orient.lvec.x * pReboundProjectile->orient.rvec.z;
                        pReboundProjectile->orient.uvec.z = pReboundProjectile->orient.lvec.x * pReboundProjectile->orient.rvec.y - pReboundProjectile->orient.lvec.y * pReboundProjectile->orient.rvec.x;*/
                        rdVector_Cross3(&pReboundProjectile->orient.uvec, &pReboundProjectile->orient.lvec, &pReboundProjectile->orient.rvec);
                        rdVector_Normalize3Acc(&pReboundProjectile->orient.uvec);

                        float wepspeed = rdVector_Len3(&pWeapon->moveInfo.physics.velocity);
                        pReboundProjectile->moveInfo.physics.velocity.x = wepspeed * 0.75f * projectDir.x;
                        pReboundProjectile->moveInfo.physics.velocity.y = wepspeed * 0.75f * projectDir.y;
                        pReboundProjectile->moveInfo.physics.velocity.z = wepspeed * 0.75f * projectDir.z;
                        sithCollision_MoveThing(pReboundProjectile, &projectDir, 0.059999999f, 5);

                        bNoProjectile = false;
                    }
                }
                else
                {
                    rdVector3 wepdir;
                    float wepspeed = rdVector_Normalize3(&wepdir, &pWeapon->moveInfo.physics.velocity);

                    rdVector3 thdir;
                    rdVector_Copy3(&thdir, &pThing->orient.lvec);

                    thdir.z = thdir.z + 0.039999999f;
                    rdVector_Normalize3Acc(&thdir);

                    float dot = rdVector_Dot3(&thdir, &wepdir);
                    if ( dot <= -0.73699999f )
                    {
                        pReboundProjectile = sithThing_CreateThing(pTemplate, pWeapon);
                        if ( pReboundProjectile )
                        {
                            /*   if ( 2.0f * dot >= 0.0f )
                               {
                                   v6 = 2.0f * dot;
                               }
                               else
                               {
                                   v6 = -(2.0f * dot);
                               }

                               dist = v6;
                               v19 = dist;*/

                            float dist = fabsf(2.0f * dot);

                            rdVector3 projectDir;
                            projectDir.x = thdir.x * dist + wepdir.x;
                            projectDir.y = thdir.y * dist + wepdir.y;
                            projectDir.z = thdir.z * dist + wepdir.z;
                            rdVector_Normalize3Acc(&projectDir);

                            rdVector_Copy3(&pReboundProjectile->orient.lvec, &projectDir);

                            /*pReboundProjectile->orient.rvec.x = pReboundProjectile->orient.lvec.y * pReboundProjectile->orient.uvec.z - pReboundProjectile->orient.lvec.z * pReboundProjectile->orient.uvec.y;
                            pReboundProjectile->orient.rvec.y = pReboundProjectile->orient.lvec.z * pReboundProjectile->orient.uvec.x - pReboundProjectile->orient.lvec.x * pReboundProjectile->orient.uvec.z;
                            pReboundProjectile->orient.rvec.z = pReboundProjectile->orient.lvec.x * pReboundProjectile->orient.uvec.y - pReboundProjectile->orient.lvec.y * pReboundProjectile->orient.uvec.x;*/
                            rdVector_Cross3(&pReboundProjectile->orient.rvec, &pReboundProjectile->orient.lvec, &pReboundProjectile->orient.uvec);
                            rdVector_Normalize3Acc(&pReboundProjectile->orient.rvec);

                            /*pReboundProjectile->orient.uvec.x = pReboundProjectile->orient.lvec.y * pReboundProjectile->orient.rvec.z - pReboundProjectile->orient.lvec.z * pReboundProjectile->orient.rvec.y;
                            pReboundProjectile->orient.uvec.y = pReboundProjectile->orient.lvec.z * pReboundProjectile->orient.rvec.x - pReboundProjectile->orient.lvec.x * pReboundProjectile->orient.rvec.z;
                            pReboundProjectile->orient.uvec.z = pReboundProjectile->orient.lvec.x * pReboundProjectile->orient.rvec.y - pReboundProjectile->orient.lvec.y * pReboundProjectile->orient.rvec.x;*/
                            rdVector_Cross3(&pReboundProjectile->orient.uvec, &pReboundProjectile->orient.lvec, &pReboundProjectile->orient.rvec);
                            rdVector_Normalize3Acc(&pReboundProjectile->orient.uvec);

                            pReboundProjectile->moveInfo.physics.velocity.x = wepspeed * 0.75f * projectDir.x;
                            pReboundProjectile->moveInfo.physics.velocity.y = wepspeed * 0.75f * projectDir.y;
                            pReboundProjectile->moveInfo.physics.velocity.z = wepspeed * 0.75f * projectDir.z;
                            sithCollision_MoveThing(pReboundProjectile, &pThing->orient.lvec, 0.059999999f, 5);

                            sithThing_DamageThing(pThing, pWeapon, 25.0f, SITH_DAMAGE_LIGHTNING);

                            bNoProjectile = false;
                        }
                    }
                }

                if ( !bNoProjectile )
                {
                    pReboundProjectile->pParent = pThing;
                    pReboundProjectile->parentSignature = pThing->signature;
                    tSoundHandle hSnd = sithSound_Load(sithWorld_g_pCurrentWorld, "aet_mr_ball_rebound.wav");
                    if ( hSnd )
                    {
                        sithSoundMixer_PlaySoundThing(hSnd, pReboundProjectile, 1.0f, 0.5f, 2.0f, SOUNDPLAY_PLAYTHIGNONCE | SOUNDPLAY_THING_POS);
                    }

                    memset(&pWeapon->moveDir, 0, sizeof(pWeapon->moveDir));
                    sithThing_DestroyThing(pWeapon);
                    return 1;
                }
            }
        }

        if ( sithGetPerformanceLevel() >= 2 )
        {
            tSoundHandle hSnd = sithSound_Load(sithWorld_g_pCurrentWorld, "aet_mr_hit_indy.wav");
            if ( hSnd )
            {
                sithSoundMixer_PlaySoundThing(hSnd, pThing, 1.0f, 0.5f, 2.0f, SOUNDPLAY_PLAYTHIGNONCE | SOUNDPLAY_THING_POS);
            }
        }
    }

    if ( (pWeapon->thingInfo.weaponInfo.flags & SITH_WF_PROXIMITY) != 0 )
    {
        /*flags = pWeapon->thingInfo.weaponInfo.flags;
        flags &= ~0x1000;
        pWeapon->thingInfo.weaponInfo.flags = flags;*/
        pWeapon->thingInfo.weaponInfo.flags &= ~SITH_WF_PROXIMITY;

        /*v8 = pWeapon->thingInfo.weaponInfo.flags;
        v8 |= 0x100u;
        pWeapon->thingInfo.weaponInfo.flags = v8;*/
        pWeapon->thingInfo.weaponInfo.flags |= SITH_WF_EXPLODE;

        pWeapon->collide.size = 0.0f;
        pWeapon->msecLifeLeft = 500;
        sithSoundClass_PlayModeFirst(pWeapon, SITHSOUNDCLASS_ACTIVATE);
        return 0;
    }

    if ( (pWeapon->thingInfo.weaponInfo.flags & SITH_WF_SURFACERICOCHET) != 0 && pThing->type == SITH_THING_COG )
    {
        size_t numRicochets = pWeapon->thingInfo.weaponInfo.numRicochets;
        pWeapon->thingInfo.weaponInfo.numRicochets = numRicochets + 1;
        if ( numRicochets < SITHWEAPON_MAX_PROJECTILE_RICOCHETS )
        {
            sithSoundClass_PlayModeRandom(pWeapon, SITHSOUNDCLASS_DEFLECTED);
        }
        else
        {
            pWeapon->moveInfo.physics.flags &= ~SITH_PF_SURFACEBOUNCE;
            pWeapon->moveInfo.physics.flags |= SITH_PF_FLOORSTICK;
        }
    }

    if ( pThing->type == SITH_THING_ACTOR || pThing->type == SITH_THING_PLAYER )
    {
        if ( pWeapon->thingInfo.weaponInfo.damage == 0.0f && (pWeapon->thingInfo.weaponInfo.flags & (SITH_WF_ATTACHTHING | SITH_WF_THINGHITEXPLODE)) == 0 )
        {
            return 0;
        }

        if ( !sithCollision_ThingCollisionHandler(pWeapon, pThing, pCollision, a5) )
        {
            return 0;
        }

        float damage = sithThing_ScaleCombatDamage(pWeapon, pThing);
        if ( damage != 0.0f )
        {
            sithThing_DamageThing(pThing, pWeapon, damage, pWeapon->thingInfo.weaponInfo.damageType);
        }

        if ( sithThing_GetThingParent(pWeapon) == sithPlayer_g_pLocalPlayerThing
            && sithWeapon_pfActorKilledCallback
            && pThing->thingInfo.actorInfo.health == 0.0f )
        {
            sithWeapon_pfActorKilledCallback(sithGetGameDifficulty());
        }

        if ( (pWeapon->thingInfo.weaponInfo.flags & SITH_WF_THINGHITEXPLODE) != 0 )
        {
            if ( pThing->thingInfo.actorInfo.health == 0.0f
                && (pWeapon->thingInfo.weaponInfo.flags & SITH_WF_ACTORKILLDESTROY) != 0
                && (pThing->thingInfo.actorInfo.flags & SITH_AF_DROID) == 0
                && pThing->type != SITH_THING_PLAYER
                && sithWeapon_bGenBloodsplort )
            {
                sithWeapon_GenBloodsplort(pThing);
                sithThing_DestroyThing(pWeapon);
            }
            else
            {
                sithWeapon_CreateWeaponExplosion(pWeapon, pWeapon->thingInfo.weaponInfo.pExplosionTemplate, NULL, /*bRotate=*/0);
            }

            return 1;
        }

        if ( (pWeapon->thingInfo.weaponInfo.flags & SITH_WF_ATTACHTHING) == 0 )
        {
            return 1;
        }

        sithPhysics_ResetThingMovement(pWeapon);
        sithThing_AttachThingToThing(pWeapon, pThing);
        pWeapon->attach.flags |= SITH_ATTACH_NOMOVE;
        pWeapon->moveInfo.physics.flags |= SITH_PF_USEGRAVITY;
        return 1;
    }

    if ( pWeapon->thingInfo.weaponInfo.damage != 0.0f )
    {
        sithThing_DamageThing(pThing, pWeapon, pWeapon->thingInfo.weaponInfo.damage, pWeapon->thingInfo.weaponInfo.damageType);
    }

    if ( (pWeapon->thingInfo.weaponInfo.flags & SITH_WF_FACEHITEXPLODE) != 0 )
    {
        if ( pCollision->pFaceCollided )
        {
            rdVector3 expDir;
            rdMatrix_TransformVector34(&expDir, &pCollision->pFaceCollided->normal, &pThing->orient);
            SithThing* pExplosion = sithWeapon_CreateWeaponExplosion(pWeapon, pWeapon->thingInfo.weaponInfo.pExplosionTemplate, &expDir, /*bRotate=*/1);
            if ( pExplosion && (pExplosion->thingInfo.weaponInfo.flags & SITH_WF_IMPACTSOUND) != 0 )
            {
                pExplosion->thingInfo.explosionInfo.pHitSurfaceMat = pCollision->pFaceCollided->pMaterial;
            }
        }
        else
        {
            //expDir.x = 1.0f;
            //expDir.y = 0.0f;
            //expDir.z = 0.0f;
            sithWeapon_CreateWeaponExplosion(pWeapon, pWeapon->thingInfo.weaponInfo.pExplosionTemplate, &rdroid_g_xVector3, /*bRotate=*/0);
        }

        return 1;
    }

    if ( (pWeapon->thingInfo.weaponInfo.flags & SITH_WF_ATTACHFACE) != 0 )
    {
        sithPhysics_ResetThingMovement(pWeapon);
        sithSoundClass_StopMode(pWeapon, SITHSOUNDCLASS_CREATE);
        sithSoundClass_PlayModeFirst(pWeapon, SITHSOUNDCLASS_HITHARD);
        pWeapon->collide.movesize = 0.0f;
        if ( pCollision->pFaceCollided && pCollision->pMeshCollided )
        {
            sithThing_AttachThingToThing(pWeapon, pThing);
            sithPhysics_SetThingLook(pWeapon, &pCollision->hitNorm, 0.0f);
            pWeapon->attach.flags |= SITH_ATTACH_NOMOVE;
            pWeapon->moveInfo.physics.flags |= SITH_PF_USEGRAVITY;
        }
        else
        {
            sithThing_AttachThingToThing(pWeapon, pThing);
            sithPhysics_SetThingLook(pWeapon, &pCollision->hitNorm, 0.0f);
            /* v10 = pWeapon->attach.flags;
             (v10 & 0xFF) = v10 | SITH_ATTACH_NOMOVE;
             pWeapon->attach.flags = v10;*/
            pWeapon->attach.flags |= SITH_ATTACH_NOMOVE;

            /*v11 = pWeapon->moveInfo.physics.flags;
            (v11 & 0xFF) = v11 | SITH_PF_USEGRAVITY;
            pWeapon->moveInfo.physics.flags = v11;*/
            pWeapon->moveInfo.physics.flags |= SITH_PF_USEGRAVITY;
        }

        return 1;
    }

    // Fallback to default collision handler
    return sithCollision_ThingCollisionHandler(pWeapon, pThing, pCollision, a5);
}

int J3DAPI sithWeapon_SurfaceCollisionHandler(SithThing* pThing, SithSurface* pSurf, SithCollision* pStack)
{
    SITH_ASSERTREL(pThing->type == SITH_THING_WEAPON);

    if ( pThing->moveType != SITH_MT_PHYSICS )
    {
        SITHLOG_ERROR("Non-physics weapon %s hit a wall.\n", pThing->aName);
        return 0;
    }

    // Print debug info
    if ( (sithMain_g_sith_mode.debugModeFlags & SITHDEBUG_TRACKSHOTS) != 0 )
    {
        const char* pMatName = "none";
        if ( pSurf->face.pMaterial )
        {
            pMatName = pSurf->face.pMaterial->aName;
        }

        int secIdx  = sithSector_GetSectorIndex(pSurf->pSector);
        int surfIdx = sithSurface_GetSurfaceIndex(pSurf);
        SITHCONSOLE_PRINTF("Weapon hit surface %d, sector %d, material '%s'.\n", surfIdx, secIdx, pMatName);
    }

    // If hit sky surface, destroy projectile
    if ( (pSurf->flags & (SITH_SURFACE_CEILINGSKY | SITH_SURFACE_HORIZONSKY)) != 0 )
    {
        sithThing_DestroyThing(pThing);
        return 1;
    }

    if ( (pThing->thingInfo.weaponInfo.flags & SITH_WF_SURFACERICOCHET) != 0 )
    {
        size_t numRicochets = pThing->thingInfo.weaponInfo.numRicochets;
        pThing->thingInfo.weaponInfo.numRicochets = numRicochets + 1;
        if ( numRicochets < SITHWEAPON_MAX_PROJECTILE_RICOCHETS )
        {
            sithSoundClass_PlayModeRandom(pThing, SITHSOUNDCLASS_DEFLECTED);
        }
        else
        {
            pThing->moveInfo.physics.flags &= ~SITH_PF_SURFACEBOUNCE;
            pThing->moveInfo.physics.flags |= SITH_PF_FLOORSTICK;
        }
    }

    if ( pThing->thingInfo.weaponInfo.damage != 0.0f )
    {
        sithSurface_HandleThingImpact(pSurf, pThing, pThing->thingInfo.weaponInfo.damage, pThing->thingInfo.weaponInfo.damageType);
    }

    if ( (pThing->thingInfo.weaponInfo.flags & SITH_WF_FACEHITEXPLODE) != 0 )
    {
        rdVector3 surfNormal;
        rdVector_Copy3(&surfNormal, &pSurf->face.normal);
        SithThing* pExplosion = sithWeapon_CreateWeaponExplosion(pThing, pThing->thingInfo.weaponInfo.pExplosionTemplate, &surfNormal, 1);
        if ( !pExplosion )
        {
            return 1;
        }

        if ( (pExplosion->thingInfo.explosionInfo.flags & SITH_EF_UPDATEDEBRISMATERIAL) != 0 )
        {
            pExplosion->thingInfo.explosionInfo.pHitSurfaceMat = pSurf->face.pMaterial;
        }

        return 1;
    }

    if ( (pThing->thingInfo.weaponInfo.flags & SITH_WF_ATTACHFACE) != 0 )
    {
        sithCollision_HandleThingHitSurface(pThing, pSurf, pStack);
        sithPhysics_ResetThingMovement(pThing);
        pThing->collide.movesize = 0.0f;

        sithThing_AttachThingToSurface(pThing, pSurf, 0);
        sithPhysics_SetThingLook(pThing, &pSurf->face.normal, 0.0f);
        pThing->moveInfo.physics.flags |= SITH_PF_NOTHRUST;
        return 1;
    }

    // Tallback to default collision handler
    return sithCollision_HandleThingHitSurface(pThing, pSurf, pStack);
}

void J3DAPI sithWeapon_DestroyWeapon(SithThing* pWeapon)
{
    SITH_ASSERTREL(pWeapon && (pWeapon->type == SITH_THING_WEAPON));

    if ( (pWeapon->thingInfo.weaponInfo.flags & SITH_WF_EXPLODE) != 0 )
    {
        rdMaterial* pMaterial = NULL;
        if ( (pWeapon->attach.flags & SITH_ATTACH_SURFACE) != 0 )
        {
            pMaterial = pWeapon->attach.attachedToStructure.pSurfaceAttached->face.pMaterial;
        }

        SithThing* pExplosion = sithWeapon_CreateWeaponExplosion(pWeapon, pWeapon->thingInfo.weaponInfo.pExplosionTemplate, 0, 0);
        if ( pExplosion && pMaterial && (pExplosion->thingInfo.explosionInfo.flags & SITH_EF_UPDATEDEBRISMATERIAL) != 0 )
        {
            pExplosion->thingInfo.explosionInfo.pHitSurfaceMat = pMaterial;
        }
    }
    else
    {
        sithThing_DestroyThing(pWeapon);
    }
}

SithThing* J3DAPI sithWeapon_CreateWeaponExplosion(SithThing* pWeapon, SithThing* pExplosionTemplate, const rdVector3* pDir, int bRotate)
{
    SITH_ASSERTREL(pWeapon->type == SITH_THING_WEAPON);
    SITH_ASSERTREL(pWeapon->moveType == SITH_MT_PHYSICS);

    if ( (pWeapon->thingInfo.weaponInfo.flags & SITH_WF_EXPLODE) != 0
        && (pWeapon->flags & SITH_TF_SUBMERGED) != 0
        && (pWeapon->moveInfo.physics.flags & SITH_PF_ONWATERSURFACE) == 0 )
    {
        pExplosionTemplate = sithTemplate_GetTemplate("+uw_blast");
    }

    if ( !pExplosionTemplate )
    {
        sithThing_DestroyThing(pWeapon);
        return NULL;
    }

    rdVector3 pos;
    rdVector_Copy3(&pos, &pWeapon->pos);
    rdMatrix34 orient = rdroid_g_identMatrix34;

    if ( bRotate )
    {
        rdVector3 offset;
        rdVector_Copy3(&offset, pDir);
        rdVector_Scale3Acc(&offset, 0.001f); // offset /1000
        /* offset.x = offset.x * 0.001f;
         offset.y = offset.y * 0.001f;
         offset.z = offset.z * 0.001f;*/

        rdVector_Add3Acc(&pos, &offset);
        /*pos.x = pos.x + offset.x;
        pos.y = pos.y + offset.y;
        pos.z = pos.z + offset.z;*/

        // SetUVec & LVec
        rdVector_Copy3(&orient.uvec, &rdroid_g_zVector3);
        rdVector_Copy3(&orient.lvec, pDir);

        // Calc RVect
        rdVector_Cross3(&orient.rvec, &orient.lvec, &orient.uvec);
        /*orient.rvec.x = orient.lvec.y * orient.uvec.z - orient.lvec.z * orient.uvec.y;
        orient.rvec.y = orient.lvec.z * orient.uvec.x - orient.lvec.x * orient.uvec.z;
        orient.rvec.z = orient.lvec.x * orient.uvec.y - orient.lvec.y * orient.uvec.x;*/
    }

    SithThing* pParent    = sithThing_GetThingParent(pWeapon);
    SithThing* pExplosion = sithThing_CreateThingAtPos(pExplosionTemplate, &pos, &orient, pWeapon->pInSector, pParent);
    if ( !pExplosion )
    {
        SITHLOG_ERROR("No thing space to create explosion from weapon %d.\n", pWeapon->idx);
        sithThing_DestroyThing(pWeapon);
        return NULL;
    }

    SithInventoryType* pItem = sithInventory_GetType(pParent->thingInfo.actorInfo.curWeaponID);
    if ( pItem->pCog ) {
        sithCog_SendMessage(pItem->pCog, SITHCOG_MSG_CREATED, SITHCOG_SYM_REF_THING, pExplosion->idx, SITHCOG_SYM_REF_NONE, 0, 0);
    }

    if ( pParent == sithPlayer_g_pLocalPlayerThing ) {
        sithAIAwareness_CreateTransmittingEvent(pExplosion->pInSector, &pExplosion->pos, 0, 1.0f, pParent);
    }

    if ( (pWeapon->flags & SITH_TF_REMOTE) != 0 ) {
        pExplosion->flags |= SITH_TF_REMOTE;
    }

    sithThing_DestroyThing(pWeapon);
    return pExplosion;
}

float sithWeapon_GetMountWait(void)
{
    return sithWeapon_secMountWait;
}

void J3DAPI sithWeapon_SetMountWait(float secWait)
{
    sithWeapon_secMountWait = sithTime_g_secGameTime + secWait;
}

void J3DAPI sithWeapon_SetFireWait(SithThing* pThing, float waitTime)
{
    SITH_ASSERTREL(pThing && ((pThing->type == SITH_THING_PLAYER) || (pThing->type == SITH_THING_ACTOR)));
    if ( waitTime == -1.0f )
    {
        pThing->thingInfo.actorInfo.secWeaponActivationWaitEndTime = -1.0f;
        pThing->thingInfo.actorInfo.secWeaponActivationWaitTime    = -1.0f;
    }
    else
    {
        pThing->thingInfo.actorInfo.secWeaponActivationWaitEndTime = sithTime_g_secGameTime + waitTime;
        pThing->thingInfo.actorInfo.secWeaponActivationWaitTime    = waitTime;
    }
}

void J3DAPI sithWeapon_SetAimWait(SithThing* pThing, float waitTime)
{
    SITH_ASSERTREL(pThing && ((pThing->type == SITH_THING_PLAYER) || (pThing->type == SITH_THING_ACTOR)));
    pThing->thingInfo.actorInfo.secAimWaitEndTime = sithTime_g_secGameTime + waitTime;
}

void J3DAPI sithWeapon_ActivateWeapon(SithThing* pThing, SithCog* pCog, float waitTime)
{
    J3D_UNUSED(pCog);

    pThing->thingInfo.actorInfo.secWeaponActivationWaitTime = waitTime;
    pThing->thingInfo.actorInfo.secWeaponActivationStartTime = sithTime_g_secGameTime;
    if ( pThing->thingInfo.actorInfo.secWeaponActivationWaitTime > 0.0f )
    {
        pThing->thingInfo.actorInfo.secWeaponActivationWaitEndTime = sithTime_g_secGameTime + pThing->thingInfo.actorInfo.secWeaponActivationWaitTime;
    }
    else
    {
        pThing->thingInfo.actorInfo.secWeaponActivationWaitEndTime = -1.0f;
    }
}

float J3DAPI sithWeapon_DeactivateWeapon(SithThing* pThing)
{
    float waitTime = 0.0f;
    if ( pThing->thingInfo.actorInfo.secWeaponActivationStartTime != -1.0f )
    {
        waitTime = sithTime_g_secGameTime - pThing->thingInfo.actorInfo.secWeaponActivationStartTime;
    }

    pThing->thingInfo.actorInfo.secWeaponActivationStartTime   = -1.0f;
    pThing->thingInfo.actorInfo.secTimeLastRapidFired          = -1.0f;
    pThing->thingInfo.actorInfo.secWeaponActivationWaitEndTime = -1.0f;
    pThing->thingInfo.actorInfo.secWeaponActivationWaitTime    = 0.0f;
    return waitTime;
}

int J3DAPI sithWeapon_ProcessWeaponControls(SithThing* pThing, float secDeltaTime)
{
    J3D_UNUSED(secDeltaTime);
    SITH_ASSERTREL(pThing->type == SITH_THING_PLAYER);

    if ( sithWeapon_IsLocalPlayerUnableToUseWeapon() )
    {
        sithWeapon_bufferedWaponKeyId = -1;
        return 0;
    }

    if ( sithPlayerControls_g_bCutsceneMode == 1 || (pThing->flags & SITH_TF_DYING) != 0 || (pThing->moveInfo.physics.flags & SITH_PF_MINECAR) != 0 )
    {
        if ( sithWeapon_bPlayerWeaponActivated == 1 )
        {
            sithWeapon_DeactivateCurrentWeapon(pThing);
        }

        sithWeapon_bufferedWaponKeyId = -1;
        return 0;
    }

    SithWeaponId curWeaponID = pThing->thingInfo.actorInfo.curWeaponID;
    SithInventoryType* pItem = sithInventory_GetType(curWeaponID);
    if ( (pThing->thingInfo.actorInfo.flags & SITH_AF_CONTROLSDISABLED) != 0 && (pItem->flags & SITHINVENTORY_TYPE_UNKNOWN_200) == 0 )
    {
        if ( sithWeapon_bPlayerWeaponActivated == 1 )
        {
            sithWeapon_DeactivateCurrentWeapon(pThing);
        }

        return 0;
    }

    if ( sithWeapon_IsMountingWeapon(pThing) )
    {
        int keyState;
        for ( SithControlFunction keyId = SITHCONTROL_WSELECT0; (unsigned int)keyId <= SITHCONTROL_WSELECT16; ++keyId )
        {
            sithControl_GetKey(keyId, &keyState);
            if ( keyState )
            {
                sithWeapon_bufferedWaponKeyId = keyId;
                return 0;
            }
        }

        if ( curWeaponID > SITHWEAPON_NO_WEAPON
            && sithTime_g_secGameTime >= (double)sithWeapon_secWeaponActivationWaitEndTime
            && (sithControl_GetKey(SITHCONTROL_ACT2, &keyState), keyState)
            && !sithWeapon_bPlayerWeaponActivated )
        {
            sithWeapon_secWeaponActivationWaitEndTime = sithTime_g_secGameTime + 0.5f;
            return 0;
        }


        sithControl_GetKey(SITHCONTROL_WEAPONTOGGLE, &keyState);
        if ( keyState )
        {
            sithWeapon_bufferedWaponKeyId = SITHCONTROL_WEAPONTOGGLE;
            return 0;
        }

        sithControl_GetKey(SITHCONTROL_LIGHTERTOGGLE, &keyState);
        if ( keyState )
        {
            sithWeapon_bufferedWaponKeyId = SITHCONTROL_LIGHTERTOGGLE;
            return 0;
        }

        sithControl_GetKey(SITHCONTROL_NEXTWEAPON, &keyState);
        if ( keyState )
        {
            sithWeapon_bufferedWaponKeyId = SITHCONTROL_NEXTWEAPON;
            return 0;
        }

        sithControl_GetKey(SITHCONTROL_PREVWEAPON, &keyState);
        if ( keyState )
        {
            sithWeapon_bufferedWaponKeyId = SITHCONTROL_PREVWEAPON;
        }

        return 0;
    }

    int keyState;
    for ( SithControlFunction keyId = SITHCONTROL_WSELECT0; keyId <= SITHCONTROL_WSELECT16; ++keyId )
    {
        sithControl_GetKey(keyId, &keyState);
        if ( keyState )
        {
            SithWeaponId weaponID = sithWeapon_GetWeaponForControlKey(keyId);
            sithWeapon_SelectWeapon(pThing, weaponID);
            sithWeapon_bufferedWaponKeyId = -1;
            return 0;
        }
    }

    if ( curWeaponID > SITHWEAPON_NO_WEAPON && sithTime_g_secGameTime >= sithWeapon_secWeaponActivationWaitEndTime )
    {
        if ( sithControl_GetKey(SITHCONTROL_ACT2, &keyState) )
        {
            if ( !sithWeapon_bPlayerWeaponActivated )
            {
                if ( (pItem->flags & SITHINVENTORY_TYPE_UNKNOWN_200) != 0 )
                {
                    if ( pThing->moveStatus > (unsigned int)SITHPLAYERMOVE_RUNNING || pThing->thingInfo.actorInfo.bControlsDisabled == 1 )
                    {
                        sithWeapon_bufferedWaponKeyId = SITHCONTROL_ACT2;
                        return 0;
                    }

                    sithPhysics_ResetThingMovement(pThing);
                    if ( curWeaponID == SITHWEAPON_WHIP && sithWeapon_ActivateWhip(pThing, pItem->pCog) == 1 )
                    {
                        sithWeapon_bLocalPlayerAiming = 0;
                        sithWeapon_bufferedWaponKeyId = -1;
                        return 0;
                    }
                }

                sithWeapon_bPlayerWeaponActivated = 1;
                if ( pItem->pCog )
                {
                    sithCog_SendMessage(pItem->pCog, SITHCOG_MSG_ACTIVATE, SITHCOG_SYM_REF_NONE, 0, SITHCOG_SYM_REF_THING, pThing->idx, 0);
                }

                sithWeapon_bufferedWaponKeyId = -1;
                sithWeapon_secWeaponActivationWaitEndTime = pThing->thingInfo.actorInfo.secAimWaitEndTime
                    + pThing->thingInfo.actorInfo.secWeaponActivationWaitTime;
            }
        }
        else if ( sithWeapon_bPlayerWeaponActivated == 1 )
        {
            sithWeapon_DeactivateCurrentWeapon(pThing);
        }
    }

    sithControl_GetKey(SITHCONTROL_WEAPONTOGGLE, &keyState);
    if ( keyState )
    {
        if ( curWeaponID )
        {
            sithWeapon_DeselectWeapon(pThing);
        }

        else if ( (pThing->flags & SITH_TF_SUBMERGED) != 0 )
        {
            sithWeapon_SelectWeapon(pThing, SITHWEAPON_MACHETE);
        }
        else
        {
            sithWeapon_SelectWeapon(pThing, sithWeapon_lastPlayerWeaponID);
        }

        sithWeapon_bufferedWaponKeyId = -1;
    }

    sithControl_GetKey(SITHCONTROL_LIGHTERTOGGLE, &keyState);
    if ( keyState )
    {
        if ( curWeaponID == SITHWEAPON_ZIPPO )
        {
            sithWeapon_DeselectWeapon(pThing);
        }
        else
        {
            sithWeapon_SelectWeapon(pThing, SITHWEAPON_ZIPPO);
        }

        sithWeapon_bufferedWaponKeyId = -1;
    }

    sithControl_GetKey(SITHCONTROL_NEXTWEAPON, &keyState);
    if ( keyState )
    {
        sithWeapon_SelectNextWeapon(pThing);
        sithWeapon_bufferedWaponKeyId = -1;
    }

    sithControl_GetKey(SITHCONTROL_PREVWEAPON, &keyState);
    if ( keyState )
    {
        sithWeapon_SelectPreviousWeapon(pThing);
        sithWeapon_bufferedWaponKeyId = -1;
    }

    int bKeyProcessed = sithControl_GetKey(SITHCONTROL_CHALK, &keyState);
    if ( bKeyProcessed )
    {
        sithInventory_SetCurrentItem(pThing, SITHWEAPON_CHALK);
        sithPlayerActions_Activate(pThing);
        sithInventory_SetCurrentItem(pThing, SITHWEAPON_NO_WEAPON);
        sithWeapon_bufferedWaponKeyId = -1;
    }

    if ( sithWeapon_bufferedWaponKeyId != -1 && !sithWeapon_bPlayerWeaponActivated )
    {
        switch ( sithWeapon_bufferedWaponKeyId )
        {
            case SITHCONTROL_LIGHTERTOGGLE:
                if ( curWeaponID == SITHWEAPON_ZIPPO )
                {
                    sithWeapon_DeselectWeapon(pThing);
                }
                else
                {
                    sithWeapon_SelectWeapon(pThing, SITHWEAPON_ZIPPO);
                }
                break;

            case SITHCONTROL_WEAPONTOGGLE:
                if ( curWeaponID <= SITHWEAPON_NO_WEAPON || curWeaponID >= SITHWEAPON_ZIPPO )
                {
                    sithWeapon_SelectWeapon(pThing, sithWeapon_lastPlayerWeaponID);
                }
                else
                {
                    sithWeapon_DeselectWeapon(pThing);
                }

                break;

            case SITHCONTROL_WSELECT0:
            case SITHCONTROL_WSELECT1:
            case SITHCONTROL_WSELECT2:
            case SITHCONTROL_WSELECT3:
            case SITHCONTROL_WSELECT4:
            case SITHCONTROL_WSELECT5:
            case SITHCONTROL_WSELECT6:
            case SITHCONTROL_WSELECT7:
            case SITHCONTROL_WSELECT8:
            case SITHCONTROL_WSELECT9:
            case SITHCONTROL_WSELECT10:
            case SITHCONTROL_WSELECT11:
            case SITHCONTROL_WSELECT12:
            case SITHCONTROL_WSELECT13:
            case SITHCONTROL_WSELECT14:
            case SITHCONTROL_WSELECT15:
            case SITHCONTROL_WSELECT16:
                SithWeaponId weaponID = sithWeapon_GetWeaponForControlKey(sithWeapon_bufferedWaponKeyId);
                sithWeapon_SelectWeapon(pThing, weaponID);
                break;

            case SITHCONTROL_NEXTWEAPON:
                sithWeapon_SelectNextWeapon(pThing);
                break;

            case SITHCONTROL_PREVWEAPON:
                sithWeapon_SelectPreviousWeapon(pThing);
                break;

            default:
                break;
        }

        SITHLOG_STATUS("Processed buffered weapon key %d.\n", sithWeapon_bufferedWaponKeyId);
        sithWeapon_bufferedWaponKeyId = -1;
        return 0;
    }


    return bKeyProcessed;
}

void J3DAPI sithWeapon_DeselectWeapon(SithThing* pThing)
{
    int typeId = pThing->thingInfo.actorInfo.curWeaponID;
    if ( typeId )
    {
        if ( (sithInventory_GetType(typeId)->flags & SITHINVENTORY_TYPE_WEAPON) != 0 )
        {
            pThing->thingInfo.actorInfo.deselectedWeaponID = pThing->thingInfo.actorInfo.curWeaponID;
            pThing->thingInfo.actorInfo.selectedWeaponID   = SITHWEAPON_NO_WEAPON;
        }
    }
}

int J3DAPI sithWeapon_IsMountingWeapon(const SithThing* pThing)
{
    if ( pThing->type == SITH_THING_PLAYER && sithTime_g_secGameTime < (double)sithWeapon_secMountWait )
    {
        return 1;
    }

    if ( pThing->thingInfo.actorInfo.selectedWeaponID != -1 )
    {
        return 1;
    }

    if ( sithTime_g_secGameTime >= (double)pThing->thingInfo.actorInfo.secAimWaitEndTime )
    {
        return sithTime_g_secGameTime < (double)pThing->thingInfo.actorInfo.secWeaponActivationWaitEndTime;
    }

    return 1;
}

int J3DAPI sithWeapon_HasWeaponSelected(const SithThing* pThing)
{
    SITH_ASSERTREL(pThing);
    if ( pThing->type == SITH_THING_PLAYER
        && pThing->thingInfo.actorInfo.curWeaponID >= SITHWEAPON_FISTS
        && pThing->thingInfo.actorInfo.curWeaponID <= SITHWEAPON_BAZOOKA )
    {
        return 1;
    }

    if ( pThing->type != SITH_THING_ACTOR )
    {
        return 0;
    }

    if ( (pThing->moveInfo.physics.flags & (SITH_PF_UNKNOWN_8000000 | SITH_PF_JEEP | SITH_PF_RAFT | SITH_PF_MINECAR)) != 0 )
    {
        return 0;
    }

    return pThing->thingInfo.actorInfo.curWeaponID >= SITHWEAPON_COMTOKAREV && pThing->thingInfo.actorInfo.curWeaponID <= SITHWEAPON_COMSHOTGUN;
}

int J3DAPI sithWeapon_GetAimOrient(rdMatrix34* pOutOrient, SithThing* pShooter, const rdMatrix34* pStartOrient, const rdVector3* pFireOffset, float autoAimFovX, float autoAimFovZ)
{
    SITH_ASSERTREL(pShooter);

    rdMatrix_Copy34(pOutOrient, pStartOrient);
    rdVector_Copy3(&pOutOrient->dvec, pFireOffset);

    int curWeaponID = pShooter->thingInfo.actorInfo.curWeaponID;
    if ( curWeaponID <= SITHWEAPON_WHIP || curWeaponID >= SITHWEAPON_GRENADE || curWeaponID == SITHWEAPON_MACHETE )
    {
        if ( autoAimFovX == 0.0f || autoAimFovZ == 0.0f )
        {
            return 0;
        }

        if ( sithCamera_g_pCurCamera - sithCamera_g_aCameras == 1 )
        {
            autoAimFovX = autoAimFovX * 2.0f;
            autoAimFovZ = autoAimFovZ * 2.0f;
        }

        SithThing* aTarget[16] = { NULL }; // Added init to 0
        size_t numThings = sithAIUtil_GetThingsInView(pShooter->pInSector, pOutOrient, autoAimFovX, autoAimFovZ, STD_ARRAYLEN(aTarget), aTarget, SITHTHING_TYPEMASK(SITH_THING_ACTOR, SITH_THING_PLAYER), 5.0f);// 0x404 - player | actor
        if ( numThings == 0 )
        {
            return 0;
        }

        int targetNum = -1;
        float curDot = -1.0f;
        for ( size_t i = 0; i < numThings; ++i )
        {
            if ( aTarget[i] && aTarget[i] != pShooter && (aTarget[i]->thingInfo.actorInfo.flags & SITH_AF_NOTARGET) == 0 ) // Fixed: Added check for aTarget[i] != NULL 
            {
                if ( sithCollision_HasLOS(pShooter, aTarget[i], 0) )
                {
                    rdVector3 toDargetDir;
                    /*toDargetDir.x = aTarget[i]->pos.x - pShooter->pos.x;
                    toDargetDir.y = aTarget[i]->pos.y - pShooter->pos.y;
                    toDargetDir.z = aTarget[i]->pos.z - pShooter->pos.z;*/

                    rdVector_Sub3(&toDargetDir, &aTarget[i]->pos, &pShooter->pos);
                    if ( rdVector_Len3(&toDargetDir) > 0.0f )
                    {

                        rdVector3 curDir;
                        rdVector_Copy3(&curDir, &pOutOrient->lvec);
                        rdVector_Normalize3Acc(&toDargetDir);
                        rdVector_Normalize3Acc(&curDir);

                        float dot = fabsf(rdVector_Dot3(&curDir, &toDargetDir));
                        /*v7 = rdVector_Dot3(&curDir, &toDargetDir) >= 0.0f
                            ? rdVector_Dot3(&curDir, &toDargetDir)
                            : -(rdVector_Dot3(&curDir, &toDargetDir));*/
                        if ( targetNum < 0 || dot >(double)curDot )
                        {
                            curDot    = dot;
                            targetNum = i;
                        }
                    }
                }
            }
        }

        if ( targetNum >= 0 )
        {
            rdMatrix_LookAt(pOutOrient, pFireOffset, &aTarget[targetNum]->pos, 0.0f);
            return 1;
        }

        return 0;

    }

    SithThing* pTarget = sithPlayerControls_GetTargetThing();
    if ( !pTarget )
    {
        return 0;
    }

    if ( (pTarget->thingInfo.actorInfo.flags & SITH_AF_NOTARGET) != 0 )
    {
        return 0;
    }

    rdVector3 targetPos;
    rdVector_Copy3(&targetPos, &pTarget->pos);

    float zOffset = pTarget->thingInfo.actorInfo.eyeOffset.z;
    if ( (pTarget->thingInfo.actorInfo.flags & SITH_AF_HUMAN) != 0 )
    {
        zOffset = zOffset * 0.25f;           // don't aim head
    }

    else if ( curWeaponID == SITHWEAPON_SUBMACHINE || curWeaponID == SITHWEAPON_SHOTGUN )
    {
        zOffset = zOffset * 0.5f;            // aim at torso
    }

    targetPos.z = targetPos.z + zOffset;

    /*v21.x = targetPos.x - pFireOffset->x;
    v21.y = targetPos.y - pFireOffset->y;
    v21.z = targetPos.z - pFireOffset->z;
    a = rdVector_Dot3(&v21, &v21);
    if ( sqrtf(a) > 0.0f )*/

    rdVector3 vecTargetFire;
    rdVector_Sub3(&vecTargetFire, &targetPos, pFireOffset);
    if ( rdVector_Len3(&vecTargetFire) > 0.0f )
    {
        rdMatrix_LookAt(pOutOrient, pFireOffset, &targetPos, 0.0f);
        return 1;
    }

    return 0;
}

SithThing* J3DAPI sithWeapon_FireProjectile(SithThing* pShooter, const SithThing* pProjectile, tSoundHandle hFireSnd, SithPuppetSubMode submode, rdVector3* pFireOffset, rdVector3* pAimError, float extra, SithFireProjectileFlags flags, float autoAimFovX, float autoAimFovZ)
{
    SITH_ASSERTREL(pShooter);
    if ( pShooter->type != SITH_THING_ACTOR && pShooter->type != SITH_THING_PLAYER )
    {
        SITHLOG_ERROR("Bad thing in sithWeapon_FireProjectile.\n");
        return 0;
    }

    rdVector3 fireOffset;
    if ( pShooter->type == SITH_THING_ACTOR )
    {
        rdVector3 targetPos;
        rdVector_Copy3(&fireOffset, &pShooter->thingInfo.actorInfo.vecUnknown0);
        rdVector_Copy3(&targetPos, &pShooter->controlInfo.aiControl.pLocal->targetPos);
        return sithWeapon_FireProjectileEx(pShooter, pProjectile, hFireSnd, submode, pFireOffset, &targetPos, extra, flags, autoAimFovX, autoAimFovZ, &fireOffset, /*bUseFireOffset*/1);
    }

    rdMatrix34 fireOrient;
    if ( (flags & SITHFIREPROJECTILE_RIGHTHAND_FIRE) != 0 )
    {
        int jointIdx = sithThing_GetThingJointIndex(pShooter, "inrhand");
        if ( jointIdx == -1 )
        {
            SITHLOG_ERROR("Bad hand node in sithWeapon_FireProjectile.\n");
            return 0;
        }

        rdMatrix_Copy34(&fireOrient, &pShooter->renderData.paJointMatrices[jointIdx]);
        rdVector_Set3(&fireOffset, 0.0f, -90.0f, 0.0f);
        rdMatrix_PreRotate34(&fireOrient, &fireOffset);
    }
    else if ( (flags & SITHFIREPROJECTILE_TORSO_FIRE) != 0 )
    {
        int jointIdx = sithThing_GetThingJointIndex(pShooter, "intorso");
        if ( jointIdx == -1 )
        {
            SITHLOG_ERROR("Bad hand node in sithWeapon_FireProjectile.\n");
            return 0;
        }

        rdMatrix_Copy34(&fireOrient, &pShooter->renderData.paJointMatrices[jointIdx]);
        rdVector_Set3(&fireOffset, 0.0f, 0.0f, 0.0f); // Fixed: Init to 0
        rdMatrix_PreRotate34(&fireOrient, &fireOffset);
    }
    else
    {
        rdMatrix_Copy34(&fireOrient, &pShooter->orient);
    }

    if ( pFireOffset->x == 0.0f && pFireOffset->y == 0.0f && pFireOffset->z == 0.0f )
    {
        rdVector_Copy3(pFireOffset, &pShooter->pos);
    }

    rdMatrix34 matAimError;
    if ( (flags & SITHFIREPROJECTILE_AIM_ERROR) != 0 )
    {
        if ( !sithWeapon_GetAimOrient(&matAimError, pShooter, &fireOrient, pFireOffset, autoAimFovX, autoAimFovZ)
            && (pAimError->x != 0.0f || pAimError->y != 0.0f || pAimError->z != 0.0f) )
        {
            rdMatrix_PreRotate34(&matAimError, pAimError);
        }
    }
    else
    {
        rdMatrix_Copy34(&matAimError, &fireOrient);
        if ( pAimError->x != 0.0f || pAimError->y != 0.0f || pAimError->z != 0.0f )
        {
            rdMatrix_PreRotate34(&matAimError, pAimError);
        }
    }

    rdVector_Copy3(&fireOffset, &matAimError.lvec);
    float secDeltaTime = 0.0f;
    if ( (flags & SITHFIREPROJECTILE_RAPID_FIRE) != 0 )
    {
        float numExpectedFires = 1.0f;
        if ( pShooter->thingInfo.actorInfo.secTimeLastRapidFired != -1.0f && pShooter->thingInfo.actorInfo.secWeaponActivationWaitTime > 0.0f )
        {
            numExpectedFires = (sithTime_g_secGameTime - pShooter->thingInfo.actorInfo.secTimeLastRapidFired)
                / pShooter->thingInfo.actorInfo.secWeaponActivationWaitTime
                - 1.0f;
        }

        pShooter->thingInfo.actorInfo.secTimeLastRapidFired = sithTime_g_secGameTime;
        SITH_ASSERTREL(numExpectedFires < 10);
        while ( numExpectedFires > 1.0f )
        {
            numExpectedFires = numExpectedFires - 1.0f;
            secDeltaTime = pShooter->thingInfo.actorInfo.secWeaponActivationWaitTime * numExpectedFires;
            sithWeapon_WeaponFire(pShooter, pProjectile, &fireOffset, pFireOffset, 0, submode, extra, flags, secDeltaTime);
        }
    }
    else
    {
        pShooter->thingInfo.actorInfo.secTimeLastRapidFired = -1.0f;
    }

    return sithWeapon_WeaponFire(pShooter, pProjectile, &fireOffset, pFireOffset, hFireSnd, submode, extra, flags, secDeltaTime);
}

void J3DAPI sithWeapon_DeactivateCurrentWeapon(SithThing* pThing)
{
    SITH_ASSERTREL(pThing && ((pThing->type == SITH_THING_PLAYER) || (pThing->type == SITH_THING_ACTOR)));

    if ( pThing->type == SITH_THING_PLAYER )
    {
        if ( sithWeapon_bPlayerWeaponActivated == 1 )
        {
            sithWeapon_bPlayerWeaponActivated = 0;
            sithWeapon_deactivatedPlayerWeaponID = pThing->thingInfo.actorInfo.curWeaponID;
            sithWeapon_secPlayerWeaponDeactivationTime = pThing->thingInfo.actorInfo.secWeaponActivationWaitEndTime;
        }
    }
    else // Actor
    {
        SithInventoryType* pItem = sithInventory_GetType(pThing->thingInfo.actorInfo.curWeaponID);
        if ( pItem->pCog ) {
            sithCog_SendMessage(pItem->pCog, SITHCOG_MSG_DEACTIVATED, SITHCOG_SYM_REF_NONE, 0, SITHCOG_SYM_REF_THING, pThing->idx, 0);
        }
    }
}

int J3DAPI sithWeapon_SelectNextWeapon(SithThing* pThing)
{
    SITH_ASSERTREL(pThing);
    SITH_ASSERTREL(pThing->type == SITH_THING_PLAYER);

    int curWeaponID = sithWeapon_lastPlayerWeaponID;
    if ( pThing->thingInfo.actorInfo.curWeaponID != SITHWEAPON_NO_WEAPON )
    {
        curWeaponID = pThing->thingInfo.actorInfo.curWeaponID;
        if ( curWeaponID > sithInventory_FindNextTypeID(pThing, curWeaponID, SITHINVENTORY_TYPE_PLAYERWEAPON) )
        {
            sithWeapon_DeselectWeapon(pThing);
            return 0;
        }
    }

    int weaponID = sithInventory_FindNextTypeID(pThing, curWeaponID, SITHINVENTORY_TYPE_PLAYERWEAPON);
    if ( weaponID == -1 )
    {
        return -1;
    }

    return sithWeapon_SelectWeapon(pThing, (SithWeaponId)weaponID);
}

int J3DAPI sithWeapon_SelectPreviousWeapon(SithThing* pThing)
{
    SITH_ASSERTREL(pThing);
    SITH_ASSERTREL(pThing->type == SITH_THING_PLAYER);

    int curWeaponID = sithWeapon_lastPlayerWeaponID;
    if ( pThing->thingInfo.actorInfo.curWeaponID != SITHWEAPON_NO_WEAPON )
    {
        curWeaponID = pThing->thingInfo.actorInfo.curWeaponID;
        if ( curWeaponID < sithInventory_FindPreviousTypeID(pThing, curWeaponID, SITHINVENTORY_TYPE_PLAYERWEAPON) )
        {
            sithWeapon_DeselectWeapon(pThing);
            return 0;
        }
    }


    int weaponId = sithInventory_FindPreviousTypeID(pThing, curWeaponID, SITHINVENTORY_TYPE_PLAYERWEAPON);
    if ( weaponId == -1 )
    {
        return -1;
    }

    return sithWeapon_SelectWeapon(pThing, (SithWeaponId)weaponId);
}

void J3DAPI sithWeapon_SetWeaponModel(SithThing* pThing, SithWeaponId weaponID)
{
    SITH_ASSERTREL(pThing);
    SITH_ASSERTREL((pThing->type == SITH_THING_PLAYER) || (pThing->type == SITH_THING_ACTOR));
    SITH_ASSERTREL(sithInventory_g_aTypes[weaponID].pModel);

    int meshIdx = sithThing_GetThingMeshIndex(pThing, "inrhand");
    if ( meshIdx != -1 )
    {
        pThing->thingInfo.actorInfo.weaponSwapRefNum = sithThing_AddSwapEntry(pThing, meshIdx, sithInventory_g_aTypes[weaponID].pModel, 0);
    }
}

void J3DAPI sithWeapon_ResetWeaponModel(SithThing* pThing)
{
    SITH_ASSERTREL(pThing);
    SITH_ASSERTREL((pThing->type == SITH_THING_PLAYER) || (pThing->type == SITH_THING_ACTOR));
    sithThing_RemoveSwapEntry(pThing, pThing->thingInfo.actorInfo.weaponSwapRefNum);
}

void J3DAPI sithWeapon_SetHolsterModel(SithThing* pThing, SithWeaponId weaponID, signed int meshNum)
{
    SITH_ASSERTREL(pThing);
    SITH_ASSERTREL(sithInventory_g_aTypes[weaponID].pHolsterModel);
    if ( pThing->type == SITH_THING_PLAYER )
    {
        switch ( weaponID )
        {
            case SITHWEAPON_WHIP:
                sithWeapon_playerWhipHolsterSwapRefNum = sithThing_AddSwapEntry(pThing, meshNum, sithInventory_g_aTypes[weaponID].pHolsterModel, /*meshNumSrc=*/0);
                return;

            case SITHWEAPON_PISTOL:
            case SITHWEAPON_TOKAREV:
            case SITHWEAPON_MAUSER:
                sithWeapon_playerPistolHolsterSwapRefNum = sithThing_AddSwapEntry(pThing, meshNum, sithInventory_g_aTypes[weaponID].pHolsterModel, /*meshNumSrc=*/0);
                return;

            case SITHWEAPON_SIMONOV:
            case SITHWEAPON_MACHETE:
            case SITHWEAPON_SUBMACHINE:
            case SITHWEAPON_SHOTGUN:
            case SITHWEAPON_BAZOOKA:
                sithWeapon_playerBackHolsterSwapRefNum = sithThing_AddSwapEntry(pThing, meshNum, sithInventory_g_aTypes[weaponID].pHolsterModel, /*meshNumSrc=*/0);
                return;

            default:
                return;
        }
    }
    else if ( pThing->type == SITH_THING_ACTOR )
    {
        sithThing_AddSwapEntry(pThing, meshNum, sithInventory_g_aTypes[weaponID].pHolsterModel, /*meshNumSrc=*/0);
    }
}

void J3DAPI sithWeapon_ResetHolsterModel(SithThing* pThing, int holsterNum)
{
    SITH_ASSERTREL(pThing);

    if ( holsterNum == SITHWEAPON_HOLSTWEWHIP ) // whipholster
    {
        if ( sithWeapon_playerWhipHolsterSwapRefNum != -1 )
        {
            sithThing_RemoveSwapEntry(pThing, sithWeapon_playerWhipHolsterSwapRefNum);
        }
    }
    else if ( holsterNum == SITHWEAPON_HOLSTERPISTOL ) // pistol holster
    {
        if ( sithWeapon_playerPistolHolsterSwapRefNum != -1 )
        {
            sithThing_RemoveSwapEntry(pThing, sithWeapon_playerPistolHolsterSwapRefNum);
        }
    }
    else if ( holsterNum == SITHWEAPON_HOLSTERBACK && sithWeapon_playerBackHolsterSwapRefNum != -1 ) // back holster
    {
        sithThing_RemoveSwapEntry(pThing, sithWeapon_playerBackHolsterSwapRefNum);
    }
}

void J3DAPI sithWeapon_EnablBloodsplort(bool bEnable)
{
    sithWeapon_bGenBloodsplort = bEnable;
}

void J3DAPI sithWeapon_SendMessageAim(SithThing* pThing, int bAim)
{
    // TODO: COG messages could be sent via thing cog overloads

    int curWeaponID = pThing->thingInfo.actorInfo.curWeaponID;
    SithInventoryType* pWaponItem = sithInventory_GetType(curWeaponID);
    if ( !pWaponItem || !pWaponItem->pCog )
    {
        return;
    }

    if ( pThing->type == SITH_THING_PLAYER )
    {
        // Fixed: Added sithPlayer_g_pLocalPlayerThing null check. 
        // This is just quick & dirty fix for sithWeapon_IsLocalPlayerUnableToUseWeapon, 
        // required when system is closing and indy is still aiming with the whip at whippable thing
        if ( !sithWeapon_IsMountingWeapon(pThing) && sithPlayer_g_pLocalPlayerThing && !sithWeapon_IsLocalPlayerUnableToUseWeapon() )
        {
            if ( bAim )
            {
                if ( !sithWeapon_bLocalPlayerAiming )
                {
                    sithCog_SendMessageEx(pWaponItem->pCog, SITHCOG_MSG_AIM, SITHCOG_SYM_REF_NONE, 0, SITHCOG_SYM_REF_THING, pThing->idx, 0, 1, 0, 0, 0);
                    sithWeapon_bLocalPlayerAiming = 1;
                }
            }
            else if ( pThing->thingInfo.actorInfo.curWeaponID != SITHWEAPON_WHIP || !sithWhip_GetWhipSwingThing() && !sithWhip_GetWhipClimbThing() )
            {
                if ( sithWeapon_bLocalPlayerAiming )
                {
                    sithWeapon_bLocalPlayerAiming = 0;
                }

                if ( sithPuppet_IsModeOnTrack(pThing, SITHPUPPETSUBMODE_AIMWEAPON) )
                {
                    sithCog_SendMessageEx(pWaponItem->pCog, SITHCOG_MSG_AIM, SITHCOG_SYM_REF_NONE, 0, SITHCOG_SYM_REF_THING, pThing->idx, 0, 0, 0, 0, 0);
                }
            }
        }
    }
    else if ( pThing->type == SITH_THING_ACTOR )
    {
        if ( bAim )
        {
            if ( !sithWeapon_IsMountingWeapon(pThing) )
            {
                sithCog_SendMessageEx(pWaponItem->pCog, SITHCOG_MSG_AIM, SITHCOG_SYM_REF_NONE, 0, SITHCOG_SYM_REF_THING, pThing->idx, 0, 1, 0, 0, 0);
            }
        }
        else
        {
            if ( sithWeapon_IsMountingWeapon(pThing) )
            {
                if ( curWeaponID >= SITHWEAPON_COMFISTS && curWeaponID <= SITHWEAPON_COMSHOTGUN )
                {
                    sithWeapon_DeactivateCurrentWeapon(pThing);
                }
                else
                {
                    sithWeapon_DeactivateWeapon(pThing);
                }
            }

            sithCog_SendMessageEx(pWaponItem->pCog, SITHCOG_MSG_AIM, SITHCOG_SYM_REF_NONE, 0, SITHCOG_SYM_REF_THING, pThing->idx, 0, 0, 0, 0, 0);
        }
    }
}

void J3DAPI sithWeapon_SetActorKilledCallback(SithWeaponActorKilledCallback pfCallback)
{
    sithWeapon_pfActorKilledCallback = pfCallback;
}

int J3DAPI sithWeapon_IsAiming(SithThing* pThing)
{
    SITH_ASSERTREL(pThing);

    if ( pThing->type == SITH_THING_PLAYER )
    {
        return sithWeapon_bLocalPlayerAiming;
    }

    if ( pThing->type != SITH_THING_ACTOR )
    {
        return 0;
    }

    bool bWeaponSelected = pThing->thingInfo.actorInfo.curWeaponID >= SITHWEAPON_COMTOKAREV && pThing->thingInfo.actorInfo.curWeaponID <= SITHWEAPON_COMSHOTGUN;
    if ( bWeaponSelected && sithPuppet_IsModeOnTrack(pThing, SITHPUPPETSUBMODE_AIMWEAPON) )
    {
        return 1;
    }

    return 0;
}

void J3DAPI sithWeapon_GenBloodsplort(SithThing* pHitThing)
{
    SITH_ASSERTREL(pHitThing != ((void*)0));
    SITH_ASSERTREL(pHitThing->renderData.data.pModel3 != ((void*)0));
    SITH_ASSERTREL((pHitThing->type == SITH_THING_ACTOR) || (pHitThing->type == SITH_THING_CORPSE));

    SithThing* pTemplate = NULL;
    rdMaterial* pMat = NULL;
    if ( (pHitThing->thingInfo.actorInfo.flags & SITH_AF_ARACHNID) != 0 )
    {
        pTemplate = sithTemplate_GetTemplate("+vulcansplort");
        pMat = sithMaterial_GetMaterialByIndex(SITHWORLD_STATICINDEX(420)); // gen_a4sprite_blood_grn.mat
    }
    else
    {
        pTemplate = sithTemplate_GetTemplate("+bloodsplort");
        pMat = sithMaterial_GetMaterialByIndex(SITHWORLD_STATICINDEX(179)); // gen_a4sprite_blood.mat
    }

    if ( pTemplate )
    {
        SithThing* pSprite = sithThing_CreateThingAtPos(pTemplate, &pHitThing->pos, &pHitThing->orient, pHitThing->pInSector, NULL);
        if ( pSprite )
        {
            int meshIdx = sithThing_GetThingMeshIndex(pHitThing, "intorso");
            if ( meshIdx == -1 )
            {
                if ( !strncmp(pHitThing->aName, "snak", 4u) )
                {
                    meshIdx = sithThing_GetThingMeshIndex(pHitThing, "snhead");
                }
                else if ( !strncmp(pHitThing->aName, "spid", 4u) )
                {
                    meshIdx = sithThing_GetThingMeshIndex(pHitThing, "spbelly");
                }
                else if ( !strncmp(pHitThing->aName, "scor", 4u) )
                {
                    meshIdx = sithThing_GetThingMeshIndex(pHitThing, "scsect1");
                }
                else if ( !strncmp(pHitThing->aName, "komo", 4u) )
                {
                    meshIdx = sithThing_GetThingMeshIndex(pHitThing, "lineck");
                }
                else if ( !strncmp(pHitThing->aName, "cent", 4u) )
                {
                    meshIdx = sithThing_GetThingMeshIndex(pHitThing, "cphead");
                }

                if ( meshIdx == -1 )
                {
                    meshIdx = 0;
                }

                SITHLOG_STATUS("Blood splort attached to mesh number %d.\n", meshIdx);
            }

            sithThing_AttachThingToThingMesh(pSprite, pHitThing, meshIdx);
            if ( pMat )
            {
                sithAnimate_StartMaterialAnim(pMat, 16.0f, (SithAnimateFlags)0);
            }

            float size = pHitThing->renderData.data.pModel3->size / 2.0f;
            size = STDMATH_CLAMP(size, 0.01f, 0.1f);
            //if ( size < 0.0099999998f )
            //{
            //    size = 0.0099999998f;
            //}
            //else if ( size > 0.1f )
            //{
            //    size = 0.1f;
            //}

            rdVector3 start;
            start.x = size;
            start.y = size;
            start.z = 1.0f;

            rdVector3 end;
            size = size * 2.0f;
            end.x = size;
            end.y = size;
            end.z = 1.0f;
            sithAnimate_StartSpriteSizeAnim(pSprite, &start, &end, 0.5f);
        }
    }
}

SithWeaponId sithWeapon_GetLastWeapon(void)
{
    return sithWeapon_lastPlayerWeaponID;
}

void J3DAPI sithWeapon_SetLastWeapon(SithWeaponId weaponNum)
{
    SITH_ASSERTREL((weaponNum >= SITHWEAPON_NO_WEAPON) && (weaponNum <= SITHWEAPON_IMP5));
    sithWeapon_lastPlayerWeaponID = weaponNum;
}

float J3DAPI sithWeapon_GetWeaponMaxAimDistance(SithWeaponId weaponId)
{
    if ( weaponId >= SITHWEAPON_NO_WEAPON && weaponId <= SITHWEAPON_BAZOOKA )
    {
        return sithWeapon_aMaxAimDistances[weaponId];
    }

    if ( weaponId >= SITHWEAPON_COMFISTS && weaponId <= SITHWEAPON_COMSHOTGUN )
    {
        return sithWeapon_aMaxAimDistances[weaponId];
    }

    if ( weaponId == SITHWEAPON_MIRROR )
    {
        return 4.0f;
    }

    return 0.0f;
}

float J3DAPI sithWeapon_GetWeaponCollideSize(SithWeaponId typeId)
{
    if ( typeId < SITHWEAPON_COMTOKAREV )
    {
        return 0.0f;
    }

    if ( typeId <= SITHWEAPON_COMSUBMACHINE )
    {
        return 0.02f;
    }

    if ( typeId == SITHWEAPON_COMSHOTGUN )
    {
        return 0.065f;
    }

    return 0.0f;
}

int sithWeapon_IsLocalPlayerUnableToUseWeapon(void)
{
    // TODO: Why sithPlayer_g_pLocalPlayerThing is used? Verify if player thing could be passed instead to this function
    SITH_ASSERTREL(sithPlayer_g_pLocalPlayerThing);
    if ( sithPuppet_IsModeOnTrack(sithPlayer_g_pLocalPlayerThing, SITHPUPPETSUBMODE_PUSHPULLREADY) )
    {
        return 1;
    }

    switch ( sithPlayer_g_pLocalPlayerThing->moveStatus )
    {
        case SITHPLAYERMOVE_STILL:
        case SITHPLAYERMOVE_WALKING:
        case SITHPLAYERMOVE_RUNNING:
        case SITHPLAYERMOVE_SWIMIDLE:
        case SITHPLAYERMOVE_WALK2STAND:
        case SITHPLAYERMOVE_STAND2WALK:
        case SITHPLAYERMOVE_UNKNOWN_78:
        case SITHPLAYERMOVE_STAND2RUN:
        case SITHPLAYERMOVE_UNKNOWN_80:
        case SITHPLAYERMOVE_UNKNOWN_81:
            return 0;
        default:
            break;
    }

    return 1;
}

int J3DAPI sithWeapon_Save(tFileHandle fh)
{
    static_assert(sizeof(sithWeapon_bPlayerWeaponActivated) == 4, "sizeof(sithWeapon_bPlayerWeaponActivated) == 4");
    static_assert(sizeof(sithWeapon_bLocalPlayerAiming) == 4, "sizeof(sithWeapon_bLocalPlayerAiming) == 4");
    static_assert(sizeof(sithWeapon_lastPlayerWeaponID) == 4, "sizeof(sithWeapon_lastPlayerWeaponID) == 4");
    static_assert(sizeof(sithWeapon_bufferedWaponKeyId) == 4, "sizeof(sithWeapon_bufferedWaponKeyId) == 4");
    static_assert(sizeof(sithWeapon_deactivatedPlayerWeaponID) == 4, "sizeof(sithWeapon_deactivatedPlayerWeaponID) == 4");
    static_assert(sizeof(sithWeapon_playerWhipHolsterSwapRefNum) == 4, "sizeof(sithWeapon_playerWhipHolsterSwapRefNum) == 4");
    static_assert(sizeof(sithWeapon_playerPistolHolsterSwapRefNum) == 4, "sizeof(sithWeapon_playerPistolHolsterSwapRefNum) == 4");
    static_assert(sizeof(sithWeapon_playerBackHolsterSwapRefNum) == 4, "sizeof(sithWeapon_playerBackHolsterSwapRefNum) == 4");
    static_assert(sizeof(sithWeapon_secMountWait) == 4, "sizeof(sithWeapon_secMountWait) == 4");
    static_assert(sizeof(sithWeapon_secPlayerWeaponDeactivationTime) == 4, "sizeof(sithWeapon_secPlayerWeaponDeactivationTime) == 4");

    return sith_g_pHS->pFileWrite(fh, &sithWeapon_bPlayerWeaponActivated, sizeof(sithWeapon_bPlayerWeaponActivated)) != sizeof(sithWeapon_bPlayerWeaponActivated)
        || sith_g_pHS->pFileWrite(fh, &sithWeapon_bLocalPlayerAiming, sizeof(sithWeapon_bLocalPlayerAiming)) != sizeof(sithWeapon_bLocalPlayerAiming)
        || sith_g_pHS->pFileWrite(fh, &sithWeapon_lastPlayerWeaponID, sizeof(sithWeapon_lastPlayerWeaponID)) != sizeof(sithWeapon_lastPlayerWeaponID)
        || sith_g_pHS->pFileWrite(fh, &sithWeapon_bufferedWaponKeyId, sizeof(sithWeapon_bufferedWaponKeyId)) != sizeof(sithWeapon_bufferedWaponKeyId)
        || sith_g_pHS->pFileWrite(fh, &sithWeapon_deactivatedPlayerWeaponID, sizeof(sithWeapon_deactivatedPlayerWeaponID)) != sizeof(sithWeapon_deactivatedPlayerWeaponID)
        || sith_g_pHS->pFileWrite(fh, &sithWeapon_playerWhipHolsterSwapRefNum, sizeof(sithWeapon_playerWhipHolsterSwapRefNum)) != sizeof(sithWeapon_playerWhipHolsterSwapRefNum)
        || sith_g_pHS->pFileWrite(fh, &sithWeapon_playerPistolHolsterSwapRefNum, sizeof(sithWeapon_playerPistolHolsterSwapRefNum)) != sizeof(sithWeapon_playerPistolHolsterSwapRefNum)
        || sith_g_pHS->pFileWrite(fh, &sithWeapon_playerBackHolsterSwapRefNum, sizeof(sithWeapon_playerBackHolsterSwapRefNum)) != sizeof(sithWeapon_playerBackHolsterSwapRefNum)
        || sith_g_pHS->pFileWrite(fh, &sithWeapon_secMountWait, sizeof(sithWeapon_secMountWait)) != sizeof(sithWeapon_secMountWait)
        || sith_g_pHS->pFileWrite(fh, &sithWeapon_secPlayerWeaponDeactivationTime, sizeof(sithWeapon_secPlayerWeaponDeactivationTime)) != sizeof(sithWeapon_secPlayerWeaponDeactivationTime);
}

int J3DAPI sithWeapon_Restore(tFileHandle fh)
{
    return sith_g_pHS->pFileRead(fh, &sithWeapon_bPlayerWeaponActivated, sizeof(sithWeapon_bPlayerWeaponActivated)) != sizeof(sithWeapon_bPlayerWeaponActivated)
        || sith_g_pHS->pFileRead(fh, &sithWeapon_bLocalPlayerAiming, sizeof(sithWeapon_bLocalPlayerAiming)) != sizeof(sithWeapon_bLocalPlayerAiming)
        || sith_g_pHS->pFileRead(fh, &sithWeapon_lastPlayerWeaponID, sizeof(sithWeapon_lastPlayerWeaponID)) != sizeof(sithWeapon_lastPlayerWeaponID)
        || sith_g_pHS->pFileRead(fh, &sithWeapon_bufferedWaponKeyId, sizeof(sithWeapon_bufferedWaponKeyId)) != sizeof(sithWeapon_bufferedWaponKeyId)
        || sith_g_pHS->pFileRead(fh, &sithWeapon_deactivatedPlayerWeaponID, sizeof(sithWeapon_deactivatedPlayerWeaponID)) != sizeof(sithWeapon_deactivatedPlayerWeaponID)
        || sith_g_pHS->pFileRead(fh, &sithWeapon_playerWhipHolsterSwapRefNum, sizeof(sithWeapon_playerWhipHolsterSwapRefNum)) != sizeof(sithWeapon_playerWhipHolsterSwapRefNum)
        || sith_g_pHS->pFileRead(fh, &sithWeapon_playerPistolHolsterSwapRefNum, sizeof(sithWeapon_playerPistolHolsterSwapRefNum)) != sizeof(sithWeapon_playerPistolHolsterSwapRefNum)
        || sith_g_pHS->pFileRead(fh, &sithWeapon_playerBackHolsterSwapRefNum, sizeof(sithWeapon_playerBackHolsterSwapRefNum)) != sizeof(sithWeapon_playerBackHolsterSwapRefNum)
        || sith_g_pHS->pFileRead(fh, &sithWeapon_secMountWait, sizeof(sithWeapon_secMountWait)) != sizeof(sithWeapon_secMountWait)
        || sith_g_pHS->pFileRead(fh, &sithWeapon_secPlayerWeaponDeactivationTime, sizeof(sithWeapon_secPlayerWeaponDeactivationTime)) != sizeof(sithWeapon_secPlayerWeaponDeactivationTime);
}

SithWeaponId J3DAPI sithWeapon_GetWeaponForControlKey(SithControlFunction keyID)
{
    switch ( keyID )
    {
        case SITHCONTROL_WSELECT0:
            return SITHWEAPON_FISTS;

        case SITHCONTROL_WSELECT1:
            return SITHWEAPON_WHIP;

        case SITHCONTROL_WSELECT2:
            return SITHWEAPON_PISTOL;

        case SITHCONTROL_WSELECT3:
            return SITHWEAPON_TOKAREV;

        case SITHCONTROL_WSELECT4:
            return SITHWEAPON_MAUSER;

        case SITHCONTROL_WSELECT5:
            return SITHWEAPON_SIMONOV;

        case SITHCONTROL_WSELECT6:
            return SITHWEAPON_MACHETE;

        case SITHCONTROL_WSELECT7:
            return SITHWEAPON_SUBMACHINE;

        case SITHCONTROL_WSELECT8:
            return SITHWEAPON_SHOTGUN;

        case SITHCONTROL_WSELECT9:
            return SITHWEAPON_BAZOOKA;

        case SITHCONTROL_WSELECT10:
            return SITHWEAPON_GRENADE;

        case SITHCONTROL_WSELECT11:
            return SITHWEAPON_SATCHEL;

        case SITHCONTROL_WSELECT12:
            return SITHWEAPON_IMP1;

        case SITHCONTROL_WSELECT13:
            return SITHWEAPON_IMP2;

        case SITHCONTROL_WSELECT14:
            return SITHWEAPON_IMP3;

        case SITHCONTROL_WSELECT15:
            return SITHWEAPON_IMP4;

        case SITHCONTROL_WSELECT16:
            return SITHWEAPON_IMP5;

        default:
            break;
    }

    return -1;
}

SithThing* J3DAPI sithWeapon_FireProjectileEx(SithThing* pShooter, const SithThing* pProjectile, tSoundHandle hSndFire, SithPuppetSubMode submode, rdVector3* pFirePos, const rdVector3* pTargetPos, float extra, SithFireProjectileFlags flags, float autoAimFovX, float autoAimFovZ, const rdVector3* pFireOffset, int bUseFireOffset)
{
    J3D_UNUSED(autoAimFovX);
    J3D_UNUSED(autoAimFovZ);
    SITH_ASSERTREL(pShooter != ((void*)0));

    if ( pShooter->type != SITH_THING_ACTOR )
    {
        SITHLOG_ERROR("Bad thing in sithWeapon_FireProjectileEx.\n");
        return 0;
    }

    const SithAIControlBlock* pLocal = pShooter->controlInfo.aiControl.pLocal;
    if ( pShooter->controlType == SITH_CT_AI
        && rdVector_Dot3(&pLocal->toTarget, &pShooter->orient.lvec) < pLocal->fireDot )
    {
        return 0;
    }

    if ( pFirePos->x == 0.0f && pFirePos->y == 0.0f && pFirePos->z == 0.0f )
    {
        rdVector_Copy3(pFirePos, &pShooter->pos);
    }

    rdVector3 fireDir;
    if ( bUseFireOffset == 1 )
    {
        if ( pShooter->thingInfo.actorInfo.fireOffset.x != 0.0f
            || pShooter->thingInfo.actorInfo.fireOffset.y != 0.0f
            || pShooter->thingInfo.actorInfo.fireOffset.z != 0.0f )
        {
            rdVector3 shooterFireOffset;
            rdVector_Copy3(&shooterFireOffset, &pShooter->thingInfo.actorInfo.fireOffset);
            rdMatrix_TransformVector34Acc(&shooterFireOffset, &pShooter->orient);

            rdVector_Add3Acc(pFirePos, &shooterFireOffset);
            /* pFirePos->x = pFirePos->x + shooterFireOffset.x;
             pFirePos->y = pFirePos->y + shooterFireOffset.y;
             pFirePos->z = pFirePos->z + shooterFireOffset.z;*/
        }

        rdVector_Sub3(&fireDir, pTargetPos, pFirePos);
        /*fireDir.x = pTargetPos->x - pFirePos->x;
        fireDir.y = pTargetPos->y - pFirePos->y;
        fireDir.z = pTargetPos->z - pFirePos->z;*/

        rdVector_Add3Acc(&fireDir, pFireOffset);
        /*fireDir.x = fireDir.x + pFireOffset->x;
        fireDir.y = fireDir.y + pFireOffset->y;
        fireDir.z = fireDir.z + pFireOffset->z;*/
        rdVector_Normalize3Acc(&fireDir);
    }
    else
    {
        rdVector_Copy3(&fireDir, &pShooter->orient.lvec);
    }

    float sedDeltaTime = 0.0f;
    if ( (flags & SITHFIREPROJECTILE_RAPID_FIRE) != 0 )
    {
        float numExpectedFires = 1.0f;
        if ( pShooter->thingInfo.actorInfo.secTimeLastRapidFired != -1.0f && pShooter->thingInfo.actorInfo.secWeaponActivationWaitTime > 0.0f )
        {
            numExpectedFires = (sithTime_g_secGameTime - pShooter->thingInfo.actorInfo.secTimeLastRapidFired)
                / pShooter->thingInfo.actorInfo.secWeaponActivationWaitTime
                - 1.0f;
        }

        pShooter->thingInfo.actorInfo.secTimeLastRapidFired = sithTime_g_secGameTime;
        SITH_ASSERTREL(numExpectedFires < 10);
        while ( numExpectedFires > 1.0f )
        {
            numExpectedFires = numExpectedFires - 1.0f;
            sedDeltaTime = pShooter->thingInfo.actorInfo.secWeaponActivationWaitTime * numExpectedFires;
            sithWeapon_WeaponFire(pShooter, pProjectile, &fireDir, pFirePos, 0, submode, extra, flags, sedDeltaTime);
        }
    }
    else
    {
        pShooter->thingInfo.actorInfo.secTimeLastRapidFired = -1.0f;
    }

    return sithWeapon_WeaponFire(pShooter, pProjectile, &fireDir, pFirePos, hSndFire, submode, extra, flags, sedDeltaTime);
}

void J3DAPI sithWeapon_CreateWeaponFireFx(SithThing* pThing, rdVector3* pos)
{
    SITH_ASSERTREL(pThing != ((void*)0));
    SITH_ASSERTREL((pThing->type == SITH_THING_PLAYER) || (pThing->type == SITH_THING_ACTOR));

    rdModel3* pHandModel = NULL;
    switch ( pThing->thingInfo.actorInfo.curWeaponID )
    {
        case SITHWEAPON_PISTOL:
            pHandModel = sithModel_GetModelByIndex(SITHWORLD_STATICINDEX(83)); // weap_revolver_fire.3do
            break;

        case SITHWEAPON_TOKAREV:
        case SITHWEAPON_COMTOKAREV:
            pHandModel = sithModel_GetModelByIndex(SITHWORLD_STATICINDEX(85)); // weap_tokarev_fire.3do
            break;

        case SITHWEAPON_MAUSER:
        case SITHWEAPON_COMMAUSER:
            pHandModel = sithModel_GetModelByIndex(SITHWORLD_STATICINDEX(81)); // weap_mauser_fire.3do
            break;

        case SITHWEAPON_SIMONOV:
        case SITHWEAPON_COMSIMONOV:
            pHandModel = sithModel_GetModelByIndex(SITHWORLD_STATICINDEX(84)); // weap_simonov_fire.3do
            break;

        case SITHWEAPON_SUBMACHINE:
        case SITHWEAPON_COMSUBMACHINE:
            pHandModel = sithModel_GetModelByIndex(SITHWORLD_STATICINDEX(82)); // weap_ppsh41_fire.3do
            break;

        case SITHWEAPON_SHOTGUN:
        case SITHWEAPON_COMSHOTGUN:
            pHandModel = sithModel_GetModelByIndex(SITHWORLD_STATICINDEX(86)); // weap_toz34_fire.3do
            break;

        default:
            return;
    }

    int meshIdx = sithThing_GetThingMeshIndex(pThing, "inrhand");
    if ( pHandModel && meshIdx != -1 )
    {
        pThing->thingInfo.actorInfo.weaponSwapRefNum = sithThing_AddSwapEntry(pThing, meshIdx, pHandModel, 0);
        pThing->thingInfo.actorInfo.secWeaponSwapTime = sithTime_g_secGameTime + 0.025f;
        SithThing* pGhostTpl = sithTemplate_GetTemplate("ghost");

        SithThing* pFlash = sithThing_CreateThingAtPos(pGhostTpl, pos, &pThing->orient, pThing->pInSector, pThing->pParent);
        if ( pFlash )
        {
            pFlash->flags |= SITH_TF_EMITLIGHT;
            pFlash->msecLifeLeft = 50;

            pFlash->light.color.red   = 0.5f;
            pFlash->light.color.green = 0.5f;
            pFlash->light.color.blue  = 0.5f;

            // TODO: Keeping this off for now as don't know if this was the intended way originally
            //pFlash->light.color.alpha = 1.0f; // Added: Setting alpha greater than 0.1 makes flash effect. 

            pFlash->light.minRadius   = 0.2f;
            pFlash->light.maxRadius   = 0.40000001f;
        }
    }
}

int J3DAPI sithWeapon_ActivateWhip(SithThing* pThing, SithCog* pCog)
{
    SITH_ASSERTREL(pCog != ((void*)0));

    bool bValidTarget = false;
    bool bSuccess     = false;

    SithThing* pWhipTarget = sithWhip_GetWhipSwingThing();
    if ( pWhipTarget )
    {
        bValidTarget = (pWhipTarget->flags & SITH_TF_WHIPCLIMB) == 0;
        if ( (pWhipTarget->flags & SITH_TF_WHIPCLIMB) == 0 )
        {
            bSuccess = sithWhip_StartWhipSwing(pThing);
        }
    }
    else
    {
        pWhipTarget = sithWhip_GetWhipClimbThing();
        if ( pWhipTarget )
        {
            bValidTarget = (pWhipTarget->flags & SITH_TF_WHIPSWING) == 0;
            if ( (pWhipTarget->flags & SITH_TF_WHIPSWING) == 0 )
            {
                bSuccess = sithWhip_StartWhipClimb(pThing, pWhipTarget);
            }
        }
    }

    if ( pWhipTarget )
    {
        if ( (pThing->thingInfo.actorInfo.flags & SITH_AF_ELECTRICWHIP) != 0 )
        {
            sithCog_ThingSendMessageEx(pWhipTarget, pThing, SITHCOG_MSG_DAMAGED, 0, SITH_DAMAGE_ELECTROWHIP, 0, 0);
        }
        else
        {
            sithCog_ThingSendMessageEx(pWhipTarget, pThing, SITHCOG_MSG_DAMAGED, 0, SITH_DAMAGE_WHIP, 0, 0);
        }

        if ( !bValidTarget )
        {
            return 1;
        }
    }

    if ( !bValidTarget || !bSuccess )
    {
        return 0;
    }

    sithCog_SendMessage(pCog, SITHCOG_MSG_ACTIVATE, SITHCOG_SYM_REF_THING, -99, SITHCOG_SYM_REF_THING, pThing->idx, 0);
    return 1;
}