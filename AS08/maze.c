/**
 * CS1010 Semester 1 AY21/22
 * Assignment 8: Maze
 *
 * @file: maze.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */

#include "cs1010.h"
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define EMPTY '.'
#define WALL  'W'
#define USER  '@'

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

/**
 * Print one row of the maze to the screen (with colors)
 * 
 * @param[in] maze_row The 1D array representing a row of maze.
 */
void print_maze_row_with_color(char *maze_row) {
  long l = (long)strlen(maze_row); 
  for (long j = 0; j < l; j++) {
    if (maze_row[j] == EMPTY) {
      cs1010_print_string(BLUE);
    } else if (maze_row[j] == USER) {
      cs1010_print_string(RED);
    } else {
      cs1010_print_string(YELLOW);
    }
    putchar(maze_row[j]);
  }
  cs1010_println_string("");
  cs1010_print_string(RESET);
}

/**
 * Print the maze to the screen.
 * 
 * @param[in] maze The 2D array representing the maze.
 * @param[in] mrows The number of rows
 * @param[in] steps The number of steps taken so far.
 */
void print_maze(char **maze, long mrows, long steps) {
  if (isatty(fileno(stdout))) {
    cs1010_clear_screen();
  }
  for (long i = 0; i < mrows; i += 1) {
    if (!isatty(fileno(stdout))) {
      cs1010_println_string(maze[i]);
    } else {
      print_maze_row_with_color(maze[i]);
    }
  }
  cs1010_println_long(steps);
  if (isatty(fileno(stdout))) {
    usleep(100*1000);
  }
}

/**
 * Check if Scully can take one step in the maze, in moveX and moveY direction
 *
 * @param[in] x The x-coordinate of Scully
 * @param[in] y The y-coordinate of Scully
 * @param[in] moveX The x-direction to move
 * @param[in] moveY The y-direction to move
 * @param[in, out] steps The number of steps taken by Scully
 *
 * @return true if Scully can move one step in moveX and moveY direction,
 * false otherwise
 */
bool oneStep(char **maze, long x, long y, long moveX, long moveY, long *steps) {
    if (maze[x + moveX][y + moveY] != EMPTY) {
        return false;
    }
    maze[x][y] = EMPTY;
    maze[x + moveX][y + moveY] = USER;
    *steps += 1;
    return true;
}

/**
 * Find a way to escape the maze from starting position x, y
 *
 * @param[in] maze The 2D array we use as the maze
 * @param[in] traversed A 2D array to keep track of all positions we go to
 * @param[in] m The number of rows in the maze
 * @param[in] n The number of columns of the maze
 * @param[in] x The x-coordinate of Scully
 * @param[in] y The y-coordinate of Scully
 * @param[in, out] steps The number of steps taken within the maze
 *
 * @return true if Scully can escape the maze, false otherwise
 */
bool canEscape(char **maze, bool **traversed, size_t m, size_t n, long x, long y, long *steps) {
    traversed[x][y] = true;

    if (x == 0 || x == (long) m - 1 || y == 0 || y == (long) n - 1) {
        return true;
    }

    long possible_moves[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
    for (long direction = 0; direction < 4; direction += 1) {
        long moveX = possible_moves[direction][0];
        long moveY = possible_moves[direction][1];

        if (traversed[x + moveX][y + moveY] == false) {
            bool canMove = oneStep(maze, x, y, moveX, moveY, steps);
            if (canMove) {
                print_maze(maze, (long) m, *steps);
                if (canEscape(maze, traversed, m, n, x + moveX, y + moveY, steps)) {
                    return true;
                }
                oneStep(maze, x + moveX, y + moveY, -moveX, -moveY, steps);
                print_maze(maze, (long) m, *steps);
            }
        }
    }
    return false;
}

/**
 * Allocate memory on the heap to store the maze
 *
 * @param[in] array The 2D array to store the maze
 * @param[in] m The number of rows in the array
 */
void fillMaze(char **array, size_t m) {
    for (size_t i = 0; i < m; i += 1) {
        array[i] = cs1010_read_word();
        if (array[i] == NULL) {
            cs1010_println_string("Unable to allocate array");
            for (size_t j = 0; j <= i; j += 1) {
                free(array[j]);
            }
            free(array);
        }
    }
}

/**
 * Deallocate a char type 2D array and free the memory on the heap
 *
 * @param[in] array The array we want to deallocate
 * @param[in] size The number of rows in the 2D array
 */
void deallocateCharArray(char **array, size_t size) {
    for (size_t i = 0; i < size; i += 1) {
        free(array[i]);
    }
    free(array);
}

/**
 * Find the first position of Scully in the initial maze
 *
 * @param[in] maze The original maze
 * @param[in] m The number of rows in the maze
 * @param[in] n The number of columns in the maze
 * @param[in, out] x The x-coordinate of the starting position
 * @param[in, out] y The y-coordinate of the starting position
 */
void findStartPos(char **maze, size_t m, size_t n, long *x, long *y) {
    for (long i = 0; i < (long) m; i += 1) {
        for (long j = 0; j < (long) n; j += 1) {
            if (maze[i][j] == '@') {
                *x = i;
                *y = j;
            }
        }
    }
}

/**
 * Allocate memory on the heap for a bool type 2D array
 *
 * @param[in, out] array The bool array to allocate
 * @param[in] m The number of rows in the array
 * @param[in] n The number of columns in the array
 */
void allocateBoolArray(bool **array, size_t m, size_t n) {
    for (size_t i = 0; i < m; i += 1) {
        array[i] = malloc(n * sizeof(bool));
    }
}

int main() {
    size_t m = cs1010_read_size_t();
    size_t n = cs1010_read_size_t();
    
    char **maze = malloc(m * sizeof(long*));
    if (maze == NULL) {
        cs1010_println_string("Unable to allocate maze");
        free(maze);
        return -1;
    }
    fillMaze(maze, m);
    
    //find the starting coordinate
    long x = 0;
    long y = 0;
    findStartPos(maze, m, n, &x, &y); 

    long steps = 0; //keep track of the number of steps taken
    bool **traversed = malloc(m * sizeof(bool*));
    if (traversed == NULL) {
        free(traversed);
        return -1;
    }
    allocateBoolArray(traversed, m, n);

    print_maze(maze, (long) m, steps); //print the original maze first
    bool escaped = canEscape(maze, traversed, m, n, x, y, &steps); 

    deallocateCharArray(maze, m);
    for (size_t i = 0; i < m; i += 1) {
        free(traversed[i]);
    }
    free(traversed);

    if (!escaped) {
        return -2;
    }
    return 0;
}
