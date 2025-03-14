#include "sithCogFunctionPlayer.h"
#include <j3dcore/j3dhook.h>

#include <sith/Cog/sithCog.h>
#include <sith/Cog/sithCogExec.h>
#include <sith/Dss/sithMulti.h>
#include <sith/Gameplay/sithInventory.h>
#include <sith/Gameplay/sithPlayer.h>
#include <sith/Gameplay/sithPlayerActions.h>
#include <sith/Gameplay/sithPlayerControls.h>
#include <sith/RTI/symbols.h>
#include <sith/World/sithMaterial.h>
#include <sith/World/sithThing.h>
#include <sith/World/sithWeapon.h>
#include <sith/Main/sithCommand.h>

#include <std/Win95/stdComm.h>

void sithCogFunctionPlayer_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    J3D_HOOKFUNC(sithCogFunctionPlayer_RegisterFunctions);
    J3D_HOOKFUNC(sithCogFunctionPlayer_IMPStartFiring);
    J3D_HOOKFUNC(sithCogFunctionPlayer_IMPEndFiring);
    J3D_HOOKFUNC(sithCogFunctionPlayer_SetPlayerInPor);
    J3D_HOOKFUNC(sithCogFunctionPlayer_JewelFlyingStatus);
    J3D_HOOKFUNC(sithCogFunctionPlayer_StartJewelFlying);
    J3D_HOOKFUNC(sithCogFunctionPlayer_MakeMeStop);
    J3D_HOOKFUNC(sithCogFunctionPlayer_SetInvActivated);
    J3D_HOOKFUNC(sithCogFunctionPlayer_SetInvAvailable);
    J3D_HOOKFUNC(sithCogFunctionPlayer_SetInvDisabled);
    J3D_HOOKFUNC(sithCogFunctionPlayer_IsInvActivated);
    J3D_HOOKFUNC(sithCogFunctionPlayer_IsInvAvailable);
    J3D_HOOKFUNC(sithCogFunctionPlayer_SetGoalFlags);
    J3D_HOOKFUNC(sithCogFunctionPlayer_ClearGoalFlags);
    J3D_HOOKFUNC(sithCogFunctionPlayer_GetNumPlayers);
    J3D_HOOKFUNC(sithCogFunctionPlayer_GetMaxPlayers);
    J3D_HOOKFUNC(sithCogFunctionPlayer_GetAbsoluteMaxPlayers);
    J3D_HOOKFUNC(sithCogFunctionPlayer_GetLocalPlayerThing);
    J3D_HOOKFUNC(sithCogFunctionPlayer_GetPlayerThing);
    J3D_HOOKFUNC(sithCogFunctionPlayer_GetPlayerNum);
    J3D_HOOKFUNC(sithCogFunctionPlayer_PickupBackpack);
    J3D_HOOKFUNC(sithCogFunctionPlayer_NthBackpackBin);
    J3D_HOOKFUNC(sithCogFunctionPlayer_NthBackpackValue);
    J3D_HOOKFUNC(sithCogFunctionPlayer_GetNumBackbackItems);
    J3D_HOOKFUNC(sithCogFunctionPlayer_CreateBackpack);
    J3D_HOOKFUNC(sithCogFunctionPlayer_GetRespawnMask);
    J3D_HOOKFUNC(sithCogFunctionPlayer_SetRespawnMask);
    J3D_HOOKFUNC(sithCogFunctionPlayer_SyncScores);
    J3D_HOOKFUNC(sithCogFunctionPlayer_GetCurItem);
    J3D_HOOKFUNC(sithCogFunctionPlayer_IsAming);
    J3D_HOOKFUNC(sithCogFunctionPlayer_SetSwimmingInventory);
    J3D_HOOKFUNC(sithCogFunctionPlayer_IsInvisible);
    J3D_HOOKFUNC(sithCogFunctionPlayer_ResetInventory);
    J3D_HOOKFUNC(sithCogFunctionPlayer_IsItemFound);
    J3D_HOOKFUNC(sithCogFunctionPlayer_SetElectricWhip);
    J3D_HOOKFUNC(sithCogFunctionPlayer_GetCutsceneMode);
    J3D_HOOKFUNC(sithCogFunctionPlayer_GetLastWeapon);
}

void sithCogFunctionPlayer_ResetGlobals(void)
{

}

