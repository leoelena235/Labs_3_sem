#ifndef _HEADER_H
#define _HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define eps 1e-6

enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OPEN_FILE
};

typedef struct
{
    int id;
    char name[64];
    char surname[64];
    char group[64];
    unsigned char marks[5];
    double average_score;
} Student;

enum errors check_valid(char *str, size_t len);
enum errors read_from_file(FILE *input, Student **array, int *size, int *capacity);
void menu();



#endif