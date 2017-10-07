cmake_minimum_required(VERSION 2.8)

add_library(csvparser CSVParser.cpp)

add_executable(parsercmd main.cpp)
target_link_libraries(parsercmd csvparser)

