# Makefile for LRanalyzer Project
# Author: Nylls Boutoto, 2025

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra

# Target executable
TARGET = LRanalyzer

# Source files
SRC = *.c

# Default rule
all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Clean rule
clean:
	rm -f $(TARGET)

.PHONY: all clean
