cmake_minimum_required(VERSION 3.22)
project(life_frontend)

set(CMAKE_CXX_STANDARD 23)
set(SOURCES
        ../life_backend/src/life_backend.cpp
        src/life_frontend.cpp
        src/main.cpp
        )

set(HEADERS
        ../life_backend/include/life_backend.h
        include/life_frontend.h
        )

set(DYNAMIC_LIBS_PATH ${CMAKE_SOURCE_DIR})

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "ARM")
    message("Target architecture: ARM")
    set(ARCH "x64")
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "ARM64")
    message("Target architecture: ARM64")
    set(ARCH "x64")
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86")
    message("Target architecture: x86")
    set(ARCH "x86")
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64")
    message("Target architecture: AMD64")
    set(ARCH "x64")
elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86-64")
    message("Target architecture: x86-64")
    set(ARCH "x64"
else()
    message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
cmake_path(APPEND SDL_INCLUDE_PATH "${CMAKE_SOURCE_DIR}" "libraries" "include" "SDL2")
#cmake_path(APPEND SDL2MIXER_INCLUDE_PATH "${CMAKE_SOURCE_DIR}" "libraries" "include" "SDL2_mixer")

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CURRENT_OS "Linux")
    set(CURRENT_EXT "so")
    cmake_path(APPEND SDL_PATH_FULL "${CMAKE_SOURCE_DIR}" "libraries" "${ARCH}" "${CURRENT_OS}" "SDL2.${CURRENT_EXT}")
    cmake_path(APPEND SDL2MIXER_PATH_FULL "${CMAKE_SOURCE_DIR}" "libraries" "${ARCH}" "${CURRENT_OS}" "SDL2_mixer.${CURRENT_EXT}")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${SDL_PATH_FULL} ${MY_VARIABLE}
            COMMAND ${CMAKE_COMMAND} -E copy ${SDL2MIXER_PATH_FULL} ${SDL2MIXER}
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES
            LINK_FLAGS "-Wl,--export-dynamic"
    )

elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CURRENT_OS "Windows")
    set(CURRENT_EXT "dll")
    set(MY_VARIABLE "SDL2.${CURRENT_EXT}")
    set(SDL2MIXER "SDL2_mixer.${CURRENT_EXT}")
    cmake_path(APPEND SDL_PATH_FULL "${CMAKE_SOURCE_DIR}" "libraries" "${ARCH}" "${CURRENT_OS}" "SDL2.${CURRENT_EXT}")
    cmake_path(APPEND SDL2MIXER_PATH_FULL "${CMAKE_SOURCE_DIR}" "libraries" "${ARCH}" "${CURRENT_OS}" "SDL2_mixer.${CURRENT_EXT}")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${SDL_PATH_FULL} ${MY_VARIABLE}
            COMMAND ${CMAKE_COMMAND} -E copy ${SDL2MIXER_PATH_FULL} ${SDL2MIXER}
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES
            WIN32_EXECUTABLE TRUE
    )
else()
    message(FATAL_ERROR "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
endif ()


message("SDL full path directory: ${SDL_PATH_FULL}")
message("SDL2_mixer full path directory: ${SDL2MIXER_PATH_FULL}")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/variables.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/variables.h)
configure_file(src/lenya.bmp ${CMAKE_CURRENT_BINARY_DIR}/lenya.bmp COPYONLY)
configure_file(src/Freddy.wav ${CMAKE_CURRENT_BINARY_DIR}/Freddy.wav COPYONLY)
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL_INCLUDE_PATH})
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2MIXER_INCLUDE_PATH})