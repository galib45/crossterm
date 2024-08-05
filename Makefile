# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra

# Directories
SRC_DIR = src
BIN_DIR = bin

# Default target
all: run

main: src/main.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $<

# Clean up build artifacts
clean:
	rm -rf $(BIN_DIR)

# Run the program
run: main
	$(BIN_DIR)/main

# Phony targets
.PHONY: all clean run
