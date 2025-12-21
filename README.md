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

## License

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Copyright (C) 2025 Formix

See [LICENSE.txt](LICENSE.txt) for full license details.

## Author

Formix

## Acknowledgments

Built with classic terminal programming techniques and ANSI escape sequences for cross-platform terminal compatibility.
