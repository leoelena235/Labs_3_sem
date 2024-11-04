#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#define Eps 10e-6
enum Errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY
};

typedef struct
{
    double *coordinats;
    int n;
} vector;

enum Errors vector_init(int n, vector *vect, ...);
void print_vect(vector *vect);
enum Errors vector_kill(vector *vect);
enum Errors norm_inf(vector *vect, double *norm);
enum Errors norm_m();
enum Errors norm_p(vector *vect, double *norm, unsigned int p);
enum Errors main_func(unsigned int p,
                      enum Errors (*norm_inf)(vector *, double *),
                      enum Errors (*norm_p)(vector *, double *, unsigned int),
                      enum Errors (*norm_m)(vector *, double *),
                      int *size_1, int *size_2, int *size_3,
                      vector **result_1, vector **result_2, vector **result_3,
                      ...);

#endif