int J3DAPI sithCogFunctionPlayer_RegisterFunctions(SithCogSymbolTable* pTable)
{
    return sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_SetInvActivated, "setinvactivated")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_SetInvAvailable, "setinvavailable")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_SetInvDisabled, "setinvdisabled")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_IsInvActivated, "isinvactivated")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_IsInvAvailable, "isinvavailable")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_SetGoalFlags, "setgoalflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_ClearGoalFlags, "cleargoalflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_GetNumPlayers, "getnumplayers")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_GetMaxPlayers, "getmaxplayers")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_GetAbsoluteMaxPlayers, "getabsolutemaxplayers")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_GetLocalPlayerThing, "getlocalplayerthing")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_GetPlayerThing, "getplayerthing")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_GetPlayerNum, "getplayernum")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_PickupBackpack, "pickupbackpack")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_CreateBackpack, "createbackpack")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_NthBackpackBin, "nthbackpackbin")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_NthBackpackValue, "nthbackpackvalue")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_GetNumBackbackItems, "numbackpackitems")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_GetRespawnMask, "getrespawnmask")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_SetRespawnMask, "setrespawnmask")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_SyncScores, "syncscores")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_GetCurItem, "getcuritem")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_JewelFlyingStatus, "jewelflyingstatus")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_StartJewelFlying, "startjewelflying")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_IsAming, "isaiming")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_SetSwimmingInventory, "setswimminginventory")
        || sithCog_RegisterFunction(pTable, sithPlayerActions_StartInvisibility, "startinvisibility")
        || sithCog_RegisterFunction(pTable, sithPlayerActions_EndInvisibility, "endinvisibility")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_IsInvisible, "isinvisible")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_ResetInventory, "resetinventory")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_MakeMeStop, "makemestop")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_IsItemFound, "isitemfound")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_SetElectricWhip, "setwhipelectric")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_SetPlayerInPor, "playerinpor")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_GetCutsceneMode, "getcutscenemode")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_GetLastWeapon, "getlastweapon")
        || sithCog_RegisterFunction(pTable, (SithCogFunctionType)sithPlayer_ToggleGuybrush, "makemeapirate")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_IMPStartFiring, "impstartfiring")
        || sithCog_RegisterFunction(pTable, sithCogFunctionPlayer_IMPEndFiring, "impendfiring");
}

void J3DAPI sithCogFunctionPlayer_IMPStartFiring(SithCog* pCog)
{
    int fireType;

    fireType = sithCogExec_PopInt(pCog);
    sithPlayer_IMPStartFiring(fireType);
}

void J3DAPI sithCogFunctionPlayer_IMPEndFiring(SithCog* pCog)
{
    int fireType;

    fireType = sithCogExec_PopInt(pCog);
    sithPlayer_IMPEndFiring(fireType);
}

void J3DAPI sithCogFunctionPlayer_SetPlayerInPor(SithCog* pCog)
{
    sithPlayer_g_bPlayerInPor = sithCogExec_PopInt(pCog);
}

void J3DAPI sithCogFunctionPlayer_JewelFlyingStatus(SithCog* pCog)
{
    SithThing* pPlasma;

    pPlasma = sithCogExec_PopThing(pCog);
    if ( sithCogExec_PopInt(pCog) )
    {
        sithPlayerActions_EnableJewelFlying(pPlasma);
    }

    else if ( sithPlayer_g_pLocalPlayerThing )  // end flaying
    {
        if ( sithPlayer_g_pLocalPlayerThing->moveStatus != SITHPLAYERMOVE_JEWELFLYING )
        {
            sithPlayerActions_DisableJewelFlying();
        }
    }
}

void J3DAPI sithCogFunctionPlayer_StartJewelFlying(SithCog* pCog)
{
    int started;

    started = sithPlayerActions_StartJewelFlying();
    sithCogExec_PushInt(pCog, started);
}

