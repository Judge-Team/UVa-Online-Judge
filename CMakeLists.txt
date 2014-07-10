cmake_minimum_required(VERSION 2.8)
project(UVa-Online-Judge)

if(${CMAKE_C_COMPILER_ID} STREQUAL "GNU" OR
    ${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
        set(CMAKE_C_FLAGS "-g -O2 -Wall -fPIC -std=c99 ${CMAKE_C_FLAGS}")
endif()

file(GLOB all_src ${PROJECT_SOURCE_DIR}/src/*)
foreach(src ${all_src})
    get_filename_component(exec_name ${src} NAME_WE)
    add_executable(${exec_name} ${src})
endforeach()
