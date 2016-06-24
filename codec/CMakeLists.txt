cmake_minimum_required(VERSION 2.8)
project(codec)
cmake_policy(SET CMP0043 NEW)
enable_testing()

find_package(JPEG REQUIRED)

file(GLOB VIDEOCODEC_SRCS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        )
add_library(codec ${JPEG_LIBRARIES} ${VIDEOCODEC_SRCS})
target_include_directories(codec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(codec PRIVATE ${JPEG_INCLUDE_DIR})
target_link_libraries(codec ${JPEG_LIBRARIES})
