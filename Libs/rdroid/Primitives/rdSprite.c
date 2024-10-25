#include "rdSprite.h"
#include <j3dcore/j3dhook.h>

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

rdMatrix34 rdSprite_aView;

void rdSprite_InstallHooks(void)
{
    J3D_HOOKFUNC(rdSprite_NewEntry);
    J3D_HOOKFUNC(rdSprite_FreeEntry);
    J3D_HOOKFUNC(rdSprite_Draw);
}

void rdSprite_ResetGlobals(void)
{
    //memset(&rdSprite_aView, 0, sizeof(rdSprite_aView));
}

rdSprite3* J3DAPI rdSprite_New(int type, const char* pName, const char* pMatNam, float width, float height, rdGeometryMode geomode, rdLightMode lightmode, const rdVector4* pExtraLight, const rdVector3* pOffset)
{
    rdSprite3* pSprite = (rdSprite3*)STDMALLOC(sizeof(rdSprite3));
    if ( !pSprite )
    {
        RDLOG_ERROR("Error allocating memory for sprite.\n");
        return NULL;
    }

    rdSprite_NewEntry(pSprite, pName, type, pMatNam, width, height, geomode, lightmode, pExtraLight, pOffset);
    return pSprite;
}

int J3DAPI rdSprite_NewEntry(rdSprite3* pSprite, const char* pName, int type, const char* pMatName, float width, float height, rdGeometryMode geomode, rdLightMode lightmode, const rdVector4* pExtraLight, const rdVector3* pOffset)
{
    if ( pName )
    {
        STD_STRCPY(pSprite->aName, pName);
    }

    pSprite->type              = type;
    pSprite->width             = width;
    pSprite->height            =  height;
    pSprite->face.flags        = RD_FF_FOG_ENABLED | RD_FF_DOUBLE_SIDED;
    pSprite->face.geometryMode = geomode;
    pSprite->face.lightingMode = lightmode;

    rdVector_Copy3(&pSprite->offset, pOffset);
    rdVector_Copy4(&pSprite->face.extraLight, pExtraLight);

    pSprite->face.pMaterial = rdMaterial_Load(pMatName);
    if ( !pSprite->face.pMaterial )
    {
        return 0;
    }

    pSprite->face.numVertices = 4;
    pSprite->face.aVertices = (int*)STDMALLOC(sizeof(*pSprite->face.aVertices) * pSprite->face.numVertices);
    if ( !pSprite->face.aVertices )
    {
        goto alloc_error;
    }

    if ( pSprite->face.geometryMode <= RD_GEOMETRY_SOLID )
    {
        for ( size_t i = 0; i < pSprite->face.numVertices; ++i )
        {
            pSprite->face.aVertices[i] = i;
        }
    }
    else
    {

        pSprite->face.aTexVertices = (int*)STDMALLOC(sizeof(*pSprite->face.aTexVertices) * pSprite->face.numVertices);
        if ( !pSprite->face.aTexVertices )
        {
            goto alloc_error;
        }

        for ( size_t i = 0; i < pSprite->face.numVertices; ++i )
        {
            pSprite->face.aVertices[i]    = i;
            pSprite->face.aTexVertices[i] = i;
        }

        pSprite->aTexVerts = (rdVector2*)STDMALLOC(sizeof(*pSprite->aTexVerts) * pSprite->face.numVertices);
        if ( !pSprite->aTexVerts )
        {
            goto alloc_error;
        }

        pSprite->aTexVerts->x = 0.0f;
        pSprite->aTexVerts->y = 0.0f;

        pSprite->aTexVerts[1].x = 1.0f;
        pSprite->aTexVerts[1].y = 0.0f;

        pSprite->aTexVerts[2].x = 1.0f;
        pSprite->aTexVerts[2].y = 1.0f;

        pSprite->aTexVerts[3].x = 0.0f;
        pSprite->aTexVerts[3].y = 1.0f;
    }

    // Success
    pSprite->widthHalf  = pSprite->width / 2.0f;
    pSprite->heightHalf = pSprite->height / 2.0f;
    pSprite->radius     = sqrtf(pSprite->widthHalf * pSprite->widthHalf + pSprite->heightHalf * pSprite->heightHalf);
    return 1;

alloc_error:
    RDLOG_ERROR("Error: Bad memory allocation for sprite '%'.\n", pName);
    return 0;
}

