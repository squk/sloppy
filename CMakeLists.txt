cmake_minimum_required (VERSION 2.6)
project (sloppy-emu)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE "Debug")

add_definitions("-DCPP_SRC_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/\"")

add_subdirectory(modules)
add_subdirectory(src)

