cmake_minimum_required(VERSION 3.12)
set(EXTERNAL_MODULES
    DirectX61c
)

# Then add other modules
foreach(MODULE ${EXTERNAL_MODULES})
    add_subdirectory(${MODULE})
endforeach()

