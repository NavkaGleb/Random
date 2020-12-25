cmake_minimum_required(VERSION 3.17)
project(Random)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Random main.cpp include/Random/Random.hpp)