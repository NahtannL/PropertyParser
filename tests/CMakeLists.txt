file(GLOB TXT_FILES test.properties test.txt)

add_executable(map_test map_test.c)
target_include_directories(map_test PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(map_test PRIVATE parser_lib)

add_executable(cstring_test cstring_test.c)
target_include_directories(cstring_test PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(cstring_test PRIVATE parser_lib)

file(COPY ${TXT_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(parser_test parser_test.c)
target_include_directories(parser_test PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(parser_test PRIVATE parser_lib)

add_test(NAME MapTest COMMAND map_test)
add_test(NAME CStringTest COMMAND cstring_test)
add_test(NAME ParserTest COMMAND parser_test)