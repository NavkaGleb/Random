cmake_minimum_required(VERSION 3.17)
project(NgRandom)

set(CMAKE_CXX_STANDARD 14)

add_library(NgRandom STATIC include/Random/Random.hpp)

target_include_directories(NgRandom PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(NgRandom PROPERTIES LINKER_LANGUAGE CXX)