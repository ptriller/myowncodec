cmake_minimum_required(VERSION 2.6)
project (codecgui)
 
set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
 
set(CODECGUI_SRCS 
${PROJECT_SOURCE_DIR}/main.cc
)
 
add_executable(codecgui ${CODECGUI_SRCS})
 
