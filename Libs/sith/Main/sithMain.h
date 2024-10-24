#ifndef SITH_SITHMAIN_H
#define SITH_SITHMAIN_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>

#include <std/types.h>
#include <std/General/std.h>

J3D_EXTERN_C_START

#define SITH_RAND() ((double)rand() * (1.0 / RAND_MAX))
#define SITHLOG_DEBUG(format, ...) \
    J3DLOG_DEBUG(sith_g_pHS, format, ##__VA_ARGS__)

#define SITHLOG_STATUS(format, ...) \
    J3DLOG_STATUS(sith_g_pHS, format, ##__VA_ARGS__)

#define SITHLOG_MESSAGE(format, ...) \
    J3DLOG_MESSAGE(sith_g_pHS, format, ##__VA_ARGS__)

#define SITHLOG_WARNING(format, ...) \
    J3DLOG_WARNING(sith_g_pHS, format, ##__VA_ARGS__)

#define SITHLOG_ERROR(format, ...) \
    J3DLOG_ERROR(sith_g_pHS, format, ##__VA_ARGS__)

#define SITHLOG_FATAL(message) \
    J3DLOG_FATAL(sith_g_pHS, message)

#define SITH_ASSERT(condition) \
    J3D_ASSERT(condition, sith_g_pHS )

#define SITH_ASSERTREL(condition) \
    J3D_ASSERTREL(condition, sith_g_pHS )

#define sith_g_pHS J3D_DECL_FAR_VAR(sith_g_pHS, tHostServices*)
// extern tHostServices *sith_g_pHS;

#define sithMain_g_frameNumber J3D_DECL_FAR_VAR(sithMain_g_frameNumber, int)
// extern int sithMain_g_frameNumber;

#define sithMain_g_sith_mode J3D_DECL_FAR_VAR(sithMain_g_sith_mode, SithMode)
// extern SithMode sithMain_g_sith_mode;

#define sithMain_g_curRenderTick J3D_DECL_FAR_VAR(sithMain_g_curRenderTick, unsigned int)
// extern unsigned int sithMain_g_curRenderTick;

void J3DAPI sithSetServices(tHostServices* pHS);
void sithClearServices(void);
int J3DAPI sithStartup();
void sithShutdown(void);
int J3DAPI sithSetPerformanceLevel(int level);
int sithGetPerformanceLevel(void);
int J3DAPI sithOpenStatic(const char* pFilename);
void sithCloseStatic(void);
// NOTE: there is debug info that originally this function was named: sithOpenNormal
int J3DAPI sithOpenNormal(char* pWorldName, const wchar_t* wszPlayerName);
void J3DAPI sithOpenPostProcess();
int J3DAPI sithOpen(const wchar_t* wszPlayerName);
void sithClose(void);
void sithUpdate(void);
void sithDrawScene(void);
void J3DAPI sithSetGameDifficulty(int difficulty);
int J3DAPI sithGetGameDifficulty();
float J3DAPI sithGetHitAccuarancyScalar();
float J3DAPI sithGetCombatDamageScalar();
double J3DAPI sithGetIMPDamageScalar();
void J3DAPI sithAdvanceRenderTick();
void sithMakeDirs(void);
const char* J3DAPI sithGetAutoSaveFilePrefix();
const char* J3DAPI sithGetPath(char* aOutPath, char* pKey, int bPrependInstallDirPath);
const char* J3DAPI sithGetSaveGamesDir();
const char* J3DAPI sithGetQuickSaveFilePrefix();
const char* J3DAPI sithGetScreenShotsDir();
const char* J3DAPI sithGetScreenShotFileTemplate();
void J3DAPI sithSetOpenCallback(SithOpenCallback pfCallback);
const char* J3DAPI sithGetCurrentWorldSaveName();
const char* J3DAPI sithGetLevelSaveFilename(unsigned int levelNum);

// Helper hooking functions
void sithMain_InstallHooks(void);
void sithMain_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHMAIN_H
