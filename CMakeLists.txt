cmake_minimum_required(VERSION 3.26)
project(Lora_sim_cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

# Add the external module's source directory
add_subdirectory(external/tqdm.cpp)  # Replace 'module_name' with the actual submodule name


add_executable(Lora_sim_cpp
        src/packet.cpp
        src/packet.h
        src/utils.h
        src/node.cpp
        src/node.h
        src/traffic.cpp
        src/traffic.h
        src/environment.cpp
        src/environment.h
        src/gateway.cpp
        src/gateway.h
        src/utils.cpp
)

# Link the external module's target to your main target
target_link_libraries(tqdm)  # Replace 'module_name' with the actual submodule name
