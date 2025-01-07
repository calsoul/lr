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
include CMakeFiles/TestReactorEventQueue.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TestReactorEventQueue.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TestReactorEventQueue.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TestReactorEventQueue.dir/flags.make

CMakeFiles/TestReactorEventQueue.dir/thread_manager.cpp.o: CMakeFiles/TestReactorEventQueue.dir/flags.make
CMakeFiles/TestReactorEventQueue.dir/thread_manager.cpp.o: thread_manager.cpp
CMakeFiles/TestReactorEventQueue.dir/thread_manager.cpp.o: CMakeFiles/TestReactorEventQueue.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/debian/lr/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TestReactorEventQueue.dir/thread_manager.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TestReactorEventQueue.dir/thread_manager.cpp.o -MF CMakeFiles/TestReactorEventQueue.dir/thread_manager.cpp.o.d -o CMakeFiles/TestReactorEventQueue.dir/thread_manager.cpp.o -c /home/debian/lr/test/thread_manager.cpp

CMakeFiles/TestReactorEventQueue.dir/thread_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestReactorEventQueue.dir/thread_manager.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/debian/lr/test/thread_manager.cpp > CMakeFiles/TestReactorEventQueue.dir/thread_manager.cpp.i

CMakeFiles/TestReactorEventQueue.dir/thread_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestReactorEventQueue.dir/thread_manager.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/debian/lr/test/thread_manager.cpp -o CMakeFiles/TestReactorEventQueue.dir/thread_manager.cpp.s

CMakeFiles/TestReactorEventQueue.dir/reactor_event_queue.cpp.o: CMakeFiles/TestReactorEventQueue.dir/flags.make
CMakeFiles/TestReactorEventQueue.dir/reactor_event_queue.cpp.o: reactor_event_queue.cpp
CMakeFiles/TestReactorEventQueue.dir/reactor_event_queue.cpp.o: CMakeFiles/TestReactorEventQueue.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/debian/lr/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TestReactorEventQueue.dir/reactor_event_queue.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TestReactorEventQueue.dir/reactor_event_queue.cpp.o -MF CMakeFiles/TestReactorEventQueue.dir/reactor_event_queue.cpp.o.d -o CMakeFiles/TestReactorEventQueue.dir/reactor_event_queue.cpp.o -c /home/debian/lr/test/reactor_event_queue.cpp

CMakeFiles/TestReactorEventQueue.dir/reactor_event_queue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestReactorEventQueue.dir/reactor_event_queue.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/debian/lr/test/reactor_event_queue.cpp > CMakeFiles/TestReactorEventQueue.dir/reactor_event_queue.cpp.i

CMakeFiles/TestReactorEventQueue.dir/reactor_event_queue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestReactorEventQueue.dir/reactor_event_queue.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/debian/lr/test/reactor_event_queue.cpp -o CMakeFiles/TestReactorEventQueue.dir/reactor_event_queue.cpp.s

CMakeFiles/TestReactorEventQueue.dir/endian_event_queue.cpp.o: CMakeFiles/TestReactorEventQueue.dir/flags.make
CMakeFiles/TestReactorEventQueue.dir/endian_event_queue.cpp.o: endian_event_queue.cpp
CMakeFiles/TestReactorEventQueue.dir/endian_event_queue.cpp.o: CMakeFiles/TestReactorEventQueue.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/debian/lr/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TestReactorEventQueue.dir/endian_event_queue.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TestReactorEventQueue.dir/endian_event_queue.cpp.o -MF CMakeFiles/TestReactorEventQueue.dir/endian_event_queue.cpp.o.d -o CMakeFiles/TestReactorEventQueue.dir/endian_event_queue.cpp.o -c /home/debian/lr/test/endian_event_queue.cpp

CMakeFiles/TestReactorEventQueue.dir/endian_event_queue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestReactorEventQueue.dir/endian_event_queue.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/debian/lr/test/endian_event_queue.cpp > CMakeFiles/TestReactorEventQueue.dir/endian_event_queue.cpp.i

CMakeFiles/TestReactorEventQueue.dir/endian_event_queue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestReactorEventQueue.dir/endian_event_queue.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/debian/lr/test/endian_event_queue.cpp -o CMakeFiles/TestReactorEventQueue.dir/endian_event_queue.cpp.s

CMakeFiles/TestReactorEventQueue.dir/test_reactor_event_queue.cpp.o: CMakeFiles/TestReactorEventQueue.dir/flags.make
CMakeFiles/TestReactorEventQueue.dir/test_reactor_event_queue.cpp.o: test_reactor_event_queue.cpp
CMakeFiles/TestReactorEventQueue.dir/test_reactor_event_queue.cpp.o: CMakeFiles/TestReactorEventQueue.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/debian/lr/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/TestReactorEventQueue.dir/test_reactor_event_queue.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TestReactorEventQueue.dir/test_reactor_event_queue.cpp.o -MF CMakeFiles/TestReactorEventQueue.dir/test_reactor_event_queue.cpp.o.d -o CMakeFiles/TestReactorEventQueue.dir/test_reactor_event_queue.cpp.o -c /home/debian/lr/test/test_reactor_event_queue.cpp

CMakeFiles/TestReactorEventQueue.dir/test_reactor_event_queue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestReactorEventQueue.dir/test_reactor_event_queue.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/debian/lr/test/test_reactor_event_queue.cpp > CMakeFiles/TestReactorEventQueue.dir/test_reactor_event_queue.cpp.i

CMakeFiles/TestReactorEventQueue.dir/test_reactor_event_queue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestReactorEventQueue.dir/test_reactor_event_queue.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/debian/lr/test/test_reactor_event_queue.cpp -o CMakeFiles/TestReactorEventQueue.dir/test_reactor_event_queue.cpp.s

# Object files for target TestReactorEventQueue
TestReactorEventQueue_OBJECTS = \
"CMakeFiles/TestReactorEventQueue.dir/thread_manager.cpp.o" \
"CMakeFiles/TestReactorEventQueue.dir/reactor_event_queue.cpp.o" \
"CMakeFiles/TestReactorEventQueue.dir/endian_event_queue.cpp.o" \
"CMakeFiles/TestReactorEventQueue.dir/test_reactor_event_queue.cpp.o"

# External object files for target TestReactorEventQueue
TestReactorEventQueue_EXTERNAL_OBJECTS =

TestReactorEventQueue: CMakeFiles/TestReactorEventQueue.dir/thread_manager.cpp.o
TestReactorEventQueue: CMakeFiles/TestReactorEventQueue.dir/reactor_event_queue.cpp.o
TestReactorEventQueue: CMakeFiles/TestReactorEventQueue.dir/endian_event_queue.cpp.o
TestReactorEventQueue: CMakeFiles/TestReactorEventQueue.dir/test_reactor_event_queue.cpp.o
TestReactorEventQueue: CMakeFiles/TestReactorEventQueue.dir/build.make
TestReactorEventQueue: CMakeFiles/TestReactorEventQueue.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/debian/lr/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable TestReactorEventQueue"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestReactorEventQueue.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TestReactorEventQueue.dir/build: TestReactorEventQueue
.PHONY : CMakeFiles/TestReactorEventQueue.dir/build

CMakeFiles/TestReactorEventQueue.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TestReactorEventQueue.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TestReactorEventQueue.dir/clean

CMakeFiles/TestReactorEventQueue.dir/depend:
	cd /home/debian/lr/test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/debian/lr/test /home/debian/lr/test /home/debian/lr/test /home/debian/lr/test /home/debian/lr/test/CMakeFiles/TestReactorEventQueue.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TestReactorEventQueue.dir/depend

