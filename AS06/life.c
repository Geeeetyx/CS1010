/**
 * CS1010 Semester 1 AY21/22
 * Assignment 6: Life
 *
 * @file: life.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */
#include "cs1010.h"
#include <stdbool.h>
#include <unistd.h>

/**
 * Replace old board with the new version of the board, reset the new board to all dead
 *
 * @param[in] n_rows number of rows of the board
 * @param[in] m_cols number of columns of the board
 * @param[in] board the previous version of the board
 * @param[in] nextBoard the new version of the board
 */
void swap(size_t n_rows, size_t m_cols, char **board, char **nextBoard) {
    for (size_t i = 1; i < n_rows - 1; i += 1) {
        for (size_t j = 1; j < m_cols -1 ; j += 1) {
            board[i][j] = nextBoard[i][j];
            nextBoard[i][j] = '.';
        }
    }   
}

/** 
 * Return true if cell is alive
 *
 * @param[in] board The board which we are checking
 * @param[in] i The row-coordinate of the cell we are checking 
 * @param[in] j The column-coordinate of the cell we are checking
 *
 * @return Returns true if the cell is alive, otherwise return false
 */
bool alive(char **board, size_t i, size_t j) {
    if (board[i][j] == '#') {
        return true;
    }
    return false;
}

/**
 * Count the number of alive neighbours surrounding the cell we are checking, 
 * in all directions
 * 
 * @param[in] board The current board
 * @param[in] i The row-coordinate of the cell we are checking
 * @param[in] j The column-coordinate of the cell we are checking
 *
 * @return count The number of alive neighbours surrounding the cell we are checking
 */
long alive_count(char **board, size_t i, size_t j) {
    long count = 0;
    for (size_t row = i - 1; row < i + 2; row += 1) {
        for (size_t col = j - 1; col < j + 2; col += 1) {
            if ((row != i || col != j) && (board[row][col] == '#')) {
                count += 1;
            }
        }
    }
    return count;
}

/** 
 * Modify the current cell depending on whether neighbour cells are alive or dead,
 * and depending on the number of alive neighbours
 *
 * @param[in] board The current board
 * @param[in] i The row-coordinate of the cell
 * @param[in] j The column-coordinate of the current cell
 * 
 * @return '#' if cell is alive and number of alive neighbours is 2 or 3, '#' if cell is not alive but alive neighbours is 3
 * otherwise return '.'
 */
char changeCell(char **board, size_t i, size_t j) {
    long aliveNeighbours = alive_count(board, i, j);
    if (alive(board, i, j)) {
        if ((aliveNeighbours == 2) || (aliveNeighbours == 3)) {
            return '#';
        }
    } else {
        if (aliveNeighbours == 3) {
            return '#';
        }
    }
    return '.';
}

/** 
 * Simulate one round of the game
 * Modify the next board depending on the previous board
 *
 * @param[in] n_rows Number of rows on the board
 * @param[in] m_cols Number of columns on the board
 * @param[in] board The current board
 * @param[in] nextBoard The next version of the board
 *
 */
void oneRound(size_t n_rows, size_t m_cols, char **board, char **nextBoard) { 
    for (size_t i = 1; i < n_rows - 1; i += 1) {
        for (size_t j = 1; j < m_cols - 1; j += 1) {
            nextBoard[i][j] = changeCell(board, i, j);
        }
    }
}

/**
 * Print a board of the game of life
 *
 * @param[in] n_rows The number of rows on the board
 * @param[in] m_cols The number of columns on the board
 * @param[in] board The current board of the game of life we want to print
 */
void printBoard(size_t n_rows, size_t m_cols, char **board) {
    for (size_t i = 0; i < n_rows; i += 1) {
        for (size_t j = 0; j < m_cols; j += 1) {
            putchar(board[i][j]);
        }
        cs1010_println_string("");
    }
}

/**
 * Simulate the game of life, with k rounds of the game
 *
 * @param[in] k The number of rounds of the game
 * @param[in] n_rows Number of rows on the board
 * @param[in] m_cols Number of columns on the board
 * @param[in] board The current board
 * @param[in] nextBoard The next version of the board
 */
void the_Game_of_Life(long k, size_t n_rows, size_t m_cols, char **board, char **nextBoard) {
    for (long count = 0; count < k; count += 1) {
        cs1010_clear_screen();
        oneRound(n_rows, m_cols, board, nextBoard);
        printBoard(n_rows, m_cols, nextBoard);
        
        swap(n_rows, m_cols, board, nextBoard);
        usleep(250 * 1000);
    }
}

/**
 * Deallocate the 2D array and free the memory on the heap
 *
 * @param[in] array The array we want to deallocate
 * @param[in] size The number of rows of the array
 */
void deallocateArray(char **array, size_t size) {
    for (size_t i = 0; i < size; i += 1) {
        free(array[i]);
    }
    free(array);
}           

int main()
{
    char **board;
    size_t n_rows = cs1010_read_size_t();
    size_t m_cols = cs1010_read_size_t();
    long k = cs1010_read_long();

    board = calloc(n_rows, sizeof(char*));
    for (size_t i = 0; i < n_rows; i += 1) {
        board[i] = cs1010_read_line();
        if (board[i] == NULL) {
            cs1010_println_string("unable to allocate board");
            for (size_t j = 0; j < i; j += 1) {
                free(board[i]);
            }
            free(board);
        }
    }

    char **nextBoard = calloc(n_rows, sizeof(char*));
    if (nextBoard == NULL) {
        cs1010_println_string("unable to allocate array");
        return 0;
    }
    for (size_t i = 0; i < n_rows; i += 1) {
        nextBoard[i] = malloc(m_cols * sizeof(char));
        if (nextBoard[i] == NULL) {
            cs1010_println_string("unable to allocate array");
            return 0;
        }
    }
    for (size_t i = 0; i < n_rows; i += 1) {
        for (size_t j = 0; j < m_cols; j += 1) {
            nextBoard[i][j] = '.';
        }
    }

    the_Game_of_Life(k, n_rows, m_cols, board, nextBoard);

    deallocateArray(board, n_rows);
    deallocateArray(nextBoard, n_rows);
}
