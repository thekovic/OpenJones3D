#include "sithCog.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithCog_aCogLinkSectors J3D_DECL_FAR_ARRAYVAR(sithCog_aCogLinkSectors, SithCogSectorLink(*)[512])
#define sithCog_aThingLinks J3D_DECL_FAR_ARRAYVAR(sithCog_aThingLinks, SithCogThingLink(*)[1024])
#define sithCog_aCogLinkSurfaces J3D_DECL_FAR_ARRAYVAR(sithCog_aCogLinkSurfaces, SithCogSurfaceLink(*)[512])
#define sithCog_bCogOpen J3D_DECL_FAR_VAR(sithCog_bCogOpen, int)
#define sithCog_numThingLinks J3D_DECL_FAR_VAR(sithCog_numThingLinks, int)
#define sithCog_numSurfLinks J3D_DECL_FAR_VAR(sithCog_numSurfLinks, int)
#define sithCog_numSectorLinks J3D_DECL_FAR_VAR(sithCog_numSectorLinks, int)

void sithCog_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithCog_Startup);
    // J3D_HOOKFUNC(sithCog_Shutdown);
    // J3D_HOOKFUNC(sithCog_Open);
    // J3D_HOOKFUNC(sithCog_Close);
    // J3D_HOOKFUNC(sithCog_FreeWorldCogs);
    // J3D_HOOKFUNC(sithCog_FreeScriptEntry);
    // J3D_HOOKFUNC(sithCog_FreeEntry);
    // J3D_HOOKFUNC(sithCog_UpdateThingTimer);
    // J3D_HOOKFUNC(sithCog_BroadcastMessage);
    // J3D_HOOKFUNC(sithCog_BroadcastMessageEx);
    // J3D_HOOKFUNC(sithCog_SendMessage);
    // J3D_HOOKFUNC(sithCog_SendMessageEx);
    // J3D_HOOKFUNC(sithCog_AllocWorldCogScripts);
    // J3D_HOOKFUNC(sithCog_AllocWorldCogs);
    // J3D_HOOKFUNC(sithCog_GetSymbolRefInitializer);
    // J3D_HOOKFUNC(sithCog_NDYReadCOGSection);
    // J3D_HOOKFUNC(sithCog_CNDWriteCOGSection);
    // J3D_HOOKFUNC(sithCog_CNDReadCOGSection);
    // J3D_HOOKFUNC(sithCog_ParseSymbolRef);
    // J3D_HOOKFUNC(sithCog_LinkCog);
    // J3D_HOOKFUNC(sithCog_Load);
    // J3D_HOOKFUNC(sithCog_GetCogByIndex);
    // J3D_HOOKFUNC(sithCog_GetCog);
    // J3D_HOOKFUNC(sithCog_LinkCogToThing);
    // J3D_HOOKFUNC(sithCog_LinkCogToSurface);
    // J3D_HOOKFUNC(sithCog_LinkCogToSector);
    // J3D_HOOKFUNC(sithCog_FixupLinksToThings);
    // J3D_HOOKFUNC(sithCog_ThingSendMessage);
    // J3D_HOOKFUNC(sithCog_ThingSendMessageEx);
    // J3D_HOOKFUNC(sithCog_SectorSendMessage);
    // J3D_HOOKFUNC(sithCog_SectorSendMessageEx);
    // J3D_HOOKFUNC(sithCog_SurfaceSendMessage);
    // J3D_HOOKFUNC(sithCog_SurfaceSendMessageEx);
    // J3D_HOOKFUNC(sithCog_NDYReadCogScripSection);
    // J3D_HOOKFUNC(sithCog_CNDWriteCogScriptSection);
    // J3D_HOOKFUNC(sithCog_CNDReadCogScriptSection);
    // J3D_HOOKFUNC(sithCog_LoadScript);
    // J3D_HOOKFUNC(sithCog_ProcessCog);
    // J3D_HOOKFUNC(sithCog_ProcessCogs);
    // J3D_HOOKFUNC(sithCog_AddIntSymbol);
    // J3D_HOOKFUNC(sithCog_TimerEventTask);
    // J3D_HOOKFUNC(sithCog_GetScript);
    // J3D_HOOKFUNC(sithCog_AddScript);
    // J3D_HOOKFUNC(sithCog_RemoveScript);
    // J3D_HOOKFUNC(sithCog_Initialize);
    // J3D_HOOKFUNC(sithCog_AddFloatSymbol);
    // J3D_HOOKFUNC(sithCog_RegisterFunction);
    // J3D_HOOKFUNC(sithCog_IsThingLinked);
}

