/***************************************************************************
 *
 * Snake Game
 * Copyright (C) 2025 Formix
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *****************************************************************************/

#ifndef asciiart_H
#define asciiart_H

// ANSI Foreground Colors
#define FG_BLACK   30
#define FG_RED     31
#define FG_GREEN   32
#define FG_YELLOW  33
#define FG_BLUE    34
#define FG_MAGENTA 35
#define FG_CYAN    36
#define FG_WHITE   37
#define FG_DEFAULT 39

// ANSI Background Colors
#define BG_BLACK   40
#define BG_RED     41
#define BG_GREEN   42
#define BG_YELLOW  43
#define BG_BLUE    44
#define BG_MAGENTA 45
#define BG_CYAN    46
#define BG_WHITE   47
#define BG_DEFAULT 49

// Box Drawing Characters - Single Line
#define BOX_SINGLE_HORIZONTAL      "─"
#define BOX_SINGLE_VERTICAL        "│"
#define BOX_SINGLE_TOP_LEFT        "┌"
#define BOX_SINGLE_TOP_RIGHT       "┐"
#define BOX_SINGLE_BOTTOM_LEFT     "└"
#define BOX_SINGLE_BOTTOM_RIGHT    "┘"
#define BOX_SINGLE_VERTICAL_RIGHT  "├"
#define BOX_SINGLE_VERTICAL_LEFT   "┤"
#define BOX_SINGLE_HORIZONTAL_DOWN "┬"
#define BOX_SINGLE_HORIZONTAL_UP   "┴"
#define BOX_SINGLE_CROSS           "┼"

// Box Drawing Characters - Double Line
#define BOX_DOUBLE_HORIZONTAL      "═"
#define BOX_DOUBLE_VERTICAL        "║"
#define BOX_DOUBLE_TOP_LEFT        "╔"
#define BOX_DOUBLE_TOP_RIGHT       "╗"
#define BOX_DOUBLE_BOTTOM_LEFT     "╚"
#define BOX_DOUBLE_BOTTOM_RIGHT    "╝"
#define BOX_DOUBLE_VERTICAL_RIGHT  "╠"
#define BOX_DOUBLE_VERTICAL_LEFT   "╣"
#define BOX_DOUBLE_HORIZONTAL_DOWN "╦"
#define BOX_DOUBLE_HORIZONTAL_UP   "╩"
#define BOX_DOUBLE_CROSS           "╬"

// Block Elements
#define BLOCK_FULL         "█"
#define BLOCK_DARK         "▓"
#define BLOCK_MEDIUM       "▒"
#define BLOCK_LIGHT        "░"
#define BLOCK_UPPER_HALF   "▀"
#define BLOCK_LOWER_HALF   "▄"
#define BLOCK_SMALL_SQUARE "■"
#define BLOCK_TINY_SQUARE  "▪"

void set_position(int row, int col);
void set_color(int fg, int bg);
void hide_cursor();
void show_cursor();
void display(float row, float col, char ch, int fgcolor);
void erease(float row, float col);
void clear_screen();
void go_home();


#endif
