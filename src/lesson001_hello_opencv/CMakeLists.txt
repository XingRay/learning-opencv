cmake_minimum_required(VERSION 3.31)
project(lesson001_hello_opencv)
message("lesson: ${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 23)

#opencv
# https://opencv.org/
# https://github.com/opencv/opencv
set(OPENCV_INSTALL_DIR "D:/develop/opencv/4.12.0/opencv/build/x64/vc16/lib")
set(OpenCV_DIR ${OPENCV_INSTALL_DIR})
find_package(OpenCV REQUIRED)
message("OpenCV_FOUND:${OpenCV_FOUND}")
message("OpenCV_INCLUDE_DIRS:${OpenCV_INCLUDE_DIRS}")
message("OpenCV_LIBS:${OpenCV_LIBS}")
if (NOT ${OpenCV_FOUND})
    message(FATAL_ERROR "OpenCV not found!")
endif ()


file(GLOB_RECURSE SRC_LIST
        *.cpp
        *.c++
        *.cxx
        *.c
)

add_executable(${PROJECT_NAME} ${SRC_LIST}
)

# 链接OpenCV库
target_link_libraries(${PROJECT_NAME}
        PRIVATE ${OpenCV_LIBS} common
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${PROJECT_SOURCE_DIR}/resource"
        "${CMAKE_CURRENT_BINARY_DIR}/resource"
)


