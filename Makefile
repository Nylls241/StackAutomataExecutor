# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Target executable
TARGET = AP

# Source files
SRCS = stack.c automaton.c main.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
    rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all Clean