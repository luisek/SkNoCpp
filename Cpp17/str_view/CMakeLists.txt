`cmake_minimum_required(VERSION 3.10)
project(string_view LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

file(GLOB STR_VIEW_SOURCES *.cpp)

foreach(src ${STR_VIEW_SOURCES})
    get_filename_component(exec_name ${src} NAME_WE)
    add_executable(${exec_name} ${src})
endforeach()