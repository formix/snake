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

/**
 * @file snake.h
 * @brief Core snake game logic and data structures
 *
 * This module provides the main game logic for the snake game, including
 * snake movement, collision detection, apple spawning, and game state management.
 * It handles the playfield setup, snake data structure operations, and game timing.
 */

#ifndef SNAKE_H
#define SNAKE_H

#include <time.h>


/**
 * @struct Segment
 * @brief Represents a single segment of the snake
 *
 * Each segment stores its position on the playfield and a pointer to the
 * next segment, forming a linked list representation of the snake.
 */
struct Segment {
    int row;                /**< Row position of the segment */
    int col;                /**< Column position of the segment */
    struct Segment *next;   /**< Pointer to the next segment in the snake */
};
typedef struct Segment Segment;

/**
 * @enum Direction
 * @brief Possible movement directions for the snake
 */
enum Direction {
    DIRECTION_NONE,   /**< No movement */
    DIRECTION_UP,     /**< Move upward */
    DIRECTION_DOWN,   /**< Move downward */
    DIRECTION_LEFT,   /**< Move left */
    DIRECTION_RIGHT   /**< Move right */
};
typedef enum Direction Direction;

/**
 * @brief Parse command-line options for playfield dimensions
 *
 * Parses command-line arguments to set the playfield height and width.
 * Supports -h for height and -w for width options. If one dimension is
 * specified, the other is calculated to maintain a 2:1 ratio.
 *
 * @param argc Argument count from main()
 * @param argv Argument vector from main()
 * @param playfield_height Pointer to store the playfield height
 * @param playfield_width Pointer to store the playfield width
 */
void parse_options(int argc, char **argv, int *playfield_height, int *playfield_width);

/**
 * @brief Initialize the terminal for raw input mode
 *
 * Configures the terminal to disable canonical mode and echo,
 * allowing character-by-character input without waiting for Enter.
 */
void initialize_terminal();

/**
 * @brief Restore the terminal to its original state
 *
 * Restores terminal settings that were modified by initialize_terminal().
 * Should be called before program exit.
 */
void restore_terminal();

/**
 * @brief Read a single keypress from the terminal
 *
 * Reads keyboard input in non-blocking mode and maps arrow keys
 * to corresponding direction values.
 *
 * @return Character code or direction constant for arrow keys, -1 if no input, -2 if the terminal is not initialized
 */
int read_key();

/**
 * @brief Draw the playfield border
 *
 * Draws the rectangular border around the playfield using box drawing characters.
 *
 * @param height Height of the playfield in rows
 * @param width Width of the playfield in columns
 */
void draw_playfield(int height, int width);

/**
 * @brief Initialize a new snake at the specified position
 *
 * Creates a snake with the given initial length, starting at the specified
 * position. All segments are initially at the same position.
 *
 * @param start_row Starting row position
 * @param start_col Starting column position
 * @param initial_length Number of segments in the initial snake
 * @return Pointer to the head segment, or NULL if allocation fails
 */
Segment* initialize_snake(int start_row, int start_col, size_t initial_length);

/**
 * @brief Create a new snake segment
 *
 * Allocates and initializes a new segment at the specified position.
 *
 * @param row Row position for the new segment
 * @param col Column position for the new segment
 * @return Pointer to the new segment, or NULL if allocation fails
 */
Segment* create_segment(int row, int col);

/**
 * @brief Add a new head segment to the snake
 *
 * Creates a new head segment at the specified position and links it
 * to the existing snake, becoming the new head.
 *
 * @param head Current head of the snake
 * @param row Row position for the new head segment
 * @param col Column position for the new head segment
 * @return Pointer to the new head segment
 */
Segment* add_head_segment(Segment* head, int row, int col);

/**
 * @brief Remove the tail segment from the snake
 *
 * Removes and frees the last segment of the snake, shortening it by one.
 * This is typically called when the snake moves without growing.
 *
 * @param head Head segment of the snake
 * @param snake_size Total number of segments in the snake
 */
void remove_tail_segment(Segment* head, size_t snake_size);

/**
 * @brief Move the snake in the specified direction
 *
 * Moves the snake in the specified direction by adding a new head
 * segment and removing the tail segment if the snake hasn't grown.
 *
 * @param head Current head of the snake
 * @param dir Direction to move
 * @param snake_size Current size of the snake
 * @return Pointer to the new head segment
 */
Segment* move_snake(Segment* head, Direction dir, size_t snake_size);

/**
 * @brief Delete the entire snake and free memory
 *
 * Frees all segments in the snake's linked list.
 *
 * @param head Head segment of the snake to delete
 */
void delete_snake(Segment* head);

/**
 * @brief Add segments to the snake
 *
 * Appends the specified number of segments to the end of the snake.
 *
 * @param head Head segment of the snake
 * @param count Number of segments to add
 * @return Number of segments successfully added
 */
int add_segment(Segment* head, int count);

/**
 * @brief Check if the snake has collided with a wall
 *
 * Determines if the snake's head is outside the playfield boundaries.
 *
 * @param head Head segment of the snake
 * @param playfield_height Height of the playfield
 * @param playfield_width Width of the playfield
 * @return true if collision detected, false otherwise
 */
bool check_wall_collision(Segment* head, int playfield_height, int playfield_width);

/**
 * @brief Check if the snake has collided with itself
 *
 * Determines if the snake's head occupies the same position as any
 * other segment in its body.
 *
 * @param head Head segment of the snake
 * @return true if self-collision detected, false otherwise
 */
bool check_self_collision(Segment* head);

/**
 * @brief Check if the snake has collided with an apple
 *
 * Determines if the snake's head is at the same position as the apple.
 *
 * @param head Head segment of the snake
 * @param apple_row Row position of the apple
 * @param apple_col Column position of the apple
 * @return true if apple collision detected, false otherwise
 */
bool check_apple_collision(Segment* head, int apple_row, int apple_col);

/**
 * @brief Spawn a new apple on the playfield
 *
 * Places an apple at a random location that doesn't overlap with the snake.
 *
 * @param playfield_height Height of the playfield
 * @param playfield_width Width of the playfield
 * @param snake_head Head segment of the snake to avoid
 * @param apple_row Pointer to store the apple's row position
 * @param apple_col Pointer to store the apple's column position
 */
void spawn_apple(int playfield_height, int playfield_width, Segment* snake_head, int* apple_row, int* apple_col);

/**
 * @brief Sleep for a consistent period to maintain frame rate
 *
 * Sleeps for the specified period minus the time elapsed since last_time,
 * ensuring consistent timing regardless of processing time.
 *
 * @param period_ms Target period in milliseconds
 * @param last_time Clock time of the last frame
 * @return Current clock time after sleep
 */
clock_t consistent_sleep(long period_ms, clock_t last_time);

/**
 * @brief Display the game score and statistics
 *
 * Shows the current username, playfield size, snake length, and score
 * on the right side of the playfield.
 *
 * @param playfield_height Height of the playfield
 * @param playfield_width Width of the playfield
 * @param score Current game score
 * @param snake_length Current length of the snake
 */
void print_score(int playfield_height, int playfield_width, int score, int snake_length);

/**
 * @brief Randomly pick a number of segments to add
 *
 * Uses weighted random selection to determine how many segments
 * to add when the snake eats an apple.
 *
 * @return Number of segments to add (1, 2, or 3)
 */
int pick_number_of_segments();

#endif

