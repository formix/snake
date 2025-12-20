# Compiler and flags
CC = gcc
CFLAGS = -Wall
DEBUG_FLAGS = -g -O0
TARGET = snake
OUTDIR = out

# Check if DEBUG=1 is set
ifdef DEBUG
CFLAGS += $(DEBUG_FLAGS)
endif

# Source files
SRCS = main.c snake.c asciiart.c
OBJS = $(SRCS:%.c=$(OUTDIR)/%.o)

# Default target
all: $(OUTDIR)/$(TARGET)

# Create output directory
$(OUTDIR):
	mkdir -p $(OUTDIR)

# Link object files to create executable
$(OUTDIR)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Compile source files to object files
$(OUTDIR)/%.o: %.c | $(OUTDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OUTDIR)

# Phony targets
.PHONY: all clean debug

debug:
	$(MAKE) DEBUG=1

# Dependencies
$(OUTDIR)/main.o: main.c snake.h asciiart.h
$(OUTDIR)/snake.o: snake.c snake.h asciiart.h
$(OUTDIR)/asciiart.o: asciiart.c asciiart.h
