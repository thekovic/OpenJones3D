#ifndef W32UTIL_RTI_ADDRESSES_H
#define W32UTIL_RTI_ADDRESSES_H
#include <j3dcore/j3d.h>

// Function addresses

#define wuRegistry_Startup_ADDR 0x004C3A70
#define wuRegistry_Shutdown_ADDR 0x004C3B60
#define wuRegistry_SaveInt_ADDR 0x004C3B80
#define wuRegistry_SaveFloat_ADDR 0x004C3C70
#define wuRegistry_GetInt_ADDR 0x004C3D60
#define wuRegistry_GetFloat_ADDR 0x004C3E60
#define wuRegistry_SaveIntEx_ADDR 0x004C3F50
#define wuRegistry_GetIntEx_ADDR 0x004C3F90
#define wuRegistry_SaveStr_ADDR 0x004C3FD0
#define wuRegistry_GetStr_ADDR 0x004C40D0

// Variable addresses

#define wuRegistry_g_bStarted_ADDR 0x005E1020
#define wuRegistry_appSubKey_ADDR 0x005E1024
#define wuRegistry_appRootKey_ADDR 0x005E1028

#endif // W32UTIL_RTI_ADDRESSES_H
