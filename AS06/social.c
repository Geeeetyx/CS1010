/**
 * CS1010 Semester 1 AY21/22
 * Assignment 6: Social
 *
 * @file: social.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */

#include "cs1010.h"
#include <stdbool.h>

/**
 * Swap the previous and current network
 *
 * @param[in] num_of_ppl The number of people in the network = num of rows in the array
 * @param[in] network The previous network
 * @param[in] k_network The kth degree of seperation network
 */
void swap(size_t num_of_ppl, char **network, char **k_network) {
    for (size_t i = 0; i < num_of_ppl; i += 1) {
        for (size_t j = 0; j <= i; j += 1) {
            network[i][j] = k_network[i][j];
            k_network[i][j] = '0';
        }
    }
}

/**
 * Deallocate the array on the heap and free the memory
 * @param[in] array The array we want to deallocate
 * @param[in] size The number of rows in the array
 */
void deallocateArray(char **array, size_t size) {
    for (size_t i = 0; i < size; i += 1) {
        free(array[i]);
    }
    free(array);
}

/**
 * Check if 2 people are friends
 *
 * @param[in] network The social network we are currently checking
 * @param[in] i The row-coordinate of the position we are checking
 * @param[in] j The column-coordinate of the position we are checking
 *
 * @return Return true if the network[i][j] == '1'
 */
bool check_friend(char **network, size_t i, size_t j) {
    if (i >= j) {
        return network[i][j] == '1';
    }
    return network[j][i] == '1';
}

/**
 * Assign values for the array '1' or '0' if 2 people are connected 
 *
 * @param[in] num_of_ppl The number of rows in the array
 * @param[in] network The social network we are currently checking
 * @param[in] i The first person
 * @param[in] j The second person
 *
 * @return Return '1' if the 2 people i and j are friend. Else, return '0'
 */
char checkConnection(size_t num_of_ppl, char **network, size_t i, size_t j) {
    for (size_t index = 0; index < num_of_ppl; index += 1) {
        if ((check_friend(network, i, index) == true) && (check_friend(network, index, j) == true)) {
            return '1';
        }
    }
    return '0';
}

/** 
 * Create the k_network
 *
 * @param[in] num_of_ppl The number of rows in the array
 * @param[in] network The original social network
 * @param[in] k_network The next iteration of the social network
 */
void k_degrees(size_t num_of_ppl, char **network, char ** k_network) {
    for (size_t i = 0; i < num_of_ppl; i += 1) {
        for (size_t j = 0; j <= i; j += 1) {
            if (check_friend(network, i, j) == true) {
                k_network[i][j] = '1';
            } else {
                k_network[i][j] = checkConnection(num_of_ppl, network, i, j);
            }
        }
    }
}

/**
 * Find the social network at k degrees of seperation, and print the final network to the standard output.
 *
 * @param[in] num_of_ppl The number of rows in the array
 * @param[in] k The degree of seperation
 * @param[in] network The previous social network
 * @param[in] k_network The next social network
 */
void calculateSeperation(size_t num_of_ppl, long k, char **network, char **k_network) {
    for (long i = 1; i < k; i += 1) {
        k_degrees(num_of_ppl, network, k_network);
        swap(num_of_ppl, network, k_network);
    }

    for (size_t i = 0; i < num_of_ppl; i += 1) {
        for (size_t j = 0; j <= i; j += 1) {
            putchar(network[i][j]);
        }
        cs1010_println_string("");
    }
}

int main()
{
    size_t num_of_ppl = cs1010_read_size_t();
    long k = cs1010_read_long();
    char **network = malloc(num_of_ppl * sizeof(char*));
    if (network == NULL) {
        cs1010_println_string("unable to allocate array");
        free(network);
        return 0;
    }
    for (size_t i = 0; i < num_of_ppl; i += 1) {
        network[i] = cs1010_read_word();
        if (network[i] == NULL) {
            cs1010_println_string("unable to allocate array");
            return 0;
        }
    }
    
    char **k_network = malloc(num_of_ppl * sizeof(char*));
    if (k_network == NULL) {
        cs1010_println_string("unable to allocate array");
        free(k_network);
        return 0;
    }
    for (size_t i = 0; i < num_of_ppl; i += 1) {
        k_network[i] = malloc((i + 1) * sizeof(char*));
        if (k_network[i] == NULL) {
            cs1010_println_string("unable to allocate array");
            return 0;
        }
    }
    
    calculateSeperation(num_of_ppl, k, network, k_network);

    deallocateArray(network, num_of_ppl);
    deallocateArray(k_network, num_of_ppl);
}
