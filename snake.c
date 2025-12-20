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

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "snake.h"
#include "asciiart.h"

Segment *initialize_snake(int start_row, int start_col, size_t initial_length)
{
    Segment *head = create_segment(start_row, start_col);
    if (head == NULL) {
        return NULL; // Memory allocation failed
    }

    Segment *current = head;
    for (size_t i = 1; i < initial_length; i++) {
        Segment *new_segment = create_segment(start_row, start_col);
        if (new_segment == NULL) {
            // Free previously allocated segments in case of failure
            Segment *temp = head;
            while (temp != NULL) {
                Segment *next = temp->next;
                free(temp);
                temp = next;
            }
            return NULL; // Memory allocation failed
        }
        current->next = new_segment;
        current = new_segment;
    }

    return head;
}

Segment *create_segment(int row, int col)
{
    Segment *new_segment = (Segment *)malloc(sizeof(Segment));
    if (new_segment == NULL) {
        return NULL; // Memory allocation failed
    }
    new_segment->row = row;
    new_segment->col = col;
    new_segment->next = NULL;
    return new_segment;
}


Segment *draw_head_segment(Segment *head, int row, int col)
{
    Segment *new_segment = create_segment(row, col);
    if (new_segment == NULL) {
        return NULL; // Memory allocation failed
    }
    display(row, col, '*', FG_GREEN);
    new_segment->next = head;
    return new_segment;
}


void draw_tail_segments(Segment *head, size_t snake_size)
{
    if (head == NULL || head->next == NULL) {
        return; // List is empty or has only one segment
    }
    Segment *current = head;
    size_t count = 1;
    while (current->next != NULL && count < snake_size) {
        current = current->next;
        count++;
        display(current->row, current->col, '#', FG_CYAN);
    }
    if (count < snake_size - 1) {
        return; // Snake is shorter than expected, nothing to remove
    }
    Segment *tail = current->next;
    if (tail->row != current->row || tail->col != current->col) {
        // Only erase if the tail has moved
        display(tail->row, tail->col, ' ', FG_BLACK); // Erase tail
    }
    free(tail);
    current->next = NULL;
}


Segment *update_snake(Segment *head, Direction dir, size_t snake_size)
{
    int row = head->row;;
    int col = head->col;
    switch (dir) {
        case DIRECTION_NONE:
            return head;
        case DIRECTION_UP:
            row--;
            break;
        case DIRECTION_DOWN:
            row++;
            break;
        case DIRECTION_LEFT:
            col--;
            break;
        case DIRECTION_RIGHT:
            col++;
            break;
    }

    head = draw_head_segment(head, row, col);
    draw_tail_segments(head, snake_size);
    return head;
}

void delete_snake(Segment *head)
{
    Segment *current = head;
    while (current != NULL) {
        Segment *next = current->next;
        free(current);
        current = next;
    }
}

int add_segment(Segment *head, int count)
{
    Segment *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    for (int i = 0; i < count; i++) {
        Segment *new_segment = create_segment(current->row, current->col);
        if (new_segment != NULL) {
            current->next = new_segment;
            current = new_segment;
        }
    }
    return count;
}

bool check_wall_collision(Segment *head, int playfield_height, int playfield_width)
{
    if (head->row < 1 || head->row > playfield_height ||
        head->col < 1 || head->col > playfield_width) {
        return true;
    }
    return false;
}

bool check_self_collision(Segment *head)
{
    Segment *current = head->next;
    while (current != NULL) {
        if (head->row == current->row && head->col == current->col) {
            return true;
        }
        current = current->next;
    }
    return false;
}

bool check_apple_collision(Segment *head, int apple_row, int apple_col)
{
    if (head->row == apple_row && head->col == apple_col) {
        return true;
    }
    return false;
}

void spawn_apple(int playfield_height, int playfield_width, Segment *snake_head, int *apple_row, int *apple_col)
{
    bool collision;
    do {
        collision = false;
        *apple_row = (rand() % playfield_height) + 1;
        *apple_col = (rand() % playfield_width) + 1;

        Segment *current = snake_head;
        while (current != NULL) {
            if (current->row == *apple_row && current->col == *apple_col) {
                collision = true;
                break;
            }
            current = current->next;
        }
    } while (collision);

    display(*apple_row, *apple_col, '@', FG_RED);
}

clock_t consistent_sleep(long period_ms, clock_t last_time)
{
    clock_t current_time = clock();
    long period_us = period_ms * 1000;
    long elapsed_us = (current_time - last_time) * 1000000 / CLOCKS_PER_SEC;
    if (elapsed_us >= period_us) {
        return current_time;
    }
    long wait_period_us = period_us - elapsed_us;
    usleep(wait_period_us);
    return current_time;
}

void print_score(int playfield_height, int playfield_width, int score, int snake_length)
{
    set_position(1, playfield_width + 3);
    set_color(FG_WHITE, BG_BLACK);
    printf("Length: %d", snake_length);
    set_position(2, playfield_width + 3);
    printf("Score:  %d", score);
    fflush(stdout);
}

int random_segment_to_add()
{
    int r = rand() % 100;
    if (r < 25) {
        return 1;
    } else if (r < 75) {
        return 2;
    } else {
        return 3;
    }
}

int read_key() {
    static struct termios oldt, newt;
    static int initialized = 0;
    int ch;
    int bytes_available;

    // Initialize terminal settings on first call
    if (!initialized) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        newt.c_cc[VMIN] = 0;
        newt.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        initialized = 1;
    }

    // Check if bytes are available in the keyboard buffer
    ioctl(STDIN_FILENO, FIONREAD, &bytes_available);

    if (bytes_available > 0) {
        ch = getchar();
        return ch;
    }

    return -1; // No key pressed
}

void draw_playfield(int height, int width) {
    clear_screen();
    go_home();

    set_color(FG_YELLOW, BG_BLACK);
    char horizontal_line[width + 2];
    memset(horizontal_line, '-', width);
    horizontal_line[width] = '\0';

    char buf[width + 2];
    memset(buf, ' ', width);
    buf[width] = '\0';

    printf("+%s+\n", horizontal_line);
    for (int r = 1; r < (height + 1); r++) {
        printf("|%s|\n", buf);
    }
    printf("+%s+\n", horizontal_line);

    set_color(FG_WHITE, BG_BLACK);
}

