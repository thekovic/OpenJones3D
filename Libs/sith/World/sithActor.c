#include "sithActor.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>


void sithActor_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithActor_SetDifficulty);
    // J3D_HOOKFUNC(sithActor_Update);
    // J3D_HOOKFUNC(sithActor_DamageActor);
    // J3D_HOOKFUNC(sithActor_DamageRaftActor);
    // J3D_HOOKFUNC(sithActor_PlayDamageSoundFx);
    // J3D_HOOKFUNC(sithActor_KillActor);
    // J3D_HOOKFUNC(sithActor_SurfaceCollisionHandler);
    // J3D_HOOKFUNC(sithActor_ActorCollisionHandler);
    // J3D_HOOKFUNC(sithActor_SetHeadPYR);
    // J3D_HOOKFUNC(sithActor_Destroy);
    // J3D_HOOKFUNC(sithActor_Remove);
    // J3D_HOOKFUNC(sithActor_ParseArg);
}

void sithActor_ResetGlobals(void)
{

}

void J3DAPI sithActor_SetDifficulty(SithThing* pActor)
{
    J3D_TRAMPOLINE_CALL(sithActor_SetDifficulty, pActor);
}

void J3DAPI sithActor_Update(SithThing* pThing, unsigned int msecDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithActor_Update, pThing, msecDeltaTime);
}

float J3DAPI sithActor_DamageActor(SithThing* pActor, SithThing* pThing, float damage, SithDamageType damageType)
{
    return J3D_TRAMPOLINE_CALL(sithActor_DamageActor, pActor, pThing, damage, damageType);
}

float J3DAPI sithActor_DamageRaftActor(SithThing* pActor, SithThing* pPerpetrator, float damage, SithDamageType damageType)
{
    return J3D_TRAMPOLINE_CALL(sithActor_DamageRaftActor, pActor, pPerpetrator, damage, damageType);
}

void J3DAPI sithActor_PlayDamageSoundFx(SithThing* pThing, SithDamageType damageType)
{
    J3D_TRAMPOLINE_CALL(sithActor_PlayDamageSoundFx, pThing, damageType);
}

void J3DAPI sithActor_KillActor(SithThing* pThing, SithThing* pSrcThing, SithDamageType damageType)
{
    J3D_TRAMPOLINE_CALL(sithActor_KillActor, pThing, pSrcThing, damageType);
}

int J3DAPI sithActor_SurfaceCollisionHandler(SithThing* pThing, SithSurface* pSurface, SithCollision* pHitStack)
{
    return J3D_TRAMPOLINE_CALL(sithActor_SurfaceCollisionHandler, pThing, pSurface, pHitStack);
}

int J3DAPI sithActor_ActorCollisionHandler(SithThing* pSrcThing, SithThing* pThing, SithCollision* pCollision, int a4)
{
    return J3D_TRAMPOLINE_CALL(sithActor_ActorCollisionHandler, pSrcThing, pThing, pCollision, a4);
}

void J3DAPI sithActor_SetHeadPYR(SithThing* pThing, const rdVector3* headAngles)
{
    J3D_TRAMPOLINE_CALL(sithActor_SetHeadPYR, pThing, headAngles);
}

void J3DAPI sithActor_Destroy(SithThing* pActor)
{
    J3D_TRAMPOLINE_CALL(sithActor_Destroy, pActor);
}

void J3DAPI sithActor_Remove(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithActor_Remove, pThing);
}

int J3DAPI sithActor_ParseArg(StdConffileArg* pArg, SithThing* pThing, int adjNum)
{
    return J3D_TRAMPOLINE_CALL(sithActor_ParseArg, pArg, pThing, adjNum);
}
