# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /snap/clion/35/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/35/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/qiansucheng/Downloads/http_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/qiansucheng/Downloads/http_server/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/webServer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/webServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/webServer.dir/flags.make

CMakeFiles/webServer.dir/https_example.cpp.o: CMakeFiles/webServer.dir/flags.make
CMakeFiles/webServer.dir/https_example.cpp.o: ../https_example.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/qiansucheng/Downloads/http_server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/webServer.dir/https_example.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webServer.dir/https_example.cpp.o -c /home/qiansucheng/Downloads/http_server/https_example.cpp

CMakeFiles/webServer.dir/https_example.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webServer.dir/https_example.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/qiansucheng/Downloads/http_server/https_example.cpp > CMakeFiles/webServer.dir/https_example.cpp.i

CMakeFiles/webServer.dir/https_example.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webServer.dir/https_example.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/qiansucheng/Downloads/http_server/https_example.cpp -o CMakeFiles/webServer.dir/https_example.cpp.s

# Object files for target webServer
webServer_OBJECTS = \
"CMakeFiles/webServer.dir/https_example.cpp.o"

# External object files for target webServer
webServer_EXTERNAL_OBJECTS =

webServer: CMakeFiles/webServer.dir/https_example.cpp.o
webServer: CMakeFiles/webServer.dir/build.make
webServer: /usr/lib/x86_64-linux-gnu/libboost_system.so
webServer: /usr/lib/x86_64-linux-gnu/libboost_thread.so
webServer: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
webServer: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
webServer: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
webServer: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
webServer: CMakeFiles/webServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/qiansucheng/Downloads/http_server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable webServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/webServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/webServer.dir/build: webServer

.PHONY : CMakeFiles/webServer.dir/build

CMakeFiles/webServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/webServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/webServer.dir/clean

CMakeFiles/webServer.dir/depend:
	cd /home/qiansucheng/Downloads/http_server/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/qiansucheng/Downloads/http_server /home/qiansucheng/Downloads/http_server /home/qiansucheng/Downloads/http_server/cmake-build-debug /home/qiansucheng/Downloads/http_server/cmake-build-debug /home/qiansucheng/Downloads/http_server/cmake-build-debug/CMakeFiles/webServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/webServer.dir/depend

