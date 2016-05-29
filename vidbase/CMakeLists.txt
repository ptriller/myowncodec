cmake_minimum_required(VERSION 2.8)
project (vidbase)
cmake_policy(SET CMP0043 NEW)

add_library(vidbase src/base.cc)
target_include_directories(vidbase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

