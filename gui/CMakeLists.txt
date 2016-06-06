cmake_minimum_required(VERSION 2.8)
project(codecgui)
cmake_policy(SET CMP0043 NEW)
find_package(wxWidgets REQUIRED COMPONENTS core base)

set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB CODECGUI_SRCS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        )
include(${wxWidgets_USE_FILE})
add_executable(codecgui ${CODECGUI_SRCS})
target_compile_features(codecgui PRIVATE cxx_range_for)
target_include_directories(codecgui PRIVATE ${PROJECT_INCLUDE_DIR})
target_link_libraries(codecgui ${wxWidgets_LIBRARIES} jpegreader)

