#ifndef HEADER_H__
#define HEADER_H__

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum Errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY
};

enum Errors char_to_int(int *value, char chr, int base);
char int_to_char(int num);
enum Errors add_numbers_in_base(char **result, const char *num_1, const char *num_2, int base);
enum Errors sum_of_numbers(int base, int count_nums, ...);

#endif