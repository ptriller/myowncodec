cmake_minimum_required (VERSION 2.8)
project (myowncodec)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

include_directories("${PROJECT_INCLUDE_DIR}")
file(GLOB CODECGUI_SRCS
    "${PROJECT_INCLUDE_DIR}/*.h"
)

add_subdirectory(gui)

