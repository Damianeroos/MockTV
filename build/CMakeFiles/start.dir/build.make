# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/damian/Pulpit/staz/MockTV

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/damian/Pulpit/staz/MockTV/build

# Utility rule file for start.

# Include the progress variables for this target.
include CMakeFiles/start.dir/progress.make

CMakeFiles/start:
	./tv_mock

start: CMakeFiles/start
start: CMakeFiles/start.dir/build.make

.PHONY : start

# Rule to build all files generated by this target.
CMakeFiles/start.dir/build: start

.PHONY : CMakeFiles/start.dir/build

CMakeFiles/start.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/start.dir/cmake_clean.cmake
.PHONY : CMakeFiles/start.dir/clean

CMakeFiles/start.dir/depend:
	cd /home/damian/Pulpit/staz/MockTV/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/damian/Pulpit/staz/MockTV /home/damian/Pulpit/staz/MockTV /home/damian/Pulpit/staz/MockTV/build /home/damian/Pulpit/staz/MockTV/build /home/damian/Pulpit/staz/MockTV/build/CMakeFiles/start.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/start.dir/depend
