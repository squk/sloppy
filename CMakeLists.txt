cmake_minimum_required (VERSION 2.6)
project (sloppy-emu)
LINK_DIRECTORIES(/usr/local/lib)

OPTION(RENDER "Use renderer" OFF)

IF(RENDER)
  MESSAGE("Adding render flag...")
  ADD_DEFINITIONS("-DSLOPPY_RENDER")
  SET(CMAKE_BUILD_TYPE Debug)
  MESSAGE("Build type is " ${CMAKE_BUILD_TYPE})
ENDIF(RENDER)
unset(RENDER CACHE)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_C_COMPILER /usr/bin/gcc)

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/modules/sdl2-cmake-scripts")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_definitions("-DCPP_SRC_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/\"")

add_subdirectory(src)
