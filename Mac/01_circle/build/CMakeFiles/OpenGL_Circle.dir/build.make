# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.20.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.20.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/01_circle

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/01_circle/build

# Include any dependencies generated for this target.
include CMakeFiles/OpenGL_Circle.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/OpenGL_Circle.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/OpenGL_Circle.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OpenGL_Circle.dir/flags.make

CMakeFiles/OpenGL_Circle.dir/main.cpp.o: CMakeFiles/OpenGL_Circle.dir/flags.make
CMakeFiles/OpenGL_Circle.dir/main.cpp.o: ../main.cpp
CMakeFiles/OpenGL_Circle.dir/main.cpp.o: CMakeFiles/OpenGL_Circle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/01_circle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OpenGL_Circle.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OpenGL_Circle.dir/main.cpp.o -MF CMakeFiles/OpenGL_Circle.dir/main.cpp.o.d -o CMakeFiles/OpenGL_Circle.dir/main.cpp.o -c /Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/01_circle/main.cpp

CMakeFiles/OpenGL_Circle.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenGL_Circle.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/01_circle/main.cpp > CMakeFiles/OpenGL_Circle.dir/main.cpp.i

CMakeFiles/OpenGL_Circle.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenGL_Circle.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/01_circle/main.cpp -o CMakeFiles/OpenGL_Circle.dir/main.cpp.s

# Object files for target OpenGL_Circle
OpenGL_Circle_OBJECTS = \
"CMakeFiles/OpenGL_Circle.dir/main.cpp.o"

# External object files for target OpenGL_Circle
OpenGL_Circle_EXTERNAL_OBJECTS =

OpenGL_Circle: CMakeFiles/OpenGL_Circle.dir/main.cpp.o
OpenGL_Circle: CMakeFiles/OpenGL_Circle.dir/build.make
OpenGL_Circle: /usr/local/Cellar/glfw/3.4/lib/libglfw.3.4.dylib
OpenGL_Circle: /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.0.dylib
OpenGL_Circle: CMakeFiles/OpenGL_Circle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/01_circle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable OpenGL_Circle"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OpenGL_Circle.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OpenGL_Circle.dir/build: OpenGL_Circle
.PHONY : CMakeFiles/OpenGL_Circle.dir/build

CMakeFiles/OpenGL_Circle.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OpenGL_Circle.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OpenGL_Circle.dir/clean

CMakeFiles/OpenGL_Circle.dir/depend:
	cd /Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/01_circle/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/01_circle /Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/01_circle /Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/01_circle/build /Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/01_circle/build /Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/01_circle/build/CMakeFiles/OpenGL_Circle.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OpenGL_Circle.dir/depend

