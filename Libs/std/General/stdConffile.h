#ifndef STD_STDCONFFILE_H
#define STD_STDCONFFILE_H
#include <j3dcore/j3d.h>
#include <std/types.h>
#include <std/RTI/addresses.h>

#include <stdio.h>

J3D_EXTERN_C_START

#define stdConffile_g_entry J3D_DECL_FAR_VAR(stdConffile_g_entry, StdConffileEntry)
// extern StdConffileEntry stdConffile_g_entry;

#define stdConffile_g_aLine J3D_DECL_FAR_VAR(stdConffile_g_aLine, char*)
// extern char *stdConffile_g_aLine;

int J3DAPI stdConffile_Open(const char* pFilename);
int J3DAPI stdConffile_OpenWrite(const char* pFilename);
int J3DAPI stdConffile_OpenMode(const char* pFilename, const char* openMode);
void stdConffile_Close(void);
void stdConffile_CloseWrite(void);
int J3DAPI stdConffile_Write(const void* pData, int size);
int J3DAPI stdConffile_Read(void* pData, size_t size);
int J3DAPI stdConffile_ReadArgsFromStr(char* pStr);
int stdConffile_ReadArgs(void);
int stdConffile_ReadLine(void);
tFileHandle stdConffile_GetFileHandle(void);
int stdConffile_GetLineNumber(void);
const char* stdConffile_GetFilename(void);
void stdConffile_PushStack(void);
void stdConffile_PopStack(void);

// Helper hooking functions
void stdConffile_InstallHooks(void);
void stdConffile_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // STD_STDCONFFILE_H
