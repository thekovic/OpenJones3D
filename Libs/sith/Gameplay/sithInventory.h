#ifndef SITH_SITHINVENTORY_H
#define SITH_SITHINVENTORY_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define sithInventory_g_bResetInventory J3D_DECL_FAR_VAR(sithInventory_g_bResetInventory, int)
// extern int sithInventory_g_bResetInventory ;

#define sithInventory_g_dword_56B74C J3D_DECL_FAR_VAR(sithInventory_g_dword_56B74C, int)
// extern int sithInventory_g_dword_56B74C;

#define sithInventory_g_dword_56B750 J3D_DECL_FAR_VAR(sithInventory_g_dword_56B750, int)
// extern int sithInventory_g_dword_56B750;

#define sithInventory_g_dword_56B754 J3D_DECL_FAR_VAR(sithInventory_g_dword_56B754, int)
// extern int sithInventory_g_dword_56B754;

#define sithInventory_g_aTypes J3D_DECL_FAR_ARRAYVAR(sithInventory_g_aTypes, SithInventoryType(*)[200])
// extern SithInventoryType sithInventory_g_aTypes[200];

void J3DAPI sithInventory_RegisterType(unsigned int typeId, const char* pName, float min, float max, SithInventoryTypeFlag flags, SithCog* pItemCog, rdModel3* pInvModel, rdModel3* pItemModel);
int J3DAPI sithInventory_FindNextItem(SithThing* pThing, signed int startSearchId, SithInventoryTypeFlag flags);
int J3DAPI sithInventory_FindPreviousItem(SithThing* pThing, int startSearchId, SithInventoryTypeFlag flags);
SithInventoryType* J3DAPI sithInventory_GetType(int typeId);
int J3DAPI sithInventory_GetCurrentWeapon(const SithThing* pThing);
void J3DAPI sithInventory_SetCurrentWeapon(SithThing* pThing, SithWeaponId weaponID);
int J3DAPI sithInventory_GetCurrentItem(SithThing* pThing);
void J3DAPI sithInventory_SetCurrentItem(SithThing* pThing, int typeId);
float J3DAPI sithInventory_ChangeInventory(SithThing* pThing, int typeId, float amount);
float J3DAPI sithInventory_GetInventory(SithThing* pThing, int typeId);
float J3DAPI sithInventory_SetInventory(SithThing* pThing, int typeId, float amount);
void J3DAPI sithInventory_SetActivated(SithThing* pThing, unsigned int typeId, int bActivated);
int J3DAPI sithInventory_IsActivated(SithThing* pThing, unsigned int typeId);
void J3DAPI sithInventory_SetAvailable(SithThing* pThing, unsigned int typeId, int bAvailable);
int J3DAPI sithInventory_IsInventoryAvailable(const SithThing* pThing, unsigned int typeId);
void J3DAPI sithInventory_SetDisabled(SithThing* pThing, unsigned int typeId, int bDisabled);
BOOL J3DAPI sithInventory_IsBackpackItem(SithThing* pThing, int typeId);
int J3DAPI sithInventory_IsWeapon(unsigned int typeID);
double J3DAPI sithInventory_GetInventoryMinimum(SithThing* pThing, unsigned int id);
double J3DAPI sithInventory_GetInventoryMaximum(SithThing* pThin, unsigned int id);
void J3DAPI sithInventory_SetInventoryFlags(SithThing* pThing, unsigned int id, SithInventoryTypeFlag flags);
float J3DAPI sithInventory_SendMessage(SithThing* pThing, SithCogSymbolRefType srcType, int srcIdx, SithCogMsgType messageType, SithInventoryTypeFlag flags, float param0, int param1, int param2, int param3);
void J3DAPI sithInventory_Reset(SithThing* pThing);
SithThing* J3DAPI sithInventory_CreateBackpack(SithThing* pThing);
void J3DAPI sithInventory_PickupBackpack(SithThing* pPlayerThing, SithThing* pBackpackThing);
int J3DAPI sithInventory_GetBackpackItem(SithThing* pBackpackThing, int itemNum);
float J3DAPI sithInventory_GetBackpackItemValue(SithThing* pBackpackThing, signed int itemNum);
int J3DAPI sithInventory_GetNumBackpackItems(SithThing* pThing);
SithInventoryType* J3DAPI sithInventory_GetInventoryType(SithThing* pThing, unsigned int typeId);
void J3DAPI sithInventory_ResetInventory(SithThing* pThing);
void J3DAPI sithInventory_SendKilledMessage(const SithThing* pSender, const SithThing* pKiller);
void J3DAPI sithInventory_SetSwimmingInventory(SithThing* pThing, int bItemsAvailable);

// Helper hooking functions
void sithInventory_InstallHooks(void);
void sithInventory_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHINVENTORY_H
