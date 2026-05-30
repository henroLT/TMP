CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic

SRC_DIR := .
BIN_DIR := bin

SRCS := $(shell find $(SRC_DIR) -name "*.cpp")

OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)
EXES := $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%)

all: $(EXES)

# link: bin/x (executable)
$(BIN_DIR)/%: $(BIN_DIR)/%.o
	$(CXX) $< -o $@

# compile: cpp -> bin/x.o
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean