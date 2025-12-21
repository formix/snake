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

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "asciiart.h"
#include "snake.h"



#define LOOP_DELAY 10 // in milliseconds


int main(int argc, char **argv) {

    const int playfield_height = 10;
    const int playfield_width = 20;

    srand(time(NULL));

    draw_playfield(playfield_height, playfield_width);
    set_position(playfield_height + 2, 0);
    set_color(FG_WHITE, BG_BLACK);
    printf("Press ESC to quit the game.\n");
    hide_cursor();

    Direction current_direction = DIRECTION_NONE;
    int snake_length = 5;
    int score = 0;

    int time_counter = 0;
    bool game_over = false;

    Segment *snake_head = initialize_snake(playfield_height / 2, playfield_width / 2, snake_length);
    display(snake_head->row, snake_head->col, '*', FG_GREEN);

    int apple_row;
    int apple_col;
    spawn_apple(playfield_height, playfield_width, snake_head, &apple_row, &apple_col);
    print_score(playfield_height, playfield_width, score, snake_length);

    bool direction_changed = false;
    clock_t last_time = clock();

    while (!game_over) {
        int key = read_key();
        game_over = (key == 27);

        if (!direction_changed) {
            switch (key) {
                case 'w':
                case 'W':
                    if (current_direction != DIRECTION_DOWN && current_direction != DIRECTION_UP) {
                        current_direction = DIRECTION_UP;
                        direction_changed = true;
                    }
                    break;
                case 's':
                case 'S':
                    if (current_direction != DIRECTION_UP && current_direction != DIRECTION_DOWN) {
                        current_direction = DIRECTION_DOWN;
                        direction_changed = true;
                    }
                    break;
                case 'a':
                case 'A':
                    if (current_direction != DIRECTION_RIGHT && current_direction != DIRECTION_LEFT) {
                        current_direction = DIRECTION_LEFT;
                        direction_changed = true;
                    }
                    break;
                case 'd':
                case 'D':
                    if (current_direction != DIRECTION_LEFT && current_direction != DIRECTION_RIGHT) {
                        current_direction = DIRECTION_RIGHT;
                        direction_changed = true;
                    }
                    break;
                default:
                    break;
            }
        }

        last_time = consistent_sleep(LOOP_DELAY, last_time);
        time_counter += LOOP_DELAY;
        if (direction_changed || time_counter >= 200) {
            direction_changed = false;
            time_counter = 0;
            snake_head = update_snake(snake_head, current_direction, snake_length);
            if (check_wall_collision(snake_head, playfield_height, playfield_width)) {
                game_over = true;
            }
            if (current_direction != DIRECTION_NONE && check_self_collision(snake_head)) {
                game_over = true;
            }
            if (check_apple_collision(snake_head, apple_row, apple_col)) {
                score += snake_length;
                int segment_count = random_segment_to_add();
                snake_length += add_segment(snake_head, segment_count);
                spawn_apple(playfield_height, playfield_width, snake_head, &apple_row, &apple_col);
                print_score(playfield_height, playfield_width, score, snake_length);
            }
            if (game_over) {
                display(snake_head->row, snake_head->col, 'X', FG_MAGENTA);
            }
        }
    }

    set_position(playfield_height + 3, 0);
    set_color(FG_WHITE, BG_BLACK);
    printf("Game Over! Thanks for playing.\n\n");
    delete_snake(snake_head);
    show_cursor();
    restore_terminal();


    return 0;
}
