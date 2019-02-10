# Name         SFA
# Author       Derek Blue
# Description  This is a makefile for compiling
#              the Structure Function Analysis(sfa) tool

# Set the compiler if not already set in the PATH
CXX          ?= g++

# Release install directory
INSTALL_DIR   = /usr/bin

# Project paths
SRC_DIR       = src
BUILD_DIR     = build
BIN_DIR       = $(BUILD_DIR)/bin
TEST_DIR      = test
TEST_BUILD    = $(TEST_DIR)/build
TEST_BIN      = $(TEST_BUILD)/bin
V_FILE        = VERSION
V_DIR         = /usr/share/sfa

# Project executable
BIN_NAME      = sfa
TEST_NAME     = gen_tests

# File extensions
SRC_EXT       = cpp
HEAD_EXT      = h

# File lists
# Find all source files in the source directory
# Sorted by most recently modified
SRC_FILES     = $(shell find $(SRC_DIR) -name '*.$(SRC_EXT)' | cut -f2-)
TEST_SRC      = $(shell find $(TEST_DIR) -name '*.$(SRC_EXT)' | cut -f2-)
# Set object names
# Must strip source directory and prepend build directory
OBJ_FILES     = $(SRC_FILES:$(SRC_DIR)/%.$(SRC_EXT)=$(BUILD_DIR)/%.o)
TEST_OBJ      = $(TEST_SRC:$(TEST_DIR)/%.$(SRC_EXT)=$(TEST_BUILD)/%.o)
# Set the dependency files for header dependencies
DEPS          = $(OBJ_FILES:.o=.d)

# Compiler flags
COMPILE_FLAGS = -Wall -Wextra -g 
LDFLAGS       = -std=c++17 -lstdc++fs
INCLUDES      = -I include/ -I /usr/local/include
# Space-separated pkg-config libraries
LIBS          = 

.PHONY: default_target
default_target: release

.PHONY: release
release: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS)
release: dirs
	@$(MAKE) all

.PHONY: dirs
dirs:
	@echo "Creating directtories"
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	@sudo mkdir -p $(V_DIR)

.PHONY: clean
clean: cleantests
	@echo "Deleting $(BIN_NAME) symlink"
	@$(RM) -r $(BIN_NAME)
	@echo "Deleting directories"
	@$(RM) -r $(BUILD_DIR)
	@$(RM) -r $(BIN_DIR)
	@echo "Deleting $(V_DIR)"
	@sudo $(RM) -r $(V_DIR)/$(V_FILE)
	@sudo $(RM) -R $(V_DIR)

# Check the executable and symlink to the output
.PHONY: all
all: $(BIN_DIR)/$(BIN_NAME)
	@echo "Making symlink: $(BIN_NAME) -> $<"
	@$(RM) $(BIN_NAME)
	@cp $(BIN_DIR)/$(BIN_NAME) $(BIN_NAME)
	@sudo cp $(V_FILE) $(V_DIR)/$(V_FILE)

# Create the executable
$(BIN_DIR)/$(BIN_NAME): $(OBJ_FILES)
	@echo "Linking: $@"
	$(CXX) $(OBJ_FILES) -o $@ $(LDFLAGS)

# Add dependency files, if they exist
-include $(DEPS)

# Source file rules
# After the first compilation they will be joined with
# the rules from the dependency files to provide header
# dependencies
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@ $(LDFLAGS)

############# TESTS #############

.PHONY: testdirs
testdirs:
	@echo "Creating testing directtories"
	@mkdir -p $(TEST_BUILD)
	@mkdir -p $(TEST_BIN)

.PHONY: cleantests
cleantests:
	@echo "Deleting $(TEST_NAME) symlink"
	@$(RM) -r $(TEST_NAME)
	@echo "Deleting any generated test input files"
	@$(RM) -r $(TEST_DIR)/*.in
	@echo "Deleting any generated test output files"
	@$(RM) -r $(TEST_DIR)/*.out
	@echo "Deleting directories"
	@$(RM) -R $(TEST_BUILD)
	@$(RM) -r $(TEST_BIN)

# Check the test executable and symlink to the output
.PHONY: tests
tests: release
tests: testdirs
	@$(MAKE) testbuild

.PHONY: testbuild
testbuild: $(TEST_BIN)/$(TEST_NAME)
	@echo "Making symlink: $(TEST_NAME) -> $<"
	@$(RM) $(TEST_NAME)
	@cp $(TEST_BIN)/$(TEST_NAME) $(TEST_NAME)

# Create the test executable
$(TEST_BIN)/$(TEST_NAME): $(TEST_OBJ)
	@echo "Linking: $@"
	$(CXX) $(TEST_OBJ) -o $@

$(TEST_BUILD)/%.o: $(TEST_DIR)/%.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@

# Proper install and uninstall
.PHONY: install
install: release
	@sudo cp $(BIN_NAME) $(INSTALL_DIR)/$(BIN_NAME)
	@sudo cp $(V_FILE) $(V_DIR)/$(V_FILE)

.PHONY: uninstall
uninstall:
	@sudo $(RM) -r $(INSTALL_DIR)/$(BIN_NAME)
	@sudo $(RM) -r $(V_DIR)/$(V_FILE)
