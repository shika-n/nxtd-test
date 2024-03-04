cmake_minimum_required(VERSION 3.27)

project(Q1)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BINARY_DIR ${CMAKE_ROOT}/bin)

set(SRC_FILES main.cpp)

add_executable(Q1 ${SRC_FILES})