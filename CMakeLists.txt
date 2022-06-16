cmake_minimum_required(VERSION 2.8)
project(ConvertRGBD)
IF(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RELEASE)
ENDIF()

message(STATUS CMAKE_MODULE_PATH)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall")

add_executable(ConvertRGBD main.cpp)

