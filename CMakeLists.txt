cmake_minimum_required (VERSION 2.6)
project (sloppy-emu)
LINK_DIRECTORIES(/usr/local/lib)

set(CMAKE_CXX_STANDARD 98)
#SET(CMAKE_C_COMPILER /usr/bin/gcc)

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/modules/sdl2-cmake-scripts")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_definitions("-DCPP_SRC_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/\"")

add_subdirectory(src)

#find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
#find_library(SDL2_LIBRARY NAME SDL2)
#add_executable(ChickenShooter main.cpp)
#target_include_directories(ChickenShooter ${SDL2_INCLUDE_DIR})
#target_link_libraries(ChickenShooter ${SDL2_LIBRARY})    
