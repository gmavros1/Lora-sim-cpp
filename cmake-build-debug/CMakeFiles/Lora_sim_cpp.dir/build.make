# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/284/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/284/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Lora_sim_cpp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Lora_sim_cpp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Lora_sim_cpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lora_sim_cpp.dir/flags.make

CMakeFiles/Lora_sim_cpp.dir/src/packet.cpp.o: CMakeFiles/Lora_sim_cpp.dir/flags.make
CMakeFiles/Lora_sim_cpp.dir/src/packet.cpp.o: /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/packet.cpp
CMakeFiles/Lora_sim_cpp.dir/src/packet.cpp.o: CMakeFiles/Lora_sim_cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Lora_sim_cpp.dir/src/packet.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lora_sim_cpp.dir/src/packet.cpp.o -MF CMakeFiles/Lora_sim_cpp.dir/src/packet.cpp.o.d -o CMakeFiles/Lora_sim_cpp.dir/src/packet.cpp.o -c /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/packet.cpp

CMakeFiles/Lora_sim_cpp.dir/src/packet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Lora_sim_cpp.dir/src/packet.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/packet.cpp > CMakeFiles/Lora_sim_cpp.dir/src/packet.cpp.i

CMakeFiles/Lora_sim_cpp.dir/src/packet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Lora_sim_cpp.dir/src/packet.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/packet.cpp -o CMakeFiles/Lora_sim_cpp.dir/src/packet.cpp.s

CMakeFiles/Lora_sim_cpp.dir/src/node.cpp.o: CMakeFiles/Lora_sim_cpp.dir/flags.make
CMakeFiles/Lora_sim_cpp.dir/src/node.cpp.o: /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/node.cpp
CMakeFiles/Lora_sim_cpp.dir/src/node.cpp.o: CMakeFiles/Lora_sim_cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Lora_sim_cpp.dir/src/node.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lora_sim_cpp.dir/src/node.cpp.o -MF CMakeFiles/Lora_sim_cpp.dir/src/node.cpp.o.d -o CMakeFiles/Lora_sim_cpp.dir/src/node.cpp.o -c /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/node.cpp

CMakeFiles/Lora_sim_cpp.dir/src/node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Lora_sim_cpp.dir/src/node.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/node.cpp > CMakeFiles/Lora_sim_cpp.dir/src/node.cpp.i

CMakeFiles/Lora_sim_cpp.dir/src/node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Lora_sim_cpp.dir/src/node.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/node.cpp -o CMakeFiles/Lora_sim_cpp.dir/src/node.cpp.s

CMakeFiles/Lora_sim_cpp.dir/src/traffic.cpp.o: CMakeFiles/Lora_sim_cpp.dir/flags.make
CMakeFiles/Lora_sim_cpp.dir/src/traffic.cpp.o: /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/traffic.cpp
CMakeFiles/Lora_sim_cpp.dir/src/traffic.cpp.o: CMakeFiles/Lora_sim_cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Lora_sim_cpp.dir/src/traffic.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lora_sim_cpp.dir/src/traffic.cpp.o -MF CMakeFiles/Lora_sim_cpp.dir/src/traffic.cpp.o.d -o CMakeFiles/Lora_sim_cpp.dir/src/traffic.cpp.o -c /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/traffic.cpp

CMakeFiles/Lora_sim_cpp.dir/src/traffic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Lora_sim_cpp.dir/src/traffic.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/traffic.cpp > CMakeFiles/Lora_sim_cpp.dir/src/traffic.cpp.i

CMakeFiles/Lora_sim_cpp.dir/src/traffic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Lora_sim_cpp.dir/src/traffic.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/traffic.cpp -o CMakeFiles/Lora_sim_cpp.dir/src/traffic.cpp.s

CMakeFiles/Lora_sim_cpp.dir/src/environment.cpp.o: CMakeFiles/Lora_sim_cpp.dir/flags.make
CMakeFiles/Lora_sim_cpp.dir/src/environment.cpp.o: /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/environment.cpp
CMakeFiles/Lora_sim_cpp.dir/src/environment.cpp.o: CMakeFiles/Lora_sim_cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Lora_sim_cpp.dir/src/environment.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lora_sim_cpp.dir/src/environment.cpp.o -MF CMakeFiles/Lora_sim_cpp.dir/src/environment.cpp.o.d -o CMakeFiles/Lora_sim_cpp.dir/src/environment.cpp.o -c /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/environment.cpp

CMakeFiles/Lora_sim_cpp.dir/src/environment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Lora_sim_cpp.dir/src/environment.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/environment.cpp > CMakeFiles/Lora_sim_cpp.dir/src/environment.cpp.i

CMakeFiles/Lora_sim_cpp.dir/src/environment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Lora_sim_cpp.dir/src/environment.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/environment.cpp -o CMakeFiles/Lora_sim_cpp.dir/src/environment.cpp.s

CMakeFiles/Lora_sim_cpp.dir/src/gateway.cpp.o: CMakeFiles/Lora_sim_cpp.dir/flags.make
CMakeFiles/Lora_sim_cpp.dir/src/gateway.cpp.o: /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/gateway.cpp
CMakeFiles/Lora_sim_cpp.dir/src/gateway.cpp.o: CMakeFiles/Lora_sim_cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Lora_sim_cpp.dir/src/gateway.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lora_sim_cpp.dir/src/gateway.cpp.o -MF CMakeFiles/Lora_sim_cpp.dir/src/gateway.cpp.o.d -o CMakeFiles/Lora_sim_cpp.dir/src/gateway.cpp.o -c /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/gateway.cpp

