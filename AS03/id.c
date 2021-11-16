/**
 * CS1010 Semester 1 AY21/22
 * Assignment 3: ID
 *
 * @file: id.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */
#include "cs1010.h"

long R(long n) {
    long sum = 0; 
    while (n != 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum % 13;
}

int main()
{
    long n = cs1010_read_long();
    long remainder = R(n);
    
    char codes[13] = {'Y','X','W','U','R','N','M','L','J','H','E','A','B'};
    putchar(codes[remainder]);
    cs1010_println_string("");
}
