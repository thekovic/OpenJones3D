#ifndef W32UTIL_RTI_SYMBOLS_H
#define W32UTIL_RTI_SYMBOLS_H
#include <j3dcore/j3d.h>

#define wuRegistry_Startup_TYPE int (J3DAPI*)(HKEY, LPCSTR)
#define wuRegistry_Shutdown_TYPE void (J3DAPI*)()
#define wuRegistry_SaveInt_TYPE int (J3DAPI*)(const char*, int)
#define wuRegistry_SaveFloat_TYPE int (J3DAPI*)(const char*, float)
#define wuRegistry_GetInt_TYPE int (J3DAPI*)(const char*, int)
#define wuRegistry_GetFloat_TYPE float (J3DAPI*)(const char*, float)
#define wuRegistry_SaveIntEx_TYPE int (J3DAPI*)(const char*, int)
#define wuRegistry_GetIntEx_TYPE int (J3DAPI*)(const char*, int)
#define wuRegistry_SaveStr_TYPE int (J3DAPI*)(const char*, const char*)
#define wuRegistry_GetStr_TYPE int (J3DAPI*)(const char*, char*, size_t, const char*)

#endif // W32UTIL_RTI_SYMBOLS_H
