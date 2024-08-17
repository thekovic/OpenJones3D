#include "wuRegistry.h"
#include <j3dcore/j3dhook.h>
#include <w32util/RTI/symbols.h>

#define wuRegistry_appSubKey J3D_DECL_FAR_VAR(wuRegistry_appSubKey, LPCSTR)
#define wuRegistry_appRootKey J3D_DECL_FAR_VAR(wuRegistry_appRootKey, HKEY)

void wuRegistry_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(wuRegistry_Startup);
    // J3D_HOOKFUNC(wuRegistry_Shutdown);
    // J3D_HOOKFUNC(wuRegistry_SaveInt);
    // J3D_HOOKFUNC(wuRegistry_SaveFloat);
    // J3D_HOOKFUNC(wuRegistry_GetInt);
    // J3D_HOOKFUNC(wuRegistry_GetFloat);
    // J3D_HOOKFUNC(wuRegistry_SaveIntEx);
    // J3D_HOOKFUNC(wuRegistry_GetIntEx);
    // J3D_HOOKFUNC(wuRegistry_SaveStr);
    // J3D_HOOKFUNC(wuRegistry_GetStr);
}

void wuRegistry_ResetGlobals(void)
{
    memset(&wuRegistry_g_bStarted, 0, sizeof(wuRegistry_g_bStarted));
    memset(&wuRegistry_appSubKey, 0, sizeof(wuRegistry_appSubKey));
    memset(&wuRegistry_appRootKey, 0, sizeof(wuRegistry_appRootKey));
}

int J3DAPI wuRegistry_Startup(HKEY hKey, LPCSTR lpSubKey)
{
    return J3D_TRAMPOLINE_CALL(wuRegistry_Startup, hKey, lpSubKey);
}

void J3DAPI wuRegistry_Shutdown()
{
    J3D_TRAMPOLINE_CALL(wuRegistry_Shutdown);
}

int J3DAPI wuRegistry_SaveInt(const char* pKey, int value)
{
    return J3D_TRAMPOLINE_CALL(wuRegistry_SaveInt, pKey, value);
}

int J3DAPI wuRegistry_SaveFloat(const char* pKey, float value)
{
    return J3D_TRAMPOLINE_CALL(wuRegistry_SaveFloat, pKey, value);
}

int J3DAPI wuRegistry_GetInt(const char* pKey, int defaultValue)
{
    return J3D_TRAMPOLINE_CALL(wuRegistry_GetInt, pKey, defaultValue);
}

float J3DAPI wuRegistry_GetFloat(const char* pKey, float defaultValue)
{
    return J3D_TRAMPOLINE_CALL(wuRegistry_GetFloat, pKey, defaultValue);
}

int J3DAPI wuRegistry_SaveIntEx(const char* pKey, int defaultValue)
{
    return J3D_TRAMPOLINE_CALL(wuRegistry_SaveIntEx, pKey, defaultValue);
}

int J3DAPI wuRegistry_GetIntEx(const char* pKey, int defaultValue)
{
    return J3D_TRAMPOLINE_CALL(wuRegistry_GetIntEx, pKey, defaultValue);
}

int J3DAPI wuRegistry_SaveStr(const char* pKey, const char* pStr)
{
    return J3D_TRAMPOLINE_CALL(wuRegistry_SaveStr, pKey, pStr);
}

int J3DAPI wuRegistry_GetStr(const char* pKey, char* pDstStr, size_t size, const char* pDefaultValue)
{
    return J3D_TRAMPOLINE_CALL(wuRegistry_GetStr, pKey, pDstStr, size, pDefaultValue);
}
