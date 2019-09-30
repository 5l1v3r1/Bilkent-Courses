cmake_minimum_required(VERSION 3.6)
project(avl)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp PeopleAVLTree.cpp PeopleAVLTree.h)
add_executable(avl ${SOURCE_FILES})