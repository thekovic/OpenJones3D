#include "sithSprite.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>


void sithSprite_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithSprite_Startup);
    // J3D_HOOKFUNC(sithSprite_Shutdown);
    // J3D_HOOKFUNC(sithSprite_Update);
    // J3D_HOOKFUNC(sithSprite_Draw);
    // J3D_HOOKFUNC(sithSprite_UpdateSize);
    // J3D_HOOKFUNC(sithSprite_NDYReadSpriteSection);
    // J3D_HOOKFUNC(sithSprite_CNDWriteSpriteSection);
    // J3D_HOOKFUNC(sithSprite_CNDReadSpriteSection);
    // J3D_HOOKFUNC(sithSprite_FreeWorldSprites);
    // J3D_HOOKFUNC(sithSprite_AllocWorldSprites);
    // J3D_HOOKFUNC(sithSprite_Initialize);
    // J3D_HOOKFUNC(sithSprite_CacheFind);
    // J3D_HOOKFUNC(sithSprite_CacheAdd);
    // J3D_HOOKFUNC(sithSprite_CacheRemove);
}

void sithSprite_ResetGlobals(void)
{
    memset(&sithSprite_g_pHashtable, 0, sizeof(sithSprite_g_pHashtable));
}

int sithSprite_Startup(void)
{
    return J3D_TRAMPOLINE_CALL(sithSprite_Startup);
}

void J3DAPI sithSprite_Shutdown()
{
    J3D_TRAMPOLINE_CALL(sithSprite_Shutdown);
}

void J3DAPI sithSprite_Update(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithSprite_Update, pThing);
}

int J3DAPI sithSprite_Draw(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithSprite_Draw, pThing);
}

void J3DAPI sithSprite_UpdateSize(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithSprite_UpdateSize, pThing);
}

int J3DAPI sithSprite_NDYReadSpriteSection(SithWorld* pWorld, int bSkip)
{
    return J3D_TRAMPOLINE_CALL(sithSprite_NDYReadSpriteSection, pWorld, bSkip);
}

int J3DAPI sithSprite_CNDWriteSpriteSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithSprite_CNDWriteSpriteSection, fh, pWorld);
}

int J3DAPI sithSprite_CNDReadSpriteSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithSprite_CNDReadSpriteSection, fh, pWorld);
}

void J3DAPI sithSprite_FreeWorldSprites(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithSprite_FreeWorldSprites, pWorld);
}

int J3DAPI sithSprite_AllocWorldSprites(SithWorld* pWorld, int size)
{
    return J3D_TRAMPOLINE_CALL(sithSprite_AllocWorldSprites, pWorld, size);
}

void J3DAPI sithSprite_Initialize(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithSprite_Initialize, pThing);
}

rdSprite3* J3DAPI sithSprite_CacheFind(const char* pName)
{
    return J3D_TRAMPOLINE_CALL(sithSprite_CacheFind, pName);
}

void J3DAPI sithSprite_CacheAdd(rdSprite3* pSprite)
{
    J3D_TRAMPOLINE_CALL(sithSprite_CacheAdd, pSprite);
}

void J3DAPI sithSprite_CacheRemove(const rdSprite3* pSprite)
{
    J3D_TRAMPOLINE_CALL(sithSprite_CacheRemove, pSprite);
}
