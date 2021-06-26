 cmake_minimum_required(VERSION 3.19)
project(ponggame)

set(CMAKE_CXX_STANDARD 20)

# resources
FILE(COPY OpenSans-Regular.ttf DESTINATION "${CMAKE_BINARY_DIR}")

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)

# FIXME: add a findSDL2 for linux
#include_directories(${SDL2_INCLUDE_DIRS})
# find_package(PkgConfig REQUIRED)

add_executable(Pong_game_SDL main.cpp)
target_link_libraries(Pong_game_SDL SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_ttf)