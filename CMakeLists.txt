cmake_minimum_required(VERSION 3.23)
project(GTT)

set(CMAKE_CXX_STANDARD 23)

set(SDL2_INCLUDE_DIR life_frontend/SDL2-2.28.5/include)
set(SDL2_LIBRARIES life_frontend/SDL2-2.28.5/lib/x64/SDL2.lib SDL2-2.28.5/lib/x64/SDL2main.lib)
set(SDL2_LIBRARY ${CMAKE_BINARY_DIR}/SDL2.dll)

IF(MINGW)
    SET(MINGW32_LIBRARY mingw32 "-mwindows" CACHE STRING "mwindows for MinGW")
ENDIF(MINGW)
IF(NOT APPLE)
    FIND_PACKAGE(Threads)
ENDIF(NOT APPLE)

IF(NOT APPLE)
    SET(SDL2_LIBRARY_TEMP ${SDL2_LIBRARY_TEMP} ${CMAKE_THREAD_LIBS_INIT})
ENDIF(NOT APPLE)

# For MinGW library
IF(MINGW)
    SET(SDL2_LIBRARY_TEMP ${MINGW32_LIBRARY} ${SDL2_LIBRARY_TEMP})
ENDIF(MINGW)
IF(MINGW)
    SET(SDL2_LIBRARY_TEMP mingw32 SDL2 -mwindows)
ENDIF(MINGW)

#add_executable(GTT life_frontend/src/main.cpp)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(life_backend/include)
include_directories(life_frontend/include)

#target_link_libraries(game_of_life)

add_subdirectory(life_backend)
add_subdirectory(life_frontend)
add_subdirectory(gtestset)

#add_subdirectory("${PROJECT_SOURCE_DIR}/life_frontend")
#add_subdirectory("${PROJECT_SOURCE_DIR}/life_backend")
#add_subdirectory("${PROJECT_SOURCE_DIR}/gtestset")

add_executable(GTT WIN32 life_frontend/src/main.cpp)
#target_link_libraries(GTT life_frontend life_backend)