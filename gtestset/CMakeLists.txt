cmake_minimum_required(VERSION 3.23)

project(GTT)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(lib/googletest-main)
include_directories(lib/googletest-main/googletest/include)
include_directories(lib/googletest-main/googlemock/include)

set(SOURCE_FILES main.cpp tests/life_backend_tests.cpp)
add_executable(gtestset ${SOURCE_FILES})
target_link_libraries(gtestset gtest gtest_main game_of_life)
