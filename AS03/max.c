/**
 * CS1010 Semester 1 AY21/22
 * Assignment 3: Max
 *
 * Read in a sequence of numbers and recursively find
 * the maximum.
 *
 * @file: max.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */
#include "cs1010.h"

long max(const long list[10000], long start, long end)
{
    //First Case: when list only has 2 elements
    if (start + 1 == end) {
        if (list[start] > list[end]) {
            return list[start];
        }
        return list[end];
    }
    
    //All other cases: list has more than 2 elements
    long maximum = max(list, start + 1, end);
    if (list[start] >= maximum) {
        return list[start];
    }
    return maximum;
}

int main()
{
    long n = cs1010_read_long();
    long list[n];
    for (long i = 0; i < n;  i += 1) {
        list[i] = cs1010_read_long();
    }
    
    if (n == 1) {
        cs1010_println_long(list[0]);
    } else {
        long mid = (n - 1) / 2;
        //split list into 2 halves, call max twice each half
        long left_max  = max(list, 0, mid);
        long right_max = max(list, mid + 1, n - 1);

        if (left_max > right_max) {
            cs1010_println_long(left_max);
        } else {
            cs1010_println_long(right_max);
        }
    }
}
