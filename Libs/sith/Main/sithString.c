#include "sithString.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithString_sithStringsTbl J3D_DECL_FAR_VAR(sithString_sithStringsTbl, tStringTable)
#define sithString_voiceStringsTbl J3D_DECL_FAR_VAR(sithString_voiceStringsTbl, tStringTable)
#define sithString_bStartup J3D_DECL_FAR_VAR(sithString_bStartup, int)

void sithString_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithString_Startup);
    // J3D_HOOKFUNC(sithString_Shutdown);
    // J3D_HOOKFUNC(sithString_GetString);
}

void sithString_ResetGlobals(void)
{
    memset(&sithString_sithStringsTbl, 0, sizeof(sithString_sithStringsTbl));
    memset(&sithString_voiceStringsTbl, 0, sizeof(sithString_voiceStringsTbl));
    memset(&sithString_bStartup, 0, sizeof(sithString_bStartup));
}

int sithString_Startup(void)
{
    return J3D_TRAMPOLINE_CALL(sithString_Startup);
}

void sithString_Shutdown(void)
{
    J3D_TRAMPOLINE_CALL(sithString_Shutdown);
}

wchar_t* J3DAPI sithString_GetString(const char* pStr)
{
    return J3D_TRAMPOLINE_CALL(sithString_GetString, pStr);
}
