#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#define MAX_STR_LEN 100

enum Errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY
};

enum Errors base_input(int *base);
enum Errors err_memory(char **input_str);
enum Errors number_input(char *number, int base);
int convert_str_to_ll_int(const char *str, long long *result, int base);
int convert_to_base(char **result, long long number, int base, char *array_base);
int valid_digit(char digit, int base);
void convert_and_print_max_number(int base, long long int max_number);

#endif
