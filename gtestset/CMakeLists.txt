cmake_minimum_required(VERSION 3.23)
project(GGT_TESTS)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(lib/googletest-main)
include_directories(lib/googletest-main/googletest/include)
include_directories(lib/googletest-main/googlemock/include)
include_directories(../life_backend/include)
include_directories(../life_frontend/include)

set(SOURCE_FILES tests/life_backend_tests.cpp
        ../life_backend/src/life_backend.cpp tests/life_frontend_tests.cpp)
add_executable(gtestset ${SOURCE_FILES} tests/life_frontend_tests.cpp)
target_link_libraries(gtestset gtest gtest_main)