#include "sithAIClass.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>


void sithAIClass_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithAIClass_Startup);
    // J3D_HOOKFUNC(sithAIClass_Shutdown);
    // J3D_HOOKFUNC(sithAIClass_NDYReadAIClassSection);
    // J3D_HOOKFUNC(sithAIClass_CNDWriteAIClassSection);
    // J3D_HOOKFUNC(sithAIClass_CNDReadAIClassSection);
    // J3D_HOOKFUNC(sithAIClass_AllocWorldAIClasses);
    // J3D_HOOKFUNC(sithAIClass_FreeWorldAIClasses);
    // J3D_HOOKFUNC(sithAIClass_Load);
    // J3D_HOOKFUNC(sithAIClass_LoadEntry);
    // J3D_HOOKFUNC(sithAIClass_CacheFind);
    // J3D_HOOKFUNC(sithAIClass_CacheAdd);
    // J3D_HOOKFUNC(sithAIClass_CacheRemove);
}

void sithAIClass_ResetGlobals(void)
{
    memset(&sithAIClass_g_pHashtable, 0, sizeof(sithAIClass_g_pHashtable));
}

int sithAIClass_Startup(void)
{
    return J3D_TRAMPOLINE_CALL(sithAIClass_Startup);
}

void J3DAPI sithAIClass_Shutdown()
{
    J3D_TRAMPOLINE_CALL(sithAIClass_Shutdown);
}

int J3DAPI sithAIClass_NDYReadAIClassSection(SithWorld* pWorld, int bSkip)
{
    return J3D_TRAMPOLINE_CALL(sithAIClass_NDYReadAIClassSection, pWorld, bSkip);
}

int J3DAPI sithAIClass_CNDWriteAIClassSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithAIClass_CNDWriteAIClassSection, fh, pWorld);
}

int J3DAPI sithAIClass_CNDReadAIClassSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithAIClass_CNDReadAIClassSection, fh, pWorld);
}

int J3DAPI sithAIClass_AllocWorldAIClasses(SithWorld* pWorld, int numClasses)
{
    return J3D_TRAMPOLINE_CALL(sithAIClass_AllocWorldAIClasses, pWorld, numClasses);
}

void J3DAPI sithAIClass_FreeWorldAIClasses(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithAIClass_FreeWorldAIClasses, pWorld);
}

SithAIClass* J3DAPI sithAIClass_Load(SithWorld* pWorld, const char* pName)
{
    return J3D_TRAMPOLINE_CALL(sithAIClass_Load, pWorld, pName);
}

int J3DAPI sithAIClass_LoadEntry(const char* pPath, SithAIClass* pClass)
{
    return J3D_TRAMPOLINE_CALL(sithAIClass_LoadEntry, pPath, pClass);
}

SithAIClass* J3DAPI sithAIClass_CacheFind(const char* pName)
{
    return J3D_TRAMPOLINE_CALL(sithAIClass_CacheFind, pName);
}

void J3DAPI sithAIClass_CacheAdd(SithAIClass* pClass)
{
    J3D_TRAMPOLINE_CALL(sithAIClass_CacheAdd, pClass);
}

int J3DAPI sithAIClass_CacheRemove(const SithAIClass* pClass)
{
    return J3D_TRAMPOLINE_CALL(sithAIClass_CacheRemove, pClass);
}
