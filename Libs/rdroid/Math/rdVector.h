#ifndef RDROID_RDVECTOR_H
#define RDROID_RDVECTOR_H
#include <j3dcore/j3d.h>
#include <j3dcore/j3dhook.h>

#include <rdroid/types.h>
#include <rdroid/Main/rdroid.h>
#include <rdroid/RTI/addresses.h>
#include <std/types.h>

#include <math.h>

J3D_EXTERN_C_START

#define rdroid_g_zeroVector3 J3D_DECL_FAR_VAR(rdroid_g_zeroVector3, const rdVector3)
// extern const rdVector3 rdroid_g_zeroVector3 ;

#define rdroid_g_xVector3 J3D_DECL_FAR_VAR(rdroid_g_xVector3, const rdVector3)
// extern const rdVector3 rdroid_g_xVector3 ;

#define rdroid_g_yVector3 J3D_DECL_FAR_VAR(rdroid_g_yVector3, const rdVector3)
// extern const rdVector3 rdroid_g_yVector3 ;

#define rdroid_g_zVector3 J3D_DECL_FAR_VAR(rdroid_g_zVector3, const rdVector3)
// extern const rdVector3 rdroid_g_zVector3 ;

void J3DAPI rdVector_Set2(rdVector2* dest, float x, float y); // Added
void J3DAPI rdVector_Set3(rdVector3* dest, float x, float y, float z);
void J3DAPI rdVector_Set4(rdVector4* dest, float x, float y, float z, float w);
void J3DAPI rdVector_Copy2(rdVector2* dest, const rdVector2* src); // Added
void J3DAPI rdVector_Copy3(rdVector3* dest, const rdVector3* src); // Added
void J3DAPI rdVector_Copy4(rdVector4* dest, const rdVector4* src); // Added

void J3DAPI rdVector_Neg3(rdVector3* dest, const rdVector3* src);
void J3DAPI rdVector_Neg3Acc(rdVector3* a); // Added

void J3DAPI rdVector_Add3(rdVector3* c, const rdVector3* a, const rdVector3* b); // Added
void J3DAPI rdVector_Add3Acc(rdVector3* a, const rdVector3* b);

void J3DAPI rdVector_Add4(rdVector4* c, const rdVector4* a, const rdVector4* b); // Added
void J3DAPI rdVector_Add4Acc(rdVector4* a, const rdVector4* b); // Added

void J3DAPI rdVector_Sub3(rdVector3* c, const rdVector3* a, const rdVector3* b); // Added
void J3DAPI rdVector_Sub3Acc(rdVector3* a, const rdVector3* b); // Added

void J3DAPI rdVector_Scale3(rdVector3* dest, const rdVector3* src, float scalar); // Added
void J3DAPI rdVector_Scale3Acc(rdVector3* v, float scalar); // Added
void J3DAPI rdVector_InvScale3(rdVector3* dest, const rdVector3* src, float scalar);
void J3DAPI rdVector_InvScale3Acc(rdVector3* v, float scalar); // Added

void J3DAPI rdVector_ScaleAdd3(rdVector3* dest, const rdVector3* src, float scalar, const rdVector3* add); // Added
void J3DAPI rdVector_ScaleAdd3Acc(rdVector3* dest, const rdVector3* src, float scalar); // Added

float J3DAPI rdVector_Len3(const rdVector3* vec);
float J3DAPI rdVector_Dist3(const rdVector3* a, const rdVector3* b); // Added
float J3DAPI rdVector_Dot3(const rdVector3* a, const rdVector3* b);

float J3DAPI rdVector_Cross2(const rdVector2* v1, const rdVector2* v2); // Added
void J3DAPI rdVector_Cross3(rdVector3* dest, const rdVector3* v1, const rdVector3* v2); // Added
void J3DAPI rdVector_Cross3Acc(rdVector3* dest, const rdVector3* v2); // Added

/**
 * @brief Calculates scalar triple product.
     i.e.: the dot product of the cross product of vectors `a` and `b` with vector `c`.
 *
 * @param a - Pointer to the first input vector.
 * @param b - Pointer to the second input vector.
 * @param c - Pointer to the third input vector.
 * @return The dot product of the cross product of `a` and `b` with `c`.
 */
float J3DAPI rdVector_CrossDot3(const rdVector3* a, const rdVector3* b, const rdVector3* c); // Added

float J3DAPI rdVector_Normalize2(rdVector2* dest, const rdVector2* src); // Added
float J3DAPI rdVector_Normalize3(rdVector3* dest, const rdVector3* src);
float J3DAPI rdVector_Normalize4(rdVector4* dest, const rdVector4* src); // Added

float J3DAPI rdVector_Normalize2Acc(rdVector2* vec);
float J3DAPI rdVector_Normalize3Acc(rdVector3* vec);
float J3DAPI rdVector_Normalize3QuickAcc(rdVector3* src);
float J3DAPI rdVector_Normalize4Acc(rdVector4* vec);

void J3DAPI rdVector_Rotate3(rdVector3* vec, const rdVector3* pivot, const rdVector3* pyr);
void J3DAPI rdVector_Rotate3Acc(rdVector3* vec, const rdVector3* pyr);

inline void J3DAPI rdVector_Set2(rdVector2* dest, float x, float y)
{
    dest->x = x;
    dest->y = y;
}

inline void J3DAPI rdVector_Set3(rdVector3* dest, float x, float y, float z)
{
    dest->x = x;
    dest->y = y;
    dest->z = z;
}

inline void J3DAPI rdVector_Set4(rdVector4* dest, float x, float y, float z, float w)
{
    dest->x = x;
    dest->y = y;
    dest->z = z;
    dest->w = w;
}

