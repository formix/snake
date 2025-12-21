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

#ifndef SNAKE_H
#define SNAKE_H

#include <time.h>


struct Segment {
    int row;
    int col;
    struct Segment *next;
};
typedef struct Segment Segment;

enum Direction {
    DIRECTION_NONE,
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT
};
typedef enum Direction Direction;


int read_key();
void restore_terminal();
void draw_playfield(int height, int width);

Segment* initialize_snake(int start_row, int start_col, size_t initial_length);
Segment* create_segment(int row, int col);
Segment* draw_head_segment(Segment* head, int row, int col);
void draw_tail_segments(Segment* head, size_t snake_size);
Segment* update_snake(Segment* head, Direction dir, size_t snake_size);
void delete_snake(Segment* head);
int add_segment(Segment* head, int count);

bool check_wall_collision(Segment* head, int playfield_height, int playfield_width);
bool check_self_collision(Segment* head);
bool check_apple_collision(Segment* head, int apple_row, int apple_col);

void spawn_apple(int playfield_height, int playfield_width, Segment* snake_head, int* apple_row, int* apple_col);
clock_t consistent_sleep(long period_ms, clock_t last_time);
void print_score(int playfield_height, int playfield_width, int score, int snake_length);
int random_segment_to_add();

#endif