void sithCog_ResetGlobals(void)
{
    memset(&sithCog_aCogLinkSectors, 0, sizeof(sithCog_aCogLinkSectors));
    memset(&sithCog_aThingLinks, 0, sizeof(sithCog_aThingLinks));
    memset(&sithCog_aCogLinkSurfaces, 0, sizeof(sithCog_aCogLinkSurfaces));
    memset(&sithCog_g_bCogStartup, 0, sizeof(sithCog_g_bCogStartup));
    memset(&sithCog_bCogOpen, 0, sizeof(sithCog_bCogOpen));
    memset(&sithCog_numThingLinks, 0, sizeof(sithCog_numThingLinks));
    memset(&sithCog_numSurfLinks, 0, sizeof(sithCog_numSurfLinks));
    memset(&sithCog_numSectorLinks, 0, sizeof(sithCog_numSectorLinks));
    memset(&sithCog_g_pHashtable, 0, sizeof(sithCog_g_pHashtable));
    memset(&sithCog_g_pSymbolTable, 0, sizeof(sithCog_g_pSymbolTable));
    memset(&sithCog_g_pMasterCog, 0, sizeof(sithCog_g_pMasterCog));
}

int sithCog_Startup(void)
{
    return J3D_TRAMPOLINE_CALL(sithCog_Startup);
}

void J3DAPI sithCog_Shutdown()
{
    J3D_TRAMPOLINE_CALL(sithCog_Shutdown);
}

// On error 1 is returned otherwise 0
int J3DAPI sithCog_Open(SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithCog_Open, pWorld);
}

void J3DAPI sithCog_Close()
{
    J3D_TRAMPOLINE_CALL(sithCog_Close);
}

void J3DAPI sithCog_FreeWorldCogs(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithCog_FreeWorldCogs, pWorld);
}

void J3DAPI sithCog_FreeScriptEntry(SithCogScript* pScript)
{
    J3D_TRAMPOLINE_CALL(sithCog_FreeScriptEntry, pScript);
}

void J3DAPI sithCog_FreeEntry(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCog_FreeEntry, pCog);
}

void J3DAPI sithCog_UpdateThingTimer(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithCog_UpdateThingTimer, pThing);
}

void J3DAPI sithCog_BroadcastMessage(SithCogMsgType msgType, SithCogSymbolRefType senderType, int senderIdx, SithCogSymbolRefType srcType, int srcIdx)
{
    J3D_TRAMPOLINE_CALL(sithCog_BroadcastMessage, msgType, senderType, senderIdx, srcType, srcIdx);
}

void J3DAPI sithCog_BroadcastMessageEx(SithCogMsgType msgType, SithCogSymbolRefType senderType, int senderIdx, SithCogSymbolRefType srcType, int srcIdx, int param0, int param1, int param2, int param3)
{
    J3D_TRAMPOLINE_CALL(sithCog_BroadcastMessageEx, msgType, senderType, senderIdx, srcType, srcIdx, param0, param1, param2, param3);
}

void J3DAPI sithCog_SendMessage(SithCog* pCog, SithCogMsgType messageType, SithCogSymbolRefType senderType, int senderIdx, SithCogSymbolRefType srcType, int srcIdx, int linkId)
{
    J3D_TRAMPOLINE_CALL(sithCog_SendMessage, pCog, messageType, senderType, senderIdx, srcType, srcIdx, linkId);
}

// return value '-9999' indicates that the message  was processed.
// Same value is returned when COG is paused or message handler for the type doesn't exist. 
// In this case no message is sent further to COG
int J3DAPI sithCog_SendMessageEx(SithCog* pCog, SithCogMsgType messageType, SithCogSymbolRefType senderType, int senderIdx, SithCogSymbolRefType srcType, int srcIdx, int linkId, int param0, int param1, int param2, int param3)
{
    return J3D_TRAMPOLINE_CALL(sithCog_SendMessageEx, pCog, messageType, senderType, senderIdx, srcType, srcIdx, linkId, param0, param1, param2, param3);
}

