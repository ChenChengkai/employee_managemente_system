cmake_minimum_required(VERSION 2.8)
project(CPP)
include_directories(
    include 
)
# user define
aux_source_directory(src DIR_SRCS)
add_library(SRC ${DIR_SRCS})

add_executable(main main.cpp)
target_link_libraries(main SRC)