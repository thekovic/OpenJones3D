#include "sithParticle.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>


void sithParticle_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithParticle_Startup);
    // J3D_HOOKFUNC(sithParticle_Shutdown);
    // J3D_HOOKFUNC(sithParticle_Load);
    // J3D_HOOKFUNC(sithParticle_AllocWorldParticles);
    // J3D_HOOKFUNC(sithParticle_ParseArg);
    // J3D_HOOKFUNC(sithParticle_Update);
    // J3D_HOOKFUNC(sithParticle_Initalize);
    // J3D_HOOKFUNC(sithParticle_Remove);
    // J3D_HOOKFUNC(sithParticle_Free);
    // J3D_HOOKFUNC(sithParticle_FreeWorldParticles);
    // J3D_HOOKFUNC(sithParticle_CacheFind);
    // J3D_HOOKFUNC(sithParticle_CacheAdd);
    // J3D_HOOKFUNC(sithParticle_CacheRemove);
}

void sithParticle_ResetGlobals(void)
{
    memset(&sithParticle_g_pHashtable, 0, sizeof(sithParticle_g_pHashtable));
}

int sithParticle_Startup(void)
{
    return J3D_TRAMPOLINE_CALL(sithParticle_Startup);
}

void J3DAPI sithParticle_Shutdown()
{
    J3D_TRAMPOLINE_CALL(sithParticle_Shutdown);
}

rdParticle* J3DAPI sithParticle_Load(SithWorld* pWorld, const char* pName)
{
    return J3D_TRAMPOLINE_CALL(sithParticle_Load, pWorld, pName);
}

int J3DAPI sithParticle_AllocWorldParticles(SithWorld* pWorld, int size)
{
    return J3D_TRAMPOLINE_CALL(sithParticle_AllocWorldParticles, pWorld, size);
}

int J3DAPI sithParticle_ParseArg(StdConffileArg* pArg, SithThing* pThing, int adjNum)
{
    return J3D_TRAMPOLINE_CALL(sithParticle_ParseArg, pArg, pThing, adjNum);
}

void J3DAPI sithParticle_Update(SithThing* pThing, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithParticle_Update, pThing, secDeltaTime);
}

void J3DAPI sithParticle_Initalize(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithParticle_Initalize, pThing);
}

void J3DAPI sithParticle_Remove(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithParticle_Remove, pThing);
}

void J3DAPI sithParticle_Free(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithParticle_Free, pThing);
}

void J3DAPI sithParticle_FreeWorldParticles(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithParticle_FreeWorldParticles, pWorld);
}

rdParticle* J3DAPI sithParticle_CacheFind(const char* pName)
{
    return J3D_TRAMPOLINE_CALL(sithParticle_CacheFind, pName);
}

tLinkListNode* J3DAPI sithParticle_CacheAdd(rdParticle* pParticle)
{
    return J3D_TRAMPOLINE_CALL(sithParticle_CacheAdd, pParticle);
}

signed int J3DAPI sithParticle_CacheRemove(const rdParticle* pParticle)
{
    return J3D_TRAMPOLINE_CALL(sithParticle_CacheRemove, pParticle);
}
