#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define MAX_LINE_LENGTH 1024

enum Errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OPEN_FILE
};

void close_files(FILE *input, FILE *output);
enum Errors read_input_from_file(FILE **input, char **buffer, int *len, int *capacity);
int determine_min_base(const char *number);
enum Errors convert_str_to_ll_int(const char *str, long long *result, int base);
enum Errors main_func(FILE *input, FILE *output, char *buffer, int *len, int *capacity);
#endif