# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/megn540/Desktop/MEGN540

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/megn540/Desktop/MEGN540

# Utility rule file for MEGN540.

# Include the progress variables for this target.
include CMakeFiles/MEGN540.dir/progress.make

CMakeFiles/MEGN540: libMEGN540-atmega32u4.a


MEGN540: CMakeFiles/MEGN540
MEGN540: CMakeFiles/MEGN540.dir/build.make

.PHONY : MEGN540

# Rule to build all files generated by this target.
CMakeFiles/MEGN540.dir/build: MEGN540

.PHONY : CMakeFiles/MEGN540.dir/build

CMakeFiles/MEGN540.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MEGN540.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MEGN540.dir/clean

CMakeFiles/MEGN540.dir/depend:
	cd /home/megn540/Desktop/MEGN540 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/megn540/Desktop/MEGN540 /home/megn540/Desktop/MEGN540 /home/megn540/Desktop/MEGN540 /home/megn540/Desktop/MEGN540 /home/megn540/Desktop/MEGN540/CMakeFiles/MEGN540.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MEGN540.dir/depend

