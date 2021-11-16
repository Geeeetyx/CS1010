/**
 * CS1010 Semester 1 AY21/22
 * Assignment 9: Digits
 *
 * @file: digits.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */

#include "cs1010.h"
#include <stdbool.h>
#include <limits.h>

#define NCOLS 28
#define NROWS 28
#define WHITE '.'
#define BLACK '#'
#define K 5

typedef struct {
    char *input[NROWS];
    long label;
} digit;

typedef struct {
    digit sample;
    long distance;
} neighbour;

/**
 * Read in training or testing samples
 *
 * @param[in] num_of_samples The number of training or testing samples
 * @param[in,out] sample Either training or testing samples
 *
 * @return true if memory allocation is successful, false otehrwise
 */
bool read_digit(digit *sample, long num_of_samples) {
    for (long i = 0; i < num_of_samples; i += 1) {
        sample[i].label = cs1010_read_long();
        for (long j = 0; j < NROWS; j += 1) {
            sample[i].input[j] = cs1010_read_word();
            if (sample[i].input[j] == NULL) {
                return false;
            }
        }
    }
    return true;
}

/**
 * Free memory allocated to a digit struct array
 *
 * @param[in] sample The struct array to free
 * @param[in] num_of_samples The number of digit structs
 */
void free_sample_digit_struct(digit *sample, size_t num_of_samples) {
    for (size_t i = 0; i < num_of_samples; i += 1) {
        for (size_t j = 0; j < NROWS; j += 1) {
            free(sample[i].input[j]);
        }
    }
    free(sample);
}

/**
 * Print out the label of the test number, followed by the scanned number
 *
 * @param[in] label The label of the test number
 * @param[in] scanned_num The scanned num read by the program
 */
void print(long label, long scanned_num) {
    cs1010_print_long(label);
    cs1010_print_string(" ");
    cs1010_println_long(scanned_num);
}

/**
 * Insert the K nearest neighbours into a "nearest" array, for all scanned numbers nearest to the test sample
 * 
 * @param[in] sample The training sample to be inserted into the "nearest" array 
 * @param[in] distance The distance of the current training sample to the test sample
 * @param[in, out] nearest The array to insert the K nearest neighbours in
 */
void insert(digit sample, long distance, neighbour nearest[]) {
    if (distance > nearest[K - 1].distance) {
        return;
    }
    if (distance == nearest[K - 1].distance && sample.label > nearest[K - 1].sample.label) {
        return;
    }

    long i = K - 1;
    do {
        nearest[i] = nearest[i - 1];
        i -= 1;
    } while (i >= 0 && 
            (nearest[i].distance > distance || (nearest[i].distance == distance && nearest[i].sample.label > sample.label)));

    nearest[i + 1].sample = sample;
    nearest[i + 1].distance = distance;
}

/**
 * Find the distance between a training sample and a test sample
 * 
 * @param[in] training_sample The training sample
 * @param[in] to_test The test sample
 * @param[in] limit The biggest distance amongst all neighbours, if distance > limit, exclude it from the K nearest neighbours
 *
 * @return distance The distance between a training sample and a test sample
 */
long find_distance(digit training_sample, digit to_test, long limit) {
    long distance = 0;
    for (long i = 0; i < NROWS; i += 1) {
        for (long j = 0; j < NCOLS; j += 1) {
            if (distance > limit) {
                return distance;
            }
            if (training_sample.input[i][j] != to_test.input[i][j]) {
                distance += 1;
            }
        }
    }
    return distance;
}

/**
 * Find the smallest distance for any digit
 *
 * @param[in] nearest The array of K nearest neighbours to the test sample
 * @param[in] num The digit to find the shortest distance for
 *
 * @return smallest The shortest distance for num
 */
long find_smallest_distance(neighbour nearest[K], long *num) {
    long smallest = LONG_MAX;
    for (long i = 0; i < K; i += 1) {
        if (nearest[i].sample.label == *num) {
            if (nearest[i].distance < smallest) {
                smallest = nearest[i].distance;
            }
        }
    }
    return smallest;
}

/**
 * If 2 numbers have the same frequency, set the most common digit (mcd) to be the number with the smallest distance
 *
 * @param[in] frequency The array with the frequency of al nearest numbers to the test sample
 * @param[in] nearest The array of the K nearest neighbours to the test sample
 * @param[in, out] max_so_far The current highest number
 * @param[in, out] mcd The number with the highest frequency
 * @param[in] i The position of the most common digit
 */
