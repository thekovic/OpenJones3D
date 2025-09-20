#ifndef STDJSON_H
#define STDJSON_H
#include <j3dcore/j3d.h>
#include <std/types.h>

#include <stdbool.h>
#include <stddef.h>

J3D_EXTERN_C_START

typedef struct sStdJSON* StdJSONHandle;

typedef enum eStdJSONType
{
    STDJSON_TYPE_NULL,
    STDJSON_TYPE_BOOL,
    STDJSON_TYPE_INTEGER,
    STDJSON_TYPE_REAL,
    STDJSON_TYPE_STRING,
    STDJSON_TYPE_ARRAY,
    STDJSON_TYPE_OBJECT
} StdJSONType;

// Key enumeration callback
typedef bool (*StdJSONEnumKeyCallback)(const char* pKey, void* pUserData);

//
// Module initialization and cleanup
//
bool J3DAPI stdJSON_Startup(void);
bool stdJSON_HasStarted(void);
void J3DAPI stdJSON_Shutdown(void);

StdJSONHandle J3DAPI stdJSON_New(void);
void J3DAPI stdJSON_FreeEntry(StdJSONHandle hJson);
void J3DAPI stdJSON_Free(StdJSONHandle hJson);

//
// Copying and merging
//
StdJSONHandle J3DAPI stdJSON_Duplicate(const StdJSONHandle hSrc); // Deep copy
bool J3DAPI stdJSON_Merge(StdJSONHandle hDst, const StdJSONHandle hSrc, bool bOverwrite); // Merge hSrc into hDst. bOverwrite - if true, existing keys in hDst will be overwritten
bool J3DAPI stdJSON_Clear(StdJSONHandle hJson); // Clear all keys/values from hJson

bool J3DAPI stdJSON_IsValid(StdJSONHandle hJson);
StdJSONType J3DAPI stdJSON_GetType(StdJSONHandle hJson);

//
// Parsing options
//
StdJSONHandle J3DAPI stdJSON_Load(const char* pFilePath);
bool J3DAPI stdJSON_LoadEntry(const char* pFilePath, StdJSONHandle hJson);

StdJSONHandle J3DAPI stdJSON_LoadFromString(const char* pJsonString);
StdJSONHandle J3DAPI stdJSON_LoadEntryFromString(const char* pJsonString, StdJSONHandle hJson);
char* J3DAPI stdJSON_ToString(StdJSONHandle hJson, bool bPretty); // Caller must free returned string with STDFREE()

//
// Save operations
//

/**
 * Save hJson or it's root to file.
 * If hJson is not a root object, the root object will be saved instead. When this is not desired, clear the parent with stdJSON_ClearParent() first.
 * If hJson has no associated file path and pFilePath is NULL, the save will fail.
 *
 * @param hJson - Handle to JSON object to save
 * @param pFilePath - Optional file path to save to. If NULL, the path associated with hJson (if any) will be used.
 */
bool J3DAPI stdJSON_Save(StdJSONHandle hJson, const char* pFilePath); // Save hJson to file. Note, if hJson is not root the root object will be saved
void J3DAPI stdJSON_SetAutoSave(StdJSONHandle hJson, bool bAutoSave); // Enable/disable auto-save on modification

//
// Parent - child relationships
//
void J3DAPI stdJSON_SetParent(StdJSONHandle hJson, StdJSONHandle hParent);
StdJSONHandle J3DAPI stdJSON_GetParent(StdJSONHandle hJson);
void J3DAPI stdJSON_ClearParent(StdJSONHandle hJson);
StdJSONHandle stdJSON_GetRoot(StdJSONHandle hJson); // Get top-level root

//
// Key enumeration
//
size_t J3DAPI stdJSON_EnumerateKeys(StdJSONHandle hJson, const char* pPath, StdJSONEnumKeyCallback callback, void* pUserData);
size_t J3DAPI stdJSON_GetKeys(StdJSONHandle hJson, const char* pPath, char** ppKeys, size_t maxKeys);

