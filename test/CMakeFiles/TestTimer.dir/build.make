# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /home/debian/lr/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/debian/lr/test

# Include any dependencies generated for this target.
include CMakeFiles/TestTimer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TestTimer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TestTimer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TestTimer.dir/flags.make

CMakeFiles/TestTimer.dir/timer.cpp.o: CMakeFiles/TestTimer.dir/flags.make
CMakeFiles/TestTimer.dir/timer.cpp.o: timer.cpp
CMakeFiles/TestTimer.dir/timer.cpp.o: CMakeFiles/TestTimer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/debian/lr/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TestTimer.dir/timer.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TestTimer.dir/timer.cpp.o -MF CMakeFiles/TestTimer.dir/timer.cpp.o.d -o CMakeFiles/TestTimer.dir/timer.cpp.o -c /home/debian/lr/test/timer.cpp

CMakeFiles/TestTimer.dir/timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestTimer.dir/timer.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/debian/lr/test/timer.cpp > CMakeFiles/TestTimer.dir/timer.cpp.i

CMakeFiles/TestTimer.dir/timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestTimer.dir/timer.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/debian/lr/test/timer.cpp -o CMakeFiles/TestTimer.dir/timer.cpp.s

CMakeFiles/TestTimer.dir/thread_manager.cpp.o: CMakeFiles/TestTimer.dir/flags.make
CMakeFiles/TestTimer.dir/thread_manager.cpp.o: thread_manager.cpp
CMakeFiles/TestTimer.dir/thread_manager.cpp.o: CMakeFiles/TestTimer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/debian/lr/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TestTimer.dir/thread_manager.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TestTimer.dir/thread_manager.cpp.o -MF CMakeFiles/TestTimer.dir/thread_manager.cpp.o.d -o CMakeFiles/TestTimer.dir/thread_manager.cpp.o -c /home/debian/lr/test/thread_manager.cpp

CMakeFiles/TestTimer.dir/thread_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestTimer.dir/thread_manager.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/debian/lr/test/thread_manager.cpp > CMakeFiles/TestTimer.dir/thread_manager.cpp.i

CMakeFiles/TestTimer.dir/thread_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestTimer.dir/thread_manager.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/debian/lr/test/thread_manager.cpp -o CMakeFiles/TestTimer.dir/thread_manager.cpp.s

CMakeFiles/TestTimer.dir/line_configure.cpp.o: CMakeFiles/TestTimer.dir/flags.make
CMakeFiles/TestTimer.dir/line_configure.cpp.o: line_configure.cpp
CMakeFiles/TestTimer.dir/line_configure.cpp.o: CMakeFiles/TestTimer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/debian/lr/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TestTimer.dir/line_configure.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TestTimer.dir/line_configure.cpp.o -MF CMakeFiles/TestTimer.dir/line_configure.cpp.o.d -o CMakeFiles/TestTimer.dir/line_configure.cpp.o -c /home/debian/lr/test/line_configure.cpp

CMakeFiles/TestTimer.dir/line_configure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestTimer.dir/line_configure.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/debian/lr/test/line_configure.cpp > CMakeFiles/TestTimer.dir/line_configure.cpp.i

CMakeFiles/TestTimer.dir/line_configure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestTimer.dir/line_configure.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/debian/lr/test/line_configure.cpp -o CMakeFiles/TestTimer.dir/line_configure.cpp.s

CMakeFiles/TestTimer.dir/test_timer.cpp.o: CMakeFiles/TestTimer.dir/flags.make
CMakeFiles/TestTimer.dir/test_timer.cpp.o: test_timer.cpp
CMakeFiles/TestTimer.dir/test_timer.cpp.o: CMakeFiles/TestTimer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/debian/lr/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/TestTimer.dir/test_timer.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TestTimer.dir/test_timer.cpp.o -MF CMakeFiles/TestTimer.dir/test_timer.cpp.o.d -o CMakeFiles/TestTimer.dir/test_timer.cpp.o -c /home/debian/lr/test/test_timer.cpp

CMakeFiles/TestTimer.dir/test_timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestTimer.dir/test_timer.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/debian/lr/test/test_timer.cpp > CMakeFiles/TestTimer.dir/test_timer.cpp.i

CMakeFiles/TestTimer.dir/test_timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestTimer.dir/test_timer.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/debian/lr/test/test_timer.cpp -o CMakeFiles/TestTimer.dir/test_timer.cpp.s

# Object files for target TestTimer
TestTimer_OBJECTS = \
"CMakeFiles/TestTimer.dir/timer.cpp.o" \
"CMakeFiles/TestTimer.dir/thread_manager.cpp.o" \
"CMakeFiles/TestTimer.dir/line_configure.cpp.o" \
"CMakeFiles/TestTimer.dir/test_timer.cpp.o"

# External object files for target TestTimer
TestTimer_EXTERNAL_OBJECTS =

TestTimer: CMakeFiles/TestTimer.dir/timer.cpp.o
TestTimer: CMakeFiles/TestTimer.dir/thread_manager.cpp.o
TestTimer: CMakeFiles/TestTimer.dir/line_configure.cpp.o
TestTimer: CMakeFiles/TestTimer.dir/test_timer.cpp.o
TestTimer: CMakeFiles/TestTimer.dir/build.make
TestTimer: CMakeFiles/TestTimer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/debian/lr/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable TestTimer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestTimer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TestTimer.dir/build: TestTimer
.PHONY : CMakeFiles/TestTimer.dir/build

CMakeFiles/TestTimer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TestTimer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TestTimer.dir/clean

CMakeFiles/TestTimer.dir/depend:
	cd /home/debian/lr/test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/debian/lr/test /home/debian/lr/test /home/debian/lr/test /home/debian/lr/test /home/debian/lr/test/CMakeFiles/TestTimer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TestTimer.dir/depend

