cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(StegTool)

SET(GCC_COVERAGE_COMPILE_FLAGS "-Wall -ansi -pedantic -g")
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

include_directories(include)

file(GLOB SOURCES "src/*c")

add_executable(StegTool ${SOURCES})

# Lib for PNG functions
target_link_libraries(StegTool png)

# zlib for compression
target_link_libraries(StegTool z)