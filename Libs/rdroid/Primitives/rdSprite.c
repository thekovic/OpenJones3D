#include "rdSprite.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>

#define rdSprite_aView J3D_DECL_FAR_VAR(rdSprite_aView, rdMatrix34)

void rdSprite_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdSprite_NewEntry);
    // J3D_HOOKFUNC(rdSprite_FreeEntry);
    // J3D_HOOKFUNC(rdSprite_Draw);
}

void rdSprite_ResetGlobals(void)
{
    memset(&rdSprite_aView, 0, sizeof(rdSprite_aView));
}

int J3DAPI rdSprite_NewEntry(rdSprite3* pSprite, const char* pName, int type, const char* pMatName, float width, float height, rdGeometryMode geomode, rdLightMode lightmode, const rdVector4* pExtraLight, const rdVector3* pOffset)
{
    return J3D_TRAMPOLINE_CALL(rdSprite_NewEntry, pSprite, pName, type, pMatName, width, height, geomode, lightmode, pExtraLight, pOffset);
}

void J3DAPI rdSprite_FreeEntry(rdSprite3* pSprite)
{
    J3D_TRAMPOLINE_CALL(rdSprite_FreeEntry, pSprite);
}

int J3DAPI rdSprite_Draw(rdThing* prdThing, const rdMatrix34* orient)
{
    return J3D_TRAMPOLINE_CALL(rdSprite_Draw, prdThing, orient);
}