inline void J3DAPI rdVector_Copy2(rdVector2* dest, const rdVector2* src)
{
    memcpy(dest, src, sizeof(rdVector2));
}

inline void J3DAPI rdVector_Copy3(rdVector3* dest, const rdVector3* src)
{
    memcpy(dest, src, sizeof(rdVector3));
}

inline void J3DAPI rdVector_Copy4(rdVector4* dest, const rdVector4* src)
{
    memcpy(dest, src, sizeof(rdVector4));
}

inline void J3DAPI rdVector_Neg3(rdVector3* dest, const rdVector3* src)
{
    dest->x = -src->x;
    dest->y = -src->y;
    dest->z = -src->z;
}

inline void J3DAPI rdVector_Neg3Acc(rdVector3* a)
{
    a->x = -a->x;
    a->y = -a->y;
    a->z = -a->z;
}

inline void J3DAPI rdVector_Add3(rdVector3* c, const rdVector3* a, const rdVector3* b)
{
    c->x = a->x + b->x;
    c->y = a->y + b->y;
    c->z = a->z + b->z;
}

inline void J3DAPI rdVector_Add3Acc(rdVector3* a, const rdVector3* b)
{
    a->x += b->x;
    a->y += b->y;
    a->z += b->z;
}

inline void J3DAPI rdVector_Add4(rdVector4* c, const rdVector4* a, const rdVector4* b)
{
    c->x = a->x + b->x;
    c->y = a->y + b->y;
    c->z = a->z + b->z;
    c->w = a->w + b->w;
}

inline void J3DAPI rdVector_Add4Acc(rdVector4* a, const rdVector4* b)
{
    a->x += b->x;
    a->y += b->y;
    a->z += b->z;
    a->w += b->w;
}

inline void J3DAPI rdVector_Sub3(rdVector3* c, const rdVector3* a, const rdVector3* b)
{
    c->x = a->x - b->x;
    c->y = a->y - b->y;
    c->z = a->z - b->z;
}

inline void J3DAPI rdVector_Sub3Acc(rdVector3* a, const rdVector3* b)
{
    a->x -= b->x;
    a->y -= b->y;
    a->z -= b->z;
}

inline void J3DAPI rdVector_Scale3(rdVector3* dest, const rdVector3* src, float scalar)
{
    dest->x = src->x * scalar;
    dest->y = src->y * scalar;
    dest->z = src->z * scalar;
}

inline void J3DAPI rdVector_Scale3Acc(rdVector3* v, float scalar)
{
    v->x = v->x * scalar;
    v->y = v->y * scalar;
    v->z = v->z * scalar;
}

inline void J3DAPI rdVector_InvScale3(rdVector3* dest, const rdVector3* src, float scalar)
{
    double invScalar = 1.0 / scalar;
    dest->x = (float)(src->x * invScalar);
    dest->y = (float)(src->y * invScalar);
    dest->z = (float)(src->z * invScalar);
}

inline void J3DAPI rdVector_InvScale3Acc(rdVector3* v, float scalar)
{
    double inv = 1.0 / scalar;
    v->x = (float)(v->x * inv);
    v->y = (float)(v->y * inv);
    v->z = (float)(v->z * inv);
}

inline void J3DAPI rdVector_ScaleAdd3(rdVector3* dest, const rdVector3* src, float scalar, const rdVector3* add)
{
    dest->x = src->x * scalar + add->x;
    dest->y = src->y * scalar + add->y;
    dest->z = src->z * scalar + add->z;
}

inline void J3DAPI rdVector_ScaleAdd3Acc(rdVector3* dest, const rdVector3* src, float scalar)
{
    dest->x += src->x * scalar;
    dest->y += src->y * scalar;
    dest->z += src->z * scalar;
}

inline float J3DAPI rdVector_Len3(const rdVector3* vec)
{
    return sqrtf(vec->y * vec->y + vec->z * vec->z + vec->x * vec->x);
}

inline float J3DAPI rdVector_Dist3(const rdVector3* a, const rdVector3* b)
{
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    float dz = a->z - b->z;
    return sqrtf(dx * dx + dy * dy + dz * dz);
}

inline float J3DAPI rdVector_Dot3(const rdVector3* a, const rdVector3* b)
{
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

inline float J3DAPI rdVector_Cross2(const rdVector2* v1, const rdVector2* v2)
{
    return v1->x * v2->y - v1->y * v2->x;
}

inline void J3DAPI rdVector_Cross3(rdVector3* dest, const rdVector3* v1, const rdVector3* v2)
{
    RD_ASSERT(((dest != v1) && (dest != v2)));
    dest->x = v1->y * v2->z - v1->z * v2->y;
    dest->y = v1->z * v2->x - v1->x * v2->z;
    dest->z = v1->x * v2->y - v1->y * v2->x;
}

inline void J3DAPI rdVector_Cross3Acc(rdVector3* dest, const rdVector3* v2)
{
    rdVector3 res;
    res.x = dest->y * v2->z - dest->z * v2->y;
    res.y = dest->z * v2->x - dest->x * v2->z;
    res.z = dest->x * v2->y - dest->y * v2->x;
    *dest = res;
}

inline float J3DAPI rdVector_CrossDot3(const rdVector3* a, const rdVector3* b, const rdVector3* c)
{
    return (a->y * b->z - b->y * a->z) * c->x
        + (a->z * b->x - b->z * a->x) * c->y
        + (a->x * b->y - b->x * a->y) * c->z;
}

// Helper hooking functions
void rdVector_InstallHooks(void);
void rdVector_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // RDROID_RDVECTOR_H
