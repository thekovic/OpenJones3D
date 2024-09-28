#ifndef SITH_SITHGAMESAVE_H
#define SITH_SITHGAMESAVE_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define SITHSAVEGAME_THUMB_WIDTH  128
#define SITHSAVEGAME_THUMB_HEIGHT 96

SithGameStatistics* J3DAPI sithGamesave_GetGameStatistics();
int sithGamesave_LockGameStatistics(void);
int sithGamesave_UnlockGameStatistics(void);
int J3DAPI sithGamesave_Save(const char* pFilename, int bOverwrite);
int J3DAPI sithGamesave_Restore(const char* pFilename, int bNotifyCog);
int J3DAPI sithGamesave_SaveCurrentWorld(unsigned int outstream);
int sithGamesave_Process(void);
int J3DAPI sithGamesave_RestoreFile(const char* pFilename, int bNotify);
void J3DAPI sithGamesave_NotifyRestored(const char* pFilePath);
int J3DAPI sithGamesave_ReadBlockTypeLength(uint16_t* pType, unsigned int* pLength);
int J3DAPI sithGamesave_SaveFile(const char* pFilename);
void J3DAPI sithGamesave_ScreenShot(tVBuffer* pVBuffer);
HBITMAP J3DAPI sithGamesave_GetScreenShotBitmap();
int J3DAPI sithGamesave_WriteScreenShot(tFileHandle fh);
int J3DAPI sithGamesave_SeekThumbNail(tFileHandle fh);
HBITMAP J3DAPI sithGamesave_LoadThumbnail(const char* pFilename);
void sithGamesave_Startup(void);
void J3DAPI sithGamesave_Shutdown();
void J3DAPI sithGamesave_Open();
void sithGamesave_CloseRestore(void);
void J3DAPI sithGamesave_Close();
void J3DAPI sithGamesave_SetPreviousLevelFilename(const char* pFilename);
const char* J3DAPI sithGamesave_GetPreviousLevelFilename();
const char* J3DAPI sithGamesave_GetLastFilename();
int J3DAPI sithGamesave_LoadLevelFilename(const char* pNdsFilePath, char* pDestFilename);
int J3DAPI sithGamesave_GetState(char** ppDestNdsFilePath);
void J3DAPI sithGamesave_SetSaveGameCallback(SithGameSaveCallback pfCallback);

// Helper hooking functions
void sithGamesave_InstallHooks(void);
void sithGamesave_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHGAMESAVE_H
