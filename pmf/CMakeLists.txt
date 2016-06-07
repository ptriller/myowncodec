cmake_minimum_required(VERSION 2.8)
project(pmf)
cmake_policy(SET CMP0043 NEW)

set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB JPEGREADER_SRCS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        )
add_library(pmf ${JPEGREADER_SRCS})

target_include_directories(pmf PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_libraries(pmf vidbase)

