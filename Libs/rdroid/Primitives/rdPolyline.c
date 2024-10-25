#include "rdPolyline.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>

#include <rdroid/Engine/rdCamera.h>
#include <rdroid/Engine/rdClip.h>
#include <rdroid/Engine/rdMaterial.h>
#include <rdroid/Main/rdroid.h>
#include <rdroid/Math/rdMath.h>
#include <rdroid/Math/rdMatrix.h>
#include <rdroid/Math/rdVector.h>
#include <rdroid/Raster/rdCache.h>
#include <rdroid/RTI/symbols.h>

#include <sith/World/sithWorld.h>

#include <std/General/stdMemory.h>
#include <std/General/stdUtil.h>

rdVector3 rdPolyline_aVerticesCache[4];

void rdPolyline_InstallHooks(void)
{
    J3D_HOOKFUNC(rdPolyline_New);
    J3D_HOOKFUNC(rdPolyline_NewEntry);
    J3D_HOOKFUNC(rdPolyline_Free);
    J3D_HOOKFUNC(rdPolyline_FreeEntry);
    J3D_HOOKFUNC(rdPolyline_Draw);
    J3D_HOOKFUNC(rdPolyline_DrawFace);
}

void rdPolyline_ResetGlobals(void)
{
    // memset(&rdPolyline_aVerticesCache, 0, sizeof(rdPolyline_aVerticesCache));
}

rdPolyline* J3DAPI rdPolyline_New(const char* pName, const char* pMatFilename, const char* pMatFilename2, float length, float baseRadius, float tipRadius, rdGeometryMode geoMode, rdLightMode lightMode, const rdVector4* pColor)
{
    J3D_UNUSED(pMatFilename2);
    rdPolyline* pLine = (rdPolyline*)STDMALLOC(sizeof(rdPolyline));
    if ( !pLine )
    {
        RDLOG_ERROR("Error allocating memory for polyline.\n");
        return NULL;
    }

    rdPolyline_NewEntry(pLine, pName, pMatFilename, length, baseRadius, tipRadius, geoMode, lightMode, pColor);
    return pLine;
}

int J3DAPI rdPolyline_NewEntry(rdPolyline* pLine, const char* pName, const char* pMatFilename, float length, float baseRadius, float tipRadius, rdGeometryMode geoMode, rdLightMode lightMode, const rdVector4* pColor)
{
    if ( pName )
    {
        STD_STRCPY(pLine->aName, pName);
    }

    pLine->length            = length;
    pLine->baseRadius        = baseRadius;
    pLine->tipRadius         = tipRadius;
    pLine->face.flags        = RD_FF_FOG_ENABLED | RD_FF_TEX_TRANSLUCENT | RD_FF_DOUBLE_SIDED;
    pLine->face.geometryMode = geoMode;
    pLine->face.lightingMode = lightMode;
    pLine->geoMode           = geoMode;
    pLine->lightMode         = lightMode;

    rdVector_Copy4(&pLine->face.extraLight, pColor);

    pLine->face.pMaterial = rdMaterial_Load(pMatFilename);
    if ( !pLine->face.pMaterial )
    {
        return 0;
    }

    pLine->face.numVertices = 4;
    pLine->face.aVertices = (int*)STDMALLOC(sizeof(*pLine->face.aVertices) * pLine->face.numVertices);
    if ( !pLine->face.aVertices )
    {
        goto alloc_error;
    }

    for ( size_t i = 0; i < pLine->face.numVertices; ++i )
    {
        pLine->face.aVertices[i] = i;
    }

    if ( pLine->face.geometryMode == RD_GEOMETRY_FULL )
    {
        pLine->face.aTexVertices = (int*)STDMALLOC(4 * pLine->face.numVertices);
        if ( !pLine->face.aTexVertices )
        {
            goto alloc_error;
        }

        for ( size_t i = 0; i < pLine->face.numVertices; ++i )
        {
            pLine->face.aTexVertices[i] = i;
        }

        pLine->apUVs = (rdVector2*)STDMALLOC(sizeof(*pLine->apUVs) * pLine->face.numVertices);
        if ( !pLine->apUVs )
        {
            goto alloc_error;
        }

        pLine->apUVs->x = 1.0f;
        pLine->apUVs->y = 0.0f;

        pLine->apUVs[1].x = 1.0f;
        pLine->apUVs[1].y = 1.0f;

        pLine->apUVs[2].x = 0.0f;
        pLine->apUVs[2].y = 1.0f;

        pLine->apUVs[3].x = 0.0f;
        pLine->apUVs[3].y = 0.0f;
    }

    // Success
    pLine->face.texVertOffset.y = 0.0f;
    pLine->face.texVertOffset.x = 0.0f;
    return 1;

alloc_error:
    RDLOG_ERROR("Error: Bad memory allocation for polyline '%'.\n", pName);
    return 0;
}

void J3DAPI rdPolyline_Free(rdPolyline* pLine)
{
    if ( !pLine )
    {
        RDLOG_ERROR("Warning: Attempt to free NULL polyline ptr.\n");
        return;
    }

    rdPolyline_FreeEntry(pLine);
    stdMemory_Free(pLine);
}

