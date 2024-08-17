#ifndef STD_STDMEMORY_H
#define STD_STDMEMORY_H
#include <j3dcore/j3d.h>
#include <std/types.h>
#include <std/RTI/addresses.h>

J3D_EXTERN_C_START

/**
 * @brief Macro for allocating memory using stdMemory_Malloc
 * @param size The size of memory to allocate in bytes
 * @return Pointer to the allocated memory
 */
#define STDMALLOC(size) \
    stdMemory_Malloc((size), J3D_FILE, __LINE__)

#define stdMemory_g_curState J3D_DECL_FAR_VAR(stdMemory_g_curState, tMemoryState)
// extern tMemoryState stdMemory_g_curState;

int stdMemory_Startup(void);
void stdMemory_Shutdown(void);
int stdMemory_Open(void);
void stdMemory_Close(void);
void* J3DAPI stdMemory_Malloc(size_t size, const char* pFilename, size_t line);
void J3DAPI stdMemory_Free(void* pBytes);
void* J3DAPI stdMemory_Realloc(void* pBytes, size_t size, const char* pFilename, size_t line);
void* J3DAPI stdMemory_BlockMalloc(size_t size);
void J3DAPI stdMemory_BlockFree(void* pMemory);
void* J3DAPI stdMemory_BlockRealloc(void* pData, size_t size);
void* J3DAPI stdMemory_BlockAlloc(int size);

// Helper hooking functions
void stdMemory_InstallHooks(void);
void stdMemory_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // STD_STDMEMORY_H
