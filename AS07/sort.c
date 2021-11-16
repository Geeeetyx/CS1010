/**
 * CS1010 Semester 1 AY21/22
 * Assignment 7: Sort
 *
 * @file: sort.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */
#include "cs1010.h"

/**
 * Print the array to the standard output
 *
 * @param[in] n The length of the array
 * @param[in] list The array we want to print
 */
void printArray(size_t n, long *list) {
    for (long i = 0; i < (long) n; i += 1) {
        cs1010_print_long(list[i]);
        cs1010_print_string(" ");
    }
    cs1010_println_string("");
}

/** Sort an array, from both ends of the array
 *
 * @pre All elements in the array are unique
 * @pre The first k elements are in increasing order,
 * the reamining n - k are in decreasing order
 *
 * @param[in] n The length of the array
 * @param[in] list The original unsorted array
 * @param[in, out] sorted An empty array to insert the elements from the original list
 * in ascending order
 *
 */
void sort(size_t n, long *list, long *sorted) {
    if (n == 1) {
        printArray(n, list);
        return;
    }

    long start = 0;
    long end = (long) n - 1;
    long sortedKey = 0;

    while (start <= end) {
        if (list[start] < list[end]) {
            sorted[sortedKey] = list[start];
            start += 1;
        } else {
            sorted[sortedKey] = list[end];
            end -= 1;
        }
        sortedKey += 1;
    }
    printArray(n, sorted);
}

int main()
{
    size_t n = cs1010_read_size_t();
    long* list = cs1010_read_long_array(n);
    long* sorted = malloc(n * sizeof(long));
    if (list != NULL) {
        sort(n, list, sorted);
        free(list);
        free(sorted);
    } else {
        cs1010_println_string("unable to allocate array");
        free(list);
        free(sorted);
        return -1;
    }
}
