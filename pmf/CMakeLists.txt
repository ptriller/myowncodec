cmake_minimum_required(VERSION 2.8)
project(pmf)
cmake_policy(SET CMP0043 NEW)

file(GLOB JPEGREADER_SRCS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        )
add_library(pmf ${JPEGREADER_SRCS})

target_include_directories(pmf PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(pmf vidbase)


add_executable(bitmappmf test/bitmappmf.cpp)
target_link_libraries(bitmappmf pmf jpegreader)