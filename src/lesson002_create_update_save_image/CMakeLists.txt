cmake_minimum_required(VERSION 3.31)
project(${CURRENT_DIR_NAME})
message("lesson: ${PROJECT_NAME}")

include("../../cmake/utils.cmake")

set(CMAKE_CXX_STANDARD 23)

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


# 自动复制 OpenCV DLL（Debug/Release 自动适配）
message("OPENCV_INSTALL_DIR:${OPENCV_INSTALL_DIR}")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${OPENCV_INSTALL_DIR}/../bin/$<IF:$<CONFIG:Debug>,opencv_world4120d.dll,opencv_world4120.dll>"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/"
        COMMENT "Copying OpenCV DLL ($<CONFIG>) to executable directory"
)
