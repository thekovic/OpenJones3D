#include "sithInventory.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>


void sithInventory_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithInventory_RegisterType);
    // J3D_HOOKFUNC(sithInventory_FindNextItem);
    // J3D_HOOKFUNC(sithInventory_FindPreviousItem);
    // J3D_HOOKFUNC(sithInventory_GetType);
    // J3D_HOOKFUNC(sithInventory_GetCurrentWeapon);
    // J3D_HOOKFUNC(sithInventory_SetCurrentWeapon);
    // J3D_HOOKFUNC(sithInventory_GetCurrentItem);
    // J3D_HOOKFUNC(sithInventory_SetCurrentItem);
    // J3D_HOOKFUNC(sithInventory_ChangeInventory);
    // J3D_HOOKFUNC(sithInventory_GetInventory);
    // J3D_HOOKFUNC(sithInventory_SetInventory);
    // J3D_HOOKFUNC(sithInventory_SetActivated);
    // J3D_HOOKFUNC(sithInventory_IsActivated);
    // J3D_HOOKFUNC(sithInventory_SetAvailable);
    // J3D_HOOKFUNC(sithInventory_IsInventoryAvailable);
    // J3D_HOOKFUNC(sithInventory_SetDisabled);
    // J3D_HOOKFUNC(sithInventory_IsBackpackItem);
    // J3D_HOOKFUNC(sithInventory_IsWeapon);
    // J3D_HOOKFUNC(sithInventory_GetInventoryMinimum);
    // J3D_HOOKFUNC(sithInventory_GetInventoryMaximum);
    // J3D_HOOKFUNC(sithInventory_SetInventoryFlags);
    // J3D_HOOKFUNC(sithInventory_SendMessage);
    // J3D_HOOKFUNC(sithInventory_Reset);
    // J3D_HOOKFUNC(sithInventory_CreateBackpack);
    // J3D_HOOKFUNC(sithInventory_PickupBackpack);
    // J3D_HOOKFUNC(sithInventory_GetBackpackItem);
    // J3D_HOOKFUNC(sithInventory_GetBackpackItemValue);
    // J3D_HOOKFUNC(sithInventory_GetNumBackpackItems);
    // J3D_HOOKFUNC(sithInventory_GetInventoryType);
    // J3D_HOOKFUNC(sithInventory_ResetInventory);
    // J3D_HOOKFUNC(sithInventory_SendKilledMessage);
    // J3D_HOOKFUNC(sithInventory_SetSwimmingInventory);
}

void sithInventory_ResetGlobals(void)
{
    int sithInventory_g_bResetInventory_tmp = 1;
    memcpy(&sithInventory_g_bResetInventory, &sithInventory_g_bResetInventory_tmp, sizeof(sithInventory_g_bResetInventory));
    
    memset(&sithInventory_g_dword_56B74C, 0, sizeof(sithInventory_g_dword_56B74C));
    memset(&sithInventory_g_dword_56B750, 0, sizeof(sithInventory_g_dword_56B750));
    memset(&sithInventory_g_dword_56B754, 0, sizeof(sithInventory_g_dword_56B754));
    memset(&sithInventory_g_aTypes, 0, sizeof(sithInventory_g_aTypes));
}

void J3DAPI sithInventory_RegisterType(unsigned int typeId, const char* pName, float min, float max, SithInventoryTypeFlag flags, SithCog* pItemCog, rdModel3* pInvModel, rdModel3* pItemModel)
{
    J3D_TRAMPOLINE_CALL(sithInventory_RegisterType, typeId, pName, min, max, flags, pItemCog, pInvModel, pItemModel);
}

int J3DAPI sithInventory_FindNextItem(SithThing* pThing, signed int startSearchId, SithInventoryTypeFlag flags)
{
    return J3D_TRAMPOLINE_CALL(sithInventory_FindNextItem, pThing, startSearchId, flags);
}

int J3DAPI sithInventory_FindPreviousItem(SithThing* pThing, int startSearchId, SithInventoryTypeFlag flags)
{
    return J3D_TRAMPOLINE_CALL(sithInventory_FindPreviousItem, pThing, startSearchId, flags);
}

SithInventoryType* J3DAPI sithInventory_GetType(int typeId)
{
    return J3D_TRAMPOLINE_CALL(sithInventory_GetType, typeId);
}

int J3DAPI sithInventory_GetCurrentWeapon(const SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithInventory_GetCurrentWeapon, pThing);
}

void J3DAPI sithInventory_SetCurrentWeapon(SithThing* pThing, SithWeaponId weaponID)
{
    J3D_TRAMPOLINE_CALL(sithInventory_SetCurrentWeapon, pThing, weaponID);
}

int J3DAPI sithInventory_GetCurrentItem(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithInventory_GetCurrentItem, pThing);
}

void J3DAPI sithInventory_SetCurrentItem(SithThing* pThing, int typeId)
{
    J3D_TRAMPOLINE_CALL(sithInventory_SetCurrentItem, pThing, typeId);
}