void tiebreaker(long frequency[10], neighbour nearest[K], long *max_so_far, long *mcd, long *i) {
    long i_distance = find_smallest_distance(nearest, i);
    long max_so_far_distance = find_smallest_distance(nearest, mcd);
    if (i_distance < max_so_far_distance) {
        *max_so_far = frequency[*i];
        *mcd = *i;
    } else if (i_distance == max_so_far_distance) {
        if (*i < *mcd) {
            *max_so_far = frequency[*i];
            *mcd = *i;
        }
    }
}

/**
 * Find the most common digit among the K nearest training samples to the test samples
 *
 * @param[in] nearest The array of the K nearest training samples 
 * @return most_common_digit The number with the highest frequency
 */
long most_common_digit(neighbour nearest[K]) {
    long frequency[10] = {0};
    for (long i = 0; i < K; i += 1) {
        frequency[nearest[i].sample.label] += 1;
    }

    long max_so_far = frequency[0];
    long most_common_digit = 0;
    for (long i = 1; i < 10; i += 1) {
        if (frequency[i] >= max_so_far) {
            if (frequency[i] == max_so_far) {
                tiebreaker(frequency, nearest, &max_so_far, &most_common_digit, &i); 
            } else {
                max_so_far = frequency[i];
                most_common_digit = i;
            }
        } 
    }
    return most_common_digit;
}

/**
 * Interpret the digit in the test sample by comparing with training samples
 *
 * @param[in] training_samples The array of training samples
 * @param[in] num_of_trainings The total number of training samples
 * @param[in] to_test The testing sample to compare with the training samples
 *
 * @return scanned_num The digit the test sample represents
 */
long scan_num(digit *training_samples, long num_of_trainings, digit to_test) {
    neighbour nearest[K];
    for (long i = 0; i < K; i += 1) {
        nearest[i].distance = LONG_MAX;
    }

    for (long j = 0; j < num_of_trainings; j += 1) {
        long d = find_distance(training_samples[j], to_test, nearest[K-1].distance);
        insert(training_samples[j], d, nearest);
    }

    long scanned_num = most_common_digit(nearest);
    return scanned_num;
}

/**
 * Find the percentage of all test samples correctly recognised
 *
 * @param[in] training_samples The array of training samples
 * @param[in] num_of_trainings The total number of training samples
 * @param[in] testing_samples  The array of test samples
 * @param[in] num_of_testings  The number of test samples
 *
 * @return accuracy The accuracy of recognising test samples
 */
double find_percentage_recognised(digit *training_samples, long num_of_trainings, digit *testing_samples, long num_of_testings) {
    long total = 0;
    for (long i = 0; i < num_of_testings; i += 1) {
        long label = testing_samples[i].label;
        long scanned_num = scan_num(training_samples, num_of_trainings, testing_samples[i]);
        print(label, scanned_num);

        if (scanned_num == label) {
            total += 1;
        }
    }

    double accuracy = total * 100.0 / num_of_testings;
    return accuracy;
}

int main()
{
    size_t num_of_train_samples = cs1010_read_size_t();
    digit *training_samples = malloc(num_of_train_samples * sizeof(digit));
    if (training_samples == NULL) {
        free(training_samples);
        return -1;
    }
    
    bool trained = read_digit(training_samples, (long) num_of_train_samples);
    if (!trained) {
        free_sample_digit_struct(training_samples, num_of_train_samples);
        return -1;
    }

    size_t num_of_test_samples = cs1010_read_size_t();
    digit *testing_samples = malloc(num_of_test_samples * sizeof(digit));
    if (testing_samples == NULL) {
        free(testing_samples);
        return -1;
    }
    bool tested = read_digit(testing_samples, (long) num_of_test_samples);
    if (!tested) {
        free_sample_digit_struct(testing_samples, num_of_test_samples);
        return -1;
    }
    
    double accuracy = find_percentage_recognised(training_samples, (long) num_of_train_samples, testing_samples, (long) num_of_test_samples);
    cs1010_println_double(accuracy);

    free_sample_digit_struct(training_samples, num_of_train_samples);
    free_sample_digit_struct(testing_samples, num_of_test_samples);
}
