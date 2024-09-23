#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <string.h>

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    NO_MULTIPLES, // h
    PRIME_OK,     // P
    PRIME_NOT,
    PRIME_NEGATIVE,
    PRIME_NOT_NATURAL,
    FACTORIAL_OVERFLOW//f
};

enum Errors input_fl_err(int argc, char *argv[], int *flag);
enum Errors input_num_convert_err(const char *str, long int *number);
enum Errors find_multiples(int x);
enum Errors prime_err(long int number);
enum Errors split_number_to_digits(long int number, char **result, int *size_arr_res);
enum Errors sum_of_numbers(long int number, long long int *result);
long int factorial(int n);
enum Errors factorial_with_overflow_check(long int number); 
enum Errors table_of_degrees(long int ***result, long int number);

#endif