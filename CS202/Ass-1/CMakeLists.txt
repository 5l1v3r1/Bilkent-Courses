cmake_minimum_required(VERSION 3.6)
project(Ass_1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wl,-stack_size -Wl,2000000")

set(SOURCE_FILES sorting.cpp main.cpp)
add_executable(Ass_1 ${SOURCE_FILES})