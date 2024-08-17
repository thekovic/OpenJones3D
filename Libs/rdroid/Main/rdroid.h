#ifndef RDROID_RDROID_H
#define RDROID_RDROID_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <rdroid/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define RDLOG_DEBUG(format, ...) \
    J3DLOG_DEBUG(rdroid_g_pHS, format, ##__VA_ARGS__)

#define RDLOG_STATUS(format, ...) \
    J3DLOG_STATUS(rdroid_g_pHS, format, ##__VA_ARGS__)

#define RDLOG_MESSAGE(format, ...) \
    J3DLOG_MESSAGE(rdroid_g_pHS, format, ##__VA_ARGS__)

#define RDLOG_WARNING(format, ...) \
    J3DLOG_WARNING(rdroid_g_pHS, format, ##__VA_ARGS__)

#define RDLOG_ERROR(format, ...) \
    J3DLOG_ERROR(rdroid_g_pHS, format, ##__VA_ARGS__)

#define RDLOG_FATAL(message) \
    J3DLOG_FATAL(rdroid_g_pHS, message)

#define RD_ASSERT(condition) \
    J3D_ASSERTREL(condition, rdroid_g_pHS )

#define RD_ASSERTREL(condition) \
    J3D_ASSERTREL(condition, rdroid_g_pHS )

#define rdroid_g_zeroVector3 J3D_DECL_FAR_VAR(rdroid_g_zeroVector3, const rdVector3)
// extern const rdVector3 rdroid_g_zeroVector3 ;

#define rdroid_g_xVector3 J3D_DECL_FAR_VAR(rdroid_g_xVector3, const rdVector3)
// extern const rdVector3 rdroid_g_xVector3 ;

#define rdroid_g_yVector3 J3D_DECL_FAR_VAR(rdroid_g_yVector3, const rdVector3)
// extern const rdVector3 rdroid_g_yVector3 ;

#define rdroid_g_zVector3 J3D_DECL_FAR_VAR(rdroid_g_zVector3, const rdVector3)
// extern const rdVector3 rdroid_g_zVector3 ;

#define rdroid_g_identMatrix34 J3D_DECL_FAR_VAR(rdroid_g_identMatrix34, const rdMatrix34)
// extern const rdMatrix34 rdroid_g_identMatrix34 ;

#define rdroid_g_curLightingMode J3D_DECL_FAR_VAR(rdroid_g_curLightingMode, rdLightMode)
// extern rdLightMode rdroid_g_curLightingMode;

#define rdroid_g_pHS J3D_DECL_FAR_VAR(rdroid_g_pHS, tHostServices*)
// extern tHostServices *rdroid_g_pHS;

#define rdroid_g_curGeometryMode J3D_DECL_FAR_VAR(rdroid_g_curGeometryMode, rdGeometryMode)
// extern rdGeometryMode rdroid_g_curGeometryMode;

#define rdroid_g_curRenderOptions J3D_DECL_FAR_VAR(rdroid_g_curRenderOptions, rdRoidFlags)
// extern rdRoidFlags rdroid_g_curRenderOptions;

void J3DAPI rdSetServices(tHostServices* pHS);
void rdClearServices(void);
void J3DAPI rdStartup();
void J3DAPI rdShutdown();
int J3DAPI rdOpen();
void J3DAPI rdClose();
void J3DAPI rdSetRenderOptions(rdRoidFlags options);
void J3DAPI rdSetGeometryMode(rdGeometryMode mode);
void J3DAPI rdSetLightingMode(rdLightMode mode);
rdRoidFlags J3DAPI rdGetRenterOptions();

// Helper hooking functions
void rdroid_InstallHooks(void);
void rdroid_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // RDROID_RDROID_H
