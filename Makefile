# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/zazu/Documents/MyProjects/StegTool

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zazu/Documents/MyProjects/StegTool

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/zazu/Documents/MyProjects/StegTool/CMakeFiles /home/zazu/Documents/MyProjects/StegTool/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/zazu/Documents/MyProjects/StegTool/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named StegTool

# Build rule for target.
StegTool: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 StegTool
.PHONY : StegTool

# fast build rule for target.
StegTool/fast:
	$(MAKE) -f CMakeFiles/StegTool.dir/build.make CMakeFiles/StegTool.dir/build
.PHONY : StegTool/fast

src/compression.o: src/compression.c.o

.PHONY : src/compression.o

# target to build an object file
src/compression.c.o:
	$(MAKE) -f CMakeFiles/StegTool.dir/build.make CMakeFiles/StegTool.dir/src/compression.c.o
.PHONY : src/compression.c.o

src/compression.i: src/compression.c.i

.PHONY : src/compression.i

# target to preprocess a source file
src/compression.c.i:
	$(MAKE) -f CMakeFiles/StegTool.dir/build.make CMakeFiles/StegTool.dir/src/compression.c.i
.PHONY : src/compression.c.i

src/compression.s: src/compression.c.s

.PHONY : src/compression.s

# target to generate assembly for a file
src/compression.c.s:
	$(MAKE) -f CMakeFiles/StegTool.dir/build.make CMakeFiles/StegTool.dir/src/compression.c.s
.PHONY : src/compression.c.s

src/image.o: src/image.c.o

.PHONY : src/image.o

# target to build an object file
src/image.c.o:
	$(MAKE) -f CMakeFiles/StegTool.dir/build.make CMakeFiles/StegTool.dir/src/image.c.o
.PHONY : src/image.c.o

src/image.i: src/image.c.i

.PHONY : src/image.i

# target to preprocess a source file
src/image.c.i:
	$(MAKE) -f CMakeFiles/StegTool.dir/build.make CMakeFiles/StegTool.dir/src/image.c.i
.PHONY : src/image.c.i

src/image.s: src/image.c.s

.PHONY : src/image.s

# target to generate assembly for a file
src/image.c.s:
	$(MAKE) -f CMakeFiles/StegTool.dir/build.make CMakeFiles/StegTool.dir/src/image.c.s
.PHONY : src/image.c.s

src/main.o: src/main.c.o

.PHONY : src/main.o

# target to build an object file
src/main.c.o:
	$(MAKE) -f CMakeFiles/StegTool.dir/build.make CMakeFiles/StegTool.dir/src/main.c.o
.PHONY : src/main.c.o

src/main.i: src/main.c.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.c.i:
	$(MAKE) -f CMakeFiles/StegTool.dir/build.make CMakeFiles/StegTool.dir/src/main.c.i
.PHONY : src/main.c.i

src/main.s: src/main.c.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.c.s:
	$(MAKE) -f CMakeFiles/StegTool.dir/build.make CMakeFiles/StegTool.dir/src/main.c.s
.PHONY : src/main.c.s

src/readPNG.o: src/readPNG.c.o

.PHONY : src/readPNG.o

# target to build an object file
src/readPNG.c.o:
	$(MAKE) -f CMakeFiles/StegTool.dir/build.make CMakeFiles/StegTool.dir/src/readPNG.c.o
.PHONY : src/readPNG.c.o

src/readPNG.i: src/readPNG.c.i

.PHONY : src/readPNG.i

# target to preprocess a source file
src/readPNG.c.i:
	$(MAKE) -f CMakeFiles/StegTool.dir/build.make CMakeFiles/StegTool.dir/src/readPNG.c.i
.PHONY : src/readPNG.c.i

src/readPNG.s: src/readPNG.c.s

.PHONY : src/readPNG.s

# target to generate assembly for a file
src/readPNG.c.s:
	$(MAKE) -f CMakeFiles/StegTool.dir/build.make CMakeFiles/StegTool.dir/src/readPNG.c.s
.PHONY : src/readPNG.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... StegTool"
	@echo "... edit_cache"
	@echo "... src/compression.o"
	@echo "... src/compression.i"
	@echo "... src/compression.s"
	@echo "... src/image.o"
	@echo "... src/image.i"
	@echo "... src/image.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/readPNG.o"
	@echo "... src/readPNG.i"
	@echo "... src/readPNG.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

