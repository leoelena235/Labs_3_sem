#ifndef HEADER_H
#define HEADER_H

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
// храненим номер стр и символа
typedef struct {
    int str_number;
    int symbol_number;
} values;

typedef enum Errors {
    OK,
    OPEN_PROBLEM,
    INVALID_MEMORY
} Errors;

typedef struct{
    Errors status;
    values * ans_for_file;//массив вхождений
    int ans_for_file_len;//его длина
    char * filename;
    int count_files;//кол-во обработанных файлов
} finalyAns;

int SizeOfStr (char * s);
void calculate_prefix(char * str, int prefix_mass[], int len);
int StrInFile(char * str, char * file, int prefix_mass[], int len, values ** start);
int checkStr (char * s);
finalyAns * Task(char * str, ...);

#endif
