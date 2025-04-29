#include "rdPrimit3.h"
#include <j3dcore/j3dhook.h>

#include <rdroid/Engine/rdCamera.h>
#include <rdroid/Engine/rdClip.h>
#include <rdroid/Primitives/rdPrimit2.h>
#include <rdroid/Math/rdMatrix.h>
#include <rdroid/Math/rdVector.h>
#include <rdroid/RTI/symbols.h>


void rdPrimit3_InstallHooks(void)
{
    J3D_HOOKFUNC(rdPrimit3_DrawClippedCircle);
    J3D_HOOKFUNC(rdPrimit3_ClipFace);
}

void rdPrimit3_ResetGlobals(void)
{}

int J3DAPI rdPrimit3_DrawPoint(rdVector3* pPoint, int32_t* pPPoint, uint32_t color)
{
    rdVector3 tpoint;
    rdMatrix_TransformPoint34(&tpoint, pPoint, &rdCamera_g_pCurCamera->orient);
    if ( !rdClip_Point3(rdCamera_g_pCurCamera->pFrustum, &tpoint) )
    {
        return 0;
    }

    rdVector3 ppoint;
    rdCamera_g_pCurCamera->pfProject(&ppoint, &tpoint);
    int32_t x = (int32_t)ppoint.x;
    int32_t y = (int32_t)ppoint.y;
    if ( pPPoint )
    {
        *pPPoint   = x;
        pPPoint[1] = y;
        pPPoint[2] = (int32_t)ppoint.z;
    }

    if ( rdCamera_g_pCurCamera->pCanvas->pVBuffer->rasterInfo.colorInfo.bpp == 8 )
    {
        rdCamera_g_pCurCamera->pCanvas->pVBuffer->pPixels[rdCamera_g_pCurCamera->pCanvas->pVBuffer->rasterInfo.rowSize * y + x] = color;
    }
    else
    {
        // TODO: only 16 bpp is supported but the pPixels might be 24bit or 32

        *(uint16_t*)&rdCamera_g_pCurCamera->pCanvas->pVBuffer->pPixels[2 * rdCamera_g_pCurCamera->pCanvas->pVBuffer->rasterInfo.rowWidth * y + 2 * x] = color;
    }

    return 1;
}

int J3DAPI rdPrimit3_DrawClippedLine(rdVector3* pPoint1, rdVector3* pPoint2, uint32_t color)
{
    rdVector3 ppoint2;
    rdVector3 ppoint1;
    rdVector3 tpoint2;
    rdVector3 tpoint1;
    rdMatrix_TransformPoint34(&tpoint1, pPoint1, &rdCamera_g_pCurCamera->orient);
    rdMatrix_TransformPoint34(&tpoint2, pPoint2, &rdCamera_g_pCurCamera->orient);
    rdCamera_g_pCurCamera->pfProject(&ppoint1, &tpoint1);
    rdCamera_g_pCurCamera->pfProject(&ppoint2, &tpoint2);
    return rdPrimit2_DrawClippedLine2(ppoint1.x, ppoint1.y, ppoint2.x, ppoint2.y, color);
}

void J3DAPI rdPrimit3_DrawClippedCircle(const rdVector3* pPos, float radius, float step, uint32_t color, uint32_t pattern)
{
    rdVector3 center;
    rdMatrix_TransformPoint34(&center, pPos, &rdCamera_g_pCurCamera->orient);

    if ( center.y > 0.0f )
    {
        rdVector3 circlePoint = center;
        circlePoint.x += radius;

        rdVector3 projCenter, projCirclePoint;
        rdCamera_g_pCurCamera->pfProject(&projCenter, &center);
        rdCamera_g_pCurCamera->pfProject(&projCirclePoint, &circlePoint);

        int32_t x = (int32_t)(projCenter.x + 0.5f);
        int32_t y = (int32_t)(projCenter.y + 0.5f);
        float radius2D = projCirclePoint.x - projCenter.x;

        rdPrimit2_DrawClippedCircle(rdCamera_g_pCurCamera->pCanvas, x, y, radius2D, step, color, pattern);
    }
}

