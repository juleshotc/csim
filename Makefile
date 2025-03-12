# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g3
LDFLAGS = -lncurses

# Directories
SRCDIR = src
OBJDIR = obj
TARGET = csim-executable  # Name your executable here

# Automatically find source files recursively and create object file names
SOURCES = $(shell find $(SRCDIR) -name '*.c')
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean
