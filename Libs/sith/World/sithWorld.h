#ifndef SITH_SITHWORLD_H
#define SITH_SITHWORLD_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

// Added
// The macro converts the resource index to static resource index (jones3Dstatic.cnd)
#define SITHWORLD_STATICINDEX(idx) ((idx) | SITH_STATICRESOURCE_INDEXMASK)
#define SITHWORLD_ISSTATICINDEX(idx) ((idx & SITH_STATICRESOURCE_INDEXMASK) != 0)
#define SITHWORLD_CLEARSTATICINDEXMASK(idx) (idx &= ~SITH_STATICRESOURCE_INDEXMASK)


#define sithWorld_g_pCurrentWorld J3D_DECL_FAR_VAR(sithWorld_g_pCurrentWorld, SithWorld*)
// extern SithWorld *sithWorld_g_pCurrentWorld;

#define sithWorld_g_pStaticWorld J3D_DECL_FAR_VAR(sithWorld_g_pStaticWorld, SithWorld*)
// extern SithWorld *sithWorld_g_pStaticWorld;

#define sithWorld_g_pLastLoadedWorld J3D_DECL_FAR_VAR(sithWorld_g_pLastLoadedWorld, SithWorld*)
// extern SithWorld *sithWorld_g_pLastLoadedWorld;

#define sithWorld_g_bLoading J3D_DECL_FAR_VAR(sithWorld_g_bLoading, int)
// extern int sithWorld_g_bLoading;

int J3DAPI sithWorld_Startup();
void sithWorld_Shutdown(void);
void J3DAPI sithWorld_SetLoadProgressCallback(SithWorldLoadProgressCallback pfProgressCallback);
void J3DAPI sithWorld_UpdateLoadProgress(float progress);
int J3DAPI sithWorld_Load(SithWorld* pWorld, const char* pFilename);
int J3DAPI sithWorld_LoadPostProcess(SithWorld* pWorld);
int J3DAPI sithWorld_LoadEntryText(SithWorld* pWorld, const char* pFilename, int bSkipParsing);
void J3DAPI sithWorld_Close(SithWorld* pWorld);
SithWorld* sithWorld_New(void);
void J3DAPI sithWorld_Free(SithWorld* pWorld);
signed int J3DAPI sithWorld_NDYReadHeaderSection(SithWorld* pWorld, int bSkip);
int J3DAPI sithWorld_NDYReadCopyrightSection(SithWorld* pWorld, int bSkip);
void J3DAPI sithWorld_GetMemoryUsage(const SithWorld* pWorld, int* aMemUsed, int* aCount);
int J3DAPI sithWorld_RegisterTextSectionParser(const char* aSectionName, SithWorldSectionParseFunc pfParseFunction);
void J3DAPI sithWorld_ResetRenderState(SithWorld* pWorld);
int J3DAPI sithWorld_ValidateWorld(const SithWorld* pWorld);
int J3DAPI sithWorld_InitPlayers(SithWorld* pWorld);
int J3DAPI sithWorld_NDYReadSection(SithWorld* pWorld, const char* aSectionName, int bSkip);
int J3DAPI sithWorld_NDYGetSectionParserIndex(const char* aSectionName);
int J3DAPI sithWorld_NDYReadGeoresourceSection(SithWorld* pWorld, int bSkip);
int J3DAPI sithWorld_CNDWriteGeoresourceSection(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithWorld_CNDReadGeoresourceSection(tFileHandle fh, SithWorld* pWorld);
// local variable allocation has failed, the output may be wrong!
int J3DAPI sithWorld_LoadEntryBinary(SithWorld* pWorld, const char* pFilePath);



// Helper hooking functions
void sithWorld_InstallHooks(void);
void sithWorld_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHWORLD_H
