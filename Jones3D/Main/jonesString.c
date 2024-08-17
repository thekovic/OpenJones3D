#include "jonesString.h"
#include <j3dcore/j3dhook.h>
#include <Jones3D/RTI/symbols.h>

#define jonesString_jonesStringsTbl J3D_DECL_FAR_VAR(jonesString_jonesStringsTbl, tStringTable)
#define jonesString_aBuffer J3D_DECL_FAR_ARRAYVAR(jonesString_aBuffer, char(*)[512])
#define jonesString_bStarted J3D_DECL_FAR_VAR(jonesString_bStarted, int)

void jonesString_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(jonesString_GetString);
    // J3D_HOOKFUNC(jonesString_Startup);
    // J3D_HOOKFUNC(jonesString_Shutdown);
}

void jonesString_ResetGlobals(void)
{
    memset(&jonesString_jonesStringsTbl, 0, sizeof(jonesString_jonesStringsTbl));
    memset(&jonesString_aBuffer, 0, sizeof(jonesString_aBuffer));
    memset(&jonesString_bStarted, 0, sizeof(jonesString_bStarted));
}

const char* J3DAPI jonesString_GetString(const char* pKey)
{
    return J3D_TRAMPOLINE_CALL(jonesString_GetString, pKey);
}

int J3DAPI jonesString_Startup()
{
    return J3D_TRAMPOLINE_CALL(jonesString_Startup);
}

void jonesString_Shutdown(void)
{
    J3D_TRAMPOLINE_CALL(jonesString_Shutdown);
}
