#ifndef STD_STDFNAMES_H
#define STD_STDFNAMES_H
#include <j3dcore/j3d.h>
#include <std/types.h>
#include <std/RTI/addresses.h>

J3D_EXTERN_C_START

const char* J3DAPI stdFnames_FindMedName(const char* pFilePath);
char* J3DAPI stdFnames_FindExt(const char* pFilePath);
void J3DAPI stdFnames_StripExtAndDot(char* pPath);
void J3DAPI stdFnames_ChangeExt(char* pPath, const char* pExt);
void J3DAPI stdFnames_Concat(char* dst, const char* src, int size);
void J3DAPI stdFnames_MakePath(char* aOutPath, int size, const char* pPath1, const char* pPath2);

// Helper hooking functions
void stdFnames_InstallHooks(void);
void stdFnames_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // STD_STDFNAMES_H
