#ifndef RDROID_RDPARTICLE_H
#define RDROID_RDPARTICLE_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <rdroid/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

rdParticle* J3DAPI rdParticle_New(unsigned int num, float size, rdMaterial* pMat, rdLightMode lightMode);
int J3DAPI rdParticle_NewEntry(rdParticle* pParticle, unsigned int num, float size, rdMaterial* pMaterial, rdLightMode lightMode);
rdParticle* J3DAPI rdParticle_Duplicate(const rdParticle* pOriginal);
void J3DAPI rdParticle_Free(rdParticle* pParticle);
void J3DAPI rdParticle_FreeEntry(rdParticle* pParticle);
int J3DAPI rdParticle_LoadEntry(const char* pFilename, rdParticle* pParticle);
int J3DAPI rdParticle_Draw(const rdThing* pParticle, const rdMatrix34* pOrient);

// Helper hooking functions
void rdParticle_InstallHooks(void);
void rdParticle_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // RDROID_RDPARTICLE_H
