cmake_minimum_required(VERSION 2.8)
project(UVa-Online-Judge)

if(${CMAKE_C_COMPILER_ID} STREQUAL "GNU" OR
    ${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
        set(CMAKE_C_FLAGS "-lm -lcrypt -O2 -pipe -ansi -DONLINE_JUDGE ${CMAKE_C_FLAGS}")
endif()

enable_testing()

file(GLOB all_src ${PROJECT_SOURCE_DIR}/src/*)
foreach(src ${all_src})
    get_filename_component(exec_name ${src} NAME_WE)
    add_executable(${exec_name} ${src})

    add_test(test-${exec_name} ${PROJECT_SOURCE_DIR}/test ${exec_name} ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})
endforeach()
