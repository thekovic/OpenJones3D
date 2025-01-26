#ifndef SITH_SITHCOGFUNCTION_H
#define SITH_SITHCOGFUNCTION_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

int J3DAPI sithCogFunction_RegisterFunctions(SithCogSymbolTable* pTable);
void J3DAPI sithCogFunction_EnablePrint(bool bEnable); // Added

// Helper hooking functions
void sithCogFunction_InstallHooks(void);
void sithCogFunction_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHCOGFUNCTION_H
