# -*- MakeFile -*-

# Compiler
CC = gcc

# Executable name
TARGET = mycomp

# Source files
SRCS = mycomp.c complex.c string_utils.c

# Object files
OBJS = $(SRCS:.c=.o)

# Compilation flags
CFLAGS = -Wall -ansi -pedantic

# Debug flags
DEBUG_FLAGS = -g

# Default target
all: $(TARGET)

# Debug target
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

# Define dependencies for source files
mycomp.o: mycomp.c mycomp.h complex.h string_utils.h common_types.h
complex.o: complex.c complex.h string_utils.h common_types.h
string_utils.o: string_utils.c string_utils.h common_types.h

# Linking the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compiling individual source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	del /q $(OBJS) $(TARGET).exe

.PHONY: clean all
