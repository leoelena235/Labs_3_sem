#include "header.h"

enum Errors check_valid(char *str, size_t len)
{
    for (size_t i = 0; i < len; ++i)
    {
        if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')))
            return INVALID_INPUT;
    }
    return OK;
}

enum Errors read_from_file(FILE *in, Student **array, int *size, int *capacity)
{
    if (in == NULL || array == NULL || size == NULL || capacity == NULL)
    {
        return INVALID_INPUT;
    }
    *size = 0;
    *array = (Student *)malloc(*capacity * sizeof(Student));

    if (*array == NULL)
    {
        return INVALID_MEMORY;
    }

    while (fscanf(in, "%d %s %s %s %hhu %hhu %hhu %hhu %hhu",
                  &(*array)[*size].id,
                  (*array)[*size].name,
                  (*array)[*size].surname,
                  (*array)[*size].group,
                  &(*array)[*size].marks[0],
                  &(*array)[*size].marks[1],
                  &(*array)[*size].marks[2],
                  &(*array)[*size].marks[3],
                  &(*array)[*size].marks[4]) == 9)
    {
        (*size)++;
        if (*size >= *capacity)
        {
            int new_capacity = (*capacity) * 2;
            Student *new_array = (Student *)realloc(*array, new_capacity * sizeof(Student));

            if (new_array == NULL)
            {
                return INVALID_MEMORY;
            }

            *array = new_array;
            *capacity = new_capacity;
        }

        Student *current_student = &(*array)[*size - 1];
        current_student->average_score = calculate_average(current_student->marks, 5);
    }
    return OK;
}

double calculate_average(const unsigned char *marks, int count)
{
    if (marks == NULL || count <= 0)
    {
        return -1.0;
    }

    int sum = 0;
    for (int i = 0; i < count; i++)
    {
        sum += marks[i];
    }
    return sum / (double)count;
}

void log_students_above_average(Student *students, int size, FILE *log_file)
{
    if (students == NULL || log_file == NULL || size <= 0)
    {
        fprintf(stderr, "Invalid input to log_students_above_average function\n");
        return;
    }

    // Подсчет общего среднего балла
    double total_average = 0;
    for (int i = 0; i < size; i++)
    {
        total_average += students[i].average_score;
    }
    total_average /= size;

    // Запись в файл информации о студентах с баллом выше среднего
    fprintf(log_file, "Students with average score above %.2f:\n", total_average);
    for (int i = 0; i < size; i++)
    {
        if (students[i].average_score > total_average)
        {
            fprintf(log_file, "%s %s\n", students[i].name, students[i].surname);
        }
    }
}

int compare_by_id(const void *a, const void *b)
{
    if (a == NULL || b == NULL)
    {
        return 0;
    }
    return ((Student *)a)->id - ((Student *)b)->id;
}

int compare_by_surname(const void *a, const void *b)
{
    if (a == NULL || b == NULL)
    {
        return 0;
    }
    return strcmp(((Student *)a)->surname, ((Student *)b)->surname);
}

int compare_by_name(const void *a, const void *b)
{
    if (a == NULL || b == NULL)
    {
        return 0;
    }
    return strcmp(((Student *)a)->name, ((Student *)b)->name);
}

int compare_by_group(const void *a, const void *b)
{
    if (a == NULL || b == NULL)
    {
        return 0;
    }
    return strcmp(((Student *)a)->group, ((Student *)b)->group);
}

void log_sorted_students(Student *students, int size, FILE *log_file)
{
    if (students == NULL || log_file == NULL || size <= 0)
    {
        fprintf(stderr, "Invalid input to log_sorted_students function\n");
        return;
    }

    fprintf(log_file, "Sorted students:\n");
    for (int i = 0; i < size; i++)
    {
        fprintf(log_file, "%d %s %s, Group: %s, Average Score: %.2f\n",
                students[i].id, students[i].name, students[i].surname, students[i].group, students[i].average_score);
    }
}

void menu(Student *students, int size, const char *log_path)
{
    int choice;
    FILE *log_file = fopen(log_path, "w");
    if (log_file == NULL)
    {
        printf("Error opening log file\n");
        return;
    }

    while (1)
    {
        printf("\nMenu:\n1. Search by ID\n2. Search by Surname\n3. Search by Name\n4. Search by Group\n5. Sort by ID\n6. Sort by Surname\n7. Sort by Name\n8. Sort by Group\n9. Students above average\n0. Exit\nChoose an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            search_student(students, size, log_file, SEARCH_ID);
            break;
        case 2:
            search_student(students, size, log_file, SEARCH_SURNAME);
            break;
        case 3:
            search_student(students, size, log_file, SEARCH_NAME);
            break;
        case 4:
            search_student(students, size, log_file, SEARCH_GROUP);
            break;
        case 5:
            qsort(students, size, sizeof(Student), compare_by_id);
            log_sorted_students(students, size, log_file);
            break;
        case 6:
            qsort(students, size, sizeof(Student), compare_by_surname);
            log_sorted_students(students, size, log_file);
            break;
        case 7:
            qsort(students, size, sizeof(Student), compare_by_name);
            log_sorted_students(students, size, log_file);
            break;
        case 8:
            qsort(students, size, sizeof(Student), compare_by_group);
            log_sorted_students(students, size, log_file);
            break;
        case 9:
            log_students_above_average(students, size, log_file);
            break;
        case 0:
            fclose(log_file);
            return;
        default:
            printf("Invalid option\n");
        }
    }
}

void search_student(Student *students, int size, FILE *log_file, int search_type)
{
    if (students == NULL || log_file == NULL || size <= 0)
    {
        fprintf(stderr, "Invalid input to search_student function\n");
        return;
    }

    if (search_type != SEARCH_ID && search_type != SEARCH_SURNAME &&
        search_type != SEARCH_NAME && search_type != SEARCH_GROUP)
    {
        fprintf(stderr, "Invalid search type\n");
        return;
    }
    char query[64];
    printf("Enter search term: ");
    scanf("%63s", query);

    for (int i = 0; i < size; i++)
    {
        int found = 0;
        switch (search_type)
        {
        case SEARCH_ID:
            found = (students[i].id == atoi(query));
            break;
        case SEARCH_SURNAME:
            found = (strcmp(students[i].surname, query) == 0);
            break;
        case SEARCH_NAME:
            found = (strcmp(students[i].name, query) == 0);
            break;
        case SEARCH_GROUP:
            found = (strcmp(students[i].group, query) == 0);
            break;
        }
        if (found)
        {
            fprintf(log_file, "Student found: %s %s, Group: %s, Average Score: %.2f\n",
                    students[i].name, students[i].surname, students[i].group, students[i].average_score);
            printf("Student found: %s %s\n", students[i].name, students[i].surname);
        }
    }
}
