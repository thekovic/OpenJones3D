#ifndef WKERNEL_WKERNEL_H
#define WKERNEL_WKERNEL_H
#include <j3dcore/j3d.h>
#include <wkernel/types.h>
#include <wkernel/RTI/addresses.h>

// TODO: move module to std

J3D_EXTERN_C_START

int J3DAPI wkernel_Run(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd, LPCSTR lpWindowName); // Note, process proc must be set before
WKERNELPROC J3DAPI wkernel_SetProcessProc(WKERNELPROC pfProc);
WKERNELSTARTUPPROC J3DAPI wkernel_SetStartupCallback(WKERNELSTARTUPPROC pfOnStartup);
WKERNELSHUTDOWNPROC J3DAPI wkernel_SetShutdownCallback(WKERNELSHUTDOWNPROC pfOnShutdown);
void J3DAPI wkernel_SetWindowStyle(LONG dwNewLong);
BOOL J3DAPI wkernel_SetWindowSize(int width, int height);
void J3DAPI wkernel_SetWindowProc(WKERNELWNDPROC pfProc); // Window process
int wkernel_PeekProcessEvents(void);
int wkernel_ProcessEvents(void);

// Helper hooking functions
void wkernel_InstallHooks(void);
void wkernel_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // WKERNEL_WKERNEL_H