//
// Value type & key checking
//
bool J3DAPI stdJSON_HasKey(StdJSONHandle hJson, const char* pKey); // Check if key exists (supports nested paths with dot notation)
bool J3DAPI stdJSON_Delete(StdJSONHandle hJson, const char* pKey); // Delete key (supports nested paths with dot notation)

//
// Required keys
//
bool J3DAPI stdJSON_SetRequiredKeys(StdJSONHandle hJson, const char** ppKeys, size_t count);
bool J3DAPI stdJSON_ValidateRequired(StdJSONHandle hJson);

//
// Data access functions
//

/**
 * Gets the JSON value associated with a given key from a JSON object.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key whose associated value is to be retrieved.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @return Returns a type of hJson.
 *         If the key does not exist, hJson is NULL, or invalid, STDJSON_TYPE_NULL is returned.
 */
StdJSONType J3DAPI stdJSON_GetValueType(StdJSONHandle hJson, const char* pKey);


/**
 * Sets a boolean value for a specified key in a JSON object.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key under which the boolean value will be stored.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param value - The boolean value to set.
 * @return - True if the operation was successful, otherwise false.
 */
bool J3DAPI stdJSON_SetBool(StdJSONHandle hJson, const char* pKey, bool value);

/**
 * Retrieves a boolean value associated with a specified key from a JSON object.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key whose associated boolean value is to be retrieved.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param defaultValue - The value to return if the key does not exist or is not a boolean.
 * @return The boolean value associated with the specified key, or defaultValue if the key does not exist or is not a boolean.
 */
bool J3DAPI stdJSON_GetBool(StdJSONHandle hJson, const char* pKey, bool defaultValue);


/**
 * Sets an integer value for a specified key in a JSON object.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key under which the integer value will be stored.,
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param value - The integer value to set.
 * @return True if the operation was successful, otherwise false.
 */
bool J3DAPI stdJSON_SetInt(StdJSONHandle hJson, const char* pKey, int value);

/**
 * Retrieves an integer value associated with a specified key from a JSON object.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key whose associated integer value is to be retrieved.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param defaultValue - The value to return if the key does not exist or is not an integer.
 * @return The integer value associated with the specified key, or defaultValue if the key does not exist or is not an integer.
 */
int J3DAPI stdJSON_GetInt(StdJSONHandle hJson, const char* pKey, int defaultValue);


/**
 * Sets a floating-point value for a specified key in a JSON object.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key under which the float value will be stored.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param value - The float value to set.
 * @return True if the operation was successful, otherwise false.
 */
bool J3DAPI stdJSON_SetFloat(StdJSONHandle hJson, const char* pKey, float value);

/**
 * Retrieves a floating-point value associated with a specified key from a JSON object.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key whose associated float value is to be retrieved.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param defaultValue - The value to return if the key does not exist or is not a float.
 * @return The float value associated with the specified key, or defaultValue if the key does not exist or is not a float.
 */
float J3DAPI stdJSON_GetFloat(StdJSONHandle hJson, const char* pKey, float defaultValue);


/**
 * Sets a string value for a specified key in a JSON object.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key under which the string value will be stored.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param pStr - The string value to set.
 * @return True if the operation was successful, otherwise false.
 *
 * Retrieves a string value associated with a specified key from a JSON object.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key whose associated string value is to be retrieved.
 * @param pDstStr - Pointer to the buffer where the retrieved string will be stored.
 * @param size - The size of the buffer pointed to by pDstStr.
 * @param pDefaultValue - The default string to use if the key does not exist or is not a string. Can be NULL.
 * @return True if the string was successfully retrieved and copied into pDstStr; otherwise, false.
 *         If false is returned, pDstStr will contain an empty string if pDefaultValue is NULL, or the default value if provided.
 */
bool J3DAPI stdJSON_SetString(StdJSONHandle hJson, const char* pKey, const char* pStr);