void J3DAPI sithCogFunctionPlayer_MakeMeStop(SithCog* pCog)
{
    SithThing* pPlayerThing;
    int guid;

    pPlayerThing = sithPlayer_g_pLocalPlayerThing;
    if ( !sithPlayer_g_pLocalPlayerThing
        || (sithPlayer_g_pLocalPlayerThing->moveInfo.physics.flags & (SITH_PF_JEEP | SITH_PF_RAFT | SITH_PF_MINECAR)) != 0 )
    {
    LABEL_7:
        sithCogExec_PushInt(pCog, -1);
    }
    else
    {
        guid = sithPlayer_g_pLocalPlayerThing->guid;
        switch ( sithPlayer_g_pLocalPlayerThing->moveStatus )
        {
            case SITHPLAYERMOVE_STILL:
            case SITHPLAYERMOVE_WALKING:
            case SITHPLAYERMOVE_RUNNING:
                sithPhysics_ResetThingMovement(sithPlayer_g_pLocalPlayerThing);
                pPlayerThing->moveStatus = SITHPLAYERMOVE_STILL;
                break;

            case SITHPLAYERMOVE_CRAWL_STILL:
            case SITHPLAYERMOVE_UNKNOWN_4:
            case SITHPLAYERMOVE_UNKNOWN_5:
                sithPlayerActions_Crawl2Stand(sithPlayer_g_pLocalPlayerThing);
                break;

            case SITHPLAYERMOVE_HANGING:
            case SITHPLAYERMOVE_CLIMBIDLE:
            case SITHPLAYERMOVE_SWIMIDLE:
            case SITHPLAYERMOVE_JEEP_IMPACT:
            case SITHPLAYERMOVE_CLIMBING_UP:
            case SITHPLAYERMOVE_CLIMBING_DOWN:
            case SITHPLAYERMOVE_CLIMBING_LEFT:
            case SITHPLAYERMOVE_CLIMBING_RIGHT:
                goto LABEL_7;

            default:
                break;
        }

        pPlayerThing->thingInfo.actorInfo.flags |= SITH_AF_CONTROLSDISABLED;
        pCog->status = SITHCOG_STATUS_WAITING_PLAYER_TO_STOP;
        pCog->statusParams[0] = guid;
        sithCogExec_PushInt(pCog, guid);
    }
}

void J3DAPI sithCogFunctionPlayer_SetInvActivated(SithCog* pCog)
{
    int bActivated;
    int typeId;
    SithThing* pThing;

    bActivated = sithCogExec_PopInt(pCog);
    typeId = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing || pThing->type != SITH_THING_PLAYER || !pThing->thingInfo.actorInfo.pPlayer )
    {
        STDLOG_ERROR("Cog %s: Invalid thing in SetInvActivated.\n",
            pCog->aName);
    }

    else if ( typeId >= 200 )
    {
        STDLOG_ERROR("Cog %s: Invalid inventory id in SetInvActivated.\n",
            pCog->aName);
    }

    else if ( bActivated )
    {
        sithInventory_SetInventoryActivated(pThing, typeId, 1);
    }
    else
    {
        sithInventory_SetInventoryActivated(pThing, typeId, 0);
    }
}

void J3DAPI sithCogFunctionPlayer_SetInvAvailable(SithCog* pCog)
{
    int bAvailable;
    int typeId;
    SithThing* pThing;

    bAvailable = sithCogExec_PopInt(pCog);
    typeId = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing || pThing->type != SITH_THING_PLAYER || !pThing->thingInfo.actorInfo.pPlayer )
    {
        STDLOG_ERROR("Cog %s: Invalid thing in SetInvAvailable.\n",
            pCog->aName);
    }

    else if ( typeId >= 200 )
    {
        STDLOG_ERROR("Cog %s: Invalid inventory id in SetInvAvailable.\n",
            pCog->aName);
    }

    else if ( bAvailable )
    {
        sithInventory_SetInventoryAvailable(pThing, typeId, 1);
    }
    else
    {
        sithInventory_SetInventoryAvailable(pThing, typeId, 0);
    }
}

void J3DAPI sithCogFunctionPlayer_SetInvDisabled(SithCog* pCog)
{
    int bDisabled;
    int typeId;
    SithThing* pThing;

    bDisabled = sithCogExec_PopInt(pCog);
    typeId = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing || pThing->type != SITH_THING_PLAYER )
    {
        STDLOG_ERROR("Cog %s: Bad thing in SetInvDisabled().\n",
            pCog->aName);
    }

    else if ( typeId >= 200 )
    {
        STDLOG_ERROR("Cog %s: Bad inventory ID in SetInvDisabled().\n",
            pCog->aName);
    }
    else
    {
        sithInventory_SetInventoryDisabled(pThing, typeId, bDisabled);
    }
}

