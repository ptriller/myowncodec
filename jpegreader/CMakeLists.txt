cmake_minimum_required(VERSION 2.8)
project (jpegreader)
cmake_policy(SET CMP0043 NEW)

set (PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB JPEGREADER_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
)
# find_package(LibJpegTurbo REQUIRED)
add_library(jpegreader ${JPEGREADER_SRCS})
target_include_directories(jpegreader PRIVATE ${PROJECT_INCLUDE_DIR})

