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
    multiples = (int *)malloc(sizeof(int) * ((size_t)(100 / x) + 1));
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
    else if (number == 1 || number == 0)
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

enum Errors hex_digit(long long int number, char **result_s, int *count)
{
    *count = 0;
    int is_negative = 0;

    if (number < 0)
    {
        is_negative = 1;
        number = -number;
        (*count)++;
    }

    long long int temp = number;
    while (temp != 0)
    {
        temp /= 16;
        (*count)++;
    }

    if (*count == 0)
    {
        *count = 1;
    }

    *result_s = (char *)malloc((*count + 1) * sizeof(char));
    if (*result_s == NULL)
    {
        free(*result_s);
        return INVALID_MEMORY;
    }

    if (is_negative)
    {
        (*result_s)[0] = '-';
    }
    for (long long int i = *count - 1; i >= (is_negative ? 1 : 0); i--)
    {
        int digit = llabs(number % 16);
        if (digit < 10)
        {
            (*result_s)[i] = '0' + digit;
        }
        else
        {
            (*result_s)[i] = 'A' + digit - 10;
        }
        number /= 16;
    }
    (*result_s)[*count] = '\0';
    return OK;
}

enum Errors degree_of_table(int number, long long int ***result_e)
{
    if (number > 10 || number < 1)
    {
        return INVALID_INPUT;
    }

    *result_e = (long long int **)malloc(10 * sizeof(long long int *));
    if (*result_e == NULL)
    {
        return INVALID_MEMORY;
    }
    for (int i = 0; i < 10; i++)
    {
        (*result_e)[i] = (long long int *)malloc(number * sizeof(long long int));
        if ((*result_e)[i] == NULL)
        {
            for (int m = 0; m < i; m++)
            {
                free((*result_e)[m]);
            }
            free(*result_e);
            return INVALID_MEMORY;
        }
    }
    for (int base = 1; base <= 10; ++base)
    {
        for (int degree = 1; degree <= number; ++degree)
        {
            (*result_e)[base - 1][degree - 1] = (long long int)round(pow(base, degree)); // чекунуть
        }
    }
    return OK;
}

enum Errors sum_of_numbers(long int number, long long int *result_a)
{
    if (number < 1)
    {
        return INVALID_INPUT;
    }

    *result_a = (long long int)number * (number + 1) / 2;

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
        return INVALID_MEMORY;
    }
    else
    {
        return OK;
    }
}
