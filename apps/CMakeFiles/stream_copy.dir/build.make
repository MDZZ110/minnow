# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = /home/chenz/data/minnow/apps

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chenz/data/minnow/apps

# Include any dependencies generated for this target.
include CMakeFiles/stream_copy.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/stream_copy.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/stream_copy.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/stream_copy.dir/flags.make

CMakeFiles/stream_copy.dir/bidirectional_stream_copy.o: CMakeFiles/stream_copy.dir/flags.make
CMakeFiles/stream_copy.dir/bidirectional_stream_copy.o: bidirectional_stream_copy.cc
CMakeFiles/stream_copy.dir/bidirectional_stream_copy.o: CMakeFiles/stream_copy.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chenz/data/minnow/apps/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/stream_copy.dir/bidirectional_stream_copy.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/stream_copy.dir/bidirectional_stream_copy.o -MF CMakeFiles/stream_copy.dir/bidirectional_stream_copy.o.d -o CMakeFiles/stream_copy.dir/bidirectional_stream_copy.o -c /home/chenz/data/minnow/apps/bidirectional_stream_copy.cc

CMakeFiles/stream_copy.dir/bidirectional_stream_copy.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/stream_copy.dir/bidirectional_stream_copy.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chenz/data/minnow/apps/bidirectional_stream_copy.cc > CMakeFiles/stream_copy.dir/bidirectional_stream_copy.i

CMakeFiles/stream_copy.dir/bidirectional_stream_copy.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/stream_copy.dir/bidirectional_stream_copy.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chenz/data/minnow/apps/bidirectional_stream_copy.cc -o CMakeFiles/stream_copy.dir/bidirectional_stream_copy.s

# Object files for target stream_copy
stream_copy_OBJECTS = \
"CMakeFiles/stream_copy.dir/bidirectional_stream_copy.o"

# External object files for target stream_copy
stream_copy_EXTERNAL_OBJECTS =

libstream_copy.a: CMakeFiles/stream_copy.dir/bidirectional_stream_copy.o
libstream_copy.a: CMakeFiles/stream_copy.dir/build.make
libstream_copy.a: CMakeFiles/stream_copy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/chenz/data/minnow/apps/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libstream_copy.a"
	$(CMAKE_COMMAND) -P CMakeFiles/stream_copy.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stream_copy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/stream_copy.dir/build: libstream_copy.a
.PHONY : CMakeFiles/stream_copy.dir/build

CMakeFiles/stream_copy.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/stream_copy.dir/cmake_clean.cmake
.PHONY : CMakeFiles/stream_copy.dir/clean

CMakeFiles/stream_copy.dir/depend:
	cd /home/chenz/data/minnow/apps && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chenz/data/minnow/apps /home/chenz/data/minnow/apps /home/chenz/data/minnow/apps /home/chenz/data/minnow/apps /home/chenz/data/minnow/apps/CMakeFiles/stream_copy.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/stream_copy.dir/depend
