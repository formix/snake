# Compiler and flags
CC = gcc
CFLAGS = -Wall
DEBUG_FLAGS = -g -O0
TARGET = snake
OUTDIR = out
DOCDIR = $(OUTDIR)/doc

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

# Clean documentation
clean-doc:
	rm -rf $(DOCDIR)

# Clean everything
clean-all: clean clean-doc

# Generate HTML documentation
$(DOCDIR)/html/index.html: *.c *.h
	@echo "Generating HTML documentation..."
	@mkdir -p $(DOCDIR)
	@(cat Doxyfile 2>/dev/null || doxygen -g - 2>/dev/null) | \
		sed -e 's|^OUTPUT_DIRECTORY.*|OUTPUT_DIRECTORY = $(DOCDIR)|' \
		    -e 's|^GENERATE_HTML.*|GENERATE_HTML = YES|' \
		    -e 's|^GENERATE_LATEX.*|GENERATE_LATEX = NO|' \
		    -e 's|^HTML_OUTPUT.*|HTML_OUTPUT = html|' \
		    -e 's|^EXTRACT_ALL.*|EXTRACT_ALL = YES|' \
		    -e 's|^PROJECT_NAME.*|PROJECT_NAME = "Snake Game"|' \
		    -e 's|^RECURSIVE.*|RECURSIVE = YES|' | \
		doxygen -

# Documentation target
doc: $(DOCDIR)/html/index.html
	@echo "Documentation generated in $(DOCDIR)/html/index.html"
	@echo "Copying documentation to ../snake-doc..."
	@mkdir -p ../snake-doc
	@cp -r $(DOCDIR)/html/* ../snake-doc/
	@echo "Documentation copied to ../snake-doc"

# Publish documentation to GitHub Pages
publish-doc:
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
$(OUTDIR)/main.o: main.c snake.h asciiart.h
$(OUTDIR)/snake.o: snake.c snake.h asciiart.h
$(OUTDIR)/asciiart.o: asciiart.c asciiart.h
