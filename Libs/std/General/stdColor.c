#include "stdColor.h"
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>


void stdColor_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(stdColor_ColorConvertOneRow);
}

void stdColor_ResetGlobals(void)
{

}

void J3DAPI stdColor_ColorConvertOneRow(uint8_t* pDestRow, const ColorInfo* pDestInfo, const uint8_t* pSrcRow, const ColorInfo* pSrcInfo, int width, int bColorKey, LPDDCOLORKEY pColorKey)
{
    J3D_TRAMPOLINE_CALL(stdColor_ColorConvertOneRow, pDestRow, pDestInfo, pSrcRow, pSrcInfo, width, bColorKey, pColorKey);
}