float J3DAPI sithInventory_ChangeInventory(SithThing* pThing, int typeId, float amount)
{
    return J3D_TRAMPOLINE_CALL(sithInventory_ChangeInventory, pThing, typeId, amount);
}

float J3DAPI sithInventory_GetInventory(SithThing* pThing, int typeId)
{
    return J3D_TRAMPOLINE_CALL(sithInventory_GetInventory, pThing, typeId);
}

float J3DAPI sithInventory_SetInventory(SithThing* pThing, int typeId, float amount)
{
    return J3D_TRAMPOLINE_CALL(sithInventory_SetInventory, pThing, typeId, amount);
}

void J3DAPI sithInventory_SetActivated(SithThing* pThing, unsigned int typeId, int bActivated)
{
    J3D_TRAMPOLINE_CALL(sithInventory_SetActivated, pThing, typeId, bActivated);
}

int J3DAPI sithInventory_IsActivated(SithThing* pThing, unsigned int typeId)
{
    return J3D_TRAMPOLINE_CALL(sithInventory_IsActivated, pThing, typeId);
}

void J3DAPI sithInventory_SetAvailable(SithThing* pThing, unsigned int typeId, int bAvailable)
{
    J3D_TRAMPOLINE_CALL(sithInventory_SetAvailable, pThing, typeId, bAvailable);
}

int J3DAPI sithInventory_IsInventoryAvailable(const SithThing* pThing, unsigned int typeId)
{
    return J3D_TRAMPOLINE_CALL(sithInventory_IsInventoryAvailable, pThing, typeId);
}

void J3DAPI sithInventory_SetDisabled(SithThing* pThing, unsigned int typeId, int bDisabled)
{
    J3D_TRAMPOLINE_CALL(sithInventory_SetDisabled, pThing, typeId, bDisabled);
}

BOOL J3DAPI sithInventory_IsBackpackItem(SithThing* pThing, int typeId)
{
    return J3D_TRAMPOLINE_CALL(sithInventory_IsBackpackItem, pThing, typeId);
}

int J3DAPI sithInventory_IsWeapon(unsigned int typeID)
{
    return J3D_TRAMPOLINE_CALL(sithInventory_IsWeapon, typeID);
}

double J3DAPI sithInventory_GetInventoryMinimum(SithThing* pThing, unsigned int id)
{
    return J3D_TRAMPOLINE_CALL(sithInventory_GetInventoryMinimum, pThing, id);
}

double J3DAPI sithInventory_GetInventoryMaximum(SithThing* pThin, unsigned int id)
{
    return J3D_TRAMPOLINE_CALL(sithInventory_GetInventoryMaximum, pThin, id);
}

void J3DAPI sithInventory_SetInventoryFlags(SithThing* pThing, unsigned int id, SithInventoryTypeFlag flags)
{
    J3D_TRAMPOLINE_CALL(sithInventory_SetInventoryFlags, pThing, id, flags);
}

float J3DAPI sithInventory_SendMessage(SithThing* pThing, SithCogSymbolRefType srcType, int srcIdx, SithCogMsgType messageType, SithInventoryTypeFlag flags, float param0, int param1, int param2, int param3)
{
    return J3D_TRAMPOLINE_CALL(sithInventory_SendMessage, pThing, srcType, srcIdx, messageType, flags, param0, param1, param2, param3);
}

void J3DAPI sithInventory_Reset(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithInventory_Reset, pThing);
}

SithThing* J3DAPI sithInventory_CreateBackpack(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithInventory_CreateBackpack, pThing);
}

void J3DAPI sithInventory_PickupBackpack(SithThing* pPlayerThing, SithThing* pBackpackThing)
{
    J3D_TRAMPOLINE_CALL(sithInventory_PickupBackpack, pPlayerThing, pBackpackThing);
}

int J3DAPI sithInventory_GetBackpackItem(SithThing* pBackpackThing, int itemNum)
{
    return J3D_TRAMPOLINE_CALL(sithInventory_GetBackpackItem, pBackpackThing, itemNum);
}

float J3DAPI sithInventory_GetBackpackItemValue(SithThing* pBackpackThing, signed int itemNum)
{
    return J3D_TRAMPOLINE_CALL(sithInventory_GetBackpackItemValue, pBackpackThing, itemNum);
}

int J3DAPI sithInventory_GetNumBackpackItems(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithInventory_GetNumBackpackItems, pThing);
}

SithInventoryType* J3DAPI sithInventory_GetInventoryType(SithThing* pThing, unsigned int typeId)
{
    return J3D_TRAMPOLINE_CALL(sithInventory_GetInventoryType, pThing, typeId);
}

void J3DAPI sithInventory_ResetInventory(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithInventory_ResetInventory, pThing);
}

void J3DAPI sithInventory_SendKilledMessage(const SithThing* pSender, const SithThing* pKiller)
{
    J3D_TRAMPOLINE_CALL(sithInventory_SendKilledMessage, pSender, pKiller);
}

void J3DAPI sithInventory_SetSwimmingInventory(SithThing* pThing, int bItemsAvailable)
{
    J3D_TRAMPOLINE_CALL(sithInventory_SetSwimmingInventory, pThing, bItemsAvailable);
}
