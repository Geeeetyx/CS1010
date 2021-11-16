/**
 * CS1010 Semester 1 AY21/22
 * Assignment 4: SelectionSort
 *
 * @file: selection.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */

#include "cs1010.h"

void printArray(long len, long list[len]) {
    for (long i = 0; i < len; i += 1) {
        cs1010_print_long(list[i]);
        cs1010_print_string(" ");
    }
    cs1010_println_string("");
}

void selectionSort(long len, long list[len]) {
    for (long i = 0; i < len - 1; i += 1) {
        long max_so_far = list[0];
        long key = 0;
        long end = len - i;
        for (long j = 1; j < end; j += 1) {
            if (list[j] > max_so_far) {
                max_so_far = list[j];
                key = j;
            }
        }
        long temp = list[end - 1];
        list[end - 1] = max_so_far;
        list[key] = temp;
        printArray(len, list);
    }
}


int main() 
{
    long n = cs1010_read_long(); //number of integers to sort
    long list[10000];
    for (long i = 0; i < n; i += 1) {
        list[i] = cs1010_read_long();
    }

    selectionSort(n, list);
}