void J3DAPI sithCogFunctionPlayer_IsInvActivated(SithCog* pCog)
{
    int bin;
    SithThing* pThing;

    bin = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing || pThing->type != SITH_THING_PLAYER || !pThing->thingInfo.actorInfo.pPlayer )
    {
        STDLOG_ERROR("Cog %s: Invalid thing in IsInvActivated.\n",
            pCog->aName);
    }

    else if ( bin >= 200 )
    {
        STDLOG_ERROR("Cog %s: Invalid inventory id in IsInvActivated.\n",
            pCog->aName);
    }

    else if ( sithInventory_IsInventoryActivated(pThing, bin) )
    {
        sithCogExec_PushInt(pCog, 1);
    }
    else
    {
        sithCogExec_PushInt(pCog, 0);
    }
}

void J3DAPI sithCogFunctionPlayer_IsInvAvailable(SithCog* pCog)
{
    int typeId;
    SithThing* pThing;

    typeId = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing || pThing->type != SITH_THING_PLAYER || !pThing->thingInfo.actorInfo.pPlayer )
    {
        STDLOG_ERROR("Cog %s: Invalid thing in IsInvAvailable.\n",
            pCog->aName);
    }

    else if ( typeId >= 200 )
    {
        STDLOG_ERROR("Cog %s: Invalid inventory id in IsInvAvailable.\n",
            pCog->aName);
    }

    else if ( sithInventory_IsInventoryAvailable(pThing, typeId) )
    {
        sithCogExec_PushInt(pCog, 1);
    }
    else
    {
        sithCogExec_PushInt(pCog, 0);
    }
}

void J3DAPI sithCogFunctionPlayer_SetGoalFlags(SithCog* pCog)
{
    int flags;
    int bin;
    SithThing* pThing;
    float amount;

    flags = sithCogExec_PopInt(pCog);
    bin = sithCogExec_PopInt(pCog) + 100;
    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing || pThing->type != SITH_THING_PLAYER || !pThing->thingInfo.actorInfo.pPlayer )
    {
        STDLOG_ERROR("Cog %s: Invalid thing in SetGoalFlags.\n",
            pCog->aName);
    }

    else if ( bin >= 200 )
    {
        STDLOG_ERROR("Cog %s: Invalid inventory bin in SetGoalFlags.\n",
            pCog->aName);
    }
    else
    {
        amount = (float)((__int64)sithInventory_GetInventory(pThing, bin) | flags);
        sithInventory_SetInventory(pThing, bin, amount);
    }
}

void J3DAPI sithCogFunctionPlayer_ClearGoalFlags(SithCog* pCog)
{
    int flags;
    int bin;
    SithThing* pThing;
    float amount;

    flags = sithCogExec_PopInt(pCog);
    bin = sithCogExec_PopInt(pCog) + 100;
    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing || pThing->type != SITH_THING_PLAYER || !pThing->thingInfo.actorInfo.pPlayer )
    {
        STDLOG_ERROR("Cog %s: Invalid thing in ClearGoalFlags.\n",
            pCog->aName);
    }

    else if ( bin >= 200 )
    {
        STDLOG_ERROR("Cog %s: Invalid inventory bin in ClearGoalFlags.\n",
            pCog->aName);
    }
    else
    {
        amount = (float)((__int64)sithInventory_GetInventory(pThing, bin) & ~flags);
        sithInventory_SetInventory(pThing, bin, amount);
    }
}

void J3DAPI sithCogFunctionPlayer_GetNumPlayers(SithCog* pCog)
{
    size_t numTotalPlayers;
    int numPlayers;
    SithPlayer* pPlayer;

    numTotalPlayers = sithPlayer_g_numPlayers;
    numPlayers = 0;
    if ( sithPlayer_g_numPlayers )
    {
        pPlayer = (SithPlayer*)&sithPlayer_g_aPlayers[0].flags;// TODO: fix offsets
        do
        {
            if ( (CONTAINING_RECORD(pPlayer, SithPlayer, flags)->flags & SITH_PLAYER_JOINEDGAME) != 0 )
            {
                ++numPlayers;
            }

            ++pPlayer;
            --numTotalPlayers;
        } while ( numTotalPlayers );
    }

    sithCogExec_PushInt(pCog, numPlayers);
}

