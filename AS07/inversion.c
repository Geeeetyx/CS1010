/**
 * CS1010 Semester 1 AY21/22
 * Assignment 7: Inversion
 *
 * @file: inversion.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */

#include "cs1010.h"

/** 
 * Find the number of inversions (i.e. number of out-of-order elements) in a given array
 *
 * @param[in] n The length of the array
 * @param[in] list The array we want to check
 * @return The total number of inversions
 */
long countInversions(size_t n, long *list) {
    if (n == 1) {
        return 0;
    }

    long start = 0;
    long end = (long) n - 1;
    long total = 0;

    while (start <= end) {
        if (list[start] < list[end]) {
            start += 1;
        } else {
            total += end - start;
            end -= 1;
        } 
    }
    return total;
}

int main()
{
    size_t n = cs1010_read_size_t();
    long* list = cs1010_read_long_array(n);

    if (list != NULL) {
        long inversions = countInversions(n, list);
        cs1010_println_long(inversions);
        free(list);
    } else {
        cs1010_println_string("unable to allocate array");
        free(list);
        return -1;
    }
}
