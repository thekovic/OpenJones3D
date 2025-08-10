cmake_minimum_required(VERSION 3.12)

if (J3D_DIRECTX6 OR J3D_DIRECTX9)
    set(EXTERNAL_MODULES
        DirectX61c
    )
else()
    set(EXTERNAL_MODULES
        ""
    )
endif()

# Then add other modules
foreach(MODULE ${EXTERNAL_MODULES})
    add_subdirectory(${MODULE})
endforeach()

