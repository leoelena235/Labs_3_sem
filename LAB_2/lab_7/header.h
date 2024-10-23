#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
enum Errors
{
    INVALID_INPUT,
    OK,
    NO_ROOTS
};

enum Errors dichotomy_method(double left, double right, double epsilon, double (*f)(double), double *result);

double function_1(double x);
double function_2(double x);
double function_3(double x);
double function_4(double x);
double function_5(double x);
double function_6(double x);
double function_7(double x);
double function_8(double x);
double function_9(double x);

#endif