#include "std.h"
#include "stdColor.h"

#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>

void stdColor_InstallHooks(void)
{
    J3D_HOOKFUNC(stdColor_ColorConvertOneRow);
}

void stdColor_ResetGlobals(void)
{

}

void J3DAPI stdColor_RGBtoHSV(float r, float g, float b, float* hue, float* saturation, float* value)
{
    float cmin;
    float v8;
    float cmax;
    float v12;
    float v13;
    float v14;
    float r1;
    float v16;
    float g1;
    float v18;

    r1 = r * 0.0039215689f;
    g1 = g * 0.0039215689f;
    v12 = b * 0.0039215689f;
    if ( r1 <= (double)g1 )
    {
        cmax = g * 0.0039215689f;
    }
    else
    {
        cmax = r * 0.0039215689f;
    }

    if ( cmax <= (double)v12 )
    {
        cmax = b * 0.0039215689f;
    }

    else if ( r1 <= (double)g1 )
    {
        cmax = g * 0.0039215689f;
    }
    else
    {
        cmax = r * 0.0039215689f;
    }

    if ( r1 >= (double)g1 )
    {
        v8 = g * 0.0039215689f;
    }
    else
    {
        v8 = r * 0.0039215689f;
    }

    if ( v8 >= (double)v12 )
    {
        cmin = b * 0.0039215689f;
    }

    else if ( r1 >= (double)g1 )
    {
        cmin = g * 0.0039215689f;
    }
    else
    {
        cmin = r * 0.0039215689f;
    }

    v13 = cmax - cmin;
    *value = cmax;
    if ( cmax == 0.0f )
    {
        *saturation = 0.0f;
    }
    else
    {
        *saturation = v13 / cmax;
    }

    if ( *saturation == 0.0f )
    {
        *hue = 0.0f;
    }
    else
    {
        v14 = (cmax - r1) / v13;
        v18 = (cmax - g1) / v13;
        v16 = (cmax - v12) / v13;
        if ( r1 == cmax )
        {
            *hue = v16 - v18;
        }

        else if ( g1 == cmax )
        {
            *hue = v14 + 2.0f - v16;
        }

        else if ( v12 == cmax )
        {
            *hue = v18 + 4.0f - v14;
        }

        *hue = *hue * 60.0f;
        if ( *hue < 0.0f )
        {
            *hue = *hue + 360.0f;
        }
    }
}

void J3DAPI stdColor_HSVtoRGB(float hue, float saturation, float value, float* r, float* g, float* b)
{
    unsigned int i;
    float ff;
    float v9;
    float v10;
    float v11;
    float p;
    float hh;

    if ( saturation == 0.0f )
    {
        v9 = value * 255.0f;
        *r = v9;
        *g = v9;
        *b = v9;
    }
    else
    {
        if ( hue == 360.0f )
        {
            hue = 0.0f;
        }

        hh = hue / 60.0f;
        i = (int32_t)hh;
        ff = hh - (float)i;
        p = (1.0f - saturation) * value;
        v11 = (1.0f - saturation * ff) * value;
        v10 = (1.0f - (1.0f - ff) * saturation) * value;

        switch ( i )
        {
            case 0u:
                *r = value * 255.0f;
                *g = v10 * 255.0f;
                *b = p * 255.0f;
                break;

            case 1u:
                *r = v11 * 255.0f;
                *g = value * 255.0f;
                *b = p * 255.0f;
                break;

            case 2u:
                *r = p * 255.0f;
                *g = value * 255.0f;
                *b = v10 * 255.0f;
                break;

            case 3u:
                *r = p * 255.0f;
                *g = v11 * 255.0f;
                *b = value * 255.0f;
                break;

            case 4u:
                *r = v10 * 255.0f;
                *g = p * 255.0f;
                *b = value * 255.0f;
                break;

            case 5u:
                *r = value * 255.0f;
                *g = p * 255.0f;
                *b = v11 * 255.0f;
                break;

            default:
                return;
        }
    }
}