/**
 * Retrieves a string value associated with a specified key from a JSON object.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key whose associated string value is to be retrieved.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param pDstStr - Pointer to the buffer where the retrieved string will be stored.
 * @param size - The size of the buffer pointed to by pDstStr.
 * @param pDefaultValue - The default string to use if the key does not exist or is not a string. Can be NULL.
 * @return True if the string was successfully retrieved and copied into pDstStr; otherwise, false.
 *         If false is returned, pDstStr will contain an empty string if pDefaultValue is NULL, or the default value if provided.
 */
bool J3DAPI stdJSON_GetString(StdJSONHandle hJson, const char* pKey, char* pDstStr, size_t size, const char* pDefaultValue);


/**
 * Retrieves a JSON object associated with the specified key from a JSON object.
 *
 * @WARNING: The returned handle is a child of `hJson` and should be freed with stdJSON_Free() when no longer needed before freeing the parent.
 *           Another option is to clear the parent with stdJSON_ClearParent(). This will decouple it from the parent.
 *
 * @param hJson - Handle to the JSON object from which to retrieve the JSON object.
 * @param pKey - The key whose associated object is to be retrieved.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @return A handle to the JSON object associated with the specified key, or an invalid handle if the key does not exist or is not a JSON object.
 */
StdJSONHandle J3DAPI stdJSON_GetObject(StdJSONHandle hJson, const char* pKey);


/**
 * Retrieves a JSON array associated with the specified key from a JSON object.
 *
 * @WARNING: The returned handle is a child of `hJson` and should be freed with stdJSON_Free() when no longer needed before freeing the parent.
 *           Another option is to clear the parent with stdJSON_ClearParent(). This will decouple it from the parent.
 *
 * @param hJson - Handle to the JSON object from which to retrieve the JSON array.
 * @param pKey - The key whose associated array is to be retrieved.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @return A handle to the JSON array associated with the specified key, or an invalid handle if the key does not exist or is not a JSON array.
 */
StdJSONHandle J3DAPI stdJSON_GetArray(StdJSONHandle hJson, const char* pKey);

//
// Bulk array operations
//

/**
 * Gets the size of a JSON array associated with a given key.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key identifying the JSON array.
 * @return The number of elements in the JSON array, or 0 if the key does not exist or is not an array.
 */
size_t J3DAPI stdJSON_GetArraySize(StdJSONHandle hJson, const char* pKey);

/**
 * Sets an array of boolean values in the JSON object under the specified key.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key under which the boolean array will be stored.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param pValues - Pointer to the array of boolean values to set.
 * @param count - The number of boolean values in the array.
 * @return True if the operation was successful; otherwise, false.
 */
bool J3DAPI stdJSON_SetBoolArray(StdJSONHandle hJson, const char* pKey, const bool* pValues, size_t count);

/**
 * Retrieves an array of boolean values from the JSON object associated with the specified key.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key identifying the JSON array.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param pValues - Pointer to the array where the retrieved boolean values will be stored.
 * @param maxCount - The maximum number of boolean values to retrieve (size of pValues array).
 * @return The number of boolean values actually retrieved and stored in pValues.
 */
size_t J3DAPI stdJSON_GetBoolArray(StdJSONHandle hJson, const char* pKey, bool* pValues, size_t maxCount);


/**
 * Sets an array of integer values in the JSON object under the specified key.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key under which the integer array will be stored.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param pValues - Pointer to the array of integer values to set.
 * @param count - The number of integer values in the array.
 * @return True if the operation was successful, otherwise false.
 */
bool J3DAPI stdJSON_SetIntArray(StdJSONHandle hJson, const char* pKey, const int* pValues, size_t count);

/**
 * Retrieves an array of integer values from the JSON object associated with the specified key.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key identifying the JSON array.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param pValues - Pointer to the array where the retrieved integer values will be stored.
 * @param maxCount - The maximum number of integer values to retrieve (size of pValues array).
 * @return The number of integer values actually retrieved and stored in pValues.
 */
size_t J3DAPI stdJSON_GetIntArray(StdJSONHandle hJson, const char* pKey, int* pValues, size_t maxCount);


