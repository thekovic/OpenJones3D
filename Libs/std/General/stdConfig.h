#ifndef STDCONFIG_H
#define STDCONFIG_H

#include <j3dcore/j3d.h>
#include <std/types.h>
#include <stddef.h>
#include <stdbool.h>

J3D_EXTERN_C_START

bool J3DAPI stdConfig_Startup(const char* pConfigPath);
bool stdConfig_HasStarted(void);
void J3DAPI stdConfig_Shutdown(void);

/**
 * Adds a mapping between a config key and a registry key.
 * This allows falling back to the registry if the config key does not exist in the JSON config.
 * The key supports nested keys using dot notation (e.g. "graphics.fullscreen").
 *
 * @param pConfigKey - Config key to map.
 * @param pRegistryKey - Registry key to map to.
 * @return true if successful, false on error (e.g. module not started).
 */
bool J3DAPI stdConfig_SetBool(const char* pKey, bool value);

/**
 * Gets bool value for given key.
 * The key supports nested keys using dot notation (e.g. "graphics.fullscreen").
 * If the key does not exist, the defaultValue is returned.
 *
 * @param pKey - Key to get value for.
 * @param defaultValue - Value to return if key does not exist.
 * @return Value associated with key, or defaultValue if key does not exist or on error (e.g. module not started).
 */
bool J3DAPI stdConfig_GetBool(const char* pKey, bool defaultValue);

/**
 * Sets int value for given key.
 * The key supports nested keys using dot notation (e.g. "graphics.resolution.width").
 *
 * @param pKey - Key to set value for.
 * @param value - Value to set.
 * @return true if successful, false on error (e.g. module not started).
 */
bool J3DAPI stdConfig_SetInt(const char* pKey, int value);

/**
 * Gets int value for given key.
 * The key supports nested keys using dot notation (e.g. "graphics.resolution.width").
 * If the key does not exist, the defaultValue is returned.
 *
 * @param pKey - Key to get value for.
 * @param defaultValue - Value to return if key does not exist.
 * @return Value associated with key, or defaultValue if key does not exist or on error (e.g. module not started).
 */
int J3DAPI stdConfig_GetInt(const char* pKey, int defaultValue);

/**
 * Sets float value for given key.
 * The key supports nested keys using dot notation (e.g. "graphics.resolution.width").
 *
 * @param pKey - Key to set value for.
 * @param value - Value to set.
 * @return true if successful, false on error (e.g. module not started).
 */
bool J3DAPI stdConfig_SetFloat(const char* pKey, float value);

/**
 * Gets float value for given key.
 * The key supports nested keys using dot notation (e.g. "graphics.resolution.width").
 * If the key does not exist, the defaultValue is returned.
 *
 * @param pKey - Key to get value for.
 * @param defaultValue - Value to return if key does not exist.
 * @return Value associated with key, or defaultValue if key does not exist or on error (e.g. module not started).
 */
float J3DAPI stdConfig_GetFloat(const char* pKey, float defaultValue);

/**
 * Sets string value for given key.
 * The key supports nested keys using dot notation (e.g. "key.subkey").
 *
 * @param pKey - Key to set value for.
 * @param pStr - String value to set.
 * @return true if successful, false on error (e.g. module not started).
 */
bool J3DAPI stdConfig_SetString(const char* pKey, const char* pStr);

/**
 * Gets string value for given key.
 * The key supports nested keys using dot notation (e.g. "key.subkey").
 * If the key does not exist, the pDefaultValue is used if provided, otherwise an empty string is returned.
 *
 * @param pKey - Key to get value for.
 * @param pDstStr - Buffer to store the retrieved string.
 * @param size - Size of the buffer pointed to by pDstStr.
 * @param pDefaultValue - Default string to use if key does not exist. Can be NULL.
 * @return true if the string was successfully retrieved and copied into pDstStr; otherwise, false.
 *         If false is returned, pDstStr will contain an empty string if pDefaultValue is NULL, or the default value if provided.
 */
bool J3DAPI stdConfig_GetString(const char* pKey, char* pDstStr, size_t size, const char* pDefaultValue);

J3D_EXTERN_C_END

#endif // STDCONFIG_H