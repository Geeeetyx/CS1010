/**
 * CS1010 Semester 1 AY21/22
 * Assignment 2: Prime
 *
 * Reads in an integer n from standard input and print 
 * the smallest prime larger or equal to n.
 *
 * @file: prime.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */
#include "cs1010.h"
#include <math.h>
#include <stdbool.h>

bool check_prime(long n) {
    if ((n == 2) || (n == 3)) {
        return true;
    }
    if ((n <= 1) || (n % 2 == 0) || (n % 3 == 0)) {
        return false;
    }
    for (long i = 5; i <= sqrt(n); i += 6) {
        if ((n % i == 0) || (n % (i+2) == 0)) {
            return false;
        }
    }
    return true;
}

int main()
{
    long n = cs1010_read_long();
    if (check_prime(n)) {
        cs1010_println_long(n);
    } else {
        bool prime = false;
        for (long next_prime = n; prime == false; next_prime += 1) {
            if (check_prime(next_prime)) {
                prime = true;
                cs1010_println_long(next_prime);
            } else {
                prime = false;
            }
        }
    }   
}
