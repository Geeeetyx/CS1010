/**
 * CS1010 Semester 1 AY21/22
 * Assignment 3: Days
 *
 * @file: days.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */
#include "cs1010.h"

int main() 
{
    long month = cs1010_read_long();
    long day   = cs1010_read_long();

    long days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    long sum = 0;
    
    for (long i = 0; i < month - 1; i += 1) {
        sum += days[i];
    }

    sum += day;
    cs1010_println_long(sum);
}