/**
 * Sets an array of float values in the JSON object under the specified key.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key under which the float array will be stored.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param pValues - Pointer to the array of float values to set.
 * @param count - The number of float values in the array.
 * @return True if the operation was successful, otherwise false.
 */
bool J3DAPI stdJSON_SetFloatArray(StdJSONHandle hJson, const char* pKey, const float* pValues, size_t count);

/**
 * Retrieves an array of float values from the JSON object associated with the specified key.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key identifying the JSON array.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param pValues - Pointer to the array where the retrieved float values will be stored.
 * @param maxCount - The maximum number of float values to retrieve (size of pValues array).
 * @return The number of float values actually retrieved and stored in pValues.
 */
size_t J3DAPI stdJSON_GetFloatArray(StdJSONHandle hJson, const char* pKey, float* pValues, size_t maxCount);

/**
 * Sets an array of string values in the JSON object under the specified key.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key under which the string array will be stored.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param ppValues - Pointer to the array of string values to set.
 * @param count - The number of string values in the array.
 * @return True if the operation was successful, otherwise false.
 */
bool J3DAPI stdJSON_SetStringArray(StdJSONHandle hJson, const char* pKey, const char** ppValues, size_t count);

/**
 * Retrieves an array of string values from the JSON object associated with the specified key.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key identifying the JSON array.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param ppValues - Pointer to the array where the retrieved string values will be stored.
 * @param maxCount - The maximum number of string values to retrieve (size of ppValues array).
 * @param maxStrLen - The maximum length of each string in ppValues (including null terminator).
 * @return The number of string values actually retrieved and stored in ppValues.
 */
size_t J3DAPI stdJSON_GetStringArray(StdJSONHandle hJson, const char* pKey, char** ppValues, size_t maxCount, size_t maxStrLen);

//
// Single element array operations
//

/**
 * Sets a boolean value in a JSON array at `index`.
 * @param hJson Handle to the JSON object.
 * @param pKey - The key identifying the JSON array.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param index - The index of the element within the array to set.
 * @param value - The boolean value to assign to the array element.
 * @return True if the operation was successful; otherwise, false.
 */
bool J3DAPI stdJSON_SetBoolArrayElement(StdJSONHandle hJson, const char* pKey, size_t index, bool value);

/**
 * Retrieves a boolean value from a JSON array at `index`.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key identifying the JSON array.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param index - The zero-based index of the element within the array.
 * @param defaultValue - The value to return if the key or index is not found, or if the value is not a boolean.
 * @return The boolean value at the specified array index, or defaultValue if not found or not a boolean.
 */
bool J3DAPI stdJSON_GetBoolArrayElement(StdJSONHandle hJson, const char* pKey, size_t index, bool defaultValue);


/**
 * Sets an integer value in a JSON array at `index`.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key identifying the array within the JSON object.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param index - The index of the element in the array to set.
 * @param value - The integer value to assign to the specified array element.
 * @return Returns true if the operation was successful; otherwise, returns false.
 */
bool J3DAPI stdJSON_SetIntArrayElement(StdJSONHandle hJson, const char* pKey, size_t index, int value);

/**
 * Retrieves an integer value from a JSON array at `index`.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key associated with the array in the JSON object.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param index - The zero-based index of the element to retrieve from the array.
 * @param defaultValue - The value to return if the key or index is not found.
 * @return The integer value at the specified index in the array, or defaultValue if not found.
 */
int J3DAPI stdJSON_GetIntArrayElement(StdJSONHandle hJson, const char* pKey, size_t index, int defaultValue);


/**
 * Sets a float value in a JSON array at `index`.
 * @param hJson - Handle to the JSON object.
 * @param pKey - Key identifying the float array in the JSON object.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param index - Index of the element in the float array to set.
 * @param value - The float value to assign to the specified array element.
 * @return True if the operation was successful; otherwise, false.
 */
bool J3DAPI stdJSON_SetFloatArrayElement(StdJSONHandle hJson, const char* pKey, size_t index, float value);

