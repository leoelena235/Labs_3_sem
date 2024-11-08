#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EPS 1e-10

enum Errors
{
    OK,
    INVALID_INPUT,
    ERROR_OPEN_FILE,
    INVALID_MEMORY
};

typedef struct
{
    int id;
    char name[64];
    char surname[64];
    double salary;
} Employee;

enum Errors input_valid(int argc, char **argv);
enum Errors read_from_file(FILE *input, Employee **data, int *size, int *capacity);
int compare_d(const void *a, const void *b);
int compare_a(const void *a, const void *b);

#endif
