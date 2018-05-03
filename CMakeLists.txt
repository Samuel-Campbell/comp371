cmake_minimum_required(VERSION 3.7)
project(comp371)

find_package(PkgConfig REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)

include_directories(${GLFW_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

add_executable(comp371 src/main.cpp src/GLFWAdapter/GlfwAdapter.cpp src/GLFWAdapter/GlfwAdapter.h)

target_link_libraries(comp371
        ${GLFW_LIBRARIES}
        -lGLEW
        -lglfw3
        -lGL
        -lX11
        -lXi
        -lXrandr
        -lXxf86vm
        -lXinerama
        -lXcursor
        -lrt
        -lm
        -pthread
        -ldl
        )