#ifndef HEADER_H_
#define HEADER_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>

enum Errors
{
    OK,
    INVALID_INPUT,
    OVERFLOW_ERROR,
    FILE_ERROR,
    ERROR_OPEN_FILE
};

enum Errors input_fl_err(int argc, char *argv[], int *flag);
enum Errors files_func_1(const char *input_1, const char *input_2, const char *output_file);
void read_and_print_lexeme(FILE *file, FILE *f_out, char **lexeme);
char* read_lexeme(FILE* file);

void convert_to_base4(char *dest, char c);
void convert_to_base8(char *dest, char c);
enum Errors convert_str_to_double(const char *str, double *result);
enum Errors files_func_2(const char *input_file, const char *output_file);

#endif
