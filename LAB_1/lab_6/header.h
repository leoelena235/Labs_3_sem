#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>

enum Errors
{
    OK,
    INVALID_INPUT,
    OVERFLOW_ERROR
};

enum Errors convert_str_to_double (const char *str, double * result);
double trapezoidal_method(double (*f)(double), double a, double b, int n);
double integral_with_eps(double epsilon, double (*f)(double), double a, double b) ;
double result_a(double x);
double result_b(double x);
double result_c(double x);
double result_d(double x);

#endif
