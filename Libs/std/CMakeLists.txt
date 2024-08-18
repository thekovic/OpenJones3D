project(std C)

file(GLOB_RECURSE SOURCES *.c)
file(GLOB_RECURSE HEADERS *.h)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(${PROJECT_NAME} PUBLIC j3dcore)
target_link_libraries(${PROJECT_NAME} PUBLIC
    Winmm # timeGetTime
    DirectX61c::ddraw
    DirectX61c::dxguid
    DirectX61c::dinput
    DirectX61c::dplayx
)

target_link_options(${PROJECT_NAME} INTERFACE "/SAFESEH:NO") # due to DirectX 6.1 libs

# Organize source files in Visual Studio
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})
