/**
 * CS1010 Semester 1 AY21/22
 * Assignment 1: Suffix
 *
 * Read in a number and prints out the number with the appropriate suffix.
 *
 * @file: suffix.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */
#include "cs1010.h"

void print_with_suffix(long n) {
	cs1010_print_long(n);	       // print out the integer
	if (n < 10) { 		       // when the number is less thatn 10
		if (n == 1) {
			cs1010_println_string("st");
		} else if (n == 2) {
			cs1010_println_string("nd");
		} else if (n == 3) {
			cs1010_println_string("rd");
		} else {
			cs1010_println_string("th"); //for all numbers less than 10 but not 1, 2 or 3
		}
	} else {
		long tens = (n/10)%10; // get the tens digit
		long ones = n%10;      // get the ones digit

		if (tens != 1) {       // for numbers with their tens digit not being 1
			if (ones == 1) {
				cs1010_println_string("st");
			} else if (ones == 2) {
				cs1010_println_string("nd");
			} else if (ones == 3) {
				cs1010_println_string("rd");
			} else {
				cs1010_println_string("th");
			}
		} else {
			cs1010_println_string("th"); // for all other numbers 
		}
	}
}

int main() 
{
	long number = cs1010_read_long();
	print_with_suffix(number);
}
