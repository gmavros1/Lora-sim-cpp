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
include external/tqdm.cpp/CMakeFiles/tqdmlib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include external/tqdm.cpp/CMakeFiles/tqdmlib.dir/compiler_depend.make

# Include the progress variables for this target.
include external/tqdm.cpp/CMakeFiles/tqdmlib.dir/progress.make

# Include the compile flags for this target's objects.
include external/tqdm.cpp/CMakeFiles/tqdmlib.dir/flags.make

external/tqdm.cpp/CMakeFiles/tqdmlib.dir/src/main.cpp.o: external/tqdm.cpp/CMakeFiles/tqdmlib.dir/flags.make
external/tqdm.cpp/CMakeFiles/tqdmlib.dir/src/main.cpp.o: /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/external/tqdm.cpp/src/main.cpp
external/tqdm.cpp/CMakeFiles/tqdmlib.dir/src/main.cpp.o: external/tqdm.cpp/CMakeFiles/tqdmlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object external/tqdm.cpp/CMakeFiles/tqdmlib.dir/src/main.cpp.o"
	cd /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/external/tqdm.cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/tqdm.cpp/CMakeFiles/tqdmlib.dir/src/main.cpp.o -MF CMakeFiles/tqdmlib.dir/src/main.cpp.o.d -o CMakeFiles/tqdmlib.dir/src/main.cpp.o -c /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/external/tqdm.cpp/src/main.cpp

external/tqdm.cpp/CMakeFiles/tqdmlib.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tqdmlib.dir/src/main.cpp.i"
	cd /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/external/tqdm.cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/external/tqdm.cpp/src/main.cpp > CMakeFiles/tqdmlib.dir/src/main.cpp.i

external/tqdm.cpp/CMakeFiles/tqdmlib.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tqdmlib.dir/src/main.cpp.s"
	cd /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/external/tqdm.cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/external/tqdm.cpp/src/main.cpp -o CMakeFiles/tqdmlib.dir/src/main.cpp.s

external/tqdm.cpp/CMakeFiles/tqdmlib.dir/src/stdafx.cpp.o: external/tqdm.cpp/CMakeFiles/tqdmlib.dir/flags.make
external/tqdm.cpp/CMakeFiles/tqdmlib.dir/src/stdafx.cpp.o: /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/external/tqdm.cpp/src/stdafx.cpp
external/tqdm.cpp/CMakeFiles/tqdmlib.dir/src/stdafx.cpp.o: external/tqdm.cpp/CMakeFiles/tqdmlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object external/tqdm.cpp/CMakeFiles/tqdmlib.dir/src/stdafx.cpp.o"
	cd /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/external/tqdm.cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/tqdm.cpp/CMakeFiles/tqdmlib.dir/src/stdafx.cpp.o -MF CMakeFiles/tqdmlib.dir/src/stdafx.cpp.o.d -o CMakeFiles/tqdmlib.dir/src/stdafx.cpp.o -c /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/external/tqdm.cpp/src/stdafx.cpp

external/tqdm.cpp/CMakeFiles/tqdmlib.dir/src/stdafx.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tqdmlib.dir/src/stdafx.cpp.i"
	cd /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/external/tqdm.cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/external/tqdm.cpp/src/stdafx.cpp > CMakeFiles/tqdmlib.dir/src/stdafx.cpp.i

external/tqdm.cpp/CMakeFiles/tqdmlib.dir/src/stdafx.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tqdmlib.dir/src/stdafx.cpp.s"
	cd /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/external/tqdm.cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/external/tqdm.cpp/src/stdafx.cpp -o CMakeFiles/tqdmlib.dir/src/stdafx.cpp.s

# Object files for target tqdmlib
tqdmlib_OBJECTS = \
"CMakeFiles/tqdmlib.dir/src/main.cpp.o" \
"CMakeFiles/tqdmlib.dir/src/stdafx.cpp.o"

# External object files for target tqdmlib
tqdmlib_EXTERNAL_OBJECTS =

external/tqdm.cpp/libtqdmlib.a: external/tqdm.cpp/CMakeFiles/tqdmlib.dir/src/main.cpp.o
external/tqdm.cpp/libtqdmlib.a: external/tqdm.cpp/CMakeFiles/tqdmlib.dir/src/stdafx.cpp.o
external/tqdm.cpp/libtqdmlib.a: external/tqdm.cpp/CMakeFiles/tqdmlib.dir/build.make
external/tqdm.cpp/libtqdmlib.a: external/tqdm.cpp/CMakeFiles/tqdmlib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libtqdmlib.a"
	cd /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/external/tqdm.cpp && $(CMAKE_COMMAND) -P CMakeFiles/tqdmlib.dir/cmake_clean_target.cmake
	cd /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/external/tqdm.cpp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tqdmlib.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold "Separating debug symbols"
	cd /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/external/tqdm.cpp && objcopy --only-keep-debug /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/external/tqdm.cpp/libtqdmlib.a /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/external/tqdm.cpp/libtqdmlib.a.debug
	cd /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/external/tqdm.cpp && strip -g /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/external/tqdm.cpp/libtqdmlib.a
	cd /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/external/tqdm.cpp && objcopy --add-gnu-debuglink=/home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/external/tqdm.cpp/libtqdmlib.a.debug /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/external/tqdm.cpp/libtqdmlib.a

# Rule to build all files generated by this target.
external/tqdm.cpp/CMakeFiles/tqdmlib.dir/build: external/tqdm.cpp/libtqdmlib.a
.PHONY : external/tqdm.cpp/CMakeFiles/tqdmlib.dir/build

external/tqdm.cpp/CMakeFiles/tqdmlib.dir/clean:
	cd /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/external/tqdm.cpp && $(CMAKE_COMMAND) -P CMakeFiles/tqdmlib.dir/cmake_clean.cmake
.PHONY : external/tqdm.cpp/CMakeFiles/tqdmlib.dir/clean

external/tqdm.cpp/CMakeFiles/tqdmlib.dir/depend:
	cd /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/external/tqdm.cpp /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/external/tqdm.cpp /home/gmavros-yoga-7/CLionProjects/Lora-sim-cpp/cmake-build-debug/external/tqdm.cpp/CMakeFiles/tqdmlib.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : external/tqdm.cpp/CMakeFiles/tqdmlib.dir/depend

