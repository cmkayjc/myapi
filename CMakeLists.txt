cmake_minimum_required(VERSION 2.8)

project(myapi)
add_definitions(-std=c++11)
include_directories(include)
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} pthread)
