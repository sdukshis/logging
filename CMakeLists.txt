cmake_minimum_required(VERSION 2.8)

project(logging)

add_definitions(-Wall)
add_definitions(-std=c++11)

include_directories(src)

add_executable(sample1 samples/sample1.cpp)
