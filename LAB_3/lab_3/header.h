#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
enum Errors redd_from_file();

#endif
