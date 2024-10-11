#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <ctype.h>

enum Errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_FILE
};
enum Errors valid_flag(const char *str);
enum Errors file_func(int argc, char *argv[], FILE **input, FILE **output, char *output_filename);
void remove_arabic_numerals(FILE *input, FILE *output);
enum Errors count_latin_letters(FILE *input, FILE *output);
void count_special_characters(FILE *input, FILE *output);
void change_simb(FILE *input, FILE *output);

#endif