#include "header.h"
enum Errors input_valid(int argc, char **argv)
{
    if ((argc != 4) ||
        ((argv[2][0] != '-' && argv[2][0] != '/') ||
         (argv[2][1] != 'a' && argv[2][1] != 'd') ||
         argv[2][2] != '\0'))
    {
        return INVALID_INPUT;
    }

    if (strcmp(argv[1], argv[3]) == 0)
    {
        return INVALID_INPUT;
    }

    return OK;
}

//  по возрастанию
int compare_a(const void *a, const void *b)
{
    const Employee *emp1 = (const Employee *)a;
    const Employee *emp2 = (const Employee *)b;

    if (fabs(emp1->salary - emp2->salary) > EPS)
        return (emp1->salary > emp2->salary) ? 1 : -1;
    int surname_cmp = strcmp(emp1->surname, emp2->surname);
    if (surname_cmp != 0)
        return surname_cmp;
    int name_cmp = strcmp(emp1->name, emp2->name);
    if (name_cmp != 0)
        return name_cmp;
    return (emp1->id - emp2->id);
}

// по убыванию
int compare_d(const void *a, const void *b)
{
    const Employee *emp1 = (const Employee *)a;
    const Employee *emp2 = (const Employee *)b;

    if (fabs(emp1->salary - emp2->salary) > EPS)
        return (emp1->salary < emp2->salary) ? 1 : -1;
    int surname_cmp = strcmp(emp1->surname, emp2->surname);
    if (surname_cmp != 0)
        return -surname_cmp;
    int name_cmp = strcmp(emp1->name, emp2->name);
    if (name_cmp != 0)
        return -name_cmp;
    return (emp2->id - emp1->id);
}

enum Errors read_from_file(FILE *input, Employee **data, int *size, int *capacity)
{
    Employee temp;
    int count = 0;
    while (fscanf(input, "%d %63s %63s %lf", &temp.id, temp.name, temp.surname, &temp.salary) == 4)
    {
        if (temp.id < 0 || temp.salary < 0 || strspn(temp.name, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != strlen(temp.name) || strspn(temp.surname, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != strlen(temp.surname))
        {
            return INVALID_INPUT;
        }

        if (*size >= *capacity)
        {
            *capacity *= 2;
            Employee *new_data = (Employee*)realloc(*data, *capacity * sizeof(Employee));
            if (!new_data)
                return INVALID_MEMORY;
            *data = new_data;
        }
        (*data)[(*size)++] = temp;
        count++;
    }
    
    return (count > 0) ? OK : INVALID_INPUT;
}
