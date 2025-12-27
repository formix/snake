# Snake Game

A classic terminal-based Snake game written in C with ANSI/VT100 escape sequences for rendering.

## Features

- 🐍 Classic snake gameplay with smooth movement
- 🎮 WASD controls for directional input
- 🍎 Random apple spawning with collision detection
- 📊 Real-time score and length tracking
- 💥 Wall and self-collision detection
- 🎨 Colorful ANSI terminal graphics
- 🎯 Dynamic segment growth system

## Requirements

- GCC compiler
- Linux/Unix terminal with ANSI/VT100 support
- Make build system

## Building

### Make Targets

The project uses Make for building and managing the project. Available targets:

| Target | Description |
|--------|-------------|
| `make` or `make all` | Build the game in production mode (default target) |
| `make debug` | Build with debug symbols (`-g -O0` flags) for use with GDB |
| `make clean` | Remove all build artifacts from the `out/` directory |
| `make doc` | Generate HTML API documentation to `out/doc/html/` |
| `make publish-doc` | Commit and push documentation to GitHub Pages (gh-pages branch) |
| `make clean-doc` | Remove the documentation from `out/doc/` |
| `make clean-all` | Remove both build artifacts and documentation |

### Standard Build
```bash
make
```

### Debug Build
```bash
make debug
```

### Clean Build Artifacts
```bash
make clean
```

The executable will be created in the `out/` directory as `out/snake`.

## How to Play

1. Build the game:
   ```bash
   make
   ```

2. Run the game:
   ```bash
   ./out/snake
   ```

3. Controls:
   - `W` - Move Up
   - `S` - Move Down
   - `A` - Move Left
   - `D` - Move Right
   - `ESC` - Quit Game

4. Objective:
   - Collect apples (`@`) to grow your snake and increase your score
   - Avoid hitting the walls or your own tail
   - The snake grows by 1-3 segments randomly with each apple

5. Scoring:
   - Score increases by the current snake length for each apple eaten
   - Example: If your snake is 5 segments long, eating an apple adds 5 points
   - As your snake grows longer, each apple is worth more points

## Project Structure

```
.
├── main.c              # Main game loop and initialization
├── snake.c             # Snake logic, collision detection, and terminal handling
├── snake.h             # Snake module header
├── asciiart.c          # ANSI/VT100 terminal rendering functions
├── asciiart.h          # ASCII art module header
├── Makefile            # Build configuration
├── LICENSE.txt         # GNU GPL v3 license
└── README.md           # This file
```

## Technical Details

- **Terminal Mode**: Uses raw terminal mode with `termios` to disable canonical input and echo
- **Non-blocking Input**: Implements non-blocking keyboard input using `ioctl` and `FIONREAD`
- **Timing**: Consistent frame timing using `clock()` and `usleep()`
- **Memory Management**: Dynamic linked list structure for snake segments
- **Terminal Restoration**: Properly restores terminal settings on exit

## Developer Guide

### Platform Requirements

This project is designed for **Linux** systems with:
- ANSI/VT100 terminal support
- POSIX-compliant environment

### Development Tools

The following tools are required for building and documenting the project:

#### Build Tools
- **GCC** - GNU C Compiler
- **Make** - Build automation tool
- **GDB** (optional) - GNU Debugger for debug builds

#### Documentation Tools
- **Doxygen** - API documentation generator

### Setting Up the Development Environment

#### Ubuntu/Debian
```bash
# Install build tools
sudo apt update
sudo apt install build-essential gcc make gdb

# Install documentation tools
sudo apt install doxygen
```

#### Fedora/RHEL/Rocky Linux
```bash
# Install build tools
sudo dnf groupinstall "Development Tools"
sudo dnf install gcc make gdb

# Install documentation tools
sudo dnf install doxygen
```

#### Arch Linux
```bash
# Install build tools
sudo pacman -S base-devel gcc make gdb

# Install documentation tools
sudo pacman -S doxygen
```

### Building the Project

#### Production Build
```bash
make
./out/snake
```

#### Debug Build (with debug symbols and `-g` flag)
```bash
make debug
gdb ./out/snake
```

#### Clean Build Artifacts
```bash
make clean
```

### Generating Documentation

The project uses Doxygen to generate HTML API documentation.

#### Generate HTML Documentation
```bash
# Generate documentation
make doc

# Documentation will be created in out/doc/html/index.html
# Open in browser
xdg-open out/doc/html/index.html
```

### Code Documentation Style

The project uses Doxygen-style comments:

```c
/**
 * @brief Function description
 *
 * @param param_name Parameter description
 * @return Return value description
 */
```

See [snake.h](snake.h) and [asciiart.h](asciiart.h) for examples.

### Development Dependencies

The project depends on the following standard Linux libraries:
- `<stdlib.h>` - Standard library
- `<stdio.h>` - Standard I/O
- `<string.h>` - String operations
- `<stdbool.h>` - Boolean type
- `<time.h>` - Timing functions
- `<unistd.h>` - POSIX API
- `<termios.h>` - Terminal I/O
- `<sys/ioctl.h>` - Device control

All dependencies are part of the standard Linux development environment.

## License

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Copyright (C) 2025 Formix

See [LICENSE.txt](LICENSE.txt) for full license details.

## Author

Formix

## Acknowledgments

Built with classic terminal programming techniques and ANSI escape sequences for cross-platform terminal compatibility.
