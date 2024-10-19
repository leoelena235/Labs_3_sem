#include "header.h"

enum Errors input_fl_err(int argc, char *argv[])
{
    if (argc < 3 || argv[1][0] != '-')
    {
        printf("Invalid input: uncorrect counts agruments\n");
        return INVALID_INPUT;
    }
    return OK;
}

int len_string(const char *str)
{
    int lenght = 0;
    while (str[lenght] != '\0')
    {
        lenght++;
    }
    return lenght;
}

enum Errors reversed_string(const char *str, char **result_r)
{
    int len = len_string(str);
    char *new_str = (char *)malloc((len + 1) * sizeof(char));
    if (new_str == NULL)
    {
        printf("INVALID MEMORY\n");
        return INVALID_MEMORY;
    }
    for (int i = 0; i < len; i++)
    {
        new_str[i] = str[len - 1 - i];
    }
    new_str[len] = '\0';

    *result_r = new_str;
    return OK;
}
enum Errors upper_str(const char *str, char **result_u)
{
    int len = len_string(str);
    char *new_str = (char *)malloc((len + 1) * sizeof(char));
    if (new_str == NULL)
    {
        printf("INVALID MEMORY\n");
        return INVALID_MEMORY;
    }
    for (int i = 0; i < len; i++)
    {
        if (i % 2 == 0)
        {
            new_str[i] = str[i];
        }
        else
        {
            if (str[i] >= 'a' && str[i] <= 'z')
            {
                new_str[i] = str[i] - 'a' + 'A';
            }
            else
            {
                new_str[i] = str[i]; // если не буква
            }
        }
    }
    new_str[len] = '\0';
    *result_u = new_str;
    return OK;
}
enum Errors sort_simbols(char *str, char **result_n)
{
    int len = len_string(str);
    char *digits = (char *)malloc(len * sizeof(char));
    char *letters = (char *)malloc(len * sizeof(char));
    char *others = (char *)malloc(len * sizeof(char));
    int digit_count = 0, letter_count = 0, other_count = 0;

    if (digits == NULL || letters == NULL || others == NULL)
    {
        printf("INVALID MEMORY\n");
        free(digits);
        free(letters);
        free(others);
        return INVALID_MEMORY;
    }

    for (int i = 0; i < len; i++)
    {
        if (isdigit(str[i]))
        {
            digits[digit_count++] = str[i];
        }
        else if (isalpha(str[i]))
        {
            letters[letter_count++] = str[i];
        }
        else
        {
            others[other_count++] = str[i];
        }
    }
    char *new_str = (char *)malloc((len + 1) * sizeof(char));
    if (new_str == NULL)
    {
        printf("INVALID MEMORY\n");
        free(digits);
        free(letters);
        free(others);
        return INVALID_MEMORY;
    }
    int ind = 0;
    for (int i = 0; i < digit_count; i++)
    {
        new_str[ind++] = digits[i];
    }
    for (int i = 0; i < letter_count; i++)
    {
        new_str[ind++] = letters[i];
    }
    for (int i = 0; i < other_count; i++)
    {
        new_str[ind++] = others[i];
    }
    new_str[ind] = '\0';

    free(digits);
    free(letters);
    free(others);

    *result_n = new_str;
    return OK;
}
// check
enum Errors convert_str_to_int(const char *str, long long int *number, int base)
{
    if (*str == '\0')
    {
        return INVALID_INPUT;
    }

    char *endptr;
    long long int result = strtoll(str, &endptr, base);

    if (*endptr != '\0' || (str == endptr))
    {
        return INVALID_INPUT;
    }

    *number = result;
    return OK;
}

enum Errors concotenation_str(char **str_array, char **result_c, int count_str, unsigned int seed)
{
    if (str_array == NULL || result_c == NULL)
    {
        return INVALID_ARGUMENT;
    }

    if (count_str <= 0)
    {
        return INVALID_ARGUMENT;
    }

    for (int i = 0; i < count_str; i++)
    {
        if (str_array[i] == NULL)
        {
            return INVALID_ARGUMENT;
        }
    }
    // вся длина строк, которые будут объединены
    int total_length = 0;
    for (int i = 0; i < count_str; i++)
    {
        int j = 0;
        while (str_array[i][j] != '\0')
        {
            total_length++;
            j++;
        }
    }

    *result_c = (char *)malloc((total_length + 1) * sizeof(char));
    if (*result_c == NULL)
    {
        return INVALID_MEMORY;
    }

    srand(seed);
    // массив для отслеживания использованных индексов
    int *used_indices = (int *)calloc(count_str, sizeof(int));
    if (used_indices == NULL)
    {
        free(*result_c);
        return INVALID_MEMORY;
    }

    // конкатенация строк
    int result_index = 0;
    for (int i = 0; i < count_str; i++)
    {
        int random_index;
        do
        {
            random_index = rand() % count_str;
        } while (used_indices[random_index]);

        used_indices[random_index] = 1;

        int j = 0;
        while (str_array[random_index][j] != '\0')
        {
            (*result_c)[result_index++] = str_array[random_index][j++];
        }
    }
    (*result_c)[result_index] = '\0';
    free(used_indices);
    return OK;
}