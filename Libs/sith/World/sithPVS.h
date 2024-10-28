#ifndef SITH_SITHPVS_H
#define SITH_SITHPVS_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

int J3DAPI sithPVS_LoadText(SithWorld* pWorld, int bSkip);
int J3DAPI sithPVS_WriteBinary(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithPVS_LoadBinary(tFileHandle fh, SithWorld* pWorld);
void J3DAPI sithPVS_SetTable(uint8_t* paAdjoinTable, const uint8_t* aElements, size_t numAdjoints);

// Helper hooking functions
void sithPVS_InstallHooks(void);
void sithPVS_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHPVS_H
