#ifndef HEADER_H
#define HEADER_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define EPSILON 1e-10

enum Errors
{
    OK,
    INVALID_INPUT,
    FINALE_REPRESENTATION,
    NO_FINALE_REPRESENTATION,
    INVALID_MEMORY
};
enum Errors valid_base(int base);
enum Errors check_fractions(int base, int *count, double **res,int arg_count, ...);
enum Errors has_finite_representation(double fraction, int base);
int gcd(int a, int b);
bool is_prime(int number);
#endif