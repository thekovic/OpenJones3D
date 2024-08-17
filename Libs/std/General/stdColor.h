#ifndef STD_STDCOLOR_H
#define STD_STDCOLOR_H
#include <j3dcore/j3d.h>
#include <std/types.h>
#include <std/RTI/addresses.h>

J3D_EXTERN_C_START

void J3DAPI stdColor_ColorConvertOneRow(uint8_t* pDestRow, const ColorInfo* pDestInfo, const uint8_t* pSrcRow, const ColorInfo* pSrcInfo, int width, int bColorKey, LPDDCOLORKEY pColorKey);

// Helper hooking functions
void stdColor_InstallHooks(void);
void stdColor_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // STD_STDCOLOR_H