int J3DAPI sithCog_AllocWorldCogScripts(SithWorld* pWorld, int numCogScripts)
{
    return J3D_TRAMPOLINE_CALL(sithCog_AllocWorldCogScripts, pWorld, numCogScripts);
}

int J3DAPI sithCog_AllocWorldCogs(SithWorld* pWorld, int sizeCogs)
{
    return J3D_TRAMPOLINE_CALL(sithCog_AllocWorldCogs, pWorld, sizeCogs);
}

int J3DAPI sithCog_GetSymbolRefInitializer(const SithWorld* pWorld, const SithCog* pCog, int symIdx, char* pOutString)
{
    return J3D_TRAMPOLINE_CALL(sithCog_GetSymbolRefInitializer, pWorld, pCog, symIdx, pOutString);
}

int J3DAPI sithCog_NDYReadCOGSection(SithWorld* pWorld, int bSkip)
{
    return J3D_TRAMPOLINE_CALL(sithCog_NDYReadCOGSection, pWorld, bSkip);
}

int J3DAPI sithCog_CNDWriteCOGSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithCog_CNDWriteCOGSection, fh, pWorld);
}

int J3DAPI sithCog_CNDReadCOGSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithCog_CNDReadCOGSection, fh, pWorld);
}

// On success 0 is returned and 1 on error
int J3DAPI sithCog_ParseSymbolRef(SithWorld* pWorld, SithCogSymbol* pSymbol, const SithCogSymbolRef* pRef, const char* pString)
{
    return J3D_TRAMPOLINE_CALL(sithCog_ParseSymbolRef, pWorld, pSymbol, pRef, pString);
}

int J3DAPI sithCog_LinkCog(const SithWorld* pWorld, SithCog* pCog, const SithCogSymbolRef* pRef, const SithCogSymbol* pSymbol)
{
    return J3D_TRAMPOLINE_CALL(sithCog_LinkCog, pWorld, pCog, pRef, pSymbol);
}

SithCog* J3DAPI sithCog_Load(SithWorld* pWorld, const char* pName)
{
    return J3D_TRAMPOLINE_CALL(sithCog_Load, pWorld, pName);
}

SithCog* J3DAPI sithCog_GetCogByIndex(int idx)
{
    return J3D_TRAMPOLINE_CALL(sithCog_GetCogByIndex, idx);
}

SithCog* J3DAPI sithCog_GetCog(const char* pName)
{
    return J3D_TRAMPOLINE_CALL(sithCog_GetCog, pName);
}

int J3DAPI sithCog_LinkCogToThing(const SithWorld* pWorld, SithCog* pCog, SithThing* pThing, int linkId, int mask)
{
    return J3D_TRAMPOLINE_CALL(sithCog_LinkCogToThing, pWorld, pCog, pThing, linkId, mask);
}

int J3DAPI sithCog_LinkCogToSurface(SithCog* pCog, SithSurface* pSurface, int linkId, int mask)
{
    return J3D_TRAMPOLINE_CALL(sithCog_LinkCogToSurface, pCog, pSurface, linkId, mask);
}

signed int J3DAPI sithCog_LinkCogToSector(const SithWorld* pWorld, SithCog* pCog, SithSector* pSector, int linkId, int mask)
{
    return J3D_TRAMPOLINE_CALL(sithCog_LinkCogToSector, pWorld, pCog, pSector, linkId, mask);
}

void sithCog_FixupLinksToThings(void)
{
    J3D_TRAMPOLINE_CALL(sithCog_FixupLinksToThings);
}

int J3DAPI sithCog_ThingSendMessage(const SithThing* pThing, const SithThing* pSrcThing, SithCogMsgType msgType)
{
    return J3D_TRAMPOLINE_CALL(sithCog_ThingSendMessage, pThing, pSrcThing, msgType);
}

