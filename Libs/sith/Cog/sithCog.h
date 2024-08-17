#ifndef SITH_SITHCOG_H
#define SITH_SITHCOG_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define sithCog_g_bCogStartup J3D_DECL_FAR_VAR(sithCog_g_bCogStartup, int)
// extern int sithCog_g_bCogStartup;

#define sithCog_g_pHashtable J3D_DECL_FAR_VAR(sithCog_g_pHashtable, tHashTable*)
// extern tHashTable *sithCog_g_pHashtable;

#define sithCog_g_pSymbolTable J3D_DECL_FAR_VAR(sithCog_g_pSymbolTable, SithCogSymbolTable*)
// extern SithCogSymbolTable *sithCog_g_pSymbolTable;

#define sithCog_g_pMasterCog J3D_DECL_FAR_VAR(sithCog_g_pMasterCog, SithCog*)
// extern SithCog *sithCog_g_pMasterCog;

int sithCog_Startup(void);
void J3DAPI sithCog_Shutdown();
// On error 1 is returned otherwise 0
int J3DAPI sithCog_Open(SithWorld* pWorld);
void J3DAPI sithCog_Close();
void J3DAPI sithCog_FreeWorldCogs(SithWorld* pWorld);
void J3DAPI sithCog_FreeScriptEntry(SithCogScript* pScript);
void J3DAPI sithCog_FreeEntry(SithCog* pCog);
void J3DAPI sithCog_UpdateThingTimer(SithThing* pThing);
void J3DAPI sithCog_BroadcastMessage(SithCogMsgType msgType, SithCogSymbolRefType senderType, int senderIdx, SithCogSymbolRefType srcType, int srcIdx);
void J3DAPI sithCog_BroadcastMessageEx(SithCogMsgType msgType, SithCogSymbolRefType senderType, int senderIdx, SithCogSymbolRefType srcType, int srcIdx, int param0, int param1, int param2, int param3);
void J3DAPI sithCog_SendMessage(SithCog* pCog, SithCogMsgType messageType, SithCogSymbolRefType senderType, int senderIdx, SithCogSymbolRefType srcType, int srcIdx, int linkId);
// return value '-9999' indicates that the message  was processed.
// Same value is returned when COG is paused or message handler for the type doesn't exist. 
// In this case no message is sent further to COG
int J3DAPI sithCog_SendMessageEx(SithCog* pCog, SithCogMsgType messageType, SithCogSymbolRefType senderType, int senderIdx, SithCogSymbolRefType srcType, int srcIdx, int linkId, int param0, int param1, int param2, int param3);
int J3DAPI sithCog_AllocWorldCogScripts(SithWorld* pWorld, int numCogScripts);
int J3DAPI sithCog_AllocWorldCogs(SithWorld* pWorld, int sizeCogs);
int J3DAPI sithCog_GetSymbolRefInitializer(const SithWorld* pWorld, const SithCog* pCog, int symIdx, char* pOutString);
int J3DAPI sithCog_NDYReadCOGSection(SithWorld* pWorld, int bSkip);
int J3DAPI sithCog_CNDWriteCOGSection(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithCog_CNDReadCOGSection(tFileHandle fh, SithWorld* pWorld);
// On success 0 is returned and 1 on error
int J3DAPI sithCog_ParseSymbolRef(SithWorld* pWorld, SithCogSymbol* pSymbol, const SithCogSymbolRef* pRef, const char* pString);
int J3DAPI sithCog_LinkCog(const SithWorld* pWorld, SithCog* pCog, const SithCogSymbolRef* pRef, const SithCogSymbol* pSymbol);
SithCog* J3DAPI sithCog_Load(SithWorld* pWorld, const char* pName);
SithCog* J3DAPI sithCog_GetCogByIndex(int idx);
SithCog* J3DAPI sithCog_GetCog(const char* pName);
int J3DAPI sithCog_LinkCogToThing(const SithWorld* pWorld, SithCog* pCog, SithThing* pThing, int linkId, int mask);
int J3DAPI sithCog_LinkCogToSurface(SithCog* pCog, SithSurface* pSurface, int linkId, int mask);
signed int J3DAPI sithCog_LinkCogToSector(const SithWorld* pWorld, SithCog* pCog, SithSector* pSector, int linkId, int mask);
void sithCog_FixupLinksToThings(void);
int J3DAPI sithCog_ThingSendMessage(const SithThing* pThing, const SithThing* pSrcThing, SithCogMsgType msgType);
int J3DAPI sithCog_ThingSendMessageEx(const SithThing* pThing, const SithThing* pSrcThing, SithCogMsgType messageType, int param0, int param1, int param2, int param3);
int J3DAPI sithCog_SectorSendMessage(const SithSector* pSector, const SithThing* pThing, SithCogMsgType msgType);
int J3DAPI sithCog_SectorSendMessageEx(const SithSector* pSector, const SithThing* pThing, SithCogMsgType messageType, int param0, int param1, int param2, int param3);
int J3DAPI sithCog_SurfaceSendMessage(const SithSurface* pSurf, const SithThing* pSrcThing, SithCogMsgType messageType);
int J3DAPI sithCog_SurfaceSendMessageEx(const SithSurface* pSurf, const SithThing* pSrcThing, SithCogMsgType messageType, int param0, int param1, int param2, int param3);
int J3DAPI sithCog_NDYReadCogScripSection(SithWorld* pWorld, int bSkip);
int J3DAPI sithCog_CNDWriteCogScriptSection(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithCog_CNDReadCogScriptSection(tFileHandle fh, SithWorld* pWorld);
SithCogScript* J3DAPI sithCog_LoadScript(SithWorld* pWorld, const char* pName);
void J3DAPI sithCog_ProcessCog(SithCog* pCog);
void J3DAPI sithCog_ProcessCogs();
void J3DAPI sithCog_AddIntSymbol(SithCogSymbolTable* pTbl, int val, const char* pName);
int J3DAPI sithCog_TimerEventTask(int msecTime, SithEventParams* aParams);
SithCogScript* J3DAPI sithCog_GetScript(const char* pName);
int J3DAPI sithCog_AddScript(SithCogScript* pScript);
int J3DAPI sithCog_RemoveScript(SithCogScript* pScript);
void J3DAPI sithCog_Initialize();
void J3DAPI sithCog_AddFloatSymbol(SithCogSymbolTable* pTbl, const char* pName, float value);
int J3DAPI sithCog_RegisterFunction(SithCogSymbolTable* pTable, SithCogFunctionType pFunction, const char* pName);
int J3DAPI sithCog_IsThingLinked(const SithThing* pThing);

// Helper hooking functions
void sithCog_InstallHooks(void);
void sithCog_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHCOG_H
