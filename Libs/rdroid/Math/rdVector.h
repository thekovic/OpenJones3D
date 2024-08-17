#ifndef RDROID_RDVECTOR_H
#define RDROID_RDVECTOR_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <rdroid/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

void J3DAPI rdVector_Set3(rdVector3* dest, float x, float y, float z);
void J3DAPI rdVector_Set4(rdVector4* dest, float x, float y, float z, float w);
void J3DAPI rdVector_Neg3(rdVector3* dest, const rdVector3* src);
void J3DAPI rdVector_Add3Acc(rdVector3* a, const rdVector3* b);
float J3DAPI rdVector_Dot3(const rdVector3* a, const rdVector3* b);
float J3DAPI rdVector_Len3(const rdVector3* vec);
float J3DAPI rdVector_Normalize3(rdVector3* dest, const rdVector3* src);
float J3DAPI rdVector_Normalize2Acc(rdVector2* vec);
float J3DAPI rdVector_Normalize3Acc(rdVector3* vec);
float J3DAPI rdVector_Normalize3QuickAcc(rdVector3* src);
void J3DAPI rdVector_InvScale3(rdVector3* dest, const rdVector3* src, float scalar);
void J3DAPI rdVector_Rotate3(rdVector3* vec, const rdVector3* pivot, const rdVector3* pyr);
void J3DAPI rdVector_Rotate3Acc(rdVector3* vec, const rdVector3* pyr);

// Helper hooking functions
void rdVector_InstallHooks(void);
void rdVector_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // RDROID_RDVECTOR_H
