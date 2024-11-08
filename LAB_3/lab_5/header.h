#ifndef _HEADER_H
#define _HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define eps 1e-6

enum Errors
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

enum SearchType {
    SEARCH_ID,
    SEARCH_SURNAME,
    SEARCH_NAME,
    SEARCH_GROUP
};


enum Errors check_valid(char *str, size_t len);
enum Errors read_from_file(FILE *input, Student **array, int *size, int *capacity);
void menu(Student *students, int size, const char *log_path);
double calculate_average(const unsigned char *marks, int count);
void log_students_above_average(Student *students, int size, FILE *log_file);
void search_student(Student *students, int size, FILE *log_file, int search_type);
int compare_by_group(const void *a, const void *b);
int compare_by_name(const void *a, const void *b);
int compare_by_surname(const void *a, const void *b);

int compare_by_id(const void *a, const void *b);

#endif
