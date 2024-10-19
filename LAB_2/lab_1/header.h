#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
enum Errors
{
    INVALID_INPUT,
    OK,
    INVALID_MEMORY,
    INVALID_ARGUMENT
};

enum Errors input_fl_err(int argc, char *argv[]);
int len_string(const char *str);
enum Errors reversed_string(const char *str, char **result_r);
enum Errors upper_str(const char *str, char **result_u);
enum Errors sort_simbols(char *str, char **result_n);
enum Errors concotenation_str(char **str_array, char **result_c, int count_str, unsigned int seed);
enum Errors convert_str_to_int(const char *str, long long int *number, int base);

#endif