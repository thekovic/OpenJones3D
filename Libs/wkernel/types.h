#ifndef WKERNEL_TYPES_H
#define WKERNEL_TYPES_H
#include <stdint.h>
#include <j3dcore/j3d.h>

J3D_EXTERN_C_START

typedef int (J3DAPI* WKERNELSTARTUPPROC)(const char* cmd);
typedef int (*WKERNELPROC)(void);
typedef void (*WKERNELSHUTDOWNPROC)(void);
typedef int (J3DAPI* WKERNELWNDPROC)(HWND, UINT, WPARAM, LPARAM, int* pRetValue);

J3D_EXTERN_C_END
#endif //WKERNEL_TYPES_H
