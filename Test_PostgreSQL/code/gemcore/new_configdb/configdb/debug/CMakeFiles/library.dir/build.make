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
CMAKE_SOURCE_DIR = /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb/debug

# Include any dependencies generated for this target.
include CMakeFiles/library.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/library.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/library.dir/flags.make

CMakeFiles/library.dir/src/database_utils.cpp.o: CMakeFiles/library.dir/flags.make
CMakeFiles/library.dir/src/database_utils.cpp.o: ../src/database_utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/library.dir/src/database_utils.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/library.dir/src/database_utils.cpp.o -c /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb/src/database_utils.cpp

CMakeFiles/library.dir/src/database_utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/library.dir/src/database_utils.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb/src/database_utils.cpp > CMakeFiles/library.dir/src/database_utils.cpp.i

CMakeFiles/library.dir/src/database_utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/library.dir/src/database_utils.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb/src/database_utils.cpp -o CMakeFiles/library.dir/src/database_utils.cpp.s

CMakeFiles/library.dir/src/database_utils.cpp.o.requires:

.PHONY : CMakeFiles/library.dir/src/database_utils.cpp.o.requires

CMakeFiles/library.dir/src/database_utils.cpp.o.provides: CMakeFiles/library.dir/src/database_utils.cpp.o.requires
	$(MAKE) -f CMakeFiles/library.dir/build.make CMakeFiles/library.dir/src/database_utils.cpp.o.provides.build
.PHONY : CMakeFiles/library.dir/src/database_utils.cpp.o.provides

CMakeFiles/library.dir/src/database_utils.cpp.o.provides.build: CMakeFiles/library.dir/src/database_utils.cpp.o


CMakeFiles/library.dir/src/vfat_configurations.cpp.o: CMakeFiles/library.dir/flags.make
CMakeFiles/library.dir/src/vfat_configurations.cpp.o: ../src/vfat_configurations.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/library.dir/src/vfat_configurations.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/library.dir/src/vfat_configurations.cpp.o -c /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb/src/vfat_configurations.cpp

CMakeFiles/library.dir/src/vfat_configurations.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/library.dir/src/vfat_configurations.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb/src/vfat_configurations.cpp > CMakeFiles/library.dir/src/vfat_configurations.cpp.i

CMakeFiles/library.dir/src/vfat_configurations.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/library.dir/src/vfat_configurations.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb/src/vfat_configurations.cpp -o CMakeFiles/library.dir/src/vfat_configurations.cpp.s

CMakeFiles/library.dir/src/vfat_configurations.cpp.o.requires:

.PHONY : CMakeFiles/library.dir/src/vfat_configurations.cpp.o.requires

CMakeFiles/library.dir/src/vfat_configurations.cpp.o.provides: CMakeFiles/library.dir/src/vfat_configurations.cpp.o.requires
	$(MAKE) -f CMakeFiles/library.dir/build.make CMakeFiles/library.dir/src/vfat_configurations.cpp.o.provides.build
.PHONY : CMakeFiles/library.dir/src/vfat_configurations.cpp.o.provides

CMakeFiles/library.dir/src/vfat_configurations.cpp.o.provides.build: CMakeFiles/library.dir/src/vfat_configurations.cpp.o


CMakeFiles/library.dir/src/vfat_settings.cpp.o: CMakeFiles/library.dir/flags.make
CMakeFiles/library.dir/src/vfat_settings.cpp.o: ../src/vfat_settings.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/library.dir/src/vfat_settings.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/library.dir/src/vfat_settings.cpp.o -c /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb/src/vfat_settings.cpp

CMakeFiles/library.dir/src/vfat_settings.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/library.dir/src/vfat_settings.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb/src/vfat_settings.cpp > CMakeFiles/library.dir/src/vfat_settings.cpp.i

CMakeFiles/library.dir/src/vfat_settings.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/library.dir/src/vfat_settings.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb/src/vfat_settings.cpp -o CMakeFiles/library.dir/src/vfat_settings.cpp.s

CMakeFiles/library.dir/src/vfat_settings.cpp.o.requires:

.PHONY : CMakeFiles/library.dir/src/vfat_settings.cpp.o.requires

