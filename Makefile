# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lucas/wrk/learning/cpp/cmake-generator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lucas/wrk/learning/cpp/cmake-generator

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake cache editor..."
	/usr/local/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/usr/local/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/lucas/wrk/learning/cpp/cmake-generator/CMakeFiles /home/lucas/wrk/learning/cpp/cmake-generator//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/lucas/wrk/learning/cpp/cmake-generator/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named cmake-generator

# Build rule for target.
cmake-generator: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 cmake-generator
.PHONY : cmake-generator

# fast build rule for target.
cmake-generator/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/cmake-generator.dir/build.make CMakeFiles/cmake-generator.dir/build
.PHONY : cmake-generator/fast

src/CommandFlags.o: src/CommandFlags.cpp.o
.PHONY : src/CommandFlags.o

# target to build an object file
src/CommandFlags.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/cmake-generator.dir/build.make CMakeFiles/cmake-generator.dir/src/CommandFlags.cpp.o
.PHONY : src/CommandFlags.cpp.o

src/CommandFlags.i: src/CommandFlags.cpp.i
.PHONY : src/CommandFlags.i

# target to preprocess a source file
src/CommandFlags.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/cmake-generator.dir/build.make CMakeFiles/cmake-generator.dir/src/CommandFlags.cpp.i
.PHONY : src/CommandFlags.cpp.i

src/CommandFlags.s: src/CommandFlags.cpp.s
.PHONY : src/CommandFlags.s

# target to generate assembly for a file
src/CommandFlags.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/cmake-generator.dir/build.make CMakeFiles/cmake-generator.dir/src/CommandFlags.cpp.s
.PHONY : src/CommandFlags.cpp.s

src/CommandGeneral.o: src/CommandGeneral.cpp.o
.PHONY : src/CommandGeneral.o

# target to build an object file
src/CommandGeneral.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/cmake-generator.dir/build.make CMakeFiles/cmake-generator.dir/src/CommandGeneral.cpp.o
.PHONY : src/CommandGeneral.cpp.o

src/CommandGeneral.i: src/CommandGeneral.cpp.i
.PHONY : src/CommandGeneral.i

# target to preprocess a source file
src/CommandGeneral.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/cmake-generator.dir/build.make CMakeFiles/cmake-generator.dir/src/CommandGeneral.cpp.i
.PHONY : src/CommandGeneral.cpp.i

src/CommandGeneral.s: src/CommandGeneral.cpp.s
.PHONY : src/CommandGeneral.s

# target to generate assembly for a file
src/CommandGeneral.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/cmake-generator.dir/build.make CMakeFiles/cmake-generator.dir/src/CommandGeneral.cpp.s
.PHONY : src/CommandGeneral.cpp.s

src/CommandHelp.o: src/CommandHelp.cpp.o
.PHONY : src/CommandHelp.o

# target to build an object file
src/CommandHelp.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/cmake-generator.dir/build.make CMakeFiles/cmake-generator.dir/src/CommandHelp.cpp.o
.PHONY : src/CommandHelp.cpp.o

src/CommandHelp.i: src/CommandHelp.cpp.i
.PHONY : src/CommandHelp.i

# target to preprocess a source file
src/CommandHelp.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/cmake-generator.dir/build.make CMakeFiles/cmake-generator.dir/src/CommandHelp.cpp.i
.PHONY : src/CommandHelp.cpp.i

src/CommandHelp.s: src/CommandHelp.cpp.s
.PHONY : src/CommandHelp.s

# target to generate assembly for a file
src/CommandHelp.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/cmake-generator.dir/build.make CMakeFiles/cmake-generator.dir/src/CommandHelp.cpp.s
.PHONY : src/CommandHelp.cpp.s

src/CommandInit.o: src/CommandInit.cpp.o
.PHONY : src/CommandInit.o

# target to build an object file
src/CommandInit.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/cmake-generator.dir/build.make CMakeFiles/cmake-generator.dir/src/CommandInit.cpp.o
.PHONY : src/CommandInit.cpp.o

src/CommandInit.i: src/CommandInit.cpp.i
.PHONY : src/CommandInit.i

# target to preprocess a source file
src/CommandInit.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/cmake-generator.dir/build.make CMakeFiles/cmake-generator.dir/src/CommandInit.cpp.i
.PHONY : src/CommandInit.cpp.i

src/CommandInit.s: src/CommandInit.cpp.s
.PHONY : src/CommandInit.s

# target to generate assembly for a file
src/CommandInit.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/cmake-generator.dir/build.make CMakeFiles/cmake-generator.dir/src/CommandInit.cpp.s
.PHONY : src/CommandInit.cpp.s

src/CommandRun.o: src/CommandRun.cpp.o
.PHONY : src/CommandRun.o

# target to build an object file
src/CommandRun.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/cmake-generator.dir/build.make CMakeFiles/cmake-generator.dir/src/CommandRun.cpp.o
.PHONY : src/CommandRun.cpp.o

src/CommandRun.i: src/CommandRun.cpp.i
.PHONY : src/CommandRun.i

# target to preprocess a source file
src/CommandRun.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/cmake-generator.dir/build.make CMakeFiles/cmake-generator.dir/src/CommandRun.cpp.i
.PHONY : src/CommandRun.cpp.i

src/CommandRun.s: src/CommandRun.cpp.s
.PHONY : src/CommandRun.s

# target to generate assembly for a file
src/CommandRun.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/cmake-generator.dir/build.make CMakeFiles/cmake-generator.dir/src/CommandRun.cpp.s
.PHONY : src/CommandRun.cpp.s

src/main.o: src/main.cpp.o
.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/cmake-generator.dir/build.make CMakeFiles/cmake-generator.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/cmake-generator.dir/build.make CMakeFiles/cmake-generator.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/cmake-generator.dir/build.make CMakeFiles/cmake-generator.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... cmake-generator"
	@echo "... src/CommandFlags.o"
	@echo "... src/CommandFlags.i"
	@echo "... src/CommandFlags.s"
	@echo "... src/CommandGeneral.o"
	@echo "... src/CommandGeneral.i"
	@echo "... src/CommandGeneral.s"
	@echo "... src/CommandHelp.o"
	@echo "... src/CommandHelp.i"
	@echo "... src/CommandHelp.s"
	@echo "... src/CommandInit.o"
	@echo "... src/CommandInit.i"
	@echo "... src/CommandInit.s"
	@echo "... src/CommandRun.o"
	@echo "... src/CommandRun.i"
	@echo "... src/CommandRun.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

