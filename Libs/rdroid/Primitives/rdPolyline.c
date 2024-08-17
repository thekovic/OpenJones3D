#include "rdPolyline.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>

#define rdPolyline_aVerticesCache J3D_DECL_FAR_ARRAYVAR(rdPolyline_aVerticesCache, rdVector3(*)[4])

void rdPolyline_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdPolyline_New);
    // J3D_HOOKFUNC(rdPolyline_NewEntry);
    // J3D_HOOKFUNC(rdPolyline_Free);
    // J3D_HOOKFUNC(rdPolyline_FreeEntry);
    // J3D_HOOKFUNC(rdPolyline_Draw);
    // J3D_HOOKFUNC(rdPolyline_DrawFace);
}

void rdPolyline_ResetGlobals(void)
{
    memset(&rdPolyline_aVerticesCache, 0, sizeof(rdPolyline_aVerticesCache));
}

rdPolyline* J3DAPI rdPolyline_New(const char* pName, const char* pMatFilename, const char* pMatFilename2, float length, float baseRadius, float tipRadius, rdGeometryMode geoMode, rdLightMode lightMode, const rdVector4* pColor)
{
    return J3D_TRAMPOLINE_CALL(rdPolyline_New, pName, pMatFilename, pMatFilename2, length, baseRadius, tipRadius, geoMode, lightMode, pColor);
}

int J3DAPI rdPolyline_NewEntry(rdPolyline* pLine, const char* pName, const char* pMatFilename, float length, float baseRadius, float tipRadius, rdGeometryMode geoMode, rdLightMode lightMode, const rdVector4* pColor)
{
    return J3D_TRAMPOLINE_CALL(rdPolyline_NewEntry, pLine, pName, pMatFilename, length, baseRadius, tipRadius, geoMode, lightMode, pColor);
}

void J3DAPI rdPolyline_Free(rdPolyline* pPolyline)
{
    J3D_TRAMPOLINE_CALL(rdPolyline_Free, pPolyline);
}

void J3DAPI rdPolyline_FreeEntry(rdPolyline* pPolyline)
{
    J3D_TRAMPOLINE_CALL(rdPolyline_FreeEntry, pPolyline);
}

int J3DAPI rdPolyline_Draw(const rdThing* pLine, const rdMatrix34* pOrient)
{
    return J3D_TRAMPOLINE_CALL(rdPolyline_Draw, pLine, pOrient);
}

void J3DAPI rdPolyline_DrawFace(const rdThing* pLine, const rdFace* pFace, const rdVector3* aVertices, const rdVector2* aUVs)
{
    J3D_TRAMPOLINE_CALL(rdPolyline_DrawFace, pLine, pFace, aVertices, aUVs);
}
