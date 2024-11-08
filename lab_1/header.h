#ifndef _HEADER_H
#define _HEADER_H

#include <stdio.h>
#include <stdlib.h>

enum Errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY
};

enum Errors func_10_to_2_in_pow_r(long int number, int r, char *result, int *count);
void print_num(char *result, int count);
int sum(int num1, int num2);
int negative(int num);

#endif