cmake_minimum_required(VERSION 3.17)
project(NgRandom)

set(CMAKE_CXX_STANDARD 20)

file(GLOB HEADER_FILES
    include/Random/*.hpp
)

file(GLOB SOURCE_FILES
    include/Random/*.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)