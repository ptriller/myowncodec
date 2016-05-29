cmake_minimum_required(VERSION 2.8)
project (jpegreader)
cmake_policy(SET CMP0043 NEW)
file(GLOB JPEGREADER_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
)
find_package(JPEG REQUIRED)
add_library(jpegreader ${JPEGREADER_SRCS})

target_link_libraries(jpegreader vidbase ${JPEG_LIBRARIES})
target_include_directories(jpegreader PRIVATE ${JPEG_INCLUDE_DIR})
target_include_directories(jpegreader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


add_executable(jpeg2bmp test/jpeg2bmp.cc)
target_include_directories(jpeg2bmp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(jpeg2bmp jpegreader)

add_executable(dirlist test/dirlisttest.cc)
target_include_directories(dirlist PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(dirlist jpegreader)
