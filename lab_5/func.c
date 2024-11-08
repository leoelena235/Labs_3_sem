#include "header.h"

enum errors check_valid(char *str, size_t len)
{
    for (size_t i = 0; i < len; ++i)
    {
        if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')))
            return INVALID_INPUT;
    }
    return OK;
}

enum errors read_from_file(FILE *in, Student **array, int *size, int *capacity)
{
    *size = 0;
    *array = (Student *)malloc(*capacity * sizeof(Student));
    if (*array == NULL)
    {
        return INVALID_MEMORY;
    }

}