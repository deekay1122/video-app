cmake_minimum_required(VERSION 3.14)
project(app C CXX)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/glfw)

add_executable(app src/main.cpp)
target_link_libraries(app glfw)