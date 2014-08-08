cmake_minimum_required(VERSION 2.8)
project(UVa-Online-Judge)

if(${CMAKE_C_COMPILER_ID} STREQUAL "GNU" OR
    ${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
        set(CMAKE_C_FLAGS "-lm -lcrypt -O2 -pipe -ansi -DONLINE_JUDGE ${CMAKE_C_FLAGS}")
endif()

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR
    ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "-lm -lcrypt -O2 -pipe -DONLINE_JUDGE ${CMAKE_CXX_FLAGS}")
endif()

configure_file(
    ${PROJECT_SOURCE_DIR}/test.in
    ${PROJECT_BINARY_DIR}/test
    @ONLY
)
execute_process(COMMAND chmod +x ${PROJECT_BINARY_DIR}/test)

set(TEST_DIR ${PROJECT_BINARY_DIR}/bin)
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${TEST_DIR})

enable_testing()
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

set(SKIP_CASES
    czchen-104 # multiple answers
    zsshen-104 # multiple answers
    zsshen-526
)

file(GLOB all_src ${PROJECT_SOURCE_DIR}/src/*)
foreach(src ${all_src})
    get_filename_component(exec_name ${src} NAME_WE)
    add_executable(${exec_name} ${src})
    add_dependencies(check ${exec_name})
    set_target_properties(${exec_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${TEST_DIR}
    )

    list(FIND SKIP_CASES "${exec_name}" idx)
    if (${idx} EQUAL -1)
        add_test(test-${exec_name} ${PROJECT_BINARY_DIR}/test ${exec_name})
    endif()
endforeach()
