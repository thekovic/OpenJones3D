#include "sithWeapon.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithWeapon_bGenBloodsplort J3D_DECL_FAR_VAR(sithWeapon_bGenBloodsplort, int)
#define sithWeapon_aMaxAimDistances J3D_DECL_FAR_ARRAYVAR(sithWeapon_aMaxAimDistances, float(*)[25])
#define sithWeapon_lastPlayerWeaponID J3D_DECL_FAR_VAR(sithWeapon_lastPlayerWeaponID, SithWeaponId)
#define sithWeapon_bPlayerWeaponActivated J3D_DECL_FAR_VAR(sithWeapon_bPlayerWeaponActivated, int)
#define sithWeapon_playerWhipHolsterSwapRefNum J3D_DECL_FAR_VAR(sithWeapon_playerWhipHolsterSwapRefNum, int)
#define sithWeapon_playerPistolHolsterSwapRefNum J3D_DECL_FAR_VAR(sithWeapon_playerPistolHolsterSwapRefNum, int)
#define sithWeapon_deactivatedPlayerWeaponID J3D_DECL_FAR_VAR(sithWeapon_deactivatedPlayerWeaponID, int)
#define sithWeapon_secPlayerWeaponDeactivationTime J3D_DECL_FAR_VAR(sithWeapon_secPlayerWeaponDeactivationTime, float)
#define sithWeapon_bLocalPlayerAiming J3D_DECL_FAR_VAR(sithWeapon_bLocalPlayerAiming, int)
#define sithWeapon_secWeaponActivationWaitEndTime J3D_DECL_FAR_VAR(sithWeapon_secWeaponActivationWaitEndTime, float)
#define sithWeapon_playerBackHolsterSwapRefNum J3D_DECL_FAR_VAR(sithWeapon_playerBackHolsterSwapRefNum, int)
#define sithWeapon_secMountWait J3D_DECL_FAR_VAR(sithWeapon_secMountWait, float)
#define sithWeapon_bufferedWaponKeyId J3D_DECL_FAR_VAR(sithWeapon_bufferedWaponKeyId, SithControlFunction)
#define sithWeapon_pfActorKilledCallback J3D_DECL_FAR_VAR(sithWeapon_pfActorKilledCallback, SithWeaponActorKilledCallback)

void sithWeapon_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithWeapon_Open);
    // J3D_HOOKFUNC(sithWeapon_InitalizeActor);
    // J3D_HOOKFUNC(sithWeapon_UpdateActorWeaponState);
    // J3D_HOOKFUNC(sithWeapon_Update);
    // J3D_HOOKFUNC(sithWeapon_SelectWeapon);
    // J3D_HOOKFUNC(sithWeapon_HandleImpact);
    // J3D_HOOKFUNC(sithWeapon_ParseArg);
    // J3D_HOOKFUNC(sithWeapon_WeaponFire);
    // J3D_HOOKFUNC(sithWeapon_WeaponFireProjectile);
    // J3D_HOOKFUNC(sithWeapon_DamageWeapon);
    // J3D_HOOKFUNC(sithWeapon_ThingCollisionHandler);
    // J3D_HOOKFUNC(sithWeapon_SurfaceCollisionHandler);
    // J3D_HOOKFUNC(sithWeapon_Destroy);
    // J3D_HOOKFUNC(sithWeapon_CreateWeaponExplosion);
    // J3D_HOOKFUNC(sithWeapon_GetMountWait);
    // J3D_HOOKFUNC(sithWeapon_SetMountWait);
    // J3D_HOOKFUNC(sithWeapon_SetFireWait);
    // J3D_HOOKFUNC(sithWeapon_SetAimWait);
    // J3D_HOOKFUNC(sithWeapon_ActivateWeapon);
    // J3D_HOOKFUNC(sithWeapon_DeactivateWeapon);
    // J3D_HOOKFUNC(sithWeapon_ProcessWeaponControls);
    // J3D_HOOKFUNC(sithWeapon_DeselectWeapon);
    // J3D_HOOKFUNC(sithWeapon_IsMountingWeapon);
    // J3D_HOOKFUNC(sithWeapon_HasWeaponSelected);
    // J3D_HOOKFUNC(sithWeapon_GetAimOrient);
    // J3D_HOOKFUNC(sithWeapon_FireProjectile);
    // J3D_HOOKFUNC(sithWeapon_DeactivateCurrentWeapon);
    // J3D_HOOKFUNC(sithWeapon_SelectNextWeapon);
    // J3D_HOOKFUNC(sithWeapon_SelectPreviousWeapon);
    // J3D_HOOKFUNC(sithWeapon_SetWeaponModel);
    // J3D_HOOKFUNC(sithWeapon_ResetWeaponModel);
    // J3D_HOOKFUNC(sithWeapon_SetHolsterModel);
    // J3D_HOOKFUNC(sithWeapon_ResetHolsterModel);
    // J3D_HOOKFUNC(sithWeapon_SendMessageAim);
    // J3D_HOOKFUNC(sithWeapon_SetActorKilledCallback);
    // J3D_HOOKFUNC(sithWeapon_IsAiming);
    // J3D_HOOKFUNC(sithWeapon_GenBloodsplort);
    // J3D_HOOKFUNC(sithWeapon_GetLastWeapon);
    // J3D_HOOKFUNC(sithWeapon_SetLastWeapon);
    // J3D_HOOKFUNC(sithWeapon_GetWeaponMaxAimDistance);
    // J3D_HOOKFUNC(sithWeapon_GetWeaponCollideSize);
    // J3D_HOOKFUNC(sithWeapon_IsLocalPlayerUnableToUseWeapon);
    // J3D_HOOKFUNC(sithWeapon_Save);
    // J3D_HOOKFUNC(sithWeapon_Restore);
    // J3D_HOOKFUNC(sithWeapon_GetWeaponForControlKey);
    // J3D_HOOKFUNC(sithWeapon_FireProjectileEx);
    // J3D_HOOKFUNC(sithWeapon_CreateWeaponFireFx);
    // J3D_HOOKFUNC(sithWeapon_ActivateWhip);
}

