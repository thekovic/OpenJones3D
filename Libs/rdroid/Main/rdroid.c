#include "rdroid.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>

#define rdroid_bRDroidStartup J3D_DECL_FAR_VAR(rdroid_bRDroidStartup, int)
#define rdroid_bRDroidOpen J3D_DECL_FAR_VAR(rdroid_bRDroidOpen, int)

void rdroid_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdSetServices);
    // J3D_HOOKFUNC(rdClearServices);
    // J3D_HOOKFUNC(rdStartup);
    // J3D_HOOKFUNC(rdShutdown);
    // J3D_HOOKFUNC(rdOpen);
    // J3D_HOOKFUNC(rdClose);
    // J3D_HOOKFUNC(rdSetRenderOptions);
    // J3D_HOOKFUNC(rdSetGeometryMode);
    // J3D_HOOKFUNC(rdSetLightingMode);
    // J3D_HOOKFUNC(rdGetRenterOptions);
}

void rdroid_ResetGlobals(void)
{
    const rdVector3 rdroid_g_zeroVector3_tmp = { { 0.0f }, { 0.0f }, { 0.0f } };
    memcpy((rdVector3 *)&rdroid_g_zeroVector3, &rdroid_g_zeroVector3_tmp, sizeof(rdroid_g_zeroVector3));
    
    const rdVector3 rdroid_g_xVector3_tmp = { { 1.0f }, { 0.0f }, { 0.0f } };
    memcpy((rdVector3 *)&rdroid_g_xVector3, &rdroid_g_xVector3_tmp, sizeof(rdroid_g_xVector3));
    
    const rdVector3 rdroid_g_yVector3_tmp = { { 0.0f }, { 1.0f }, { 0.0f } };
    memcpy((rdVector3 *)&rdroid_g_yVector3, &rdroid_g_yVector3_tmp, sizeof(rdroid_g_yVector3));
    
    const rdVector3 rdroid_g_zVector3_tmp = { { 0.0f }, { 0.0f }, { 1.0f } };
    memcpy((rdVector3 *)&rdroid_g_zVector3, &rdroid_g_zVector3_tmp, sizeof(rdroid_g_zVector3));
    
    const rdMatrix34 rdroid_g_identMatrix34_tmp = {
      { { 1.0f }, { 0.0f }, { 0.0f } },
      { { 0.0f }, { 1.0f }, { 0.0f } },
      { { 0.0f }, { 0.0f }, { 1.0f } },
      { { 0.0f }, { 0.0f }, { 0.0f } }
    };
    memcpy((rdMatrix34 *)&rdroid_g_identMatrix34, &rdroid_g_identMatrix34_tmp, sizeof(rdroid_g_identMatrix34));
    
    memset(&rdroid_bRDroidStartup, 0, sizeof(rdroid_bRDroidStartup));
    memset(&rdroid_bRDroidOpen, 0, sizeof(rdroid_bRDroidOpen));
    memset(&rdroid_g_curLightingMode, 0, sizeof(rdroid_g_curLightingMode));
    memset(&rdroid_g_pHS, 0, sizeof(rdroid_g_pHS));
    memset(&rdroid_g_curGeometryMode, 0, sizeof(rdroid_g_curGeometryMode));
    memset(&rdroid_g_curRenderOptions, 0, sizeof(rdroid_g_curRenderOptions));
}

void J3DAPI rdSetServices(tHostServices* pHS)
{
    J3D_TRAMPOLINE_CALL(rdSetServices, pHS);
}

void rdClearServices(void)
{
    J3D_TRAMPOLINE_CALL(rdClearServices);
}

void J3DAPI rdStartup()
{
    J3D_TRAMPOLINE_CALL(rdStartup);
}

void J3DAPI rdShutdown()
{
    J3D_TRAMPOLINE_CALL(rdShutdown);
}

int J3DAPI rdOpen()
{
    return J3D_TRAMPOLINE_CALL(rdOpen);
}

void J3DAPI rdClose()
{
    J3D_TRAMPOLINE_CALL(rdClose);
}

void J3DAPI rdSetRenderOptions(rdRoidFlags options)
{
    J3D_TRAMPOLINE_CALL(rdSetRenderOptions, options);
}

void J3DAPI rdSetGeometryMode(rdGeometryMode mode)
{
    J3D_TRAMPOLINE_CALL(rdSetGeometryMode, mode);
}

void J3DAPI rdSetLightingMode(rdLightMode mode)
{
    J3D_TRAMPOLINE_CALL(rdSetLightingMode, mode);
}

rdRoidFlags J3DAPI rdGetRenterOptions()
{
    return J3D_TRAMPOLINE_CALL(rdGetRenterOptions);
}
