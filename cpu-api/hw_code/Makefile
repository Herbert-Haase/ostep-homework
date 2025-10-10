# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -std=c11 -pedantic

# Automatically find all source files and corresponding object files
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

# Default target: Name executable based on the directory name
EXEC = $(notdir $(CURDIR))

# Build the default target
all: $(EXEC)

# Rule to create the executable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to create object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(EXEC) $(OBJ)

# Phony targets to avoid conflicts with files named "all" or "clean"
.PHONY: all clean
