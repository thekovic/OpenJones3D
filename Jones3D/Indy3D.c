#include "Indy3D.h"
#include <j3dcore/j3dhook.h>
#include <Jones3D/RTI/symbols.h>


void Indy3D_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(Indy3D_WinMain);
}

void Indy3D_ResetGlobals(void)
{

}

int __stdcall Indy3D_WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    return J3D_TRAMPOLINE_CALL(Indy3D_WinMain, hInstance, hPrevInstance, lpCmdLine, nShowCmd);
}