int J3DAPI sithCog_ThingSendMessageEx(const SithThing* pThing, const SithThing* pSrcThing, SithCogMsgType messageType, int param0, int param1, int param2, int param3)
{
    return J3D_TRAMPOLINE_CALL(sithCog_ThingSendMessageEx, pThing, pSrcThing, messageType, param0, param1, param2, param3);
}

int J3DAPI sithCog_SectorSendMessage(const SithSector* pSector, const SithThing* pThing, SithCogMsgType msgType)
{
    return J3D_TRAMPOLINE_CALL(sithCog_SectorSendMessage, pSector, pThing, msgType);
}

int J3DAPI sithCog_SectorSendMessageEx(const SithSector* pSector, const SithThing* pThing, SithCogMsgType messageType, int param0, int param1, int param2, int param3)
{
    return J3D_TRAMPOLINE_CALL(sithCog_SectorSendMessageEx, pSector, pThing, messageType, param0, param1, param2, param3);
}

int J3DAPI sithCog_SurfaceSendMessage(const SithSurface* pSurf, const SithThing* pSrcThing, SithCogMsgType messageType)
{
    return J3D_TRAMPOLINE_CALL(sithCog_SurfaceSendMessage, pSurf, pSrcThing, messageType);
}

int J3DAPI sithCog_SurfaceSendMessageEx(const SithSurface* pSurf, const SithThing* pSrcThing, SithCogMsgType messageType, int param0, int param1, int param2, int param3)
{
    return J3D_TRAMPOLINE_CALL(sithCog_SurfaceSendMessageEx, pSurf, pSrcThing, messageType, param0, param1, param2, param3);
}

int J3DAPI sithCog_NDYReadCogScripSection(SithWorld* pWorld, int bSkip)
{
    return J3D_TRAMPOLINE_CALL(sithCog_NDYReadCogScripSection, pWorld, bSkip);
}

int J3DAPI sithCog_CNDWriteCogScriptSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithCog_CNDWriteCogScriptSection, fh, pWorld);
}

int J3DAPI sithCog_CNDReadCogScriptSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithCog_CNDReadCogScriptSection, fh, pWorld);
}

SithCogScript* J3DAPI sithCog_LoadScript(SithWorld* pWorld, const char* pName)
{
    return J3D_TRAMPOLINE_CALL(sithCog_LoadScript, pWorld, pName);
}

void J3DAPI sithCog_ProcessCog(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCog_ProcessCog, pCog);
}

void J3DAPI sithCog_ProcessCogs()
{
    J3D_TRAMPOLINE_CALL(sithCog_ProcessCogs);
}

void J3DAPI sithCog_AddIntSymbol(SithCogSymbolTable* pTbl, int val, const char* pName)
{
    J3D_TRAMPOLINE_CALL(sithCog_AddIntSymbol, pTbl, val, pName);
}

int J3DAPI sithCog_TimerEventTask(int msecTime, SithEventParams* aParams)
{
    return J3D_TRAMPOLINE_CALL(sithCog_TimerEventTask, msecTime, aParams);
}

SithCogScript* J3DAPI sithCog_GetScript(const char* pName)
{
    return J3D_TRAMPOLINE_CALL(sithCog_GetScript, pName);
}

int J3DAPI sithCog_AddScript(SithCogScript* pScript)
{
    return J3D_TRAMPOLINE_CALL(sithCog_AddScript, pScript);
}

int J3DAPI sithCog_RemoveScript(SithCogScript* pScript)
{
    return J3D_TRAMPOLINE_CALL(sithCog_RemoveScript, pScript);
}

void J3DAPI sithCog_Initialize()
{
    J3D_TRAMPOLINE_CALL(sithCog_Initialize);
}

void J3DAPI sithCog_AddFloatSymbol(SithCogSymbolTable* pTbl, const char* pName, float value)
{
    J3D_TRAMPOLINE_CALL(sithCog_AddFloatSymbol, pTbl, pName, value);
}

int J3DAPI sithCog_RegisterFunction(SithCogSymbolTable* pTable, SithCogFunctionType pFunction, const char* pName)
{
    return J3D_TRAMPOLINE_CALL(sithCog_RegisterFunction, pTable, pFunction, pName);
}

int J3DAPI sithCog_IsThingLinked(const SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithCog_IsThingLinked, pThing);
}
