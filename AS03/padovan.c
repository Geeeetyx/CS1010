/**
 * CS1010 Semester 1 AY21/22
 * Assignment 3: Padovan
 *
 * @file: padovan.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */
#include "cs1010.h"

long* pad(const long length, long list[length]) {

    list[0] = 1;
    list[1] = 0;
    list[2] = 0;

    for (long i = 3; i <= length; i += 1) {
        list[i] = list[i-2] + list[i-3];
    }
    return list;
}

int main()
{
    long n = cs1010_read_long();
    long list[n+1];
    
    long *padovan;
    padovan = pad(n+1, list);
    
    for (long i = n; i >= 0; i -= 1) {
        cs1010_println_long(padovan[i]);
    }
}