void sithWeapon_ResetGlobals(void)
{
    int sithWeapon_bGenBloodsplort_tmp = 1;
    memcpy(&sithWeapon_bGenBloodsplort, &sithWeapon_bGenBloodsplort_tmp, sizeof(sithWeapon_bGenBloodsplort));
    
    float sithWeapon_aMaxAimDistances_tmp[25] = {
      0.0f,
      0.0f,
      0.0f,
      1.0f,
      1.5f,
      1.5f,
      2.5f,
      0.0f,
      1.5f,
      1.0f,
      3.0f,
      0.0f,
      0.0f,
      0.0f,
      0.0f,
      0.0f,
      0.0f,
      0.0f,
      0.0f,
      0.0f,
      1.5f,
      1.5f,
      2.5f,
      1.5f,
      1.0f
    };
    memcpy(&sithWeapon_aMaxAimDistances, &sithWeapon_aMaxAimDistances_tmp, sizeof(sithWeapon_aMaxAimDistances));
    
    memset(&sithWeapon_lastPlayerWeaponID, 0, sizeof(sithWeapon_lastPlayerWeaponID));
    memset(&sithWeapon_bPlayerWeaponActivated, 0, sizeof(sithWeapon_bPlayerWeaponActivated));
    memset(&sithWeapon_playerWhipHolsterSwapRefNum, 0, sizeof(sithWeapon_playerWhipHolsterSwapRefNum));
    memset(&sithWeapon_playerPistolHolsterSwapRefNum, 0, sizeof(sithWeapon_playerPistolHolsterSwapRefNum));
    memset(&sithWeapon_deactivatedPlayerWeaponID, 0, sizeof(sithWeapon_deactivatedPlayerWeaponID));
    memset(&sithWeapon_secPlayerWeaponDeactivationTime, 0, sizeof(sithWeapon_secPlayerWeaponDeactivationTime));
    memset(&sithWeapon_bLocalPlayerAiming, 0, sizeof(sithWeapon_bLocalPlayerAiming));
    memset(&sithWeapon_secWeaponActivationWaitEndTime, 0, sizeof(sithWeapon_secWeaponActivationWaitEndTime));
    memset(&sithWeapon_playerBackHolsterSwapRefNum, 0, sizeof(sithWeapon_playerBackHolsterSwapRefNum));
    memset(&sithWeapon_secMountWait, 0, sizeof(sithWeapon_secMountWait));
    memset(&sithWeapon_bufferedWaponKeyId, 0, sizeof(sithWeapon_bufferedWaponKeyId));
    memset(&sithWeapon_pfActorKilledCallback, 0, sizeof(sithWeapon_pfActorKilledCallback));
}

void sithWeapon_Open(void)
{
    J3D_TRAMPOLINE_CALL(sithWeapon_Open);
}

void J3DAPI sithWeapon_InitalizeActor(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithWeapon_InitalizeActor, pThing);
}

void J3DAPI sithWeapon_UpdateActorWeaponState(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithWeapon_UpdateActorWeaponState, pThing);
}

void J3DAPI sithWeapon_Update(SithThing* pThing, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithWeapon_Update, pThing, secDeltaTime);
}