void J3DAPI rdPolyline_FreeEntry(rdPolyline* pPolyline)
{
    if ( pPolyline->apUVs )
    {
        stdMemory_Free(pPolyline->apUVs);
        pPolyline->apUVs = NULL;
    }

    if ( pPolyline->face.aVertices )
    {
        stdMemory_Free(pPolyline->face.aVertices);
        pPolyline->face.aVertices = NULL;
    }

    if ( pPolyline->face.aTexVertices )
    {
        stdMemory_Free(pPolyline->face.aTexVertices);
        pPolyline->face.aTexVertices = NULL;
    }
}

int J3DAPI rdPolyline_Draw(const rdThing* pLine, const rdMatrix34* pOrient)
{
    rdPolyline* pPolyline = pLine->data.pPolyline;

    rdMatrix34 mat;
    rdMatrix_Multiply34(&mat, &rdCamera_g_pCurCamera->orient, pOrient);

    rdVector3 vecFwd;
    vecFwd.x = 0.0f;
    vecFwd.y = pPolyline->length;
    vecFwd.z = 0.0f;

    rdVector3 vecEnd;
    rdMatrix_TransformPoint34(&vecEnd, &vecFwd, &mat);

    float deX   = vecEnd.x - mat.dvec.x;
    float deZ   = vecEnd.z - mat.dvec.z;
    float xzLen = sqrtf(deX * deX + deZ * deZ);

    float sinv  = -deX / xzLen;
    float angle = stdMath_ArcSin3(sinv);
    if ( deZ < 0.0f )
    {
        if ( deX <= 0.0f )
        {
            angle = -(angle + 180.0f);
        }
        else
        {
            angle = 180.0f - angle;
        }
    }

    float cosv;
    stdMath_SinCos(angle, &sinv, &cosv);

    rdPolyline_aVerticesCache[0].x = pPolyline->tipRadius * cosv - xzLen * sinv + mat.dvec.x;
    rdPolyline_aVerticesCache[0].y = vecEnd.y;
    rdPolyline_aVerticesCache[0].z = pPolyline->tipRadius * sinv + xzLen * cosv + mat.dvec.z;

    rdPolyline_aVerticesCache[1].x = -pPolyline->tipRadius * cosv - xzLen * sinv + mat.dvec.x;
    rdPolyline_aVerticesCache[1].y = vecEnd.y;
    rdPolyline_aVerticesCache[1].z = -pPolyline->tipRadius * sinv + xzLen * cosv + mat.dvec.z;

    rdPolyline_aVerticesCache[2].x = -pPolyline->baseRadius * cosv - 0.0f * sinv + mat.dvec.x;
    rdPolyline_aVerticesCache[2].y = mat.dvec.y;
    rdPolyline_aVerticesCache[2].z =  -pPolyline->baseRadius * sinv + 0.0f * cosv + mat.dvec.z;

    rdPolyline_aVerticesCache[3].x = pPolyline->baseRadius * cosv - 0.0f * sinv + mat.dvec.x;
    rdPolyline_aVerticesCache[3].y = mat.dvec.y;
    rdPolyline_aVerticesCache[3].z = pPolyline->baseRadius * sinv + 0.0f * cosv + mat.dvec.z;

    rdPolyline_DrawFace(pLine, &pPolyline->face, rdPolyline_aVerticesCache, pPolyline->apUVs);
    return 1;
}

void J3DAPI rdPolyline_DrawFace(const rdThing* pLine, const rdFace* pFace, const rdVector3* aVertices, const rdVector2* aUVs)
{
    J3D_UNUSED(pLine);
    rdCacheProcEntry* pPoly = rdCache_GetAlphaProcEntry();
    if ( pPoly )
    {

        if ( rdClip_FaceToPlane(rdCamera_g_pCurCamera->pFrustum, pPoly, pFace, aVertices, aUVs, 0, 0) )
        {
            for ( size_t i = 0; i < pFace->numVertices; ++i )
            {
                rdVector_Copy4(&pPoly->aVertIntensities[i], &pFace->extraLight);
            }

            if ( (rdroid_g_curRenderOptions & RDROID_USE_AMBIENT_CAMERA_LIGHT) != 0 )
            {
                rdVector_Add4Acc(&pPoly->extraLight, &rdCamera_g_pCurCamera->ambientLight);
                rdMath_ClampVector4(&pPoly->extraLight, 0.0f, 1.0f); // Added: Clamp to [0,1.0]
            }

            pPoly->flags = pFace->flags;
            pPoly->flags |= RD_FF_FOG_ENABLED | RD_FF_ZWRITE_DISABLED | RD_FF_TEX_TRANSLUCENT;

            // Fixed: Disable fog rendering for poly when fog is globally disabled
            //        OG: Poly fog rendering was enabled by default which lead to undesired render effect when fog is disabled in level (i.e.: fog color is applied)
            if ( !sithWorld_g_pCurrentWorld->fog.bEnabled ) // // TODO: add special function that will enable/disable fog rendering
            {
                pPoly->flags &= ~RD_FF_FOG_ENABLED;
            }

            pPoly->matCelNum    = pFace->matCelNum;
            pPoly->lightingMode = RD_LIGHTING_NONE;
            pPoly->pMaterial    = pFace->pMaterial;
            rdCache_AddAlphaProcFace(pFace->numVertices);
        }
    }
}
