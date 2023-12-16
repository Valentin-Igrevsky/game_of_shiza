cmake_minimum_required(VERSION 3.23)
project(GTT)

set(CMAKE_CXX_STANDARD 23)

include_directories(life_backend/include)
include_directories(life_frontend/include)

add_subdirectory("${PROJECT_SOURCE_DIR}/life_backend")
add_subdirectory("${PROJECT_SOURCE_DIR}/life_frontend")
add_subdirectory("${PROJECT_SOURCE_DIR}/gtestset")