CMakeFiles/Lora_sim_cpp.dir/src/gateway.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Lora_sim_cpp.dir/src/gateway.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/gateway.cpp > CMakeFiles/Lora_sim_cpp.dir/src/gateway.cpp.i

CMakeFiles/Lora_sim_cpp.dir/src/gateway.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Lora_sim_cpp.dir/src/gateway.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/gateway.cpp -o CMakeFiles/Lora_sim_cpp.dir/src/gateway.cpp.s

CMakeFiles/Lora_sim_cpp.dir/src/utils.cpp.o: CMakeFiles/Lora_sim_cpp.dir/flags.make
CMakeFiles/Lora_sim_cpp.dir/src/utils.cpp.o: /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/utils.cpp
CMakeFiles/Lora_sim_cpp.dir/src/utils.cpp.o: CMakeFiles/Lora_sim_cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Lora_sim_cpp.dir/src/utils.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lora_sim_cpp.dir/src/utils.cpp.o -MF CMakeFiles/Lora_sim_cpp.dir/src/utils.cpp.o.d -o CMakeFiles/Lora_sim_cpp.dir/src/utils.cpp.o -c /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/utils.cpp

CMakeFiles/Lora_sim_cpp.dir/src/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Lora_sim_cpp.dir/src/utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/utils.cpp > CMakeFiles/Lora_sim_cpp.dir/src/utils.cpp.i

CMakeFiles/Lora_sim_cpp.dir/src/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Lora_sim_cpp.dir/src/utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/utils.cpp -o CMakeFiles/Lora_sim_cpp.dir/src/utils.cpp.s

CMakeFiles/Lora_sim_cpp.dir/src/multihopNode.cpp.o: CMakeFiles/Lora_sim_cpp.dir/flags.make
CMakeFiles/Lora_sim_cpp.dir/src/multihopNode.cpp.o: /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/multihopNode.cpp
CMakeFiles/Lora_sim_cpp.dir/src/multihopNode.cpp.o: CMakeFiles/Lora_sim_cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Lora_sim_cpp.dir/src/multihopNode.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lora_sim_cpp.dir/src/multihopNode.cpp.o -MF CMakeFiles/Lora_sim_cpp.dir/src/multihopNode.cpp.o.d -o CMakeFiles/Lora_sim_cpp.dir/src/multihopNode.cpp.o -c /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/multihopNode.cpp

CMakeFiles/Lora_sim_cpp.dir/src/multihopNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Lora_sim_cpp.dir/src/multihopNode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/multihopNode.cpp > CMakeFiles/Lora_sim_cpp.dir/src/multihopNode.cpp.i

CMakeFiles/Lora_sim_cpp.dir/src/multihopNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Lora_sim_cpp.dir/src/multihopNode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/src/multihopNode.cpp -o CMakeFiles/Lora_sim_cpp.dir/src/multihopNode.cpp.s

# Object files for target Lora_sim_cpp
Lora_sim_cpp_OBJECTS = \
"CMakeFiles/Lora_sim_cpp.dir/src/packet.cpp.o" \
"CMakeFiles/Lora_sim_cpp.dir/src/node.cpp.o" \
"CMakeFiles/Lora_sim_cpp.dir/src/traffic.cpp.o" \
"CMakeFiles/Lora_sim_cpp.dir/src/environment.cpp.o" \
"CMakeFiles/Lora_sim_cpp.dir/src/gateway.cpp.o" \
"CMakeFiles/Lora_sim_cpp.dir/src/utils.cpp.o" \
"CMakeFiles/Lora_sim_cpp.dir/src/multihopNode.cpp.o"

# External object files for target Lora_sim_cpp
Lora_sim_cpp_EXTERNAL_OBJECTS =

Lora_sim_cpp: CMakeFiles/Lora_sim_cpp.dir/src/packet.cpp.o
Lora_sim_cpp: CMakeFiles/Lora_sim_cpp.dir/src/node.cpp.o
Lora_sim_cpp: CMakeFiles/Lora_sim_cpp.dir/src/traffic.cpp.o
Lora_sim_cpp: CMakeFiles/Lora_sim_cpp.dir/src/environment.cpp.o
Lora_sim_cpp: CMakeFiles/Lora_sim_cpp.dir/src/gateway.cpp.o
Lora_sim_cpp: CMakeFiles/Lora_sim_cpp.dir/src/utils.cpp.o
Lora_sim_cpp: CMakeFiles/Lora_sim_cpp.dir/src/multihopNode.cpp.o
Lora_sim_cpp: CMakeFiles/Lora_sim_cpp.dir/build.make
Lora_sim_cpp: CMakeFiles/Lora_sim_cpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable Lora_sim_cpp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lora_sim_cpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lora_sim_cpp.dir/build: Lora_sim_cpp
.PHONY : CMakeFiles/Lora_sim_cpp.dir/build

CMakeFiles/Lora_sim_cpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Lora_sim_cpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Lora_sim_cpp.dir/clean

CMakeFiles/Lora_sim_cpp.dir/depend:
	cd /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/CMakeFiles/Lora_sim_cpp.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Lora_sim_cpp.dir/depend

