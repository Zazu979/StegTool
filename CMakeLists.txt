cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(stegtool)

SET(GCC_COVERAGE_COMPILE_FLAGS "-Wall -ansi -pedantic -g")
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

include_directories(include)

file(GLOB SOURCES "src/*c")

add_executable(stegtool ${SOURCES})
set_property(TARGET stegtool PROPERTY C_STANDARD 99)
# Lib for PNG functions
target_link_libraries(stegtool png)

# Lib for PNG functions
target_link_libraries(stegtool jpeg)

# zlib for compression
target_link_libraries(stegtool z)
