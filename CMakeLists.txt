cmake_minimum_required(VERSION 3.19)
project(Pong_game_SDL)

set(CMAKE_CXX_STANDARD 20)

# resources
FILE(COPY OpenSans-Regular.ttf DESTINATION "${CMAKE_BINARY_DIR}")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

add_executable(Pong_game_SDL main.cpp)

target_link_libraries(Pong_game_SDL ${SDL2_LIBRARIES} ${SDL2TTF_INCLUDE_DIRS} ${SDL2TTF_LIBRARIES})