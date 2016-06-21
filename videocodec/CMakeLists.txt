cmake_minimum_required(VERSION 2.8)
project(videocodec)
cmake_policy(SET CMP0043 NEW)
enable_testing()

find_package(JPEG REQUIRED)

file(GLOB VIDEOCODEC_SRCS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        )
add_library(videocodec ${JPEG_LIBRARIES} ${VIDEOCODEC_SRCS})
target_include_directories(videocodec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(videocodec PRIVATE ${JPEG_INCLUDE_DIR})
target_link_libraries(videocodec ${JPEG_LIBRARIES})

add_executable(jpeg2bmp tools/jpeg2bmp.cpp)
target_include_directories(jpeg2bmp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(jpeg2bmp videocodec)

add_executable(dirlist tools/dirlisttest.cpp)
target_include_directories(dirlist PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(dirlist videocodec)

add_executable(pmfreader tools/pmfreader.cpp)
target_include_directories(dirlist PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(pmfreader videocodec)

add_executable(encodepmf tools/encodepmf.cpp)
target_include_directories(dirlist PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(encodepmf videocodec)

# TESTS

add_executable(teststring test/teststring.cpp)

add_test(teststring teststring)