/**
 * Retrieves a float value from a JSON array at `index`.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key identifying the JSON array.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param index - The index of the element within the array.
 * @param defaultValue - The value to return if the key or index is not found.
 * @return The float value at the specified index in the array, or defaultValue if not found.
 */
float J3DAPI stdJSON_GetFloatArrayElement(StdJSONHandle hJson, const char* pKey, size_t index, float defaultValue);


/**
 * Sets the value of a string element at a specified index in a JSON array associated with a given key.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key identifying the JSON array.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param index - The index of the element within the array to set.
 * @param pValue - The string value to assign to the array element.
 * @return True if the operation was successful; otherwise, false.
 */
bool J3DAPI stdJSON_SetStringArrayElement(StdJSONHandle hJson, const char* pKey, size_t index, const char* pValue);

/**
 * Retrieves a string element from a JSON array associated with a specified key.
 * @param hJson - Handle to the JSON object.
 * @param pKey - The key identifying the JSON array.
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param index - The zero-based index of the string element to retrieve.
 * @param pDstStr - Pointer to the buffer where the retrieved string will be stored.
 * @param size - The size of the destination buffer in bytes.
 * @param pDefaultValue - The default string to use if the element is not found.
 * @return true if the string element was successfully retrieved; false otherwise.
 */
bool J3DAPI stdJSON_GetStringArrayElement(StdJSONHandle hJson, const char* pKey, size_t index, char* pDstStr, size_t size, const char* pDefaultValue);


/**
 * Sets a JSON object in a JSON array at `index`.
 * @param hJson - Handle to JSON object containing the array
 * @param pKey - Key of the array
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param index - Index of the element to set
 * @param value - Handle to the JSON object to set at the specified index
 * @return true if successful, false on error (e.g. index out of bounds or not an array)
 */
bool J3DAPI stdJSON_SetObjectArrayElement(StdJSONHandle hJson, const char* pKey, size_t index, StdJSONHandle value);

/**
 * Retrieves a JSON object from a JSON array at `index`.
 *
 * @WARNING: The returned handle is a child of `hJson` and should be freed with stdJSON_Free() when no longer needed before freeing the parent.
 *           Another option is to clear the parent with stdJSON_ClearParent().
 *
 * @param hJson - Handle to JSON object containing the array
 * @param pKey - Key of the array
 *               Supports nested paths using dot notation (e.g., "parent.child.key").
 * @param index - Index of the element to retrieve
 * @return Handle to the JSON object at the specified index, or NULL if not found or not an object
 */
StdJSONHandle J3DAPI stdJSON_GetObjectArrayElement(StdJSONHandle hJson, const char* pKey, size_t index);

//
// Array object setters / getters
//

/**
 * Returns the number of elements in a JSON array.
 * @param hArray - Handle to the JSON array whose size is to be retrieved.
 * @return The number of elements in the specified JSON array.
 */
size_t J3DAPI stdJSON_ArrayGetSize(StdJSONHandle hArray);

/**
 * Clears all elements from a JSON array.
 * @param hArray - Handle to the JSON array to be cleared.
 * @return Returns true if the array was successfully cleared; otherwise, returns false.
 */
bool J3DAPI stdJSON_ArrayClear(StdJSONHandle hArray);

/**
 * Retrieves the type of the element at the specified index in a JSON array.
 * @param hArray - Handle to the JSON array.
 * @param index - Zero-based index of the element whose type is to be retrieved.
 * @return The type of the element at the given index, represented as a StdJSONType value.
 */
StdJSONType J3DAPI stdJSON_ArrayGetElementType(StdJSONHandle hArray, size_t index);

/**
 * Removes an element from a JSON array at the specified index.
 * @param hArray - Handle to the JSON array from which the element will be removed.
 * @param index - The zero-based index of the element to remove.
 * @return True if the element was successfully removed otherwise false.
 */
bool J3DAPI stdJSON_ArrayRemoveElement(StdJSONHandle hArray, size_t index);


