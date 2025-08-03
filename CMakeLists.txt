cmake_minimum_required(VERSION 3.31)
project(learning_opencv)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(src/common)

include("cmake/utils.cmake")
add_subdirectories(src "^lesson")