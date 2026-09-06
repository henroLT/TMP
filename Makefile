CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic -I.

SRC_DIR := .
BIN_DIR := bin

SRCS := $(shell find $(SRC_DIR) -name "*.cpp")
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)
EXES := $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%)

all: $(EXES)

# Build a specific directory:
twoSum:
	$(MAKE) $(BIN_DIR)/twoSum/twoSum

threeSum:
	$(MAKE) $(BIN_DIR)/threeSum/threeSum

# link
$(BIN_DIR)/%: $(BIN_DIR)/%.o
	$(CXX) $< -o $@

# compile
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean twoSum threeSum