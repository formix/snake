# Compiler and flags
CC = gcc
CFLAGS = -Wall
DEBUG_FLAGS = -g -O0
TARGET = snake
SRCDIR = src
OUTDIR = out
DOCDIR = $(OUTDIR)/doc

# Check if DEBUG=1 is set
ifdef DEBUG
CFLAGS += $(DEBUG_FLAGS)
endif

# Source files
SRCS = $(SRCDIR)/main.c $(SRCDIR)/snake.c $(SRCDIR)/asciiart.c
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OUTDIR)/%.o)

# Default target
all: $(OUTDIR)/$(TARGET)

# Create output directory
$(OUTDIR):
	mkdir -p $(OUTDIR)

# Link object files to create executable
$(OUTDIR)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Compile source files to object files
$(OUTDIR)/%.o: $(SRCDIR)/%.c | $(OUTDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OUTDIR)

# Generate HTML documentation
$(DOCDIR)/html/index.html: $(SRCDIR)/*.c $(SRCDIR)/*.h README.md Doxyfile
	@echo "Generating HTML documentation..."
	@mkdir -p $(DOCDIR)
	@doxygen Doxyfile

# Documentation target
doc: $(DOCDIR)/html/index.html
	@echo "Documentation generated in $(DOCDIR)/html/index.html"

# Publish documentation to GitHub Pages
publish-doc:
	@echo "Copying documentation to ../snake-doc..."
	@mkdir -p ../snake-doc
	@cp -r $(DOCDIR)/html/* ../snake-doc/
	@cp LICENSE.txt ../snake-doc/
	@echo "Documentation copied to ../snake-doc"
	@echo "Committing and pushing documentation..."
	@cd ../snake-doc && \
		git add -A && \
		git commit -m "Update documentation $$(date '+%Y-%m-%d %H:%M:%S')" && \
		git push
	@echo "Documentation published to GitHub Pages"

# Phony targets
.PHONY: all clean clean-doc clean-all debug doc publish-doc

debug:
	$(MAKE) DEBUG=1

# Dependencies
$(OUTDIR)/main.o: $(SRCDIR)/main.c $(SRCDIR)/snake.h $(SRCDIR)/asciiart.h
$(OUTDIR)/snake.o: $(SRCDIR)/snake.c $(SRCDIR)/snake.h $(SRCDIR)/asciiart.h
$(OUTDIR)/asciiart.o: $(SRCDIR)/asciiart.c $(SRCDIR)/asciiart.h