void J3DAPI sithCogFunctionPlayer_GetMaxPlayers(SithCog* pCog)
{
    sithCogExec_PushInt(pCog, sithPlayer_g_numPlayers);
}

void J3DAPI sithCogFunctionPlayer_GetAbsoluteMaxPlayers(SithCog* pCog)
{
    sithCogExec_PushInt(pCog, SITHPLAYER_MAX_PLAYERS);
}

void J3DAPI sithCogFunctionPlayer_GetLocalPlayerThing(SithCog* pCog)
{
    if ( sithPlayer_g_pLocalPlayerThing )
    {
        sithCogExec_PushInt(pCog, sithPlayer_g_pLocalPlayerThing->idx);
    }
    else
    {
        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionPlayer_GetPlayerThing(SithCog* pCog)
{
    unsigned int playerNum;

    playerNum = sithCogExec_PopInt(pCog);
    if ( playerNum >= sithPlayer_g_numPlayers )
    {
        STDLOG_ERROR("Cog %s: Invalid player num in GetPlayerThing.\n",
            pCog->aName);

        sithCogExec_PushInt(pCog, -1);
    }
    else
    {
        sithCogExec_PushInt(pCog, sithPlayer_g_aPlayers[playerNum].pThing->idx);
    }
}

void J3DAPI sithCogFunctionPlayer_GetPlayerNum(SithCog* pCog)
{
    SithThing* pThing;
    int playerNum;

    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing || pThing->type != SITH_THING_PLAYER )
    {
        STDLOG_ERROR("Cog %s: Invalid thing in GetPlayerNum.\n",
            pCog->aName);
    }
    else
    {
        playerNum = sithPlayer_GetThingPlayerNum(pThing);
        if ( playerNum != -1 )
        {
            sithCogExec_PushInt(pCog, playerNum);
            return;
        }

        STDLOG_ERROR("Cog %s: Invalid player in GetPlayerNum.\n",
            pCog->aName);
    }

    sithCogExec_PushInt(pCog, -1);
}

void J3DAPI sithCogFunctionPlayer_PickupBackpack(SithCog* pCog)
{
    SithThing* pBackpack;
    SithThing* pThing;

    pBackpack = sithCogExec_PopThing(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing || pThing->type != SITH_THING_PLAYER || !pThing->thingInfo.actorInfo.pPlayer )
    {
        STDLOG_ERROR("Cog %s: Invalid player in PickupBackpack.\n",
            pCog->aName);
    }

    else if ( !pBackpack
        || pBackpack->type != SITH_THING_ITEM
        || (pBackpack->thingInfo.itemInfo.flags & SITH_ITEM_BACKPACK) == 0 )
    {
        STDLOG_ERROR("Cog %s: Invalid backpack in PickupBackpack.\n",
            pCog->aName);
    }
    else
    {
        sithInventory_PickupBackpack(pThing, pBackpack);
    }
}

void J3DAPI sithCogFunctionPlayer_NthBackpackBin(SithCog* pCog)
{
    int itemNum;
    SithThing* pThing;
    int itemID;

    itemNum = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing || pThing->type != SITH_THING_ITEM || (pThing->thingInfo.itemInfo.flags & SITH_ITEM_BACKPACK) == 0 )
    {
        STDLOG_ERROR("Cog %s: Invalid backpack in NthBackpackBin.\n",
            pCog->aName);
    }
    else
    {
        itemID = sithInventory_GetBackpackItemID(pThing, itemNum);
        sithCogExec_PushInt(pCog, itemID);
    }
}

void J3DAPI sithCogFunctionPlayer_NthBackpackValue(SithCog* pCog)
{
    int itemId;
    SithThing* pThing;
    float itemID;

    itemId = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing || pThing->type != SITH_THING_ITEM || (pThing->thingInfo.itemInfo.flags & SITH_ITEM_BACKPACK) == 0 )
    {
        STDLOG_ERROR("Cog %s: Invalid backpack in NthBackpackBin.\n",
            pCog->aName);
    }
    else
    {
        itemID = sithInventory_GetBackpackItemValue(pThing, itemId);
        sithCogExec_PushFlex(pCog, itemID);
    }
}

