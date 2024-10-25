
#ifndef HEADER_H
#define HEADER_H

#include <stdbool.h>
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

enum Errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
   // NOT_ENOUGH_VERTICES
};
enum Errors is_valid_flag(const char *str);

enum Errors is_convex_polygon(int *result, int num_vertices, ...);
double oriented_area(double x1, double y1, double x2, double y2, double x3, double y3);

enum Errors evaluate_polynomial(double *result, double x, int count, ...);\


enum Errors find_kaprekar_numbers(int base, size_t count_nums, ...);
int convert_to_decimal(char *str, int base);
char *decimal_to_base(int decimal, int base);
int is_kaprekar(int num, int base);
int count_digits(int decimal, int base);

#endif