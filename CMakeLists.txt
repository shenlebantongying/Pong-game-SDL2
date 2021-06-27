cmake_minimum_required(VERSION 3.19)
project(ponggame)
set(CMAKE_CXX_STANDARD 20)

# resources
FILE(COPY OpenSans-Regular.ttf DESTINATION "${CMAKE_BINARY_DIR}")

add_executable(Pong_game_SDL main.cpp)

# Platform detection codes
# https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html#variables-that-describe-the-system

if(MINGW) # -> MSYS2
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)
    find_package(SDL2 CONFIG REQUIRED)
    find_package(SDL2_ttf REQUIRED)

    target_link_libraries(Pong_game_SDL PUBLIC mingw32 SDL2::SDL2main SDL2::SDL2 ${SDL2_TTF_LIBRARIES})
    #                                          ^ SDL require some windows.h functionality
elseif(WIN32)
     message(NOTICE "MSVC build require vcpkg")
     find_package(SDL2 CONFIG REQUIRED)
     find_package(sdl2-ttf CONFIG REQUIRED)

     target_link_libraries(Pong_game_SDL SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_ttf)
elseif(UNIX) #TODO: may not work
    find_package(SDL2 REQUIRED)
    #include_directories(${SDL2_INCLUDE_DIRS})
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

    target_link_libraries(Pong_game_SDL ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES})
endif()


# FIXME: add a findSDL2 for linux
#include_directories(${SDL2_INCLUDE_DIRS})
# find_package(PkgConfig REQUIRED)

