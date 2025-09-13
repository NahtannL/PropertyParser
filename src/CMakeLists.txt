file(GLOB SRC_FILES *.c)

add_library(parser_lib ${SRC_FILES})

target_include_directories(parser_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

source_group(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header Files"
    FILES ${CMAKE_SOURCE_DIR}/include/*.h
)