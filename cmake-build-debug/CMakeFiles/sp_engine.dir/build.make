# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion 2022.3.3\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion 2022.3.3\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\krabu\Desktop\sp-engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\krabu\Desktop\sp-engine\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/sp_engine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/sp_engine.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/sp_engine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sp_engine.dir/flags.make

CMakeFiles/sp_engine.dir/src/main.c.obj: CMakeFiles/sp_engine.dir/flags.make
CMakeFiles/sp_engine.dir/src/main.c.obj: CMakeFiles/sp_engine.dir/includes_C.rsp
CMakeFiles/sp_engine.dir/src/main.c.obj: C:/Users/krabu/Desktop/sp-engine/src/main.c
CMakeFiles/sp_engine.dir/src/main.c.obj: CMakeFiles/sp_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\krabu\Desktop\sp-engine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/sp_engine.dir/src/main.c.obj"
	C:\msys64\mingw64\bin\cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/sp_engine.dir/src/main.c.obj -MF CMakeFiles\sp_engine.dir\src\main.c.obj.d -o CMakeFiles\sp_engine.dir\src\main.c.obj -c C:\Users\krabu\Desktop\sp-engine\src\main.c

CMakeFiles/sp_engine.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sp_engine.dir/src/main.c.i"
	C:\msys64\mingw64\bin\cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\krabu\Desktop\sp-engine\src\main.c > CMakeFiles\sp_engine.dir\src\main.c.i

CMakeFiles/sp_engine.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sp_engine.dir/src/main.c.s"
	C:\msys64\mingw64\bin\cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\krabu\Desktop\sp-engine\src\main.c -o CMakeFiles\sp_engine.dir\src\main.c.s

# Object files for target sp_engine
sp_engine_OBJECTS = \
"CMakeFiles/sp_engine.dir/src/main.c.obj"

# External object files for target sp_engine
sp_engine_EXTERNAL_OBJECTS =

sp_engine.exe: CMakeFiles/sp_engine.dir/src/main.c.obj
sp_engine.exe: CMakeFiles/sp_engine.dir/build.make
sp_engine.exe: CMakeFiles/sp_engine.dir/linklibs.rsp
sp_engine.exe: CMakeFiles/sp_engine.dir/objects1.rsp
sp_engine.exe: CMakeFiles/sp_engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\krabu\Desktop\sp-engine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable sp_engine.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\sp_engine.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sp_engine.dir/build: sp_engine.exe
.PHONY : CMakeFiles/sp_engine.dir/build

CMakeFiles/sp_engine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\sp_engine.dir\cmake_clean.cmake
.PHONY : CMakeFiles/sp_engine.dir/clean

CMakeFiles/sp_engine.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\krabu\Desktop\sp-engine C:\Users\krabu\Desktop\sp-engine C:\Users\krabu\Desktop\sp-engine\cmake-build-debug C:\Users\krabu\Desktop\sp-engine\cmake-build-debug C:\Users\krabu\Desktop\sp-engine\cmake-build-debug\CMakeFiles\sp_engine.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sp_engine.dir/depend
