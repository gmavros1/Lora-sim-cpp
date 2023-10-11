cmake_minimum_required(VERSION 3.26)
project(Lora_sim_cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(Lora_sim_cpp
        src/environment.cpp
        src/gateway.cpp
        src/lorawan.cpp
        src/main.cpp
        src/multihop.cpp
        src/node.cpp
        src/node.h
        src/packet.cpp
        src/packet.h
        src/server.cpp
        src/topology.cpp
        src/utils.cpp
        src/traffic.cpp
        src/traffic.h)
