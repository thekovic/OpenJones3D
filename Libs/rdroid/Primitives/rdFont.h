#ifndef RDROID_RDFONT_H
#define RDROID_RDFONT_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <rdroid/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

rdFont* J3DAPI rdFont_Load(char* pFilename);
int J3DAPI rdFont_LoadEntry(const char* pFilename, rdFont* pFont);
int J3DAPI rdFont_LoadMaterial(const char* pFilename, rdFont* pFont);
void J3DAPI rdFont_Free(rdFont* pFont);
void J3DAPI rdFont_SetFontColor(rdVector4* apColor);
const char* J3DAPI rdFont_GetTextEnd(const char* pText, rdFont* pFont, float maxTextWidthScalar);
int J3DAPI rdFont_GetTextWidth(const char* pText, rdFont* pFont);
// local variable allocation has failed, the output may be wrong!
void J3DAPI rdFont_DrawText(const char* pText, float x, float y, float z, const rdFont* pFont, int flags);
void J3DAPI rdFont_DrawChar(uint8_t chr, float x, float y, float z, const rdFont* pFont);
void J3DAPI rdFont_DrawText2(const char* pText, float x, float y, float z, const rdFont* pFont, int flags);
void J3DAPI rdFont_Startup();
void rdFont_Shutdown();
int J3DAPI rdFont_Open();
void J3DAPI rdFont_Close();

// Helper hooking functions
void rdFont_InstallHooks(void);
void rdFont_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // RDROID_RDFONT_H
