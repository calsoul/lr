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
include CMakeFiles/TestCachePool.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TestCachePool.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TestCachePool.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TestCachePool.dir/flags.make

CMakeFiles/TestCachePool.dir/thread_manager.cpp.o: CMakeFiles/TestCachePool.dir/flags.make
CMakeFiles/TestCachePool.dir/thread_manager.cpp.o: thread_manager.cpp
CMakeFiles/TestCachePool.dir/thread_manager.cpp.o: CMakeFiles/TestCachePool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/debian/lr/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TestCachePool.dir/thread_manager.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TestCachePool.dir/thread_manager.cpp.o -MF CMakeFiles/TestCachePool.dir/thread_manager.cpp.o.d -o CMakeFiles/TestCachePool.dir/thread_manager.cpp.o -c /home/debian/lr/test/thread_manager.cpp

CMakeFiles/TestCachePool.dir/thread_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestCachePool.dir/thread_manager.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/debian/lr/test/thread_manager.cpp > CMakeFiles/TestCachePool.dir/thread_manager.cpp.i

CMakeFiles/TestCachePool.dir/thread_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestCachePool.dir/thread_manager.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/debian/lr/test/thread_manager.cpp -o CMakeFiles/TestCachePool.dir/thread_manager.cpp.s

CMakeFiles/TestCachePool.dir/bi_cache_pool.cpp.o: CMakeFiles/TestCachePool.dir/flags.make
CMakeFiles/TestCachePool.dir/bi_cache_pool.cpp.o: bi_cache_pool.cpp
CMakeFiles/TestCachePool.dir/bi_cache_pool.cpp.o: CMakeFiles/TestCachePool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/debian/lr/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TestCachePool.dir/bi_cache_pool.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TestCachePool.dir/bi_cache_pool.cpp.o -MF CMakeFiles/TestCachePool.dir/bi_cache_pool.cpp.o.d -o CMakeFiles/TestCachePool.dir/bi_cache_pool.cpp.o -c /home/debian/lr/test/bi_cache_pool.cpp

CMakeFiles/TestCachePool.dir/bi_cache_pool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestCachePool.dir/bi_cache_pool.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/debian/lr/test/bi_cache_pool.cpp > CMakeFiles/TestCachePool.dir/bi_cache_pool.cpp.i

CMakeFiles/TestCachePool.dir/bi_cache_pool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestCachePool.dir/bi_cache_pool.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/debian/lr/test/bi_cache_pool.cpp -o CMakeFiles/TestCachePool.dir/bi_cache_pool.cpp.s

CMakeFiles/TestCachePool.dir/test_cache_pool.cpp.o: CMakeFiles/TestCachePool.dir/flags.make
CMakeFiles/TestCachePool.dir/test_cache_pool.cpp.o: test_cache_pool.cpp
CMakeFiles/TestCachePool.dir/test_cache_pool.cpp.o: CMakeFiles/TestCachePool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/debian/lr/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TestCachePool.dir/test_cache_pool.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TestCachePool.dir/test_cache_pool.cpp.o -MF CMakeFiles/TestCachePool.dir/test_cache_pool.cpp.o.d -o CMakeFiles/TestCachePool.dir/test_cache_pool.cpp.o -c /home/debian/lr/test/test_cache_pool.cpp

CMakeFiles/TestCachePool.dir/test_cache_pool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestCachePool.dir/test_cache_pool.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/debian/lr/test/test_cache_pool.cpp > CMakeFiles/TestCachePool.dir/test_cache_pool.cpp.i

CMakeFiles/TestCachePool.dir/test_cache_pool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestCachePool.dir/test_cache_pool.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/debian/lr/test/test_cache_pool.cpp -o CMakeFiles/TestCachePool.dir/test_cache_pool.cpp.s

# Object files for target TestCachePool
TestCachePool_OBJECTS = \
"CMakeFiles/TestCachePool.dir/thread_manager.cpp.o" \
"CMakeFiles/TestCachePool.dir/bi_cache_pool.cpp.o" \
"CMakeFiles/TestCachePool.dir/test_cache_pool.cpp.o"

# External object files for target TestCachePool
TestCachePool_EXTERNAL_OBJECTS =

TestCachePool: CMakeFiles/TestCachePool.dir/thread_manager.cpp.o
TestCachePool: CMakeFiles/TestCachePool.dir/bi_cache_pool.cpp.o
TestCachePool: CMakeFiles/TestCachePool.dir/test_cache_pool.cpp.o
TestCachePool: CMakeFiles/TestCachePool.dir/build.make
TestCachePool: CMakeFiles/TestCachePool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/debian/lr/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable TestCachePool"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestCachePool.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TestCachePool.dir/build: TestCachePool
.PHONY : CMakeFiles/TestCachePool.dir/build

CMakeFiles/TestCachePool.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TestCachePool.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TestCachePool.dir/clean

CMakeFiles/TestCachePool.dir/depend:
	cd /home/debian/lr/test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/debian/lr/test /home/debian/lr/test /home/debian/lr/test /home/debian/lr/test /home/debian/lr/test/CMakeFiles/TestCachePool.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TestCachePool.dir/depend

