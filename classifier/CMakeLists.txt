cmake_minimum_required(VERSION 3.4)
project(classifier)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(dlib REQUIRED)
set(SOURCE_FILES main.cpp)
add_executable(classifier ${SOURCE_FILES})