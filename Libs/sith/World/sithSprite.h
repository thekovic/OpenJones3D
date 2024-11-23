#ifndef SITH_SITHSPRITE_H
#define SITH_SITHSPRITE_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define sithSprite_g_pHashtable J3D_DECL_FAR_VAR(sithSprite_g_pHashtable, tHashTable*)
// extern tHashTable *sithSprite_g_pHashtable;

int sithSprite_Startup(void);
void sithSprite_Shutdown(void);
void J3DAPI sithSprite_Update(SithThing* pThing, uint32_t msecDeltaTime);
int J3DAPI sithSprite_Draw(SithThing* pThing);
void J3DAPI sithSprite_UpdateSize(SithThing* pThing);
int J3DAPI sithSprite_NDYReadSpriteSection(SithWorld* pWorld, int bSkip);
int J3DAPI sithSprite_CNDWriteSpriteSection(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithSprite_CNDReadSpriteSection(tFileHandle fh, SithWorld* pWorld);
void J3DAPI sithSprite_FreeWorldSprites(SithWorld* pWorld);
int J3DAPI sithSprite_AllocWorldSprites(SithWorld* pWorld, int size);
rdSprite3* J3DAPI sithSprite_Load(SithWorld* pWorld, const char* pName);
void J3DAPI sithSprite_Initialize(SithThing* pThing);
rdSprite3* J3DAPI sithSprite_CacheFind(const char* pName);
void J3DAPI sithSprite_CacheAdd(rdSprite3* pSprite);
void J3DAPI sithSprite_CacheRemove(const rdSprite3* pSprite);

// Helper hooking functions
void sithSprite_InstallHooks(void);
void sithSprite_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHSPRITE_H
