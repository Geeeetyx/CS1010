/**
 * CS1010 Semester 1 AY21/22
 * Assignment 6: Contact
 *
 * @file: contact.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */
#include "cs1010.h"

/**
 * For indirect contact only, print out "contact through" and 
 * the id of the person in contact with our 2 people query
 * 
 * @param[in] index the id of the 3rd person for indirect contact
 *
 */
void printIndirectContact(long index) {
    cs1010_print_string("contact through ");
    cs1010_println_long(index);
}

/** 
 * Perform contact tracing between 2 people with 3 scenarios
 * 1: direct contact
 * 2: indirect contact --> 3 cases
 *    a) when the indirect contact is before the m id
 *    b) when the indirect contact is in between m and n id
 *    c) when the indirect contact is after n id
 * 3: no contact
 *
 * @param[in] m the first id
 * @param[in] n the second id
 * @param[in] contact array of contact traces of a certain number of people
 * @param[in] size the number of people with contact tracing
 *
 */
void contactTracing(long m, long n, char **contact, size_t size) {
    long firstID  =  m;
    long secondID =  n;

    if (m > n) {
        firstID  = n;
        secondID = m;
    }
    
    //Case of direct contact
    if (contact[secondID][firstID] == '1') {
        cs1010_println_string("direct contact");
        return;
    }

    //Case 1 of indirect contact
    for (long i = 0; i < firstID; i += 1) {
        if (contact[firstID][i] == '1' && contact[secondID][i] == '1') {
            printIndirectContact(i); 
            return;
        }
    }

    //Case 2 of indirect contact
    for (long j = firstID + 1; j < secondID; j += 1) {
        if (contact[j][firstID] == '1' && contact[secondID][j] == '1') {
            printIndirectContact(j); 
            return;
        }
    }

    //Case 3 of indirect contact
    for (long k = secondID + 1; k < (long) size; k += 1) {
        if (contact[k][firstID] == '1' && contact[k][secondID] == '1') {
            printIndirectContact(k); 
            return;
        }
    }
    //Case of no contact
    cs1010_println_string("no contact");
}

/** 
 * Dealloacte a 2D array and free the memory on the heap
 *
 * @param[in] array The array we want to deallocate 
 * @param[in] size The number of rows in the 2D array
 */
void deallocateArray(char **array, size_t size) {
    for (size_t i = 0; i < size; i += 1) {
        free(array[i]);
    }
    free(array);
}

int main()
{
    size_t size = cs1010_read_size_t();

    char **contact = malloc(size * sizeof(char*));
    if (contact == NULL) {
        cs1010_println_string("unable to allocate array");
        free(contact);
        return 0;
    }

    for (size_t i = 0; i < size; i += 1) {
        contact[i] = cs1010_read_word();
        if (contact[i] == NULL) {
            cs1010_println_string("unable to allocate array");
            for (size_t j = 0; j <= i; j += 1) {
                free(contact[j]);
            }
            free(contact);
        }
    }
        
    long m = cs1010_read_long();
    long n = cs1010_read_long();

    contactTracing(m, n, contact, size);
    deallocateArray(contact, size);
}
