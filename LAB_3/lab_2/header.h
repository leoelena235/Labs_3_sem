#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

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
void print_vector(vector *vect);
vector_kill(vector *vect);
enum Errors norm_inf(vector *vect, double *norm);
enum Errors norm_m();
enum Errors norm_p(vector *vect, double *norm, unsigned int p);
#endif
