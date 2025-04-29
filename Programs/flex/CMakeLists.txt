cmake_minimum_required(VERSION 3.12)
project(flex C)

set(FLEX_HEADERS
    flexdef.h
    ${CMAKE_CURRENT_BINARY_DIR}/parse.h
)

set(FLEX_SOURCES
    ccl.c
    dfa.c
    ecs.c
    gen.c
    main.c
    misc.c
    nfa.c
    ${CMAKE_CURRENT_BINARY_DIR}/parse.c
    ${CMAKE_CURRENT_BINARY_DIR}/scan.c
    sym.c
    tblcmp.c
    yylex.c
)

add_executable(${PROJECT_NAME} ${FLEX_SOURCES} ${FLEX_HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_BINARY_DIR}
)

target_include_directories(flex PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}         # For flexdef.h
    ${CMAKE_CURRENT_BINARY_DIR}         # For generated parse.h
)

# Add yacc project as dependency to ensure to be built first 
add_dependencies(${PROJECT_NAME} yacc)

if(MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -D_CRT_SECURE_NO_WARNINGS)
    target_compile_options(${PROJECT_NAME} PRIVATE "/sdl-")
endif()

# Custom command to generate parse.c and parse.h from parse.y.
# yacc generates y.tab.c and y.tab.h in the source directory,
# with custom command we rename them to parse.c and parse.h.
add_custom_command(
    DEPENDS  yacc
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/parse.c ${CMAKE_CURRENT_BINARY_DIR}/parse.h
    COMMAND $<TARGET_FILE:yacc> -d ${CMAKE_CURRENT_SOURCE_DIR}/parse.y
    COMMAND ${CMAKE_COMMAND} -E rename ${CMAKE_CURRENT_BINARY_DIR}/y.tab.c ${CMAKE_CURRENT_BINARY_DIR}/parse.c
    COMMAND ${CMAKE_COMMAND} -E rename ${CMAKE_CURRENT_BINARY_DIR}/y.tab.h ${CMAKE_CURRENT_BINARY_DIR}/parse.h
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/parse.y
    COMMENT "Generating parse.c and parse.h from parse.y"
)

# Custom command to copy initscan.c to scan.c in the binary directory.
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/scan.c
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/initscan.c ${CMAKE_CURRENT_BINARY_DIR}/scan.c
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/initscan.c
    COMMENT "Copying initscan.c to scan.c"
)
