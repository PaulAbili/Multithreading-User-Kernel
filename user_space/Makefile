#
# A simple makefile for managing build of project composed of C source files.
#

# Variables
CC = gcc                # Compiler to use

# The CFLAGS variable sets compile flags for gcc:
#  -g        compile with debug information
#  -Wall     give verbose compiler warnings
#  -O0       do not optimize generated code
#  -std=c99  use the C99 standard language definition
CFLAGS = -g -Wall -O0 -std=c99 -pthread

# In this section, you list the files that are part of the project.
# If you add/change names of source files, here is where you
# edit the Makefile.

TARGET = main     # Output file name
SRCS = main.c    # Source files
OBJS = $(SRCS:.c=.o)    # Object files (automatically replaces .c with .o)


# The first target defined in the makefile is the one
# used when make is invoked with no argument. Given the definitions
# above, this Makefile file will build the one named TARGET and
# assume that it depends on all the named OBJECTS files.

# Default target

all: $(TARGET)

# Linking step (combine object files into the final program)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Phony means not a "real" target, it doesn't build anything
# The phony target "clean" is used to remove all compiled object files.

.PHONY: clean

# Clean build (removes generated files)

clean:
	rm -f $(OBJS) $(TARGET) core

run: utest
	./utest
