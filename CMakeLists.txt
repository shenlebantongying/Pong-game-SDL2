cmake_minimum_required(VERSION 3.19)
project(Pong_game_SDL)

set(CMAKE_CXX_STANDARD 20)

# resources
FILE(COPY hello_world.bmp DESTINATION "${CMAKE_BINARY_DIR}")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Pong_game_SDL main.cpp)

target_link_libraries(Pong_game_SDL ${SDL2_LIBRARIES})