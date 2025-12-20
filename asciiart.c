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

#include "asciiart.h"
#include <stdio.h>

void set_position(int row, int col) {
    printf("\033[%d;%dH", row + 1, col + 1); // ANSI escape code to set cursor position
    fflush(stdout);
}

void set_color(int fg, int bg) {
    printf("\033[%d;%dm", fg, bg); // ANSI escape code to set colors
    fflush(stdout);
}

void hide_cursor() {
    printf("\033[?25l");  // Hide cursor
    fflush(stdout);
}

void show_cursor() {
    printf("\033[?25h");  // Show cursor
    fflush(stdout);
}

// Display character ch at (row, col) with specified color
void display(float row, float col, char ch, int color) {
    set_position((int)row, (int)col);
    set_color(color, BG_BLACK);
    putchar(ch);
    set_color(FG_WHITE, BG_BLACK); // flushes stdout
}

// Erase character at (row, col)
void erease(float row, float col) {
    set_position((int)row, (int)col);
    putchar(' ');
    fflush(stdout);
}

void clear_screen()
{
    printf("\033[2J"); // Clear screen
    fflush(stdout);
}

void go_home()
{
    printf("\033[H");  // Move cursor to home position
    fflush(stdout);
}
