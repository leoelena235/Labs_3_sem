#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>

enum Errors
{
    OK,
    INVALID_INPUT,
    OVERFLOW_ERROR
};

enum Errors convert_str_to_double(const char *str, double *result);
enum Errors func_sum_a(const double epsilon, const double x, double *res_a);
enum Errors func_sum_b(const double epsilon, const double x, double *res_b);
double factorial(int n);
enum Errors func_sum_c(const double epsilon, const double x, double *res_c);
enum Errors func_sum_d(const double epsilon, const double x, double *res_d);

#endif
