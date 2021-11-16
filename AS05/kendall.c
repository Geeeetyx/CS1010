/*
 * CS1010 Semester 1 AY21/22
 * Assignment 5: Kendall
 *
 * Read in a sequence of numbers and find its kendall tau 
 * distance.
 *
 * @file: kendall.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */
#include "cs1010.h"

/**
 * This function returns the total number of number pairs possible from numbers 1 to n
 *
 * @param[in] n the end number from 1 to n
 * @return combinations the number of combination of pairs
 */
long totalCombinations(size_t n) {
    long combinations = ((n * (n - 1)) / 2);
    return combinations;
}

/** 
 * This function finds the total number of pairs in the list that are not in order
 * For example, the given list is {2, 3, 1}, the out of order pairs are as follows:
 * (2, 1), (3, 1). Thus, the output would be 2.
 *
 * @pre list is not empty
 *
 * @param[in] list The list of given numbers
 * @param[in] n The length of the list
 *
 * @return count The total number of pairs that are not in order
 *
 */
long out_of_order(long list[], size_t n) {
    long count = 0;
    
    for (size_t i = 0; i < n; i += 1) {
        for (size_t j = i + 1; j < n; j += 1) {
            if (list[i] > list[j]) {
                count += 1;
            }
        }
    }
    return count;
}

/** 
 * This function calculates the Kendall tau distance 
 * Calculate the total number of out_of_order pairs divided by the total number of pairs
 *
 * @param[in] out_of_order The total number of pairs of numbers in the list that are not in order
 * @param[in] totalCombinations The total number of pairs of numbers from 1 to n
 *
 * @return tau The Kendall tau distance
 */
double kendallTau(long out_of_order, long totalCombinations) {
    double tau = (out_of_order * 1.0) / totalCombinations;
    return tau;
}

int main()
{
    size_t n = cs1010_read_size_t();
    long* numbers = cs1010_read_long_array(n);
    if (numbers != NULL) {
        cs1010_println_double(kendallTau(out_of_order(numbers,n), totalCombinations(n)));
        free(numbers);
    }
}
