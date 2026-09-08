CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic \
            -I. \
            -ILeetCode

SRC_DIR := .
BIN_DIR := bin

SRCS := $(shell find $(SRC_DIR) -name "*.cpp" -not -path "./$(BIN_DIR)/*")
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)
EXES := $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%)

all: $(EXES)

# Link
$(BIN_DIR)/%: $(BIN_DIR)/%.o
	@mkdir -p $(dir $@)
	$(CXX) $< -o $@

# Compile
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean