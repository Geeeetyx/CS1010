/**
 * CS1010 Semester 1 AY21/22
 * Assignment 5: CountingSort
 *
 * Read in a series of numbers between 0 and 10000 
 * and sort them using counting sort.
 *
 * @file: countingsort.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */
#include "cs1010.h"

/**
 * Finds the max element in the list
 * This max element will be used as the range of a list in the countingSort function
 * 
 * @param[in] list The unsorted array of integers
 * @param[in] n The length of the array
 * @return max The max element in the array
 *
 */
long findMax(long list[], long n) {
    long max = list[0];
    for (long i = 1; i < n; i += 1) {
        if (list[i] > max) {
            max = list[i];
        }
    }
    return max;
}

void printArray(long list[], long n) {
    for (long i = 0; i < n; i += 1) {
        cs1010_println_long(list[i]);
    }
}

/**
 * Use counting sort to sort an array in ascending order via several steps
 * Step 1: Create a counts array, then counts[array[index]] += 1
 * Step 2: Modify the counts array such that counts[i] contains the actual
 * position of this number in the sorted array
 * Step 3: Build the sorted array
 *
 * @pre list contains positive intgers, to be between 0 and 10000 inclusive
 * @param[in] list The array of unsorted numbers
 * @param[in] n The length of the unsorted array
 * @param[in] max The range of the counts array, as we're storing the counts 
 * of each digit at their respective indexes in the counts list
 *
 */
void countingSort(long list[], long n, long max) {
    long counts[10001];
    for (long i = 0; i < n; i += 1) {
        counts[list[i]] += 1;
    }

    for (long i = 1; i <= max; i += 1) {
        counts[i] += counts[i - 1];
    }

    long sorted[10001];
    for (long i = 0; i < n; i += 1) {
        sorted[counts[list[i]] - 1] = list[i];
        counts[list[i]] -= 1;
    }

    printArray(sorted, n);
}
        
int main()
{
    long n = cs1010_read_long();
    long list[10001];
    for (long i = 0; i < n; i += 1) {
        list[i] = cs1010_read_long();
    }
    long max = findMax(list, n);
    countingSort(list, n, max);
}
