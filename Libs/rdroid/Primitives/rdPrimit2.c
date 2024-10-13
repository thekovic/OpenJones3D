#include "rdPrimit2.h"
#include <j3dcore/j3dhook.h>

#include <rdroid/Engine/rdClip.h>
#include <rdroid/RTI/symbols.h>

#include <std/General/stdMath.h>
#include <std/Win95/std3D.h>
#include <std/Win95/stdDisplay.h>

D3DTLVERTEX rdPrimit2_aD3DVertices[2];

void rdPrimit2_InstallHooks(void)
{
    J3D_HOOKFUNC(rdPrimit2_DrawClippedLine);
    J3D_HOOKFUNC(rdPrimit2_Reset);
    J3D_HOOKFUNC(rdPrimit2_DrawClippedLine2);
    J3D_HOOKFUNC(rdPrimit2_DrawClippedCircle);
    J3D_HOOKFUNC(rdPrimit2_DrawClippedCircle2);
}

void rdPrimit2_ResetGlobals(void)
{
}

int J3DAPI rdPrimit2_DrawLine(rdCanvas* pCanvas, int x1, int y1, int x2, int y2, uint32_t color, uint32_t flags)
{
    int result;
    int v8;
    int v9;
    int v10;
    int v11;
    int v12;
    int v13;
    int v14;
    int v15;
    int bVBLocked;
    int v17;
    int v18;
    int v19;
    int v20;
    int v21;
    int v22;
    int v23;
    int v24;
    unsigned int mask;

    bVBLocked = 0;
    if ( pCanvas->pVBuffer->rasterInfo.colorInfo.bpp == 8 )
    {
        mask = 0x80000000;
        v12 = x2 - x1;
        v10 = y2 - y1;
        v19 = x1;
        v17 = y1;
        if ( x2 - x1 <= 0 )
        {
            v23 = -1;
        }
        else
        {
            v23 = 1;
        }

        if ( v10 <= 0 )
        {
            v21 = -1;
        }
        else
        {
            v21 = 1;
        }

        if ( v23 < 0 )
        {
            v10 = y1 - y2;
        }

        if ( v21 > 0 )
        {
            v12 = x1 - x2;
        }

        if ( (flags & 0x80000000) != 0 )
        {
            pCanvas->pVBuffer->pPixels[pCanvas->pVBuffer->rasterInfo.rowSize * y1 + x1] = color;
        }

        v14 = 0;
        while ( 1 )
        {
            result = v19;
            if ( v19 == x2 && v17 == y2 )
            {
                break;
            }

            mask >>= 1;
            if ( !mask )
            {
                mask = 0x80000000;
            }

            v8 = abs(v10 + v14);
            if ( v8 >= abs(v12 + v14) )
            {
                v17 += v21;
                v14 += v12;
            }
            else
            {
                v19 += v23;
                v14 += v10;
            }

            if ( (mask & flags) != 0 )
            {
                pCanvas->pVBuffer->pPixels[pCanvas->pVBuffer->rasterInfo.rowSize * v17 + v19] = color;
            }
        }
    }
    else
    {
        if ( pCanvas->pVBuffer->lockRefCount == 1 )
        {
            bVBLocked = 1;
            stdDisplay_VBufferLock(pCanvas->pVBuffer);
        }

        mask = 0x80000000;
        v13 = x2 - x1;
        v11 = y2 - y1;
        v20 = x1;
        v18 = y1;
        if ( x2 - x1 <= 0 )
        {
            v24 = -1;
        }
        else
        {
            v24 = 1;
        }

        if ( v11 <= 0 )
        {
            v22 = -1;
        }
        else
        {
            v22 = 1;
        }

        if ( v24 < 0 )
        {
            v11 = y1 - y2;
        }

        if ( v22 > 0 )
        {
            v13 = x1 - x2;
        }

        if ( (flags & 0x80000000) != 0 )
        {
            *(uint16_t*)&pCanvas->pVBuffer->pPixels[2 * pCanvas->pVBuffer->rasterInfo.rowWidth * y1 + 2 * x1] = color;// TODO: [BUG] should not expect that pPixels pix size is 2
        }

        v15 = 0;
        while ( 1 )
        {
            result = v20;
            if ( v20 == x2 && v18 == y2 )
            {
                break;
            }

            mask >>= 1;
            if ( !mask )
            {
                mask = 0x80000000;
            }

            v9 = abs(v11 + v15);
            if ( v9 >= abs(v13 + v15) )
            {
                v18 += v22;
                v15 += v13;
            }
            else
            {
                v20 += v24;
                v15 += v11;
            }

            if ( (mask & flags) != 0 )
            {
                *(uint16_t*)&pCanvas->pVBuffer->pPixels[2 * pCanvas->pVBuffer->rasterInfo.rowWidth * v18 + 2 * v20] = color;// TODO: [BUG] should not expect that pPixels pix size is 2
            }
        }

        if ( bVBLocked )
        {
            return stdDisplay_VBufferUnlock(pCanvas->pVBuffer);
        }
    }

    return result;
}