void J3DAPI rdSprite_Free(rdSprite3* pSprite)
{
    if ( !pSprite )
    {
        RDLOG_ERROR("Warning: Attempt to free NULL sprite ptr.\n");
        return;
    }

    rdSprite_FreeEntry(pSprite);
    stdMemory_Free(pSprite);
}

void J3DAPI rdSprite_FreeEntry(rdSprite3* pSprite)
{
    if ( pSprite->aTexVerts )
    {
        stdMemory_Free(pSprite->aTexVerts);
        pSprite->aTexVerts = NULL;
    }

    if ( pSprite->face.aVertices )
    {
        stdMemory_Free(pSprite->face.aVertices);
        pSprite->face.aVertices = NULL;
    }

    if ( pSprite->face.aTexVertices )
    {
        stdMemory_Free(pSprite->face.aTexVertices);
        pSprite->face.aTexVertices = NULL;
    }
}

int J3DAPI rdSprite_Draw(rdThing* prdThing, const rdMatrix34* orient)
{
    rdSprite3* pSprite3 = prdThing->data.pSprite3;

    rdVector3 tpos = { 0 };
    rdVector3 lvec = { 0 };

    if ( pSprite3->type )
    {
        if ( pSprite3->type == 2 )
        {
            rdVector_Copy3(&tpos, &orient->dvec);
            rdVector_Copy3(&lvec, &orient->lvec);
        }
    }
    else
    {
        rdMatrix_TransformPoint34(&tpos, &orient->dvec, &rdCamera_g_pCurCamera->orient);
    }

    RdFrustumCull frustumCull = prdThing->frustumCull;
    if ( frustumCull == RDFRUSTUMCULL_OUTSIDE )
    {
        return 0;
    }

    rdCacheProcEntry* pPoly = rdCache_GetAlphaProcEntry();
    if ( !pPoly )
    {
        return 0;
    }

    if ( pSprite3->type == 0 )
    {
        rdSprite_aView.rvec.x = pSprite3->offset.x - pSprite3->widthHalf;
        rdSprite_aView.rvec.y = pSprite3->offset.y;
        rdSprite_aView.rvec.z = pSprite3->heightHalf + pSprite3->offset.z;

        rdSprite_aView.lvec.x = pSprite3->widthHalf + pSprite3->offset.x;
        rdSprite_aView.lvec.y = pSprite3->offset.y;
        rdSprite_aView.lvec.z = pSprite3->heightHalf + pSprite3->offset.z;

        rdSprite_aView.uvec.x = pSprite3->widthHalf + pSprite3->offset.x;
        rdSprite_aView.uvec.y = pSprite3->offset.y;
        rdSprite_aView.uvec.z = pSprite3->offset.z - pSprite3->heightHalf;

        rdSprite_aView.dvec.x = pSprite3->offset.x - pSprite3->widthHalf;
        rdSprite_aView.dvec.y = pSprite3->offset.y;
        rdSprite_aView.dvec.z = pSprite3->offset.z - pSprite3->heightHalf;

        if ( pSprite3->rollAngle != 0.0f )
        {
            rdVector3 vecPYR = { 0 };
            vecPYR.z = pSprite3->rollAngle;
            rdMatrix_PostRotate34(&rdSprite_aView, &vecPYR);
            pSprite3->rollAngle = 0.0f;
        }

        rdVector_Add3Acc(&rdSprite_aView.rvec, &tpos);
        /*rdSprite_aView.rvec.x = rdSprite_aView.rvec.x + tpos.x;
        rdSprite_aView.rvec.y = rdSprite_aView.rvec.y + tpos.y;
        rdSprite_aView.rvec.z = rdSprite_aView.rvec.z + tpos.z;*/

        rdVector_Add3Acc(&rdSprite_aView.lvec, &tpos);
        /*rdSprite_aView.lvec.x = rdSprite_aView.lvec.x + tpos.x;
        rdSprite_aView.lvec.y = rdSprite_aView.lvec.y + tpos.y;
        rdSprite_aView.lvec.z = rdSprite_aView.lvec.z + tpos.z;*/

        rdVector_Add3Acc(&rdSprite_aView.uvec, &tpos);
        /*rdSprite_aView.uvec.x = rdSprite_aView.uvec.x + tpos.x;
        rdSprite_aView.uvec.y = rdSprite_aView.uvec.y + tpos.y;
        rdSprite_aView.uvec.z = rdSprite_aView.uvec.z + tpos.z;*/

        rdVector_Add3Acc(&rdSprite_aView.dvec, &tpos);
        /* rdSprite_aView.tpos.x = rdSprite_aView.tpos.x + tpos.x;
         rdSprite_aView.tpos.y = rdSprite_aView.tpos.y + tpos.y;
         rdSprite_aView.tpos.z = rdSprite_aView.tpos.z + tpos.z;*/
    }
    else if ( pSprite3->type == 2 )
    {
        rdVector3 v9;
        rdVector3 v10;
        rdVector3 v11;
        rdVector3 prod;
        rdVector3 v13;

        if ( fabsf(lvec.z) < 1.0f ) // Fixed, was: if ( fabsf((double)(lvec.z >= 0.99989998f)) == 0.0f )
        {
            // vec cross rdroid_g_zVector
         /*   prod.x = 0.0f * lvec.z - 1.0f * lvec.y;
            prod.y = 1.0f * lvec.x - 0.0f * lvec.z;
            v3 = 0.0f * lvec.y - 0.0f * lvec.x;*/
            rdVector_Cross3(&prod, &lvec, &rdroid_g_zVector3);
        }
        else
        {
            // vec cross rdroid_g_xVector3
       /*     prod.x = 0.0f * lvec.z - 0.0f * lvec.y;
            prod.y = 0.0f * lvec.x - 1.0f * lvec.z;
            v3 = 1.0f * lvec.y - 0.0f * lvec.x;*/
            rdVector_Cross3(&prod, &lvec, &rdroid_g_xVector3);
        }

        // vec cross lvec
        //prod.z = v3;
      /*  v13.x = prod.y * lvec.z - prod.z * lvec.y;
        v13.y = prod.z * lvec.x - prod.x * lvec.z;
        v13.z = prod.x * lvec.y - prod.y * lvec.x;*/
        rdVector_Cross3(&v13, &prod, &lvec);

        rdVector_Scale3(&v11, &prod, pSprite3->widthHalf);
        /* v11.x = pSprite3->widthHalf * prod.x;
         v11.y = pSprite3->widthHalf * prod.y;
         v11.z = pSprite3->widthHalf * prod.z;*/

        rdVector_Scale3(&v10, &v13, pSprite3->heightHalf);
        /*  v10.x = pSprite3->heightHalf * v13.x;
          v10.y = pSprite3->heightHalf * v13.y;
          v10.z = pSprite3->heightHalf * v13.z;*/

          /*  v9.x = -v11.x;
            v9.y = -v11.y;
            v9.z = -v11.z;*/

        rdVector_Neg3(&v9, &v11);

        rdSprite_aView.rvec.x = v9.x - v10.x;
        rdSprite_aView.rvec.y = v9.y - v10.y;
        rdSprite_aView.rvec.z = v9.z - v10.z;

        rdSprite_aView.lvec.x = v11.x - v10.x;
        rdSprite_aView.lvec.y = v11.y - v10.y;
        rdSprite_aView.lvec.z = v11.z - v10.z;

        rdSprite_aView.uvec.x = v11.x + v10.x;
        rdSprite_aView.uvec.y = v11.y + v10.y;
        rdSprite_aView.uvec.z = v11.z + v10.z;

        rdSprite_aView.dvec.x = v9.x + v10.x;
        rdSprite_aView.dvec.y = v9.y + v10.y;
        rdSprite_aView.dvec.z = v9.z + v10.z;

        if ( pSprite3->rollAngle != 0.0f )
        {
            rdMatrix34 tmat;
            rdMatrix_BuildFromVectorAngle34(&tmat, &lvec, pSprite3->rollAngle);
            rdMatrix_PostMultiply34(&rdSprite_aView, &tmat);
            pSprite3->rollAngle = 0.0f;
        }

        rdVector_Add3Acc(&rdSprite_aView.rvec, &tpos);
        /*rdSprite_aView.rvec.x = rdSprite_aView.rvec.x + tpos.x;
        rdSprite_aView.rvec.y = rdSprite_aView.rvec.y + tpos.y;
        rdSprite_aView.rvec.z = rdSprite_aView.rvec.z + tpos.z;*/

        rdVector_Add3Acc(&rdSprite_aView.lvec, &tpos);
        /*rdSprite_aView.lvec.x = rdSprite_aView.lvec.x + tpos.x;
        rdSprite_aView.lvec.y = rdSprite_aView.lvec.y + tpos.y;
        rdSprite_aView.lvec.z = rdSprite_aView.lvec.z + tpos.z;*/

        rdVector_Add3Acc(&rdSprite_aView.uvec, &tpos);
        /*rdSprite_aView.uvec.x = rdSprite_aView.uvec.x + tpos.x;
        rdSprite_aView.uvec.y = rdSprite_aView.uvec.y + tpos.y;
        rdSprite_aView.uvec.z = rdSprite_aView.uvec.z + tpos.z;*/

        rdVector_Add3Acc(&rdSprite_aView.dvec, &tpos);
        /* rdSprite_aView.tpos.x = rdSprite_aView.tpos.x + tpos.x;
         rdSprite_aView.tpos.y = rdSprite_aView.tpos.y + tpos.y;
         rdSprite_aView.tpos.z = rdSprite_aView.tpos.z + tpos.z;*/
    }

    if ( pSprite3->type == 2 )
    {
        for ( size_t i = 0; i < 4; ++i )
        {
            rdVector3 tvec;
            rdMatrix_TransformPoint34(&tvec, (const rdVector3*)&rdSprite_aView.rvec + i, &rdCamera_g_pCurCamera->orient);
            rdVector_Copy3(&rdSprite_aView.rvec + i, &tvec);
        }
    }

    if ( !rdClip_FaceToPlane(rdCamera_g_pCurCamera->pFrustum, pPoly, &pSprite3->face, &rdSprite_aView.rvec, pSprite3->aTexVerts, 0, 0) )
    {
        return 0;
    }

    pPoly->aVertIntensities->alpha = pSprite3->face.extraLight.alpha;
    rdVector_Copy4(&pPoly->extraLight, &pSprite3->face.extraLight);

    if ( (rdroid_g_curRenderOptions & RDROID_USE_AMBIENT_CAMERA_LIGHT) != 0 )
    {
        rdVector_Add4Acc(&pPoly->extraLight, &rdCamera_g_pCurCamera->ambientLight);
        rdMath_ClampVector4(&pPoly->extraLight, 0.0f, 1.0f); // Added: Clamp to [0,1.0]
    }

    pPoly->matCelNum = prdThing->matCelNum;
    pPoly->flags     = pSprite3->face.flags;
    pPoly->flags    |=  RD_FF_FOG_ENABLED | RD_FF_ZWRITE_DISABLED | RD_FF_TEX_CLAMP_Y | RD_FF_TEX_CLAMP_X | RD_FF_TEX_TRANSLUCENT;

    // Fixed: Disable fog rendering for poly when fog is globally disabled
    //        OG: Poly fog rendering was enabled by default which lead to undesired render effect when fog is disabled in level (i.e.: fog color is applied)
    if ( !sithWorld_g_pCurrentWorld->fog.bEnabled ) // TODO: add special function that will enable/disable fog rendering
    {
        pPoly->flags &= ~RD_FF_FOG_ENABLED;
    }

    pPoly->pMaterial    = pSprite3->face.pMaterial;
    pPoly->lightingMode = J3DMIN(J3DMIN(pSprite3->face.lightingMode, RD_LIGHTING_DIFFUSE), rdroid_g_curLightingMode);
    rdCache_AddAlphaProcFace(pSprite3->face.numVertices);
    return 1;
}