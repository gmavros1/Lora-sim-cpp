cmake_minimum_required(VERSION 3.26)
project(Lora_sim_cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(Lora_sim_cpp
        src/packet.cpp
        src/packet.h
        src/utils.cpp
        src/node.cpp
        src/node.h
)
