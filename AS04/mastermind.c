/**
 * CS1010 Semester 1 AY21/22
 * Assignment 4: Mastermind
 *
 * @file: mastermind.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */
#include "cs1010.h"
#include <stdbool.h>

long correct_position_and_color(long code[4], long guess[4]) {
    long count = 0;
    for (long i = 0; i < 4; i += 1) {
        if (guess[i] == code[i]) {
            count += 1;
        }
    }
    return count;
}

long correct_color(long code[4], long guess[4]) {
    long count = 0;
    long check[4]; //temporary array to hold values of the guess, used to check against the correct code

    for (long i = 0; i < 4; i += 1) {
        check[i] = code[i];
    }
    
    for (long i = 0; i < 4; i += 1) {
        if (guess[i] == check[0]) {
            check[0] = 0;
            count += 1;
        } else if (guess[i] == check[1]) {
            check[1] = 0;
            count += 1;
        } else if (guess[i] == check[2]) {
            check[2] = 0;
            count += 1;
        } else if (guess[i] == check[3]) {
            check[3] = 0;
            count += 1;
        }
    }
    return count;
}

void printResult(long PosColor, long color) {
    cs1010_print_long(PosColor);
    cs1010_print_string(" ");
    cs1010_println_long(color);
}

bool mastermind(long code[4], long guess[4]) {
    long correctPosColor = correct_position_and_color(code, guess);
    long correctColor = correct_color(code, guess);
    
    if (correctColor == 0) {
        printResult(correctPosColor, correctColor);
        return false;
    }
    if (correctPosColor != 4) {
        printResult(correctPosColor, correctColor - correctPosColor);
        return false;
    }
    printResult(correctPosColor, correctColor - correctPosColor);
    return true;
}

int main()
{
    long code[4];
    for (long i = 0; i < 4; i += 1) {
        code[i] = cs1010_read_long();
    }
    
    long guess[4];
    for (long i = 0; i < 4; i += 1) {
        guess[i] = cs1010_read_long();
    }

    while (!mastermind(code, guess)) {
        for (long i = 0; i < 4; i += 1) {
            guess[i] = cs1010_read_long();
        }
    }
}
