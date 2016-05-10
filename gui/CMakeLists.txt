cmake_minimum_required(VERSION 2.6)
project (codecgui)
 
set (PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
find_package(wxWidgets REQUIRED COMPONENTS core base) 
set(CODECGUI_SRCS 
${PROJECT_SOURCE_DIR}/myapp.cc
)
include(${wxWidgets_USE_FILE})
add_executable(codecgui ${CODECGUI_SRCS})
target_include_directories(codecgui PRIVATE ${PROJECT_INCLUDE_DIR}) 
target_link_libraries(codecgui ${wxWidgets_LIBRARIES})

