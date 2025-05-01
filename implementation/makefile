# Makefile for open-LIN-c project with correct include paths
# For the directory structure:
#   ./source.c, ./source.h (parent dir)
#   ./implementation/makefile
#   ./implementation/test/ (test files)

# Compiler settings
CC = gcc
CXX = g++
AR = ar

# Directories
ROOT_DIR = ./../
BUILD_DIR = build
TEST_DIR = unit_test
LIB_DIR = lib

# Create build directories if they don't exist
$(shell mkdir -p $(BUILD_DIR) $(LIB_DIR))

# Flags - trying with absolute path for includes
ROOT_ABSOLUTE_PATH := $(shell cd $(ROOT_DIR) && pwd)
CFLAGS = -Wall -Wextra -std=c99 -I$(ROOT_ABSOLUTE_PATH)
CXXFLAGS = -Wall -Wextra -std=c++11 -I$(ROOT_ABSOLUTE_PATH) -I$(TEST_DIR)

# Get source files (C files in parent directory)
C_SOURCES := $(wildcard $(ROOT_DIR)/*.c)
C_OBJECTS := $(addprefix $(BUILD_DIR)/, $(notdir $(C_SOURCES:.c=.o)))

# Get test source files
TEST_SOURCES := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS := $(addprefix $(BUILD_DIR)/, $(notdir $(TEST_SOURCES:.cpp=.o)))

# Library name
LIB_NAME = openlin
LIB_STATIC = $(LIB_DIR)/lib$(LIB_NAME).a

# Test executable
TEST_EXECUTABLE = $(BUILD_DIR)/test_runner

# Default target
all: lib test

# Library target
lib: $(LIB_STATIC)

# Static library
$(LIB_STATIC): $(C_OBJECTS)
	$(AR) rcs $@ $^

# Pattern rule for building C objects from parent directory
$(BUILD_DIR)/%.o: $(ROOT_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Pattern rule for building C++ test objects
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build test runner
test: $(LIB_STATIC) $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TEST_EXECUTABLE) $(TEST_OBJECTS) $(LIB_STATIC)

# Run tests
run: test
	./$(TEST_EXECUTABLE)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)/*.o $(TEST_EXECUTABLE) $(LIB_STATIC)

# Phony targets
.PHONY: all lib test run clean info