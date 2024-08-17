#ifndef JONES3D_JONESFILE_H
#define JONES3D_JONESFILE_H
#include <Jones3D/types.h>
#include <Jones3D/RTI/addresses.h>
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <std/types.h>

J3D_EXTERN_C_START

void J3DAPI JonesFile_Startup(tHostServices* pHS);
void JonesFile_Shutdown(void);
int J3DAPI JonesFile_Open(tHostServices* pEnv, const char* pInstallPath, const char* pPathCD);
void J3DAPI JonesFile_Close();
int J3DAPI JonesFile_GetCurrentCDNum();
int J3DAPI JonesFile_FileExists(const char* pFilename);
void J3DAPI JonesFile_AddInstallPath(const char* pPath);
void J3DAPI JonesFile_AddCDPath(const char* pPath);
void JonesFile_InitServices(void);
void JonesFile_ResetServices(void);
void J3DAPI JonesFile_AddResourcePath(JonesResource* pRsource, const char* pPath);
void J3DAPI JonesFile_CloseResource(JonesResource* pResource);
tFileHandle J3DAPI JonesFile_OpenFile(const char* pFilename, const char* mode);
int J3DAPI JonesFile_CloseFile(tFileHandle fh);
size_t J3DAPI JonesFile_FileRead(tFileHandle fh, void* pDst, size_t size);
size_t J3DAPI JonesFile_FileWrite(tFileHandle fh, const void* pData, size_t size);
char* J3DAPI JonesFile_FileGets(tFileHandle fh, char* pStr, size_t size);
int J3DAPI JonesFile_FileEOF(tFileHandle fh);
int J3DAPI JonesFile_FileTell(tFileHandle fh);
int J3DAPI JonesFile_FileSeek(tFileHandle fh, int offset, int origin);
size_t J3DAPI JonesFile_FileSize(const char* pFilename);
int JonesFile_FilePrintf(tFileHandle fh, const char* aFormat, ...);

// Helper hooking functions
void JonesFile_InstallHooks(void);
void JonesFile_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // JONES3D_JONESFILE_H
