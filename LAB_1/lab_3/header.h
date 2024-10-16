#ifndef HEADER_H_
#define HEADER_H_

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <string.h>

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    OVERFLOW
};

enum Errors input_fl_err(int argc, char *argv[], int *flag);
enum Errors convert_str_to_double(const char *str, double *result);
void solve_quadratic_equation(double a, double b, double c, double epsilon, double *x1, double *x2);
void print_solutions(double epsilon, double coefficients[3]);
enum Errors generate_permutations(double coefficients[3], double epsilon);
enum Errors input_num_convert_err(const char *str, long long int *number);
int is_multiple(long int num1, long int num2);
int is_right_triangle(double a, double b, double c, double epsilon);

#endif