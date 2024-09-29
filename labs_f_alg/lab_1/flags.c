#include "header.h"
#include <ctype.h>

enum Errors input_fl_err(int argc, char *argv[], int *flag)
{
    if (argc != 3)
    {
        return INVALID_INPUT;
    }

    if (!((argv[1][0] == '-' || argv[1][0] == '/') && argv[1][2] == '\0'))
    {
        return INVALID_INPUT;
    }
    *flag = argv[1][1];

    return OK;
}

enum Errors input_num_convert_err(const char *str, long int *number)
{
    if (*str == '\0')
    {
        return INVALID_INPUT;
    }

    char *endptr;
    long int result = strtol(str, &endptr, 10);

    if (*endptr != '\0' || (str == endptr))
    {
        return INVALID_INPUT;
    }
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (i == 0 && str[i] == '-') // p
        {
            continue;
        }
        if (!isdigit(str[i]))
        {
            return INVALID_INPUT;
        }
    }
    if ((result == LONG_MAX && strcmp(endptr, "") != 0) ||
        (result == LONG_MIN && strcmp(endptr, "") != 0))
    {
        return INVALID_INPUT;
    }

    *number = result;
    return OK;
}

enum Errors find_multiples(int x)
{
    int *multiples = NULL;
    int count = 0;
    int capacity = 10;
    if (x == 0)
    {
        return INVALID_INPUT;
    }
    multiples = (int *)malloc(sizeof(int) * (100 / x + 1));
    if (multiples == NULL)
    {
        return INVALID_MEMORY;
    }

    for (int i = 1; i <= 100; ++i)
    {
        if (i % x == 0)
        {
            if (count >= capacity)
            {
                capacity *= 2;
                int *new_multiples = (int *)realloc(multiples, sizeof(int) * capacity);
                if (new_multiples == NULL)
                {
                    free(multiples);
                    return INVALID_MEMORY;
                }
                multiples = new_multiples;
            }
            multiples[count++] = i;
        }
    }

    if (count == 0)
    {
        free(multiples);
        return NO_MULTIPLES;
    }

    printf("Числа в диапазоне [1, 100], кратные %d:\n", x);
    for (int i = 0; i < count; ++i)
    {
        printf("%d ", multiples[i]);
    }
    printf("\n");

    free(multiples);
    return OK;
}

enum Errors prime_err(long int number)
{
    if (number < 0)
    {
        return PRIME_NEGATIVE;
    }
    else if (number <= 1)
    {
        return PRIME_NOT_NATURAL;
    }
    for (long int i = 2; i * i <= number; i++)
    {
        if (number % i == 0)
        {
            return PRIME_NOT;
        }
    }
    return OK;
}

enum Errors split_number_to_digits(long int number, char **result, int *size_arr_res)
{
    (*size_arr_res)++;
    *result = (char *)calloc((*size_arr_res + 1), sizeof(char));
    if (*result == NULL)
        return INVALID_MEMORY;

    if (number < 0)
    {
        (*result)[0] = '-';
        number = labs(number);
    }

    for (int i = *size_arr_res - 1; i >= 0; --i)
    {
        (*result)[i + 1] = '0' + (number % 10);
        number /= 10;
    }

    (*size_arr_res)++;
    return OK;
}

enum Errors table_of_degrees(long int ***result, long int number)
{

    *result = (long int **)malloc(11 * sizeof(long int *));
    if ((*result) == NULL)
        return INVALID_MEMORY;

    for (int i = 0; i <= 10; ++i)
    {
        (*result)[i] = (long int *)malloc((number + 1) * sizeof(long int));

        if ((*result)[i] == NULL)
        {
            for (int j = 0; j < i; ++j)
            {
                free((*result)[j]);
            }
            free(*result);
            return INVALID_MEMORY;
        }
    }

    (*result)[0][0] = 1;
    for (int i = 1; i < 11; ++i)
    {
        (*result)[i][0] = 1;
        (*result)[i][1] = i;
    }

    for (int i = 2; i <= number; ++i)
    {
        (*result)[0][i] = 0;
        (*result)[2][i] = 1;
    }

    for (int base = 0; base <= 10; ++base)
    {
        for (int degree = 2; degree <= number; ++degree)
        {
            (*result)[base][degree] = (*result)[base][degree - 1] * base;
        }
    }

    return OK;
}

enum Errors sum_of_numbers(long int number, long long int *result)
{
    int flag = 1;
    if (number < 0)
    {
        number = labs(number);
        flag = -1;
    }
    for (int i = 1; i <= number; ++i)
    {
        if (*result > INT_MAX - i || *result < INT_MIN + i)
            return INVALID_MEMORY;

        *result += i;
    }
    *result = *result * flag;
    return OK;
}

long int factorial(int n)
{
    if (n == 0)
    {
        return 1;
    }
    else
    {
        return n * factorial(n - 1);
    }
}

enum Errors factorial_with_overflow_check(long int number)
{
    if (number < 0)
    {
        return INVALID_INPUT;
    }
    else if (number > 20)
    {
        return FACTORIAL_OVERFLOW;
    }
    else
    {
        return OK;
    }
}