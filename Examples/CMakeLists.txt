set(TARGET Examples)

file(GLOB SOURCE_FILES ./*.cpp)

add_executable(${TARGET} ${SOURCE_FILES})

target_link_libraries(${TARGET} Ng::Random)