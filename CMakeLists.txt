cmake_minimum_required(VERSION 3.26)
project(Lora_sim_cpp)

set(CMAKE_CXX_STANDARD 14)

# Add the external module's source directory
add_subdirectory(external/tqdm.cpp)  # Replace 'module_name' with the actual submodule name
add_subdirectory(external/json)  # Replace 'module_name' with the actual submodule name

# Include the JSON nlohmann library as a target
add_library(nlohmann_json_external INTERFACE)
target_include_directories(nlohmann_json_external INTERFACE external/json/include)

# Your project's source files
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
        src/device.cpp
        src/device.h
        src/node_wur.cpp
        src/node_wur.h
)

# Link the external modules to your main target
target_link_libraries(Lora_sim_cpp PRIVATE nlohmann_json_external)  # Replace 'module_name' with the actual submodule name
