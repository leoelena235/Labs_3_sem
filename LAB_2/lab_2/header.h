#ifndef HEADER_H
#define HEADER_H

#include <stdarg.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Errors
{
    OK,
    INVALID_INPUT,
    INVALID_ARGUMENT_COUNT,
    INVALID_ARGUMENT
};

enum Errors geometric_mean(double *result, int count, double numbers[]);
enum Errors convert_str_to_int(const char *str, long long int *number, int base);
enum Errors recurse_double_in_int_pow(double base, int exp, double *result);

#endif