void J3DAPI sithCogFunctionPlayer_GetNumBackbackItems(SithCog* pCog)
{
    SithThing* pThing;
    int numItems;

    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing || pThing->type != SITH_THING_ITEM || (pThing->thingInfo.itemInfo.flags & SITH_ITEM_BACKPACK) == 0 )
    {
        STDLOG_ERROR("Cog %s: Invalid backpack in NthBackpackBin.\n",
            pCog->aName);
    }
    else
    {
        numItems = sithInventory_GetNumBackpackItems(pThing);
        sithCogExec_PushInt(pCog, numItems);
    }
}

void J3DAPI sithCogFunctionPlayer_CreateBackpack(SithCog* pCog)
{
    SithThing* pThing;
    SithThing* pBackpack;

    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing || pThing->type != SITH_THING_PLAYER || !pThing->thingInfo.actorInfo.pPlayer )
    {
        STDLOG_ERROR("Cog %s: Invalid player in CreateBackpack.\n",
            pCog->aName);
    }
    else
    {
        pBackpack = sithInventory_CreateBackpack(pThing);
        if ( !pBackpack )
        {
            STDLOG_ERROR("Cog %s: Invalid backpack in CreateBackpack.\n",
                pCog->aName);
            sithCogExec_PushInt(pCog, -1);
        }
        else
        {
            sithCogExec_PushInt(pCog, pBackpack->idx);
        }
    }
}

void J3DAPI sithCogFunctionPlayer_GetRespawnMask(SithCog* pCog)
{
    SithThing* pThing;
    SithPlayer* pPlayer;

    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing || pThing->type != SITH_THING_PLAYER || (pPlayer = pThing->thingInfo.actorInfo.pPlayer) == 0 )
    {
        STDLOG_ERROR("Cog %s: Invalid player thing in GetRespawnMask.\n",
            pCog->aName);

        sithCogExec_PushInt(pCog, -1);
    }
    else
    {
        sithCogExec_PushInt(pCog, pPlayer->respawnMask);
    }
}

void J3DAPI sithCogFunctionPlayer_SetRespawnMask(SithCog* pCog)
{
    int mask;
    SithThing* pThing;
    SithPlayer* pPlayer;

    mask = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing || pThing->type != SITH_THING_PLAYER || (pPlayer = pThing->thingInfo.actorInfo.pPlayer) == 0 )
    {
        STDLOG_ERROR("Cog %s: Invalid player thing in SetRespawnMask.\n",
            pCog->aName);
    }
    else
    {
        pPlayer->respawnMask = mask;
    }
}

void J3DAPI sithCogFunctionPlayer_SyncScores(SithCog* pCog)
{
    if ( stdComm_IsGameActive() )
    {
        sithMulti_SyncScores();
    }
}

void J3DAPI sithCogFunctionPlayer_GetCurItem(SithCog* pCog)
{
    SithThing* pThing;
    int itemID;

    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing || pThing->type != SITH_THING_PLAYER || !pThing->thingInfo.actorInfo.pPlayer )
    {
        STDLOG_ERROR("Cog %s: Invalid player THING in GetCurItem().\n",
            pCog->aName);

        sithCogExec_PushInt(pCog, -1);
    }
    else
    {
        itemID = sithInventory_GetCurrentItem(pThing);
        sithCogExec_PushInt(pCog, itemID);
    }
}

void J3DAPI sithCogFunctionPlayer_IsAming(SithCog* pCog)
{
    SithThing* pThing;
    SithThingType type;

    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing || (type = pThing->type, type != SITH_THING_ACTOR) && type != SITH_THING_PLAYER )
    {
        STDLOG_ERROR("Cog %s: Invalid THING passed to IsAiming().\n",
            pCog->aName);
    }

    else if ( sithWeapon_IsAiming(pThing) )
    {
        sithCogExec_PushInt(pCog, 1);
        return;
    }

    sithCogExec_PushInt(pCog, 0);
}

