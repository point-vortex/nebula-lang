cmake_minimum_required(VERSION 3.19)
project(nebula_lang)

set(CMAKE_CXX_STANDARD 20)

include_directories(nebcc)
include_directories(nruntime)

add_subdirectory(nebcc)
add_subdirectory(nruntime)
