#ifndef JONES3D_INDY3D_H
#define JONES3D_INDY3D_H
#include <Jones3D/types.h>
#include <Jones3D/RTI/addresses.h>
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <std/types.h>

J3D_EXTERN_C_START

int __stdcall Indy3D_WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);

// Helper hooking functions
void Indy3D_InstallHooks(void);
void Indy3D_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // JONES3D_INDY3D_H
