cmake_minimum_required(VERSION 3.12)
project(yacc)

project(yacc)

set(HEADERS
    defs.h
)

set(SOURCES
    closure.c
    error.c
    lalr.c
    lr0.c
    main.c
    mkpar.c
    output.c
    reader.c
    skeleton.c
    symtab.c
    verbose.c
    warshall.c
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_BINARY_DIR}
)

if(MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -D_CRT_SECURE_NO_WARNINGS)
    target_compile_options(${PROJECT_NAME} PRIVATE "/sdl-")
endif()

# Organize source files in Visual Studio
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})
