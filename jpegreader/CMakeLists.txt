cmake_minimum_required(VERSION 2.8)
project (jpegreader)
cmake_policy(SET CMP0043 NEW)

set (PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB JPEGREADER_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
)
find_package(JPEG REQUIRED)
add_library(jpegreader ${JPEGREADER_SRCS})

target_link_libraries(jpegreader ${JPEG_LIBRARIES})
# find_package(LibJpegTurbo REQUIRED)
target_include_directories(jpegreader PUBLIC ${JPEG_INCLUDE_DIR})
target_include_directories(jpegreader PRIVATE ${PROJECT_INCLUDE_DIR})


add_executable(jpeg2bmp test/jpeg2bmp.cc)
target_include_directories(jpeg2bmp PRIVATE ${PROJECT_INCLUDE_DIR})
target_link_libraries(jpeg2bmp jpegreader)

