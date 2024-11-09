#ifndef SITH_SITHTIME_H
#define SITH_SITHTIME_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define sithTime_g_frameTime J3D_DECL_FAR_VAR(sithTime_g_frameTime, uint32_t)
// extern unsigned int sithTime_g_frameTime;

#define sithTime_g_frameTimeFlex J3D_DECL_FAR_VAR(sithTime_g_frameTimeFlex, float)
// extern float sithTime_g_secFrameTime;

#define sithTime_g_fps J3D_DECL_FAR_VAR(sithTime_g_fps, float)
// extern float sithTime_g_fps;

#define sithTime_g_msecGameTime J3D_DECL_FAR_VAR(sithTime_g_msecGameTime, uint32_t)
// extern unsigned int sithTime_g_msecGameTime;

#define sithTime_g_secGameTime J3D_DECL_FAR_VAR(sithTime_g_secGameTime, float)
// extern float sithTime_g_secGameTime;

#define sithTime_g_clockTime J3D_DECL_FAR_VAR(sithTime_g_clockTime, uint32_t)
// extern unsigned int sithTime_g_clockTime;

#define sithTime_g_bPaused J3D_DECL_FAR_VAR(sithTime_g_bPaused, int)
// extern int sithTime_g_bPaused;

void sithTime_Advance(void);
void sithTime_Pause(void);
void sithTime_Resume(void);
void J3DAPI sithTime_SetFrameTime(uint32_t frameTime); //Added
void sithTime_Reset(void);
void J3DAPI sithTime_SetGameTime(uint32_t msecTime);
int sithTime_IsPaused(void);

// Helper hooking functions
void sithTime_InstallHooks(void);
void sithTime_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHTIME_H
