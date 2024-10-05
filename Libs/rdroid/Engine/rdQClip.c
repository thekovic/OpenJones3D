#include "rdQClip.h"
#include <j3dcore/j3dhook.h>

#include <rdroid/Engine/rdClip.h>
#include <rdroid/Main/rdroid.h>
#include <rdroid/RTI/symbols.h>

#include <std/General/stdUtil.h>

rdVector3* rdQClip_pDestVert   = NULL;
rdVector3* rdQClip_pSourceVert = NULL;
rdVector3 rdQClip_aWorkVerts[RDQCLIP_MAXWORKVERTS];

void rdQClip_InstallHooks(void)
{

    J3D_HOOKFUNC(rdQClip_VerticesInFrustrum);
    J3D_HOOKFUNC(rdQClip_Face3W);
}

void rdQClip_ResetGlobals(void)
{

}

size_t J3DAPI rdQClip_VerticesInFrustrum(const rdClipFrustum* pFrustrum, const rdVector3* aVertices, size_t numVertices)
{
    const rdVector3* pCurVert;

    if ( aVertices->y >= (double)pFrustrum->nearPlane )
    {
        if ( pFrustrum->bClipFar && aVertices->y > (double)pFrustrum->farPlane )
        {
            for ( pCurVert = &aVertices[numVertices - 1]; pCurVert > aVertices && pCurVert->y > (double)pFrustrum->farPlane; --pCurVert )
            {
                ;
            }

            if ( pCurVert == aVertices )
            {
                return 0;
            }
        }
    }
    else
    {
        for ( pCurVert = &aVertices[numVertices - 1]; pCurVert > aVertices && pCurVert->y < (double)pFrustrum->nearPlane; --pCurVert )
        {
            ;
        }

        if ( pCurVert == aVertices )
        {
            return 0;
        }
    }

    if ( aVertices->y * pFrustrum->leftPlane <= aVertices->x )
    {
        if ( aVertices->y * pFrustrum->rightPlane < aVertices->x )
        {
            for ( pCurVert = &aVertices[numVertices - 1]; pCurVert > aVertices && pCurVert->y * pFrustrum->rightPlane < pCurVert->x; --pCurVert )
            {
                ;
            }

            if ( pCurVert == aVertices )
            {
                return 0;
            }
        }
    }
    else
    {
        for ( pCurVert = &aVertices[numVertices - 1]; pCurVert > aVertices && pCurVert->y * pFrustrum->leftPlane > pCurVert->x; --pCurVert )
        {
            ;
        }

        if ( pCurVert == aVertices )
        {
            return 0;
        }
    }

    if ( aVertices->y * pFrustrum->topPlane >= aVertices->z )
    {
        if ( aVertices->y * pFrustrum->bottomPlane > aVertices->z )
        {
            for ( pCurVert = &aVertices[numVertices - 1]; pCurVert > aVertices && pCurVert->y * pFrustrum->bottomPlane > pCurVert->z; --pCurVert )
            {
                ;
            }

            if ( pCurVert == aVertices )
            {
                return 0;
            }
        }
    }
    else
    {
        for ( pCurVert = &aVertices[numVertices - 1]; pCurVert > aVertices && pCurVert->y * pFrustrum->topPlane < pCurVert->z; --pCurVert )
        {
            ;
        }

        if ( pCurVert == aVertices )
        {
            return 0;
        }
    }

    return numVertices;
}

int J3DAPI rdQClip_Face3W(const rdClipFrustum* pFrustrum, rdVector3* aVertices, size_t numVertices)
{
    rdClip_g_faceStatus = 0;
    rdQClip_pSourceVert = aVertices;
    rdQClip_pDestVert   = rdQClip_aWorkVerts;

    size_t clipindex     = 0;
    rdVector3* pPrevVert = &aVertices[numVertices - 1];
    rdVector3* pCurVert  = aVertices;

    for ( size_t i = 0; i < numVertices; ++i )
    {
        if ( pPrevVert->y >= (double)pFrustrum->nearPlane || pCurVert->y >= (double)pFrustrum->nearPlane )
        {
            if ( pPrevVert->y != pFrustrum->nearPlane
              && pCurVert->y != pFrustrum->nearPlane
              && (pPrevVert->y < (double)pFrustrum->nearPlane || pCurVert->y < (double)pFrustrum->nearPlane) )
            {
                float clipFactor = (pFrustrum->nearPlane - pPrevVert->y) / (pCurVert->y - pPrevVert->y);
                rdQClip_pDestVert[clipindex].y = pFrustrum->nearPlane;
                rdQClip_pDestVert[clipindex].z = (pCurVert->z - pPrevVert->z) * clipFactor + pPrevVert->z;
                rdQClip_pDestVert[clipindex++].x = (pCurVert->x - pPrevVert->x) * clipFactor + pPrevVert->x;

                /* v3 = rdClip_g_faceStatus;
                 (v3 & 0xFF) = rdClip_g_faceStatus | 1;
                 rdClip_g_faceStatus = v3;*/
                rdClip_g_faceStatus |= 0x01;
            }

            if ( pCurVert->y >= (double)pFrustrum->nearPlane )
            {
                memcpy(&rdQClip_pDestVert[clipindex++], pCurVert, sizeof(rdVector3));
            }
        }

        RD_ASSERTREL(clipindex < STD_ARRAYLEN(rdQClip_aWorkVerts));
        pPrevVert = pCurVert++;
    }

    if ( clipindex >= 3 )
    {
        if ( rdQClip_pDestVert != aVertices )
        {
            memcpy(aVertices, rdQClip_pDestVert, sizeof(aVertices[0]) * clipindex);
        }

        return clipindex;
    }
    else
    {
        rdClip_g_faceStatus |= 0x40u;
        return clipindex;
    }
}
