#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

enum Errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY
};
#define MIN_SIZE 10
#define MAX_SIZE 10000
#define MIN_VALUE -1000
#define MAX_VALUE 1000

enum Errors generate_random_array(int **array, int size, int min_value, int max_value);

enum Errors convert_str_to_ll_int(const char *str, long long *result, int base);
void fill_array_with_random_numbers_1(int *array, int size, int a, int b);
enum Errors find_min_max_and_swap(int *array, int size);
void print_array_int(int *array, int size);

enum Errors task_2(int len, int *A, int *B, int **C);

#endif