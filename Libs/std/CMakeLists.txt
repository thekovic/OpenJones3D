project(std C)

file(GLOB_RECURSE SOURCES *.c)
file(GLOB_RECURSE HEADERS *.h)

# Remove DirectX 6/9 specific files based on the build option
if(J3D_DIRECTX6)
  # Remove DX9 files.
    list(FILTER SOURCES EXCLUDE REGEX ".*DX9\\.c$")
elseif(J3D_DIRECTX9)
    # Remove DX6 files.
    list(FILTER SOURCES EXCLUDE REGEX ".*DX6\\.c$")
endif()

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(${PROJECT_NAME} PUBLIC 
    j3dcore
    Winmm # timeGetTime
)

if (J3D_DIRECTX6)
    target_link_libraries(${PROJECT_NAME} PUBLIC
        DirectX61c::ddraw
        DirectX61c::dxguid
        DirectX61c::dinput
        DirectX61c::dplayx
    )
else() # J3D_DIRECTX9
    target_link_libraries(${PROJECT_NAME} PUBLIC
        d3d9
        dxguid
        DirectX61c::dinput
        DirectX61c::dplayx
    )
endif()

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC
        dbghelp # for minidump & stack trace
    )
endif()

target_link_options(${PROJECT_NAME} INTERFACE "/SAFESEH:NO") # due to DirectX 6.1 libs

# Organize source files in Visual Studio
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})
