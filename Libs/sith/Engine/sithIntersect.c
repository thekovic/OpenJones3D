#include "sithIntersect.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithIntersect_aSphereHitIndices J3D_DECL_FAR_ARRAYVAR(sithIntersect_aSphereHitIndices, int(*)[3][2])

void sithIntersect_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithIntersect_IsSphereInSector);
    // J3D_HOOKFUNC(sithIntersect_CheckFaceVerticesIntersection);
    // J3D_HOOKFUNC(sithIntersect_CheckSphereThingIntersection);
    // J3D_HOOKFUNC(sithIntersect_CheckSphereThingModelIntersection);
    // J3D_HOOKFUNC(sithIntersect_CheckSphereMeshIntersection);
    // J3D_HOOKFUNC(sithIntersect_CheckSphereIntersection);
    // J3D_HOOKFUNC(sithIntersect_TestSphereFaceHit);
    // J3D_HOOKFUNC(sithIntersect_CheckSphereFaceHitVerticesIntersection);
    // J3D_HOOKFUNC(sithIntersect_CheckSphereHit);
    // J3D_HOOKFUNC(sithIntersect_CheckSphereFaceIntersectionEx);
    // J3D_HOOKFUNC(sithIntersect_CheckSphereFaceIntersection);
}

void sithIntersect_ResetGlobals(void)
{
    int sithIntersect_aSphereHitIndices_tmp[3][2] = { { 2, 1 }, { 0, 2 }, { 1, 0 } };
    memcpy(&sithIntersect_aSphereHitIndices, &sithIntersect_aSphereHitIndices_tmp, sizeof(sithIntersect_aSphereHitIndices));
    
}

int J3DAPI sithIntersect_IsSphereInSector(const SithWorld* pWorld, const rdVector3* pos, float radius, const SithSector* pSector)
{
    return J3D_TRAMPOLINE_CALL(sithIntersect_IsSphereInSector, pWorld, pos, radius, pSector);
}

SithCollisionType J3DAPI sithIntersect_CheckFaceVerticesIntersection(const rdVector3* startPos, float radius, const rdFace* pFace, const rdVector3* aVertices, rdVector3* pHitVert)
{
    return J3D_TRAMPOLINE_CALL(sithIntersect_CheckFaceVerticesIntersection, startPos, radius, pFace, aVertices, pHitVert);
}

SithCollisionType J3DAPI sithIntersect_CheckSphereThingIntersection(SithThing* pThing, const rdVector3* startPos, const rdVector3* moveNorm, float moveDist, float radius, SithThing* pCheck, int flags, float* pHitDistance, rdModel3Mesh** ppHitMesh, rdFace** ppHitFace, rdVector3* hitNorm)
{
    return J3D_TRAMPOLINE_CALL(sithIntersect_CheckSphereThingIntersection, pThing, startPos, moveNorm, moveDist, radius, pCheck, flags, pHitDistance, ppHitMesh, ppHitFace, hitNorm);
}

SithCollisionType J3DAPI sithIntersect_CheckSphereThingModelIntersection(const rdVector3* startPos, const rdVector3* moveNorm, float moveDist, float radius, const rdThing* prdThing, float* hitDistance, rdFace** ppFace, rdModel3Mesh** ppMesh, rdVector3* hitNorm)
{
    return J3D_TRAMPOLINE_CALL(sithIntersect_CheckSphereThingModelIntersection, startPos, moveNorm, moveDist, radius, prdThing, hitDistance, ppFace, ppMesh, hitNorm);
}

SithCollisionType J3DAPI sithIntersect_CheckSphereMeshIntersection(const rdVector3* startPos, const rdVector3* moveNorm, float moveDist, float radius, const rdModel3Mesh* pMesh, float* hitDistance, rdFace** ppFace, rdVector3* hitNorm)
{
    return J3D_TRAMPOLINE_CALL(sithIntersect_CheckSphereMeshIntersection, startPos, moveNorm, moveDist, radius, pMesh, hitDistance, ppFace, hitNorm);
}

int J3DAPI sithIntersect_CheckSphereIntersection(const rdVector3* startPos, const rdVector3* moveNorm, float moveDist, float radius, const rdVector3* endPos, float size, float* hitDistance, int bCheckEndPos, int flags)
{
    return J3D_TRAMPOLINE_CALL(sithIntersect_CheckSphereIntersection, startPos, moveNorm, moveDist, radius, endPos, size, hitDistance, bCheckEndPos, flags);
}

int J3DAPI sithIntersect_TestSphereFaceHit(const rdVector3* startPos, float radius, const rdFace* pFace, const rdVector3* aVertices, int* pHitMask)
{
    return J3D_TRAMPOLINE_CALL(sithIntersect_TestSphereFaceHit, startPos, radius, pFace, aVertices, pHitMask);
}

SithCollisionType J3DAPI sithIntersect_CheckSphereFaceHitVerticesIntersection(const rdVector3* startPos, float radius, const rdFace* pFace, const rdVector3* aVertices, int vertHitMask, rdVector3* pHitVert)
{
    return J3D_TRAMPOLINE_CALL(sithIntersect_CheckSphereFaceHitVerticesIntersection, startPos, radius, pFace, aVertices, vertHitMask, pHitVert);
}

int J3DAPI sithIntersect_CheckSphereHit(const rdVector3* startPos, const rdVector3* moveNorm, float moveDistance, float radius, const rdVector3* normal, const rdVector3* point, float* pSphereHitDist, int flags)
{
    return J3D_TRAMPOLINE_CALL(sithIntersect_CheckSphereHit, startPos, moveNorm, moveDistance, radius, normal, point, pSphereHitDist, flags);
}

SithCollisionType J3DAPI sithIntersect_CheckSphereFaceIntersectionEx(const rdVector3* startPos, const rdVector3* moveNorm, float moveDistance, float radius, const rdFace* pFace, const rdVector3* aVertices, float* pHitDist, rdVector3* hitNorm, int flags)
{
    return J3D_TRAMPOLINE_CALL(sithIntersect_CheckSphereFaceIntersectionEx, startPos, moveNorm, moveDistance, radius, pFace, aVertices, pHitDist, hitNorm, flags);
}

SithCollisionType J3DAPI sithIntersect_CheckSphereFaceIntersection(const rdVector3* startPos, const rdVector3* moveNorm, float moveDistance, float radius, const rdFace* pFace, const rdVector3* aVertices, float* pHitDist, int flags)
{
    return J3D_TRAMPOLINE_CALL(sithIntersect_CheckSphereFaceIntersection, startPos, moveNorm, moveDistance, radius, pFace, aVertices, pHitDist, flags);
}
