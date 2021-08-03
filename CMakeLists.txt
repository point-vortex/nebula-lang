cmake_minimum_required(VERSION 3.19)
project(nebula_lang)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_EXE main.cpp)

include_directories(nruntime)

add_executable(nebula_lang ${SOURCE_EXE})

add_subdirectory(nruntime)
target_link_libraries(nebula_lang nruntime)