signed int J3DAPI sithWeapon_SelectWeapon(SithThing* pThing, SithWeaponId typeId)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_SelectWeapon, pThing, typeId);
}

int J3DAPI sithWeapon_HandleImpact(SithThing* pWeapon)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_HandleImpact, pWeapon);
}

int J3DAPI sithWeapon_ParseArg(StdConffileArg* pArg, SithThing* pThing, int adjNum)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_ParseArg, pArg, pThing, adjNum);
}

SithThing* J3DAPI sithWeapon_WeaponFire(SithThing* pShooter, const SithThing* pProjectileTemplate, const rdVector3* pFireDir, rdVector3* pFirePos, tSoundHandle hFireSnd, SithPuppetSubMode submode, float extra, SithFireProjectileFlags projectileFlags, float secDeltaTime)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_WeaponFire, pShooter, pProjectileTemplate, pFireDir, pFirePos, hFireSnd, submode, extra, projectileFlags, secDeltaTime);
}

SithThing* J3DAPI sithWeapon_WeaponFireProjectile(SithThing* pShooter, const SithThing* pProjectileTemplate, const rdVector3* pFireDir, rdVector3* pFirePos, tSoundHandle hFireSnd, SithPuppetSubMode submode, float extra, SithFireProjectileFlags flags, float secDeltaTime)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_WeaponFireProjectile, pShooter, pProjectileTemplate, pFireDir, pFirePos, hFireSnd, submode, extra, flags, secDeltaTime);
}

void J3DAPI sithWeapon_DamageWeapon(SithThing* pThing, const SithThing* pPurpetrator, float damage)
{
    J3D_TRAMPOLINE_CALL(sithWeapon_DamageWeapon, pThing, pPurpetrator, damage);
}

int J3DAPI sithWeapon_ThingCollisionHandler(SithThing* pWeapon, SithThing* pThing, SithCollision* pCollision, int a5)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_ThingCollisionHandler, pWeapon, pThing, pCollision, a5);
}

int J3DAPI sithWeapon_SurfaceCollisionHandler(SithThing* pThing, SithSurface* pSurf, SithCollision* pStack)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_SurfaceCollisionHandler, pThing, pSurf, pStack);
}

void J3DAPI sithWeapon_Destroy(SithThing* pWeapon)
{
    J3D_TRAMPOLINE_CALL(sithWeapon_Destroy, pWeapon);
}

SithThing* J3DAPI sithWeapon_CreateWeaponExplosion(SithThing* pWeapon, SithThing* pExplosionTemplate, const rdVector3* pDir, int bRotate)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_CreateWeaponExplosion, pWeapon, pExplosionTemplate, pDir, bRotate);
}

float sithWeapon_GetMountWait(void)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_GetMountWait);
}

void J3DAPI sithWeapon_SetMountWait(float secWait)
{
    J3D_TRAMPOLINE_CALL(sithWeapon_SetMountWait, secWait);
}

void J3DAPI sithWeapon_SetFireWait(SithThing* pThing, float waitTime)
{
    J3D_TRAMPOLINE_CALL(sithWeapon_SetFireWait, pThing, waitTime);
}

void J3DAPI sithWeapon_SetAimWait(SithThing* pThing, float waitTime)
{
    J3D_TRAMPOLINE_CALL(sithWeapon_SetAimWait, pThing, waitTime);
}

void J3DAPI sithWeapon_ActivateWeapon(SithThing* pThing, SithCog* pCog, float waitTime)
{
    J3D_TRAMPOLINE_CALL(sithWeapon_ActivateWeapon, pThing, pCog, waitTime);
}

float J3DAPI sithWeapon_DeactivateWeapon(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_DeactivateWeapon, pThing);
}

int J3DAPI sithWeapon_ProcessWeaponControls(SithThing* pThing, float secDeltaTime)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_ProcessWeaponControls, pThing, secDeltaTime);
}

void J3DAPI sithWeapon_DeselectWeapon(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithWeapon_DeselectWeapon, pThing);
}

int J3DAPI sithWeapon_IsMountingWeapon(const SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_IsMountingWeapon, pThing);
}

int J3DAPI sithWeapon_HasWeaponSelected(const SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_HasWeaponSelected, pThing);
}

int J3DAPI sithWeapon_GetAimOrient(rdMatrix34* pOutOrient, SithThing* pShooter, const rdMatrix34* pStartOrient, const rdVector3* pFireOffset, float autoAimFovX, float autoAimFovZ)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_GetAimOrient, pOutOrient, pShooter, pStartOrient, pFireOffset, autoAimFovX, autoAimFovZ);
}