/**
 * Appends a boolean to a JSON array.
 * @param hArray - Handle to the JSON array.
 * @param value - The boolean value to append to the array.
 * @return Returns true if the boolean was successfully appended, otherwise false.
 */
bool J3DAPI stdJSON_ArrayAppendBool(StdJSONHandle hArray, bool value);

/**
 * Sets a boolean value at the specified index in a JSON array.
 * @param hArray - Handle to the JSON array.
 * @param index - The position in the array where the boolean will be set.
 * @param value - The boolean value to set at the specified index.
 * @return Returns true if the boolean was successfully set, otherwise false.
 */
bool J3DAPI stdJSON_ArraySetBool(StdJSONHandle hArray, size_t index, bool value);

/**
 * Retrieves a boolean value from a JSON array at the specified index.
 * @param hArray - Handle to the JSON array.
 * @param index - Zero-based index of the boolean value to retrieve.
 * @param defaultValue - Default boolean value to return if the index is out of bounds or the value is not a boolean.
 * @return The boolean value at the specified index, or defaultValue if the index is invalid or the value is not a boolean.
 */
bool J3DAPI stdJSON_ArrayGetBool(StdJSONHandle hArray, size_t index, bool defaultValue);


/**
 * Appends an integer to a JSON array.
 * @param hArray - Handle to the JSON array.
 * @param value - The integer value to append to the array.
 * @return Returns true if the integer was successfully appended, otherwise false.
 */
bool J3DAPI stdJSON_ArrayAppendInt(StdJSONHandle hArray, int value);

/**
 * Sets an integer at the specified index in a JSON array.
 * @param hArray - Handle to the JSON array.
 * @param index - The position in the array where the integer will be set.
 * @param value - The integer value to set at the specified index.
 * @return Returns true if the integer was successfully set, otherwise false.
 */
bool J3DAPI stdJSON_ArraySetInt(StdJSONHandle hArray, size_t index, int value);

/**
 * Retrieves an integer from a JSON array at the specified index.
 * @param hArray - Handle to the JSON array.
 * @param index - Zero-based index of the integer to retrieve.
 * @param defaultValue - Default integer value to return if the index is out of bounds or the value is not an integer.
 * @return The integer value at the specified index, or defaultValue if the index is invalid or the value is not an integer.
 */
int J3DAPI stdJSON_ArrayGetInt(StdJSONHandle hArray, size_t index, int defaultValue);

/**
 * Appends a floating-point number to a JSON array.
 * @param hArray - Handle to the JSON array.
 * @param value - The float value to append to the array.
 * @return Returns true if the float was successfully appended, otherwise false.
 */
bool J3DAPI stdJSON_ArrayAppendFloat(StdJSONHandle hArray, float value);

/**
 * Sets a floating-point number at the specified index in a JSON array.
 * @param hArray - Handle to the JSON array.
 * @param index - The position in the array where the float will be set.
 * @param value - The float value to set at the specified index.
 * @return Returns true if the float was successfully set, otherwise false.
 */
bool J3DAPI stdJSON_ArraySetFloat(StdJSONHandle hArray, size_t index, float value);

/**
 * Retrieves a floating-point number from a JSON array at the specified index.
 * @param hArray - Handle to the JSON array.
 * @param index - Zero-based index of the float to retrieve.
 * @param defaultValue - Default float value to return if the index is out of bounds or the value is not a float.
 * @return The float value at the specified index, or defaultValue if the index is invalid or the value is not a float.
 */
float J3DAPI stdJSON_ArrayGetFloat(StdJSONHandle hArray, size_t index, float defaultValue);


/**
 * Appends a string to a JSON array.
 * @param hArray - Handle to the JSON array.
 * @param pValue - The string value to append to the array.
 * @return Returns true if the string was successfully appended, otherwise false.
 */
bool J3DAPI stdJSON_ArrayAppendString(StdJSONHandle hArray, const char* pValue);

