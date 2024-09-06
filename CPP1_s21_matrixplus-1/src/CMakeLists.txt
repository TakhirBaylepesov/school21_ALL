cmake_minimum_required(VERSION 3.10)

project(S21Matrix VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
    -Wall
    -Wextra
    -Werror
    -pedantic
    -O2
    -fprofile-arcs
    -ftest-coverage
)

set(SOURCE_DIR src/main)
set(TEST_DIR src/tests)
set(INCLUDE_DIR src/headers)

include_directories(${INCLUDE_DIR})

file(GLOB SRC_FILES "${SOURCE_DIR}/*.cpp")
file(GLOB TEST_SRC_FILES "${TEST_DIR}/*.cpp")

add_library(s21_matrix_oop STATIC ${SRC_FILES})

add_executable(s21_matrix ${TEST_SRC_FILES})

target_link_libraries(s21_matrix PRIVATE s21_matrix_oop gtest gtest_main pthread)

enable_testing()

add_executable(run_tests ${TEST_SRC_FILES})

target_link_libraries(run_tests PRIVATE s21_matrix_oop gtest gtest_main pthread)

add_test(NAME S21MatrixTests COMMAND run_tests)

find_program(LCOV_EXECUTABLE lcov)
find_program(GCOV_EXECUTABLE gcov)
find_program(GENHTML_EXECUTABLE genhtml)

if(LCOV_EXECUTABLE AND GCOV_EXECUTABLE AND GENHTML_EXECUTABLE)
    add_custom_target(coverage
        COMMAND ${LCOV_EXECUTABLE} --capture --directory . --output-file Coverage_Report.info --rc branch_coverage=1
        COMMAND ${GENHTML_EXECUTABLE} Coverage_Report.info --output-directory report --branch-coverage
        COMMAND rm -f *.gcda *.gcno
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating coverage report..."
    )
endif()
