#ifndef STD_STDPLATFORM_H
#define STD_STDPLATFORM_H
#include <j3dcore/j3d.h>
#include <std/types.h>
#include <std/RTI/addresses.h>

J3D_EXTERN_C_START

int J3DAPI stdPlatform_InitServices(tHostServices* pHS);
void J3DAPI stdPlatform_ClearServices(tHostServices* pHS);
unsigned int stdPlatform_GetTimeMsec(void);

J3DNORETURN void J3DAPI stdPlatform_Assert(const char* pErrorStr, const char* pFilename, int linenum);
int stdPlatform_Printf(const char* format, ...);

void* J3DAPI stdPlatform_AllocHandle(size_t size);
void J3DAPI stdPlatform_FreeHandle(void* pData);
void* J3DAPI stdPlatform_ReallocHandle(void* pMemory, size_t newSize);

int J3DAPI stdPlatform_LockHandle(int a1);
void J3DAPI stdPlatform_UnlockHandle();

bool J3DAPI stdPlatform_DirExists(const char* pPath);

// Helper hooking functions
void stdPlatform_InstallHooks(void);
void stdPlatform_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // STD_STDPLATFORM_H