SithThing* J3DAPI sithWeapon_FireProjectile(SithThing* pShooter, const SithThing* pProjectile, tSoundHandle hFireSnd, SithPuppetSubMode submode, rdVector3* pFireOffset, rdVector3* pAimError, float extra, SithFireProjectileFlags flags, float autoAimFovX, float autoAimFovZ)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_FireProjectile, pShooter, pProjectile, hFireSnd, submode, pFireOffset, pAimError, extra, flags, autoAimFovX, autoAimFovZ);
}

void J3DAPI sithWeapon_DeactivateCurrentWeapon(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithWeapon_DeactivateCurrentWeapon, pThing);
}

int J3DAPI sithWeapon_SelectNextWeapon(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_SelectNextWeapon, pThing);
}

int J3DAPI sithWeapon_SelectPreviousWeapon(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_SelectPreviousWeapon, pThing);
}

void J3DAPI sithWeapon_SetWeaponModel(SithThing* pThing, SithWeaponId weaponID)
{
    J3D_TRAMPOLINE_CALL(sithWeapon_SetWeaponModel, pThing, weaponID);
}

void J3DAPI sithWeapon_ResetWeaponModel(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithWeapon_ResetWeaponModel, pThing);
}

void J3DAPI sithWeapon_SetHolsterModel(SithThing* pThing, SithWeaponId weaponID, signed int meshNum)
{
    J3D_TRAMPOLINE_CALL(sithWeapon_SetHolsterModel, pThing, weaponID, meshNum);
}

void J3DAPI sithWeapon_ResetHolsterModel(SithThing* pThing, int holsterNum)
{
    J3D_TRAMPOLINE_CALL(sithWeapon_ResetHolsterModel, pThing, holsterNum);
}

void J3DAPI sithWeapon_SendMessageAim(SithThing* pThing, int bAim)
{
    J3D_TRAMPOLINE_CALL(sithWeapon_SendMessageAim, pThing, bAim);
}

void J3DAPI sithWeapon_SetActorKilledCallback(SithWeaponActorKilledCallback pfCallback)
{
    J3D_TRAMPOLINE_CALL(sithWeapon_SetActorKilledCallback, pfCallback);
}

int J3DAPI sithWeapon_IsAiming(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_IsAiming, pThing);
}

void J3DAPI sithWeapon_GenBloodsplort(SithThing* pHitThing)
{
    J3D_TRAMPOLINE_CALL(sithWeapon_GenBloodsplort, pHitThing);
}

SithWeaponId sithWeapon_GetLastWeapon(void)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_GetLastWeapon);
}

void J3DAPI sithWeapon_SetLastWeapon(SithWeaponId weaponNum)
{
    J3D_TRAMPOLINE_CALL(sithWeapon_SetLastWeapon, weaponNum);
}

float J3DAPI sithWeapon_GetWeaponMaxAimDistance(SithWeaponId weaponId)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_GetWeaponMaxAimDistance, weaponId);
}

float J3DAPI sithWeapon_GetWeaponCollideSize(SithWeaponId typeId)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_GetWeaponCollideSize, typeId);
}

int J3DAPI sithWeapon_IsLocalPlayerUnableToUseWeapon()
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_IsLocalPlayerUnableToUseWeapon);
}

int J3DAPI sithWeapon_Save(tFileHandle fh)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_Save, fh);
}

int J3DAPI sithWeapon_Restore(tFileHandle fh)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_Restore, fh);
}

SithWeaponId J3DAPI sithWeapon_GetWeaponForControlKey(SithControlFunction keyID)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_GetWeaponForControlKey, keyID);
}

SithThing* J3DAPI sithWeapon_FireProjectileEx(SithThing* pShooter, const SithThing* pProjectile, tSoundHandle hSndFire, SithPuppetSubMode submode, rdVector3* pFirePos, const rdVector3* pTargetPos, float extra, SithFireProjectileFlags flags, float autoAinFovX, float autoAimFovZ, const rdVector3* pFireOffset, int bUseFireOffset)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_FireProjectileEx, pShooter, pProjectile, hSndFire, submode, pFirePos, pTargetPos, extra, flags, autoAinFovX, autoAimFovZ, pFireOffset, bUseFireOffset);
}

void J3DAPI sithWeapon_CreateWeaponFireFx(SithThing* pThing, rdVector3* pos)
{
    J3D_TRAMPOLINE_CALL(sithWeapon_CreateWeaponFireFx, pThing, pos);
}

int J3DAPI sithWeapon_ActivateWhip(SithThing* pThing, SithCog* pCog)
{
    return J3D_TRAMPOLINE_CALL(sithWeapon_ActivateWhip, pThing, pCog);
}
