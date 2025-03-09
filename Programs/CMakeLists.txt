cmake_minimum_required(VERSION 3.12)
project(Programs)

add_subdirectory( byacc )
add_subdirectory( flex  )

# Group all lib modules under "Libs" in Visual Studio
set_target_properties(yacc flex PROPERTIES FOLDER "Programs")
