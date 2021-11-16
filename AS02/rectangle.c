/**
 * CS1010 Semester 1 AY21/22
 * Assignment 2: Rectangle
 *
 * Reads in two integer numbers corresponding to the width and the 
 * height of a rectangle.   Draw the rectangle with the given characters
 * to the standard output.
 *
 * @file: rectangle.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */
#include "cs1010.h"

#define TOP_LEFT "╔"
#define TOP_RIGHT "╗"
#define BOTTOM_RIGHT "╝"
#define BOTTOM_LEFT "╚"
#define HORIZONTAL "═"
#define VERTICAL "║"

void draw_rectangle(long w, long h) {
    if ((w == 2) && (h == 2)) {
        cs1010_print_string(TOP_LEFT);
        cs1010_println_string(TOP_RIGHT);
        cs1010_print_string(BOTTOM_LEFT);
        cs1010_println_string(BOTTOM_RIGHT);
    } else {
        long h_count = w - 2; //count number of Horizontal lines for top and bottom row (minus away top left and top right)
    
        //print first row
        cs1010_print_string(TOP_LEFT);
        for (long i = 1; i <= h_count; i += 1) {
            cs1010_print_string(HORIZONTAL);
        } 
        cs1010_println_string(TOP_RIGHT);

        //print the body (in between first and last row
        long v_count = h - 2; //number of vertical lines
        long space_count = w - 2;
        for (v_count = h - 2; v_count > 0; v_count -= 1) {
            cs1010_print_string(VERTICAL); //print the first vertical line in the row
            for (long i = 1; i <= space_count; i += 1) {
                cs1010_print_string(" ");
            }
            cs1010_println_string(VERTICAL);
        }

        //print bottom row
        cs1010_print_string(BOTTOM_LEFT);
        for (long i = 1; i <= h_count; i += 1) {
            cs1010_print_string(HORIZONTAL);
        }
        cs1010_println_string(BOTTOM_RIGHT);
    }

}

int main()
{
    long w = cs1010_read_long(); //width
    long h = cs1010_read_long(); //height

    if ((w < 2) || (h < 0)) {
        cs1010_println_string("Width and height are at least 2");
        return 0;
    }

    draw_rectangle(w,h);
}
