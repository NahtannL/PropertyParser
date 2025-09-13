cmake_minimum_required(VERSION 3.10.0)
project(property_parser VERSION 0.1.0 LANGUAGES C)

enable_testing()

include_directories(include)
add_subdirectory(src)
add_subdirectory(tests)