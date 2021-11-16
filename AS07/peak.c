/**
 * CS1010 Semester 1 AY21/22
 * Assignment 7: Peak
 *
 * @file: peak.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */
#include "cs1010.h"

/**
 * Find the peak in the array, except those at the first and last index
 *
 * @param[in] list The list of elevations
 * @param[in] start The starting index to search from, forwards
 * @param[in] end The last index to search from, backwards
 * @return Return the position of the peak
 *
 */
long findPeak(const long list[], long start, long end) {
    if ((end - start) < 3) {
        return -1;
    }

    long mid = (start + end) / 2;
    long current = list[mid];

    //mid is higher than the left and right points, thus it is the peak
    if ((current > list[mid + 1]) && (current > list[mid - 1])) {
        return mid;
    }
    
    //mid is the same height as the left and right points
    //check both sides for peak
    if ((current == list[mid - 1]) && (current = list[mid + 1])) {
        long nextHeight = findPeak(list, start, mid);
        if (nextHeight != -1) {
            return nextHeight;
        }
        return findPeak(list, mid, end);
    }

    //check for peak on right side
    if ((current <= list[mid + 1]) && (current >= list[mid - 1])) {
        return findPeak(list, mid, end);
    }

    //peak is on the left side
    return findPeak(list, start, mid);
}

int main()
{
    size_t n = cs1010_read_size_t();
    long* heights = cs1010_read_long_array(n);
    if (heights != NULL) {
        long position = findPeak(heights, 0, (long) n);
        if (position == -1) {
            cs1010_println_string("no peak");
        } else {
            cs1010_println_long(position);
        }
        free(heights);
    } else {
        cs1010_println_string("Unable to allocate array");
        free(heights);
        return -1;
    }
}
