#ifndef HEADER_H
#define HEADER_H

#include <stdarg.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>
#include <time.h>
#define BASE 256
#define HASH_SPREAD 1000000007
enum Errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OPEN_FILE
};

enum Errors find_substring(int **result, int *count_val, const char *str, const int count, ...);
enum Errors validate_input(const char *substr, const int count, va_list args);
enum Errors search_substring_in_file(int** result, int* cur_elem, const char *filename, long long int str_hash, int substring_len);
long long int calculate_hash(const char *str, int len, int begin);

#endif