void J3DAPI stdColor_ColorConvertOneRow(uint8_t* pDestRow, const ColorInfo* pDestInfo, const uint8_t* pSrcRow, const ColorInfo* pSrcInfo, int width, int bColorKey, LPDDCOLORKEY pColorKey)
{
    unsigned int redMask       = 0xFFFFFFFF >> (32 - (pSrcInfo->redBPP & 0xFF));
    unsigned int greenMask     = 0xFFFFFFFF >> (32 - (pSrcInfo->greenBPP & 0xFF));
    unsigned int blueMask      = 0xFFFFFFFF >> (32 - (pSrcInfo->blueBPP & 0xFF));
    unsigned int alphaMask     = 0; // Added: Zero init
    unsigned int maxAlphaValue = 0; // Added: Zero init
    if ( pSrcInfo->alphaBPP )
    {
        alphaMask = 0xFFFFFFFF >> (32 - (pSrcInfo->alphaBPP & 0xFF));
        if ( (255 >> pSrcInfo->alphaPosShiftRight) / 2 <= 1 )
        {
            maxAlphaValue = 1;
        }
        else
        {
            maxAlphaValue = (255 >> pSrcInfo->alphaPosShiftRight) / 2;
        }
    }

    int redDelta   = pSrcInfo->redBPP - pDestInfo->redBPP;
    int greenDelta = pSrcInfo->greenBPP - pDestInfo->greenBPP;
    int blueDelta  = pSrcInfo->blueBPP - pDestInfo->blueBPP;
    int alphaDelta = 0;
    if ( pSrcInfo->alphaBPP )
    {
        alphaDelta = pSrcInfo->alphaBPP - pDestInfo->alphaBPP;
    }


    for ( int i = 0; i < width; ++i )
    {
        unsigned int pixel = 0;
        switch ( pSrcInfo->bpp )
        {
            case 8:
                pixel = *pSrcRow;
                break;

            case 16:
                pixel = *(uint16_t*)pSrcRow;
                break;

            case 24:
                // Fixed: Swap first and third byte to correctly extract encoded pixel in little-endian format (BGR/RGB)
                //        Original: pixel = pSrcRow[2] | (pSrcRow[1] << 8) | (*pSrcRow << 16);
                pixel = pSrcRow[0] | (pSrcRow[1] << 8) | (pSrcRow[2] << 16);
                break;

            case 32:
                pixel = *(uint32_t*)pSrcRow;
                break;

            default:
                STDLOG_FATAL("Unsupported pixel depth. Only 8, 16, 24, &32 bits per pixel supported at the moment.");
                break;
        }

        unsigned int r = redMask & (pixel >> pSrcInfo->redPosShift);
        unsigned int g = greenMask & (pixel >> pSrcInfo->greenPosShift);
        unsigned int b = blueMask & (pixel >> pSrcInfo->bluePosShift);
        unsigned int a = 0; // Added: Zero init
        if ( pSrcInfo->alphaBPP )
        {
            a = alphaMask & (pixel >> pSrcInfo->alphaPosShift);
        }

        if ( redDelta <= 0 ) {
            r <<= -(char)redDelta;
        }
        else {
            r >>= redDelta;
        }

        if ( greenDelta <= 0 ) {
            g <<= -(char)greenDelta;
        }
        else {
            g >>= greenDelta;
        }

        if ( redDelta <= 0 ) {
            b <<= -(char)blueDelta;
        }
        else {
            b >>= blueDelta;
        }

        pixel = (b << pDestInfo->bluePosShift) | (g << pDestInfo->greenPosShift) | (r << pDestInfo->redPosShift);
        if ( pSrcInfo->alphaBPP )
        {
            if ( bColorKey )
            {
                if ( a < maxAlphaValue ) {
                    pixel = (unsigned int)pColorKey;
                }
            }
            else
            {
                if ( alphaDelta <= 0 ) {
                    a <<= -(char)alphaDelta;
                }
                else {
                    a >>= alphaDelta;
                }

                pixel |= a << pDestInfo->alphaPosShift;
            }
        }

        switch ( pDestInfo->bpp )
        {
            case 8:
                *pDestRow = (pixel & 0xff);
                break;

            case 16:
                *(uint16_t*)pDestRow = (uint16_t)pixel;
                break;

            case 24:
                // Fixed: Swap first and third byte to correctly write encoded pixel in little-endian format (BGR/RGB)
                //        Original: 
                //             pDestRow[0] = (pixel >> 16) & 0xFF;
                //             pDestRow[1] = (pixel >> 8) & 0xFF;
                //             pDestRow[2] = pixel & 0xFF;
                pDestRow[0] = pixel & 0xFF;
                pDestRow[1] = (pixel >> 8) & 0xFF;
                pDestRow[2] = (pixel >> 16) & 0xFF;
                break;
            case 32:
                *(uint32_t*)pDestRow = pixel;
                break;

            default:
                STDLOG_FATAL("Unsupported pixel depth. Only 8, 16, 24, &32 bits per pixel supported at the moment.");
                break;
        }

        pSrcRow += (unsigned int)pSrcInfo->bpp >> 3;
        pDestRow += (unsigned int)pDestInfo->bpp >> 3;
    }
}

int J3DAPI stdColor_ColorConvertOnePixel(ColorInfo* pDestInfo, int pixl, ColorInfo* pSrcInfo, int bColorKey, LPDDCOLORKEY pColorKey)
{
    int cpixel = 0;
    stdColor_ColorConvertOneRow((uint8_t*)&cpixel, pDestInfo, (const uint8_t*)&pixl, pSrcInfo, 1, bColorKey, pColorKey);
    return cpixel;
}
