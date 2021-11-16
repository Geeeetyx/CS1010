/**
 * CS1010 Semester 1 AY21/22
 * Assignment 5: Add
 *
 * @file: add.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */

#include "cs1010.h"
#include <stdbool.h>

/**
 * This function adds 2 single digits together. To be called repeatedly
 * @pre x and y are less than 10
 *
 * @param[in] x first digit for addition
 * @param[in] y second digit for addition
 * @param[in,out] carry true if there is a need to carry forward, false otherwise
 *
 * @return digit single digit returned
 */
char addDigit(char x, char y, bool *carry) {
    long total = (x - '0') + (y - '0');
    char digit;
    if (*carry == true) {
        total += 1;
    }

    if (total >= 10) {
        digit = (total % 10) + '0';
        *carry = true;
    } else {
        digit = (char) total + '0';
        *carry = false;
    }
    
    return digit;
}

/** 
 * Sum individual digits in the array, print out as one long string
 *
 * @param[in] n1 first number string
 * @param[in] n2 second number string
 * @param[in] length1 length of first string
 * @param[in] length2 length of second string
 *
 * @pre length1 > length2
 * inputs will be reversed upon calling function if length2 > length1
 */
void add(char n1[], char n2[], long length1, long length2) { //length1 and n1 are bigger than length2 and n2
    char finalDigit[length1 + 2];
    finalDigit[length1 + 1] = '\0';

    long keyN1 = length1 - 1;
    long keyN2 = length2 - 1;    
    long keyFinalDigit = length1;
    bool carry = false;

    while ((keyN1 >= 0) && (keyN2 >= 0)) {
        finalDigit[keyFinalDigit] = addDigit(n1[keyN1], n2[keyN2], &carry);
        keyN1 -= 1;
        keyN2 -= 1;
        keyFinalDigit -= 1;
    }

    //since keyN2 is smaller, we're left with keyN1 since keyN2 is now 0
    char *rest = n1;
    keyN2 = keyN1;
      
    while (keyN2 >= 0) {
        finalDigit[keyFinalDigit] = addDigit(rest[keyN2], '0', &carry);
        keyFinalDigit -= 1;
        keyN2 -= 1;
    }

    if (carry == true) {
        finalDigit[0] = '1';
        cs1010_println_string(finalDigit);
    } else {
        cs1010_println_string(&finalDigit[1]);
    }
}

int main()
{
    char* n1 = cs1010_read_word();
    char* n2 = cs1010_read_word();
    
    long length1 = (long) strlen(n1);
    long length2 = (long) strlen(n2);
    if (length1 > length2) {
        add(n1, n2, length1, length2);
    } else {
        add(n2, n1, length2, length1);
    }
    
    free(n1);
    free(n2);

}
