#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define MAX_POW_TO_DALAY 7
#define PI 3.1415926535
#define EKS 2.71828182846

enum Errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    OVERFLOW_ERROR
};

enum Errors convert_str_to_double(const char *str, double *result);
#endif