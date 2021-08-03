cmake_minimum_required(VERSION 3.19)
project(nebula_lang)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(nebcc)
add_subdirectory(nruntime)
add_subdirectory(examples)
