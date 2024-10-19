#ifndef RDROID_RDFONT_H
#define RDROID_RDFONT_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>

#include <rdroid/Math/rdVector.h>
#include <rdroid/RTI/addresses.h>

#include <std/types.h>

J3D_EXTERN_C_START

#define RDFONT_ALIGNCENTER 1
#define RDFONT_ALIGNLEFT   2
#define RDFONT_ALIGNRIGHT  4

#define RDFONT_REF_WIDTH  640.0f
#define RDFONT_REF_HEIGHT 480.0f

typedef rdVector4 rdFontColor[4];

void rdFont_Startup(void);
void rdFont_Shutdown(void);
int rdFont_Open(void);
void rdFont_Close(void);

rdFont* J3DAPI rdFont_Load(const char* pFilename);
int J3DAPI rdFont_LoadEntry(const char* pFilename, rdFont* pFont);
int J3DAPI rdFont_LoadMaterial(const char* pFilename, rdFont* pFont);

int J3DAPI rdFont_Write(const char* pFilename, const rdFont* pFont, tVBuffer*** paTextures); // Added
int J3DAPI rdFont_WriteEntry(const char* pFilename, const rdFont* pFont); // Added
int J3DAPI rdFont_WriteMaterial(const char* pFilename, const rdMaterial* pMat, tVBuffer*** paTextures); // Added

void J3DAPI rdFont_Free(rdFont* pFont);

void J3DAPI rdFont_SetFontColorDiffuse(const rdFontColor apColor); // Added
void J3DAPI rdFont_SetFontColor(const rdFontColor apColor);
rdFontColor* rdFont_DuplicateFontColor(void); // Added

// Returns normalized X in screen pixels that can be used in draw line funcs
inline float rdFont_GetNormX(float x)
{
    return (x / RDFONT_REF_WIDTH);
}

// Returns normalized Y in screen pixels that can be used in draw line funcs
inline float rdFont_GetNormY(float y)
{
    return (y / RDFONT_REF_HEIGHT);
}

inline float rdFont_GetNormLineSpacing(const rdFont* pFont)
{
    return rdFont_GetNormY((float)pFont->lineSpacing);
}

/**
 * @brief Returns the pointer to the end of the last word in the text that can still fit within the specified screen width.
 *
 * The function calculates the line's end by measuring the width of each character using the provided font.
 * It continues until the accumulated width plus the next character exceeds the screen width (calculated as 640 * widthScale).
 * The pointer returned points to the end of the last word that still fits within these bounds.
 *
 * @param pText - Pointer to the input text string to be wrapped.
 * @param pFont - Pointer to the rdFont structure that provides the font metrics for character widths.
 * @param widthScale - Scaling factor applied to 640 pixels to determine the line's maximum width.
 *
 * @return A pointer to the end of the last word that fits within the width (640 * widthScale) or NULL if no valid line is found.
 */
const char* J3DAPI rdFont_GetWrapLine(const char* pText, const rdFont* pFont, float widthScale);

/**
 * @brief Calculates the total width of the given text based on the provided font metrics.
 *
 * This function computes the total width of a string of text by summing up the width of each character
 * according to the font specified by the rdFont structure.
 *
 * @param pText Pointer to the input text string whose width is to be calculated.
 * @param pFont Pointer to the rdFont structure that provides the font metrics for character widths.
 *
 * @return The total width of the text, in pixels.
 */
size_t J3DAPI rdFont_GetTextWidth(const char* pText, const rdFont* pFont);

/**
 * @brief Draws a line of text to screen at a normalized screen position using the specified font, stopping when the screen width is exceeded.
 *
 * The text is drawn starting at the normalized coordinates (x, y), where both x and y are within the range [0.0, 1.0], representing
 * the relative position on the screen. The z parameter represents the NDC (Normalized Device Coordinates) z-depth value.
 * The text will be drawn until it reaches the end of the screen width, and any remaining characters after that point will not be drawn.
 *
 * @param pText -  Pointer to the input text string to be drawn.
 * @param x - Normalized X position in the range [0.0, 1.0], representing horizontal placement on the screen.
 * @param y - Normalized Y position in the range [0.0, 1.0], representing vertical placement on the screen.
 * @param z - NDC Z-depth value for positioning the text in depth.
 * @param pFont - Pointer to the rdFont structure that defines the font for the text rendering.
 * @param alignFlags -  Flags for alignment, defining how the text should be aligned (RDFONT_ALIGN*).
 */
void J3DAPI rdFont_DrawTextLine(const char* pText, float x, float y, float z, const rdFont* pFont, int alignFlags);

/**
 * @brief Draws a line of text to screen at a normalized screen position with clipping based on Y-axis, stopping when the screen width is exceeded.
 *
 * This function behaves similarly to `rdFont_DrawTextLine`, except it additionally checks if the text fits in the Y-axis
 * (vertical placement). If the Y-coordinate is outside the screen height range (0.0 to 1.0), or the text line would be fully
 * outside the screen's vertical bounds, the text will not be drawn.
 *
 * @param pText - Pointer to the input text string to be drawn.
 * @param x - Normalized X position in the range [0.0, 1.0], representing horizontal placement on the screen.
 * @param y - Normalized Y position in the range [0.0, 1.0], representing vertical placement on the screen.
 * @param z - NDC Z-depth value for positioning the text in depth.
 * @param pFont - Pointer to the rdFont structure that defines the font for the text rendering.
 * @param alignFlags - Flags for alignment, defining how the text should be aligned (RDFONT_ALIGN*).
 */
void J3DAPI rdFont_DrawTextLineClipped(const char* pText, float x, float y, float z, const rdFont* pFont, int alignFlags);

// Helper hooking functions
void rdFont_InstallHooks(void);
void rdFont_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // RDROID_RDFONT_H
