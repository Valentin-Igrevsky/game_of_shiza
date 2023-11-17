cmake_minimum_required(VERSION 3.23)
project(GTT)

set(CMAKE_CXX_STANDARD 23)

set(life_src_files life_backend/src/Life.cpp life_backend/include/Life.h)

add_library(game_of_life ${life_src_files})
