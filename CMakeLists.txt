cmake_minimum_required(VERSION 3.12)
project(breakout)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_subdirectory(src)