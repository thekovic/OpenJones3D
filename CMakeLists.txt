cmake_minimum_required(VERSION 3.15)

project(OpenJones3D VERSION 0.3.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20) # C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(JONES3D_BUILD_PROGRAMS "Build programs" ON)
option(JONES3D_QOL_IMPROVEMENTS "Enable quality-of-life improvements" ON)

if(JONES3D_QOL_IMPROVEMENTS)
    add_compile_definitions(J3D_QOL_IMPROVEMENTS=1)
endif()

# Configure the version header file
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/LIBS/j3dcore/j3d.h.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/LIBS/j3dcore/j3d.h"
)

# Set global property for MSVC runtime library (CMake 3.15+)
set(CMAKE_MSVC_RUNTIME_LIBRARY "$<$<CONFIG:Release>:MultiThreaded>$<$<CONFIG:MinSizeRel>:MultiThreaded>")

if (MSVC)
    add_compile_definitions("__FILE_NAME__=\"%(Filename)%(Extension)\"")
    add_compile_options(
        /utf-8
        /Zc:__STDC__
        /Zc:__cplusplus
        /diagnostics:caret
        /sdl
        #"$<$<CONFIG:DEBUG>:/Gm>" # minimal rebuild TODO: uncomment
        /W4 # warning level 4
        /Zc:preprocessor # This option enables a token-based preprocessor that conforms to C99 and C++11 and later standards.
        "$<$<NOT:$<CXX_COMPILER_ID:Clang>>:/MP>" # TODO: remove when /Gm is uncommented
        #$<$<AND:$<NOT:$<CXX_COMPILER_ID:Clang>>,$<NOT:$<CONFIG:DEBUG>>>:/MP> TODO: uncomment when /Gm is uncommented
        "$<$<CONFIG:DEBUG>:/ZI>"
    )
    add_link_options("/Brepro")
else()
    message(FATAL_ERROR "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

# Add Libs subdirectory
add_subdirectory(Libs)

# Add main project Jones3D
add_subdirectory(Jones3D)

if (JONES3D_BUILD_PROGRAMS)
    add_subdirectory(Programs)
endif()