/**
 * Sets a string at the specified index in a JSON array.
 * @param hArray - Handle to the JSON array.
 * @param index - The position in the array where the string will be set.
 * @param pValue - The string value to set at the specified index.
 * @return Returns true if the string was successfully set, otherwise false.
 */
bool J3DAPI stdJSON_ArraySetString(StdJSONHandle hArray, size_t index, const char* pValue);

/**
 * Retrieves a string from a JSON array at the specified index.
 * @param hArray - Handle to the JSON array.
 * @param index - Zero-based index of the string to retrieve.
 * @param pDstStr - Pointer to the buffer where the retrieved string will be copied.
 * @param size - Size of the destination buffer.
 * @param pDefaultValue - Default string to use if the index is out of bounds or the value is not a string.
 * @return Returns true if the string was successfully retrieved and copied to pDstStr, otherwise false.
 */
bool J3DAPI stdJSON_ArrayGetString(StdJSONHandle hArray, size_t index, char* pDstStr, size_t size, const char* pDefaultValue);


/**
 * Appends a JSON object to a JSON array.
 * @param hArray - Handle to the JSON array.
 * @param hObjectToAppend - Handle to the JSON object to append to the array.
 * @return Returns true if the object was successfully appended, otherwise false.
 */
bool J3DAPI stdJSON_ArrayAppendObject(StdJSONHandle hArray, StdJSONHandle hObjectToAppend);

/**
 * Sets an object at the specified index in a JSON array.
 * @param hArray - Handle to the JSON array.
 * @param index - The position in the array where the object will be set.
 * @param hObjectToSet - Handle to the JSON object to set at the specified index.
 * @return Returns true if the object was successfully set, otherwise false.
 */
bool J3DAPI stdJSON_ArraySetObject(StdJSONHandle hArray, size_t index, StdJSONHandle hObjectToSet);

/**
 * Retrieves an object from a JSON array at the specified index.
 *
 * @WARNING: The returned handle is a child of `hJson` and should be freed with stdJSON_Free() when no longer needed before freeing the parent.
 *           Another option is to clear the parent with stdJSON_ClearParent(). This will decouple it from the parent.
 *
 * @param hArray - Handle to the JSON array.
 * @param index - Zero-based index of the object to retrieve.
 * @return Handle to the JSON object at the given index, or a null/invalid handle if the index is out of bounds or the element is not an object.
 */
StdJSONHandle J3DAPI stdJSON_ArrayGetObject(StdJSONHandle hArray, size_t index);


/**
 * Appends all elements from one JSON array to another.
 * @param hArray - Handle to the destination JSON array.
 * @param hArrayToAppend - Handle to the source JSON array whose elements will be appended.
 * @return Returns true if the elements were successfully appended, otherwise false.
 */
bool J3DAPI stdJSON_ArrayAppendArray(StdJSONHandle hArray, StdJSONHandle hArrayToAppend);

/**
 * Sets an array element at the specified index in a JSON array to another JSON array.
 * @param hArray - Handle to the target JSON array.
 * @param index - Zero-based index of the element to set.
 * @param hArrayToSet - Handle to the JSON array to assign to the specified index.
 * @return Returns true if the operation succeeds, otherwise false.
 */
bool J3DAPI stdJSON_ArraySetArray(StdJSONHandle hArray, size_t index, StdJSONHandle hArrayToSet);

/**
 * Retrieves a JSON array element as an array from the specified index.
 *
 * @WARNING: The returned handle is a child of `hJson` and should be freed with stdJSON_Free() when no longer needed before freeing the parent.
 *           Another option is to clear the parent with stdJSON_ClearParent(). This will decouple it from the parent.
 *
 * @param hArray - Handle to the JSON array.
 * @param index - Zero-based index of the element to retrieve.
 * @return A handle to the JSON array at the specified index, or an invalid handle if the element is not an array.
 */
StdJSONHandle J3DAPI stdJSON_ArrayGetArray(StdJSONHandle hArray, size_t index);

J3D_EXTERN_C_END

#endif // STDJSON_H