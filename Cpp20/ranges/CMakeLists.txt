cmake_minimum_required(VERSION 3.16)
project(RangesExamples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB RANGES_SOURCES *.cpp)

foreach(src ${RANGES_SOURCES})
    get_filename_component(exec_name ${src} NAME_WE)
    add_executable(${exec_name} ${src})
    target_compile_definitions(${exec_name} PRIVATE $<$<CONFIG:Debug>:_GLIBCXX_DEBUG>)
endforeach()