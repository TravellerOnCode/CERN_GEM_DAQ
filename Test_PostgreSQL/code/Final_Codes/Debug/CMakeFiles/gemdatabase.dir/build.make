# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/Final_Codes

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/Final_Codes/Debug

# Include any dependencies generated for this target.
include CMakeFiles/gemdatabase.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gemdatabase.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gemdatabase.dir/flags.make

CMakeFiles/gemdatabase.dir/main.cpp.o: CMakeFiles/gemdatabase.dir/flags.make
CMakeFiles/gemdatabase.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/Final_Codes/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gemdatabase.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gemdatabase.dir/main.cpp.o -c /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/Final_Codes/main.cpp

CMakeFiles/gemdatabase.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gemdatabase.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/Final_Codes/main.cpp > CMakeFiles/gemdatabase.dir/main.cpp.i

CMakeFiles/gemdatabase.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gemdatabase.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/Final_Codes/main.cpp -o CMakeFiles/gemdatabase.dir/main.cpp.s

CMakeFiles/gemdatabase.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/gemdatabase.dir/main.cpp.o.requires

CMakeFiles/gemdatabase.dir/main.cpp.o.provides: CMakeFiles/gemdatabase.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/gemdatabase.dir/build.make CMakeFiles/gemdatabase.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/gemdatabase.dir/main.cpp.o.provides

CMakeFiles/gemdatabase.dir/main.cpp.o.provides.build: CMakeFiles/gemdatabase.dir/main.cpp.o


# Object files for target gemdatabase
gemdatabase_OBJECTS = \
"CMakeFiles/gemdatabase.dir/main.cpp.o"

# External object files for target gemdatabase
gemdatabase_EXTERNAL_OBJECTS =

gemdatabase: CMakeFiles/gemdatabase.dir/main.cpp.o
gemdatabase: CMakeFiles/gemdatabase.dir/build.make
gemdatabase: liblibrary.a
gemdatabase: CMakeFiles/gemdatabase.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/Final_Codes/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable gemdatabase"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gemdatabase.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gemdatabase.dir/build: gemdatabase

.PHONY : CMakeFiles/gemdatabase.dir/build

CMakeFiles/gemdatabase.dir/requires: CMakeFiles/gemdatabase.dir/main.cpp.o.requires

.PHONY : CMakeFiles/gemdatabase.dir/requires

CMakeFiles/gemdatabase.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gemdatabase.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gemdatabase.dir/clean

CMakeFiles/gemdatabase.dir/depend:
	cd /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/Final_Codes/Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/Final_Codes /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/Final_Codes /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/Final_Codes/Debug /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/Final_Codes/Debug /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/Final_Codes/Debug/CMakeFiles/gemdatabase.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gemdatabase.dir/depend