void J3DAPI rdPrimit3_ClipFace(const rdClipFrustum* pFrustrum, rdGeometryMode geoMode, rdLightMode lightMode, const rdPrimit3* pSrc, rdPrimit3* pDest, const rdVector2* pTexVertOffset)
{
    float green;
    float red;
    float alpha;
    float blue;

    switch ( geoMode )
    {
        case RD_GEOMETRY_NONE:
            for ( size_t i = 0; i < pSrc->numVertices; ++i )
            {
                rdVector_Copy3(&pDest->aVertices[i], &pSrc->aVertices[pSrc->aVertIdxs[i]]);
            }

            if ( rdCamera_g_pCurCamera->projectType == RDCAMERA_PROJECT_PERSPECTIVE )
            {
                pDest->numVertices = rdClip_Face3S(pFrustrum, pDest->aVertices, pSrc->numVertices);
            }
            else
            {
                pDest->numVertices = rdClip_Face3SOrtho(pFrustrum, pDest->aVertices, pSrc->numVertices);
            }

            break;

        case RD_GEOMETRY_VERTEX:
        case RD_GEOMETRY_WIREFRAME:
            for ( size_t i = 0; i < pSrc->numVertices; ++i )
            {
                rdVector_Copy3(&pDest->aVertices[i], &pSrc->aVertices[pSrc->aVertIdxs[i]]);
            }

            if ( rdCamera_g_pCurCamera->projectType == RDCAMERA_PROJECT_PERSPECTIVE )
            {
                pDest->numVertices = rdClip_Face3W(pFrustrum, pDest->aVertices, pSrc->numVertices);
            }
            else
            {
                pDest->numVertices = rdClip_Face3WOrtho(pFrustrum, pDest->aVertices, pSrc->numVertices);
            }

            break;

        case RD_GEOMETRY_SOLID:
            switch ( lightMode )
            {
                case RD_LIGHTING_NONE:
                case RD_LIGHTING_LIT:
                    for ( size_t i = 0; i < pSrc->numVertices; ++i )
                    {
                        rdVector_Copy3(&pDest->aVertices[i], &pSrc->aVertices[pSrc->aVertIdxs[i]]);
                    }

                    if ( rdCamera_g_pCurCamera->projectType == RDCAMERA_PROJECT_PERSPECTIVE )
                    {
                        pDest->numVertices = rdClip_Face3S(pFrustrum, pDest->aVertices, pSrc->numVertices);
                    }
                    else
                    {
                        pDest->numVertices = rdClip_Face3SOrtho(pFrustrum, pDest->aVertices, pSrc->numVertices);
                    }

                    break;

                case RD_LIGHTING_DIFFUSE:
                    for ( size_t i = 0; i < pSrc->numVertices; ++i )
                    {
                        rdVector_Copy3(&pDest->aVertices[i], &pSrc->aVertices[pSrc->aVertIdxs[i]]);
                    }

                    if ( rdCamera_g_pCurCamera->projectType == RDCAMERA_PROJECT_PERSPECTIVE )
                    {
                        pDest->numVertices = rdClip_Face3S(pFrustrum, pDest->aVertices, pSrc->numVertices);
                    }
                    else
                    {
                        pDest->numVertices = rdClip_Face3SOrtho(pFrustrum, pDest->aVertices, pSrc->numVertices);
                    }

                    break;

                case RD_LIGHTING_GOURAUD:
                    if ( pSrc->aVertIntensities )
                    {
                        for ( size_t i = 0; i < pSrc->numVertices; ++i )
                        {
                            rdVector_Copy3(&pDest->aVertices[i], &pSrc->aVertices[pSrc->aVertIdxs[i]]);

                            // TODO: verify if it's a bug assigning to pDest->aVertLights[i] instead of pSrc->aVertLights[pSrc->aVertIdxs[i]]

                            if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].red + pSrc->aVertIntensities[i].red < 0.0f )
                            {
                                red = 0.0f;
                            }

                            else if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].red + pSrc->aVertIntensities[i].red > 1.0f )
                            {
                                red = 1.0f;
                            }
                            else
                            {
                                red = pSrc->aVertLights[pSrc->aVertIdxs[i]].red + pSrc->aVertIntensities[i].red;
                            }

                            pDest->aVertLights[i].red = red;

                            if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].green + pSrc->aVertIntensities[i].green < 0.0f )
                            {
                                green = 0.0f;
                            }

                            else if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].green + pSrc->aVertIntensities[i].green > 1.0f )
                            {
                                green = 1.0f;
                            }
                            else
                            {
                                green = pSrc->aVertLights[pSrc->aVertIdxs[i]].green + pSrc->aVertIntensities[i].green;
                            }

                            pDest->aVertLights[i].green = green;

                            if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].blue + pSrc->aVertIntensities[i].blue < 0.0f )
                            {
                                blue = 0.0f;
                            }

                            else if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].blue + pSrc->aVertIntensities[i].blue > 1.0f )
                            {
                                blue = 1.0f;
                            }
                            else
                            {
                                blue = pSrc->aVertLights[pSrc->aVertIdxs[i]].blue + pSrc->aVertIntensities[i].blue;
                            }

                            pDest->aVertLights[i].blue = blue;

                            if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].alpha < 0.0f )
                            {
                                alpha = 0.0f;
                            }

                            else if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].alpha > 1.0f )
                            {
                                alpha = 1.0f;
                            }
                            else
                            {
                                alpha = pSrc->aVertLights[pSrc->aVertIdxs[i]].alpha;
                            }

                            pDest->aVertLights[i].alpha = alpha;
                        }
                    }
                    else
                    {
                        for ( size_t i = 0; i < pSrc->numVertices; ++i )
                        {
                            rdVector_Copy3(&pDest->aVertices[i], &pSrc->aVertices[pSrc->aVertIdxs[i]]);

                            // TODO: verify if it's a bug assigning to pDest->aVertLights[i] instead of pSrc->aVertLights[pSrc->aVertIdxs[i]]

                            if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].red < 0.0f )
                            {
                                red = 0.0f;
                            }

                            else if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].red > 1.0f )
                            {
                                red = 1.0f;
                            }
                            else
                            {
                                red = pSrc->aVertLights[pSrc->aVertIdxs[i]].red;
                            }

                            pDest->aVertLights[i].red = red;

                            if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].green < 0.0f )
                            {
                                green = 0.0f;
                            }

                            else if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].green > 1.0f )
                            {
                                green = 1.0f;
                            }
                            else
                            {
                                green = pSrc->aVertLights[pSrc->aVertIdxs[i]].green;
                            }

                            pDest->aVertLights[i].green = green;

                            if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].blue < 0.0f )
                            {
                                blue = 0.0f;
                            }

                            else if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].blue > 1.0f )
                            {
                                blue = 1.0f;
                            }
                            else
                            {
                                blue = pSrc->aVertLights[pSrc->aVertIdxs[i]].blue;
                            }

                            pDest->aVertLights[i].blue = blue;

                            if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].alpha < 0.0f )
                            {
                                alpha = 0.0f;
                            }

                            else if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].alpha > 1.0f )
                            {
                                alpha = 1.0f;
                            }
                            else
                            {
                                alpha = pSrc->aVertLights[pSrc->aVertIdxs[i]].alpha;
                            }

                            pDest->aVertLights[i].alpha = alpha;
                        }
                    }

                    if ( rdCamera_g_pCurCamera->projectType == RDCAMERA_PROJECT_PERSPECTIVE )
                    {
                        pDest->numVertices = rdClip_Face3GS(pFrustrum, pDest->aVertices, pDest->aVertLights, pSrc->numVertices);
                    }
                    else
                    {
                        pDest->numVertices = rdClip_Face3GSOrtho(pFrustrum, pDest->aVertices, pDest->aVertLights, pSrc->numVertices);
                    }

                    break;

                default:
                    return;
            }

            break;

        case RD_GEOMETRY_FULL:
            if ( lightMode >= RD_LIGHTING_NONE )
            {
                if ( lightMode <= RD_LIGHTING_DIFFUSE )
                {
                    for ( size_t i = 0; i < pSrc->numVertices; ++i )
                    {
                        rdVector_Copy3(&pDest->aVertices[i], &pSrc->aVertices[pSrc->aVertIdxs[i]]);
                        rdVector_Copy2(&pDest->aTexVertices[i], &pSrc->aTexVertices[pSrc->aTexVertIdxs[i]]);

                        pDest->aTexVertices[i].x = pDest->aTexVertices[i].x + pTexVertOffset->x;
                        pDest->aTexVertices[i].y = pDest->aTexVertices[i].y + pTexVertOffset->y;
                    }

                    if ( rdCamera_g_pCurCamera->projectType == RDCAMERA_PROJECT_PERSPECTIVE )
                    {
                        pDest->numVertices = rdClip_Face3GT(pFrustrum, pDest->aVertices, pDest->aTexVertices, pSrc->numVertices);
                    }
                    else
                    {
                        pDest->numVertices = rdClip_Face3GTOrtho(pFrustrum, pDest->aVertices, pDest->aTexVertices, pSrc->numVertices);
                    }
                }
                else if ( lightMode == RD_LIGHTING_GOURAUD )
                {
                    if ( pSrc->aVertIntensities )
                    {
                        for ( size_t i = 0; i < pSrc->numVertices; ++i )
                        {
                            rdVector_Copy3(&pDest->aVertices[i], &pSrc->aVertices[pSrc->aVertIdxs[i]]);
                            rdVector_Copy2(&pDest->aTexVertices[i], &pSrc->aTexVertices[pSrc->aTexVertIdxs[i]]);

                            pDest->aTexVertices[i].x = pDest->aTexVertices[i].x + pTexVertOffset->x;
                            pDest->aTexVertices[i].y = pDest->aTexVertices[i].y + pTexVertOffset->y;

                            // TODO: verify if it's a bug assigning to pDest->aVertLights[i] instead of pSrc->aVertLights[pSrc->aVertIdxs[i]]

                            if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].red + pSrc->aVertIntensities[i].red < 0.0f )
                            {
                                red = 0.0f;
                            }

                            else if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].red + pSrc->aVertIntensities[i].red > 1.0f )
                            {
                                red = 1.0f;
                            }
                            else
                            {
                                red = pSrc->aVertLights[pSrc->aVertIdxs[i]].red + pSrc->aVertIntensities[i].red;
                            }

                            pDest->aVertLights[i].red = red;

                            if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].green + pSrc->aVertIntensities[i].green < 0.0f )
                            {
                                green = 0.0f;
                            }

                            else if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].green + pSrc->aVertIntensities[i].green > 1.0f )
                            {
                                green = 1.0f;
                            }
                            else
                            {
                                green = pSrc->aVertLights[pSrc->aVertIdxs[i]].green + pSrc->aVertIntensities[i].green;
                            }

                            pDest->aVertLights[i].green = green;

                            if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].blue + pSrc->aVertIntensities[i].blue < 0.0f )
                            {
                                blue = 0.0f;
                            }

                            else if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].blue + pSrc->aVertIntensities[i].blue > 1.0f )
                            {
                                blue = 1.0f;
                            }
                            else
                            {
                                blue = pSrc->aVertLights[pSrc->aVertIdxs[i]].blue + pSrc->aVertIntensities[i].blue;
                            }

                            pDest->aVertLights[i].blue = blue;

                            if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].alpha < 0.0f )
                            {
                                alpha = 0.0f;
                            }

                            else if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].alpha > 1.0f )
                            {
                                alpha = 1.0f;
                            }
                            else
                            {
                                alpha = pSrc->aVertLights[pSrc->aVertIdxs[i]].alpha;
                            }

                            pDest->aVertLights[i].alpha = alpha;
                        }
                    }
                    else
                    {
                        for ( size_t i = 0; i < pSrc->numVertices; ++i )
                        {
                            rdVector_Copy3(&pDest->aVertices[i], &pSrc->aVertices[pSrc->aVertIdxs[i]]);
                            rdVector_Copy2(&pDest->aTexVertices[i], &pSrc->aTexVertices[pSrc->aTexVertIdxs[i]]);

                            pDest->aTexVertices[i].x = pDest->aTexVertices[i].x + pTexVertOffset->x;
                            pDest->aTexVertices[i].y = pDest->aTexVertices[i].y + pTexVertOffset->y;

                            // TODO: verify if it's a bug assigning to pDest->aVertLights[i] instead of pSrc->aVertLights[pSrc->aVertIdxs[i]]

                            if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].red < 0.0f )
                            {
                                red = 0.0f;
                            }

                            else if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].red > 1.0f )
                            {
                                red = 1.0f;
                            }
                            else
                            {
                                red = pSrc->aVertLights[pSrc->aVertIdxs[i]].red;
                            }

                            pDest->aVertLights[i].red = red;

                            if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].green < 0.0f )
                            {
                                green = 0.0f;
                            }

                            else if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].green > 1.0f )
                            {
                                green = 1.0f;
                            }
                            else
                            {
                                green = pSrc->aVertLights[pSrc->aVertIdxs[i]].green;
                            }

                            pDest->aVertLights[i].green = green;

                            if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].blue < 0.0f )
                            {
                                blue = 0.0f;
                            }

                            else if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].blue > 1.0f )
                            {
                                blue = 1.0f;
                            }
                            else
                            {
                                blue = pSrc->aVertLights[pSrc->aVertIdxs[i]].blue;
                            }

                            pDest->aVertLights[i].blue = blue;

                            if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].alpha < 0.0f )
                            {
                                alpha = 0.0f;
                            }

                            else if ( pSrc->aVertLights[pSrc->aVertIdxs[i]].alpha > 1.0f )
                            {
                                alpha = 1.0f;
                            }
                            else
                            {
                                alpha = pSrc->aVertLights[pSrc->aVertIdxs[i]].alpha;
                            }

                            pDest->aVertLights[i].alpha = alpha;
                        }
                    }

                    if ( rdCamera_g_pCurCamera->projectType == RDCAMERA_PROJECT_PERSPECTIVE )
                    {
                        pDest->numVertices = rdClip_Face3T(pFrustrum, pDest->aVertices, pDest->aTexVertices, pDest->aVertLights, pSrc->numVertices);
                    }
                    else
                    {
                        pDest->numVertices = rdClip_Face3TOrtho(pFrustrum, pDest->aVertices, pDest->aTexVertices, pDest->aVertLights, pSrc->numVertices);
                    }
                }
            }

            break;

        default:
            return;
    }
}