set(TARGET NgRandom)

file(GLOB HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/Random/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/Random/*.inl
)

file(GLOB SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp
)

add_library(${TARGET} STATIC ${HEADER_FILES} ${SOURCE_FILES})
add_library(Ng::Random ALIAS ${TARGET})

target_include_directories(${TARGET}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/Random
)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)