CMakeFiles/library.dir/src/vfat_settings.cpp.o.provides: CMakeFiles/library.dir/src/vfat_settings.cpp.o.requires
	$(MAKE) -f CMakeFiles/library.dir/build.make CMakeFiles/library.dir/src/vfat_settings.cpp.o.provides.build
.PHONY : CMakeFiles/library.dir/src/vfat_settings.cpp.o.provides

CMakeFiles/library.dir/src/vfat_settings.cpp.o.provides.build: CMakeFiles/library.dir/src/vfat_settings.cpp.o


CMakeFiles/library.dir/src/vfat_indexes.cpp.o: CMakeFiles/library.dir/flags.make
CMakeFiles/library.dir/src/vfat_indexes.cpp.o: ../src/vfat_indexes.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/library.dir/src/vfat_indexes.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/library.dir/src/vfat_indexes.cpp.o -c /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb/src/vfat_indexes.cpp

CMakeFiles/library.dir/src/vfat_indexes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/library.dir/src/vfat_indexes.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb/src/vfat_indexes.cpp > CMakeFiles/library.dir/src/vfat_indexes.cpp.i

CMakeFiles/library.dir/src/vfat_indexes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/library.dir/src/vfat_indexes.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb/src/vfat_indexes.cpp -o CMakeFiles/library.dir/src/vfat_indexes.cpp.s

CMakeFiles/library.dir/src/vfat_indexes.cpp.o.requires:

.PHONY : CMakeFiles/library.dir/src/vfat_indexes.cpp.o.requires

CMakeFiles/library.dir/src/vfat_indexes.cpp.o.provides: CMakeFiles/library.dir/src/vfat_indexes.cpp.o.requires
	$(MAKE) -f CMakeFiles/library.dir/build.make CMakeFiles/library.dir/src/vfat_indexes.cpp.o.provides.build
.PHONY : CMakeFiles/library.dir/src/vfat_indexes.cpp.o.provides

CMakeFiles/library.dir/src/vfat_indexes.cpp.o.provides.build: CMakeFiles/library.dir/src/vfat_indexes.cpp.o


# Object files for target library
library_OBJECTS = \
"CMakeFiles/library.dir/src/database_utils.cpp.o" \
"CMakeFiles/library.dir/src/vfat_configurations.cpp.o" \
"CMakeFiles/library.dir/src/vfat_settings.cpp.o" \
"CMakeFiles/library.dir/src/vfat_indexes.cpp.o"

# External object files for target library
library_EXTERNAL_OBJECTS =

liblibrary.a: CMakeFiles/library.dir/src/database_utils.cpp.o
liblibrary.a: CMakeFiles/library.dir/src/vfat_configurations.cpp.o
liblibrary.a: CMakeFiles/library.dir/src/vfat_settings.cpp.o
liblibrary.a: CMakeFiles/library.dir/src/vfat_indexes.cpp.o
liblibrary.a: CMakeFiles/library.dir/build.make
liblibrary.a: CMakeFiles/library.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library liblibrary.a"
	$(CMAKE_COMMAND) -P CMakeFiles/library.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/library.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/library.dir/build: liblibrary.a

.PHONY : CMakeFiles/library.dir/build

CMakeFiles/library.dir/requires: CMakeFiles/library.dir/src/database_utils.cpp.o.requires
CMakeFiles/library.dir/requires: CMakeFiles/library.dir/src/vfat_configurations.cpp.o.requires
CMakeFiles/library.dir/requires: CMakeFiles/library.dir/src/vfat_settings.cpp.o.requires
CMakeFiles/library.dir/requires: CMakeFiles/library.dir/src/vfat_indexes.cpp.o.requires

.PHONY : CMakeFiles/library.dir/requires

CMakeFiles/library.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/library.dir/cmake_clean.cmake
.PHONY : CMakeFiles/library.dir/clean

CMakeFiles/library.dir/depend:
	cd /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb/debug /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb/debug /home/chakraborty/My_Workspace/Data_Acquisition/Test_PostgreSQL/code/gemcore/new_configdb/configdb/debug/CMakeFiles/library.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/library.dir/depend