int J3DAPI rdPrimit2_DrawClippedLine(rdCanvas* pCanvas, int x1, int y1, int x2, int y2, uint32_t color, uint32_t flags)
{
    int v7;
    int v8;
    int dy;
    int dxx;
    int v14;
    int v15;
    int bVBLocked;
    int y;
    int x;
    int v21;
    int v22;
    int v23;
    int v24;
    unsigned int mask;

    bVBLocked = 0;
    if ( !rdClip_Line2(pCanvas, &x1, &y1, &x2, &y2) )
    {
        return 0;
    }

    if ( pCanvas->pVBuffer->rasterInfo.colorInfo.bpp == 8 )
    {
        mask = 0x80000000;
        dxx = x2 - x1;
        dy = y2 - y1;
        x = x1;
        y = y1;
        if ( x2 - x1 <= 0 )
        {
            v23 = -1;
        }
        else
        {
            v23 = 1;
        }

        if ( dy <= 0 )
        {
            v21 = -1;
        }
        else
        {
            v21 = 1;
        }

        if ( v23 < 0 )
        {
            dy = y1 - y2;
        }

        if ( v21 > 0 )
        {
            dxx = x1 - x2;
        }

        if ( (flags & 0x80000000) != 0 )
        {
            pCanvas->pVBuffer->pPixels[pCanvas->pVBuffer->rasterInfo.rowSize * y1 + x1] = color;
        }

        v14 = 0;
        while ( x != x2 || y != y2 )
        {
            mask >>= 1;
            if ( !mask )
            {
                mask = 0x80000000;
            }

            v7 = abs(dy + v14);
            if ( v7 >= abs(dxx + v14) )
            {
                y += v21;
                v14 += dxx;
            }
            else
            {
                x += v23;
                v14 += dy;
            }

            if ( (mask & flags) != 0 )
            {
                pCanvas->pVBuffer->pPixels[pCanvas->pVBuffer->rasterInfo.rowSize * y + x] = color;
            }
        }
    }
    else
    {
        if ( pCanvas->pVBuffer->lockRefCount == 1 )
        {
            bVBLocked = 1;
            stdDisplay_VBufferLock(pCanvas->pVBuffer);
        }

        mask = 0x80000000;
        dxx = x2 - x1;
        dy = y2 - y1;
        x = x1;
        y = y1;
        if ( x2 - x1 <= 0 )
        {
            v24 = -1;
        }
        else
        {
            v24 = 1;
        }

        if ( dy <= 0 )
        {
            v22 = -1;
        }
        else
        {
            v22 = 1;
        }

        if ( v24 < 0 )
        {
            dy = y1 - y2;
        }

        if ( v22 > 0 )
        {
            dxx = x1 - x2;
        }

        if ( (flags & 0x80000000) != 0 )
        {
            *(uint16_t*)&pCanvas->pVBuffer->pPixels[2 * pCanvas->pVBuffer->rasterInfo.rowWidth * y1 + 2 * x1] = color;// TODO: [BUG] should not expect that pPixels pix size is 2
        }

        v15 = 0;
        while ( x != x2 || y != y2 )
        {
            mask >>= 1;
            if ( !mask )
            {
                mask = 0x80000000;
            }

            v8 = abs(dy + v15);
            if ( v8 >= abs(dxx + v15) )
            {
                y += v22;
                v15 += dxx;
            }
            else
            {
                x += v24;
                v15 += dy;
            }

            if ( (mask & flags) != 0 )
            {
                *(uint16_t*)&pCanvas->pVBuffer->pPixels[2 * pCanvas->pVBuffer->rasterInfo.rowWidth * y + 2 * x] = color;// TODO: [BUG] should not expect that pPixels pix size is 2
            }
        }

        if ( bVBLocked )
        {
            stdDisplay_VBufferUnlock(pCanvas->pVBuffer);
        }
    }

    return 1;
}

