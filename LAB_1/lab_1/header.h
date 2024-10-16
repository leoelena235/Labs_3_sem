#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    NO_MULTIPLES, // for h
    PRIME_NOT,
    PRIME_NEGATIVE,
    PRIME_NOT_NATURAL
};

enum Errors input_fl_err(int argc, char *argv[], int *flag);
enum Errors input_num_convert_err(const char *str, long int *number);
enum Errors find_multiples(int x);
enum Errors prime_err(long int number);
enum Errors hex_digit(long long int number, char **result, int *count);
enum Errors degree_of_table( int number, long long int ***result_e);
enum Errors sum_of_numbers(long int number, long long int *result_a);
long int factorial(int n);
enum Errors factorial_with_overflow_check(long int number); 

#endif
