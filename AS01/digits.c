/**
 * CS1010 Semester 1 AY21/22
 * Assignment 1: Digits
 *
 * Read in a positive integer from the standard input and print
 * the sum of its digits to the standard output.
 *
 * @file: digits.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */

#include "cs1010.h"

long sum_of_digits(long number) {
	if (number/10 == 0){
		return number;
	}
	return (number%10) + sum_of_digits(number/10);
}


int main()
{
	long number = cs1010_read_long();
	long sum = sum_of_digits(number);
	cs1010_print_long(sum);
	cs1010_println_string("\0");
}
