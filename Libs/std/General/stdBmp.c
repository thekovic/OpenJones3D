#include "std.h"
#include "stdBmp.h"
#include "stdColor.h"
#include "stdMemory.h"

#include <j3dcore/j3dhook.h>


#include <std/RTI/symbols.h>
#include <std/Win95/stdDisplay.h>

static const uint16_t BMP_TYPE = 0x4D42;

void stdBmp_InstallHooks(void)
{
    J3D_HOOKFUNC(stdBmp_WriteVBuffer);
    J3D_HOOKFUNC(stdBmp_Load);
}

void stdBmp_ResetGlobals(void)
{

}

int J3DAPI stdBmp_WriteVBuffer(const char* pFilename, tVBuffer* pVBuffer)
{
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;


    STD_ASSERTREL(pFilename != ((void*)0));
    STD_ASSERTREL(pVBuffer != ((void*)0));

    if ( pVBuffer->rasterInfo.colorInfo.colorMode == STDCOLOR_PAL )
    {
        return 1;
    }

    ColorInfo ciBmp = stdColor_cfRGB888; // Note, changed encoding format due to little-endian fix in stdColor_ColorConvertOneRow

    // TODO: Add padding
    DWORD imageSize = (pVBuffer->rasterInfo.width * pVBuffer->rasterInfo.height * ciBmp.bpp) / 8; // Added: Fixed bug and changed pVBuffer->rasterInfo.colorInfo.bpp => ciBmp.bpp

    fileHeader.bfType      = BMP_TYPE;
    fileHeader.bfOffBits   = sizeof(fileHeader) + sizeof(infoHeader);
    fileHeader.bfSize      = fileHeader.bfOffBits + imageSize;
    fileHeader.bfReserved1 = 0;
    fileHeader.bfReserved2 = 0;

    memset(&infoHeader, 0, sizeof(infoHeader));
    infoHeader.biSize          = sizeof(infoHeader);
    infoHeader.biWidth         = pVBuffer->rasterInfo.width;
    infoHeader.biHeight        = pVBuffer->rasterInfo.height;
    infoHeader.biPlanes        = 1;
    infoHeader.biBitCount      = (WORD)ciBmp.bpp;
    infoHeader.biXPelsPerMeter = 2834;
    infoHeader.biYPelsPerMeter = 2834;
    infoHeader.biCompression   = BI_RGB;
    infoHeader.biSizeImage     = imageSize;

    tFileHandle fh = std_g_pHS->pFileOpen(pFilename, "wb");
    if ( !fh )
    {
        STDLOG_ERROR("Unable to open file '%s' for writing.\n", pFilename);

        return 1;
    }

    if ( std_g_pHS->pFileWrite(fh, &fileHeader, sizeof(fileHeader)) != sizeof(fileHeader) )
    {
        STDLOG_ERROR("Error attempting to write %d bytes to file '%s'.\n", sizeof(fileHeader), pFilename);
        std_g_pHS->pFileClose(fh);
        return 1;
    }

    if ( std_g_pHS->pFileWrite(fh, &infoHeader, sizeof(infoHeader)) != sizeof(infoHeader) )
    {
        STDLOG_ERROR("Error attempting to write %d bytes to file '%s'.\n", sizeof(infoHeader), pFilename);

        std_g_pHS->pFileClose(fh);
        return 1;
    }

    unsigned stride = 3 * pVBuffer->rasterInfo.width; // 3 - 24 bpp
    uint8_t* pRow = (uint8_t*)STDMALLOC(stride);
    if ( !pRow )
    {
        std_g_pHS->pFileClose(fh);
        return 1;
    }

    memset(pRow, 0, stride);

    int res = 0;
    stdDisplay_VBufferLock(pVBuffer);
    for ( int rowIdx = pVBuffer->rasterInfo.height - 1; rowIdx >= 0; rowIdx-- )
    {
        stdColor_ColorConvertOneRow(
            pRow,
            &ciBmp,
            &pVBuffer->pPixels[pVBuffer->rasterInfo.rowSize * rowIdx],
            &pVBuffer->rasterInfo.colorInfo,
            pVBuffer->rasterInfo.width,
            0,
            0
        );

        size_t nWritten = std_g_pHS->pFileWrite(fh, pRow, stride);
        if ( nWritten != stride )
        {
            STDLOG_ERROR("Error attempting to write %d bytes to file '%s'.\n", stride, pFilename);
            res = 1;
            break;
        }
    }

    stdMemory_Free(pRow);
    stdDisplay_VBufferUnlock(pVBuffer);
    std_g_pHS->pFileClose(fh);
    return res;
}

HBITMAP J3DAPI stdBmp_Load(const char* pFilename)
{
    HDC hdc;
    BITMAPFILEHEADER bmpHeader;
    tFileHandle fh;
    void* ppvBits;
    BITMAPINFO bmi;
    size_t nRead;
    BITMAPINFOHEADER infoHeader;

    if ( !pFilename )
    {
        return NULL;
    }

    fh = std_g_pHS->pFileOpen(pFilename, "rb");
    if ( !fh )
    {
        STDLOG_ERROR("Error: Invalid filename '%s'.\n", pFilename);
        return NULL;
    }

    nRead = std_g_pHS->pFileRead(fh, &bmpHeader, 14);
    nRead += std_g_pHS->pFileRead(fh, &infoHeader, 40);

    if ( nRead != (sizeof(bmpHeader) + sizeof(infoHeader)) )
    {
        STDLOG_ERROR("Error: Cannot read File's header.\n");
        std_g_pHS->pFileClose(fh);
        return NULL;
    }

    if ( bmpHeader.bfType != BMP_TYPE )
    {
        STDLOG_ERROR("Error: File's header does not contain 'BM' so its not a BMP file.\n");
        std_g_pHS->pFileClose(fh);
        return NULL;
    }

    if ( infoHeader.biSize != sizeof(BITMAPINFOHEADER) )
    {
        STDLOG_ERROR("Error: File's info header contains wrong header size.  The file may not be a BMP.\n");
        std_g_pHS->pFileClose(fh);
        return NULL;
    }

    HBITMAP hbmp = NULL;
    switch ( infoHeader.biBitCount )
    {
        case 24u:
            memcpy(&bmi, &infoHeader, sizeof(BITMAPINFOHEADER));
            bmi.bmiHeader.biSizeImage = 3 * bmi.bmiHeader.biHeight * bmi.bmiHeader.biWidth;
            hdc = CreateCompatibleDC(NULL);
            if ( hdc )
            {
                hbmp = CreateDIBSection(hdc, &bmi, 0, &ppvBits, NULL, 0);
                if ( hbmp )
                {
                    nRead = std_g_pHS->pFileRead(fh, ppvBits, bmi.bmiHeader.biSizeImage);
                    if ( nRead != bmi.bmiHeader.biSizeImage ) {
                        STDLOG_ERROR("Unable to read all the data from your BMP file. It may be corrupted.\n");
                    }
                    DeleteDC(hdc); // Fixed: Delete hdcThumbnail in case of an error
                }
            }
            break;

        case 8u:
            STDLOG_ERROR("8 bpp BMP not yet supported.\n");
            break;

        case 16u:
            STDLOG_ERROR("16 bpp BMP not yet supported.\n");
            break;

        case 32u:
            STDLOG_ERROR("32 bpp BMP not yet supported.\n");
            break;

        default:
            STDLOG_ERROR("This BMP file uses a bit-depth I do not support yet.\n");
            break;
    }

    std_g_pHS->pFileClose(fh);
    return hbmp;
}