void rdPrimit2_Reset(void)
{
    std3D_SetWireframeRenderState();
    memset(rdPrimit2_aD3DVertices, 0, sizeof(rdPrimit2_aD3DVertices));
}

int J3DAPI rdPrimit2_DrawClippedLine2(float x1, float y1, float x2, float y2, uint32_t color)
{
    if ( !rdClip_Line2Ex(&x1, &y1, &x2, &y2) )
    {
        return 0;
    }

    rdPrimit2_aD3DVertices[0].sx = x1;
    rdPrimit2_aD3DVertices[0].sy = y1;
    rdPrimit2_aD3DVertices[0].color = color;

    rdPrimit2_aD3DVertices[1].sx = x2;
    rdPrimit2_aD3DVertices[1].sy = y2;
    rdPrimit2_aD3DVertices[1].color = color;

    std3D_DrawLineStrip(rdPrimit2_aD3DVertices, 2u);
    return 1;
}

void J3DAPI rdPrimit2_DrawClippedCircle(rdCanvas* pCanvas, int x, int y, float radius, float step, uint32_t color, uint32_t flags)
{
    float angle;
    int v8;
    int y2;
    int x2;
    float cosval;
    int y1;
    int x1;
    float sinval;

    v8 = (int32_t)(radius + 0.5f);
    if ( v8 + x >= pCanvas->rect.left && x - v8 <= pCanvas->rect.right && v8 + y >= pCanvas->rect.top && y - v8 <= pCanvas->rect.bottom )
    {
        stdMath_SinCos(0.0f, &sinval, &cosval);
        x1 = x + (int32_t)(radius * cosval + 0.5f);
        y1 = y + (int32_t)(radius * sinval + 0.5f);
        for ( angle = step + 0.0f; angle <= 360.0f; angle = angle + step )
        {
            stdMath_SinCos(angle, &sinval, &cosval);
            x2 = x + (int32_t)(radius * cosval + 0.5f);
            y2 = y + (int32_t)(radius * sinval + 0.5f);

            rdPrimit2_DrawClippedLine(pCanvas, x1, y1, x2, y2, color, flags);
            x1 = x2;
            y1 = y2;
        }
    }
}

void J3DAPI rdPrimit2_DrawClippedCircle2(float centerX, float centerY, float radius, float degrees, uint32_t color)
{
    float cosval;
    float sinval;

    stdMath_SinCos(0.0f, &sinval, &cosval);
    float x1 = radius * cosval + centerX;
    float y1 = radius * sinval + centerY;
    for ( float angle = degrees + 0.0f; angle <= 360.0f; angle = angle + degrees )
    {
        stdMath_SinCos(angle, &sinval, &cosval);
        float x2 = radius * cosval + centerX;
        float y2 = radius * sinval + centerY;
        rdPrimit2_DrawClippedLine2(x1, y1, x2, y2, color);
        x1 = x2;
        y1 = y2;
    }
}

int J3DAPI rdPrimit2_DrawRectangle(rdCanvas* pCanvas, int x1, int y1, int x2, int y2, uint32_t color, uint32_t flags)
{
    rdPrimit2_DrawClippedLine(pCanvas, x1, y1, x2, y1, color, flags);
    rdPrimit2_DrawClippedLine(pCanvas, x2, y1, x2, y2, color, flags);
    rdPrimit2_DrawClippedLine(pCanvas, x1, y1, x1, y2, color, flags);
    return rdPrimit2_DrawClippedLine(pCanvas, x1, y2, x2, y2, color, flags);
}

int J3DAPI rdPrimit2_DrawTriangle(rdCanvas* pCanvas, int x1, int y1, int x2, int y2, int a6, int a7, uint32_t color, uint32_t flags)
{
    rdPrimit2_DrawClippedLine(pCanvas, x1, y1, x2, y2, color, flags);
    rdPrimit2_DrawClippedLine(pCanvas, x2, y2, a6, a7, color, flags);
    return rdPrimit2_DrawClippedLine(pCanvas, a6, a7, x1, y1, color, flags);
}
