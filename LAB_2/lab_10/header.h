#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

enum Errors
{
  OK,
  INVALID_MEMORY,
  INVALID_INPUT
};

double factorial(int n);
enum Errors decomposition_of_a_polynomial(int count, double eps, double x, double **result_k, ...);
enum Errors coef_calculation(double x, double *coefs, int n, double *res);
enum Errors calc_differ(double *coefs, int count, int iter);

#endif