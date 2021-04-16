cmake_minimum_required(VERSION 3.19)
project(synchronizer)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} src/main.cpp src/utils.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)
