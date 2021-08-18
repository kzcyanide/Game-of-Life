cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

project (GameofLife)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# check if boost was found
if(SDL2_FOUND)
    message ("SDL2 found")
else()
    message (FATAL_ERROR "Cannot find SDL")
endif()

add_executable(GameofLife src/main.cpp src/canvas.cpp)

target_link_libraries( GameofLife ${SDL2_LIBRARIES})


target_include_directories(GameofLife
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)


