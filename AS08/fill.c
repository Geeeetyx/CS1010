/**
 * CS1010 Semester 1 AY21/22
 * Assignment 8: Fill
 *
 * @file: fill.c
 * @author: TAN YU XIANG, GARETH (D07)
 */

#include "cs1010.h"
#include <stdbool.h>

/**
 * Check surrounding pixels, see if they are beyond the boundaries and if they are equal to our new colour
 * 
 * @param[in] image The image we want to update
 * @param[in] m The number of rows in image
 * @param[in] n THe number of columns in image
 * @param[in] colourCode The colour code of the original pixel, to find others in the same segment
 * @param[in] x The x-coordinate of the pixel we are at
 * @param[in] y The y-coordinate of the pixel we are at
 *
 * @return true if pixel is within image boundaries and if it is in the same segment as the original pixel
 */
bool same_segment(long **image, size_t m, size_t n, long colourCode[3], long x, long y) {
    if (x > (long) m || x < 0 || y > (long) n || y < 0) {
        return false;
    }
    for (long i = 0; i < 3; i += 1) {
        if (image[x][y + i] != colourCode[i]) {
            return false;
        }
    }
    return true;
}

/**
 * Perform a fill operation for all pixels in the same segment as the first pixel that was changed
 *
 * @param[in] m The number of rows in image
 * @param[in] n The number of columns in image
 * @param[in] fill_index The index of which fill_operation we are doing currently
 * @param[in] x The x-coordinate of the pixel we are at
 * @param[in] y The y-coordinate of the pixel we are at
 * @param[in, out] image The image we want to update
 * @param[in] fill_operation The array of current fill operations we are pperforming
 * @param[in] colourCode The colour code of the original pixel, to find others in the same segment
 */
void fill(size_t m, size_t n, size_t fill_index, long x, long y, long **image, long **fill_operation, long colourCode[3]) {
    for (long index = 0; index < 3; index += 1) {
        image[x][y + index] = fill_operation[fill_index][2 + index];
    }

    long possible_directions[4][2] = { {0,3}, {0,-3}, {1,0} ,{-1,0} };
    for (long direction = 0; direction < 4; direction += 1) {
       long moveX = possible_directions[direction][0];
       long moveY = possible_directions[direction][1];
       if (same_segment(image, m, n, colourCode, x + moveX, y + moveY)) {
           fill(m, n, fill_index, x + moveX, y + moveY, image, fill_operation, colourCode);
       }
    }
}

/** 
 * Perfom q fill operations on image
 *
 * @param[in] m The number of rows in image
 * @param[in] n The number of columns in image
 * @param[in] q The total number of fill operations
 * @param[in, out] image The image we want to update
 * @param[in] fill_operation The 2D array containing q number of fill operations
 */
void perform_q_fill_operations(size_t m, size_t n, size_t q, long **image, long **fill_operation) {
    for (size_t fill_index = 0; fill_index < q; fill_index += 1) {
        long x = fill_operation[fill_index][0];
        long y = 3 * (fill_operation[fill_index][1]);
        long colourCode[3] = {image[x][y], image[x][y + 1], image[x][y + 2]};
        fill(m, n, fill_index, x, y, image, fill_operation, colourCode);
    }
}

/** 
 * Print the updated image
 *
 * @param[in] m The number of rows in image
 * @param[in] n The number of columns in image
 * @param[in] image The updated image
 */
void print(size_t m, size_t n, long **image) {
    cs1010_print_string("P3 ");
    cs1010_print_long(((long) n + 1) / 3);
    cs1010_print_string(" ");
    cs1010_print_long((long) m + 1);
    cs1010_println_string(" 255");
    
    for (size_t i = 0; i <= m; i += 1) {
        long count = 0;
        for (size_t j = 0; j <= n; j += 1) {
            cs1010_print_long(image[i][j]);
            cs1010_print_string(" ");
            count += 1;
            if (count == 3) {
                cs1010_println_string("");
                count = 0;
            }
        }
    }
}

/** 
 * Deallocate a long type 2D array on the heap
 *
 * @param[in] array The long type array we want to deallocate
 * @param[in] size The number of rows in the array
 */
void deallocateLongArray(long **array, size_t size) {
    for (size_t i = 0; i < size; i += 1) {
        free(array[i]);
    }
    free(array);
}

int main()
{
    size_t m = cs1010_read_size_t();
    size_t n = cs1010_read_size_t();
    n *= 3;

    long **image = malloc(m * sizeof(long*));
    for (size_t i = 0; i < m; i += 1) {
        image[i] = cs1010_read_long_array(n);
        if (image[i] == NULL) {
            for (size_t j = 0; j <= i; j += 1) {
                free(image[i]);
            }
            free(image);
            return -1;
        }
    }

    m -= 1;
    n -= 1;

    size_t q = cs1010_read_size_t();
    long **fill_operation = malloc(q * sizeof(long*));
    for (size_t i = 0; i < q; i += 1) {
        fill_operation[i] = cs1010_read_long_array(5);
        if (fill_operation[i] == NULL) {
            for (size_t j = 0; j <= i; j += 1) {
                free(fill_operation[i]);
            }
            free(fill_operation);
            return -1;
        }
    }
    perform_q_fill_operations(m, n, q, image, fill_operation);
    print(m, n, image);

    deallocateLongArray(image, m + 1);
    deallocateLongArray(fill_operation, q);
}
