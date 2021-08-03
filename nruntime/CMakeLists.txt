cmake_minimum_required(VERSION 3.19)

project(nruntime C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB nruntime.h enums/data_type.h enums/instruction.h tokenizer.h tokenizer.c runtime.h runtime.c utils/dstack.h utils/dstack.c utils/nstatus.h utils/flex_buffer.h utils/flex_buffer.c)

add_library(nruntime STATIC ${SOURCE_LIB})