void J3DAPI sithCogFunctionPlayer_SetSwimmingInventory(SithCog* pCog)
{
    int bItemsAvailable;
    SithThing* pThing;

    bItemsAvailable = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing || pThing->type != SITH_THING_PLAYER )
    {
        SITH_ASSERTREL((pThing != ((void*)0)) && (pThing->type == SITH_THING_PLAYER));
    }

    sithInventory_SetSwimmingInventory(pThing, bItemsAvailable);

    if ( !bItemsAvailable )
    {
        sithInventory_SetInventoryDisabled(pThing, 7u, 0);
        sithInventory_SetInventoryDisabled(pThing, 93u, 0);
        sithInventory_SetInventoryDisabled(pThing, 94u, 0);
    }
}

void J3DAPI sithCogFunctionPlayer_IsInvisible(SithCog* pCog)
{
    if ( sithPlayerActions_IsInvisible() )
    {
        sithCogExec_PushInt(pCog, 1);
    }
    else
    {
        sithCogExec_PushInt(pCog, 0);
    }
}

void J3DAPI sithCogFunctionPlayer_ResetInventory(SithCog* pCog)
{
    SithThing* pThing;
    SithInventoryItem* aItems;
    SithInventoryItem* pItem;
    SithWeaponId i;

    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing || pThing->type != SITH_THING_PLAYER )
    {
        STDLOG_ERROR("Cog %s: Invalid player thing in ResetInventory().\n",
            pCog->aName);
    }
    else
    {
        sithInventory_InitInventory(pThing);
        sithThing_ResetSwapList(pThing);
        aItems = pThing->thingInfo.actorInfo.pPlayer->aItems;
        if ( pThing->thingInfo.actorInfo.pPlayer != (SithPlayer*)~0x87 )// pThing->thingInfo.actorInfo.pPlayer->aItems != NULL ??
        {
            for ( i = SITHWEAPON_WHIP; i < SITHWEAPON_ZIPPO; ++i )
            {
                pItem = &aItems[i];
                if ( pItem )
                {
                    pItem->status &= ~SITHINVENTORY_ITEM_FOUND;
                }
            }
        }
    }
}

void J3DAPI sithCogFunctionPlayer_IsItemFound(SithCog* pCog)
{
    int itemID;
    SithInventoryItem* pItem;

    itemID = sithCogExec_PopInt(pCog);
    if ( sithPlayer_g_pLocalPlayerThing )
    {
        if ( sithPlayer_g_pLocalPlayerThing->thingInfo.actorInfo.pPlayer != (SithPlayer*)-136 )// TODO: point to ->aItems member
        {
            pItem = &sithPlayer_g_pLocalPlayerThing->thingInfo.actorInfo.pPlayer->aItems[itemID];
            if ( pItem )
            {
                if ( (pItem->status & SITHINVENTORY_ITEM_FOUND) != 0 )
                {
                    sithCogExec_PushInt(pCog, 1);
                }
                else
                {
                    sithCogExec_PushInt(pCog, 0);
                }
            }
        }
    }
}

void J3DAPI sithCogFunctionPlayer_SetElectricWhip(SithCog* pCog)
{
    int bElectrict;
    int aflags;
    rdMaterial* pMat;

    bElectrict = sithCogExec_PopInt(pCog);
    if ( sithPlayer_g_pLocalPlayerThing )
    {
        aflags = sithPlayer_g_pLocalPlayerThing->thingInfo.actorInfo.flags;
        if ( bElectrict )
        {
            aflags |= SITH_AF_ELECTRICWHIP;
        }
        else
        {
            aflags &= ~SITH_AF_ELECTRICWHIP;
        }

        sithPlayer_g_pLocalPlayerThing->thingInfo.actorInfo.flags = aflags;
    }

    pMat = sithMaterial_GetMaterialByIndex(0x8146);// 0x8000 is SITH_STATICRESOURCE_INDEXMASK
    if ( pMat )
    {
        pMat->curCelNum = bElectrict;           // 0 - regular, 1 - elect , what happens if the num is out of bound ? :)
    }
}

void J3DAPI sithCogFunctionPlayer_GetCutsceneMode(SithCog* pCog)
{
    if ( sithPlayerControls_g_bCutsceneMode == 1 )
    {
        sithCogExec_PushInt(pCog, 1);
    }
    else
    {
        sithCogExec_PushInt(pCog, 0);
    }
}

void J3DAPI sithCogFunctionPlayer_GetLastWeapon(SithCog* pCog)
{
    int weaponID;

    weaponID = sithWeapon_GetLastWeapon();
    sithCogExec_PushInt(pCog, weaponID);
}
