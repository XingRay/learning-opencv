cmake_minimum_required(VERSION 3.31)
project(learning_opencv)

set(CMAKE_CXX_STANDARD 23)

# 设置源码的编码
if (MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/source-charset:utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")
else ()
    add_compile_options(-finput-charset=UTF-8)
endif ()

add_subdirectory(src/common)

include("cmake/utils.cmake")
add_subdirectories(src "^lesson")