cmake_minimum_required(VERSION 2.8)
project(pmf)
cmake_policy(SET CMP0043 NEW)

set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB JPEGREADER_SRCS
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
        )
add_library(pmf ${JPEGREADER_SRCS})

target_include_directories(pmf INTERFACE ${PROJECT_INCLUDE_DIR})


add_executable(pmfinspect test/jpeg2bmp.cc)
target_include_directories(pmfinspect PRIVATE ${PROJECT_INCLUDE_DIR})

