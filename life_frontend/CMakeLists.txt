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

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_executable(life_frontend WIN32 ${SOURCES} ${HEADERS})
    target_include_directories(life_frontend PUBLIC include)
    target_include_directories(life_frontend PRIVATE src)
#    set(path ${CMAKE_SOURCE_DIR}/cmake-build-debug/life_backend/life_backend.dll)
#    add_library(life_backend SHARED ${path})
    set_target_properties(life_backend PROPERTIES LINKER_LANGUAGE CXX)
#    target_link_libraries(life_frontend PUBLIC life_backend)
    set_target_properties(life_frontend PROPERTIES OUTPUT_NAME "life_frontend")
    set(Library_path $<TARGET_FILE:life_frontend>)
    set(out_path $<TARGET_FILE_DIR:life_frontend>)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-delete-incomplete")
    add_library(life_frontend SHARED ${SOURCES} ${HEADERS})
    target_include_directories(life_frontend PUBLIC include)
    set_target_properties(life_frontend PROPERTIES OUTPUT_NAME "life_frontend")
    set(Library_path $<TARGET_FILE:life_frontend>)
    set(out_path $<TARGET_FILE_DIR:life_frontend>)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-delete-incomplete")
    add_library(life_frontend SHARED ${SOURCES} ${HEADERS})
    target_include_directories(life_frontend PUBLIC include)
    set_target_properties(life_frontend PROPERTIES OUTPUT_NAME "life_frontend")
    set(Library_path $<TARGET_FILE:life_frontend>)
    set(out_path $<TARGET_FILE_DIR:life_frontend>)
endif ()

#set(SDL2_LIBRARY ${CMAKE_BINARY_DIR}/SDL2.dll)


#target_link_libraries(life_frontend PRIVATE ${SDL2_LIBRARY})


add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${Library_path} ${CMAKE_BINARY_DIR}/
)
