cmake_minimum_required(VERSION 3.16)
project(Lab4_Templates)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# --- Основное приложение ---
add_executable(Lab4 src/main.cpp)

# --- GoogleTest ---
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(Lab4_tests tests/test_figures.cpp)
target_link_libraries(Lab4_tests ${GTEST_LIBRARIES} pthread)

add_test(NAME Lab4Tests COMMAND Lab4_tests)
