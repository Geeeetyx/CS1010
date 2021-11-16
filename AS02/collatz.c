/**
 * CS1010 Semester 1 AY21/22
 * Assignment 2: Collatz 
 *
 * Read in a positive integer n from the standard input,
 * then, for each number k between number 1 .. n, transform
 * it into 1 based on the steps below:
 * - if k is even, k = k/2
 * - else, k = 3k + 1
 * Find the number k that requires the most number of steps
 * between 1 and n, and print both k and the number of steps
 * to standard output. If there are multiple numbers with
 * the same number of steps, we prefer to output the smaller
 * among these numbers.
 *
 * @file: collatz.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */
#include "cs1010.h"
#include <math.h>


long STC(long num) { //STC stands for Stopping Time Calculator
    if (num == 1) {
        return 0;
    }
    
    long counter = 0; //set count to 0

    while (num != 1) {
        if (num % 2 == 0) {
            num /= 2;
        } else {
            num = num*3 + 1;
        }
        counter += 1;
    }
    return counter;
}

int main()
{
    long input = cs1010_read_long();   
    
    if (input == 1) { //the case where input integer is 1 --> return 1 and 0 as the stopping time straightaway
        cs1010_println_long(input);
        cs1010_println_long(0);
    } else {
        long max    = input;    //initialise max to be the input intger at first
        long max_st = STC(max); //initialise max_st to be the correspoding stopping time
        for (long i = input - 1; i > 0; i-= 1) { //E.g if input is 10, set i to be 9, start comparing from 9 onwards
            long steps = STC(i); //count the number of steps to go from input integer to 1

            if (steps > max_st) {
                max_st = steps;
                max = i;
            }

            if (steps == max_st) {
                max = i;
            }
        }
        cs1010_println_long(max);
        cs1010_println_long(max_st);
    }
}
