/**
 * CS1010 Semester 1 AY21/22
 * Assignment 2: Pattern
 *
 * Read in two positive integers: an interval n (n >= 1) 
 * and the height of the triangle h.  Then draw a triangle
 * according to a given pattern.  
 *
 * @file: pattern.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */
#include "cs1010.h"
#include <math.h>
#include <stdbool.h>

bool check_prime(long n) {
    if ((n == 2) || (n == 3)) {
        return true;
    }
    if ((n <= 1) || (n % 2 == 0) || (n % 3 == 0)) {
        return false;
    }
    for (long i = 5; i <= sqrt(n); i += 6) {
        if ((n % i == 0) || (n % (i+2) == 0)) {
            return false;
        }
    }
    return true;
}

long cells(long row) { //function to return the number of cells in a particular row
    return 2*row - 1;
}

long lead_number(long n, long row_num) { //function to find the first number of the first cell in every row
    long x = 1;
    long y = 1;
    while (y < row_num) {
        x += y*n;
        y += 1;
    }
    return x;
}

void print_left_blank(long h) { //print all the left spaces
    for (long i = 1; i < h; i += 1) {
        cs1010_print_string(" ");
    }
}

bool cell_has_prime(long row, long cell, long n) {
    long first_num = lead_number(n, row) + cell - 1; //first number of the entire row
    for (long i = 1; i <= n; i += 1) { 
        if (check_prime(first_num)) {
            return true;
        }
        first_num += row; 
    }
    return false;
}

void print_body(long num_of_cells, long row, long n) { //print the body of the pyramid
     for (long cell = 1; cell <= num_of_cells; cell += 1) { //loop from cell to cell
         if (cell_has_prime(row, cell, n)) {
             cs1010_print_string("#");
         } else {
             cs1010_print_string(" ");
         }
     }
}

int main()
{
    long n = cs1010_read_long(); //a fixed number
    long h = cs1010_read_long(); //a variable that needs to minus one everytime through loop until h = 1 --> used to get number of left blanks

    if (h == 1) { //if height h is input as 1, regardless of value of n
        cs1010_println_string("#");
    } else {
        //do first row first, before moving on to 2nd row and beyond
        print_left_blank(h);
        cs1010_println_string("#");

        h -= 1; //MINUS h once before entering the loop below ==> for all other rows of the traingle
        long row = 2; //set row to start from second row
        while (h >= 1) {
            print_left_blank(h);
            long num_of_cells = cells(row); //return number of cells in this row
            print_body(num_of_cells, row, n);
            h -= 1;
            row += 1;
            cs1010_println_string(""); //print new line at the end
        }
    }
}
