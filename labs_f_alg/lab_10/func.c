#include "Header.h"
#include <ctype.h>

enum Errors base_input(int *base)
{
    if (scanf("%d", base) != 1 || *base < 2 || *base > 36)
    {
        printf("Error input\n");
        return INVALID_INPUT;
    }
    return OK;
}
enum Errors err_memory(char **input_str)
{
    if (input_str == NULL)
    {
        return INVALID_MEMORY;
    }
    *input_str = (char *)malloc(MAX_STR_LEN * sizeof(char));
    if (*input_str == NULL)
    {
        printf("Ошибка выделения памяти\n");
        return INVALID_MEMORY;
    }
    return OK;
}

int valid_digit(char digit, int base)
{
    if (isdigit(digit))
    {
        return digit - '0' < base;
    }
    else if (isalpha(digit))
    {
        return toupper(digit) - 'A' + 10 < base;
    }
    return 0;
}

enum Errors number_input(char *number, int base)
{
    for (int i = 0; number[i] != '\0'; ++i)
    {
        if (number[i] == '-' && i == 0)
            continue;

        if (!valid_digit(number[i], base))
        {
            return INVALID_INPUT;
        }
    }

    return OK;
}

int convert_str_to_ll_int(const char *str, long long *result, int base)
{
    if (str == NULL || result == NULL)
    {
        return INVALID_INPUT;
    }

    *result = 0;
    int len = strlen(str);
    int sign = 1;

    // проверка на знак
    int start = 0;
    if (str[0] == '-')
    {
        sign = -1;
        start = 1;
    }

    for (int i = start; i < len; i++)
    {
        char c = toupper(str[i]);
        int digit;

        if (c >= '0' && c <= '9')
        {
            digit = c - '0';
        }
        else if (c >= 'A' && c <= 'Z')
        {
            digit = c - 'A' + 10;
        }
        else
        {
            return INVALID_INPUT;
        }

        if (digit >= base)
        {
            return INVALID_INPUT;
        }

        *result = *result * base + digit;
    }

    *result *= sign;
    return OK;
}
void convert_and_print_max_number(int base, long long int max_number)
{
    char *result = NULL;
    int res_of_bases[] = {base, 9, 18, 27, 36};
    char *array_base = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXWZ";

    for (int i = 0; i < 5; i++)
    {
        if (convert_to_base(&result, max_number, res_of_bases[i], array_base) != OK)
        {
            printf("Ошибка: ошибка при конвертации числа\n");
            free(result);
            exit(INVALID_MEMORY);
        }
        printf("%d: %s\n", res_of_bases[i], result);
        free(result);
        result = NULL;
    }
}

int convert_to_base(char **result, long long number, int base, char *array_base)
{
    if (number == 0)
    {
        *result = (char *)malloc(2 * sizeof(char));
        if (*result == NULL)
        {
            return INVALID_MEMORY;
        }
        (*result)[0] = '0';
        (*result)[1] = '\0';
        return OK;
    }
    int is_negative = 0;
    if (number < 0)
    {
        is_negative = 1;
        number = -number;
    }

    int len = 0;
    long long temp = number;
    while (temp > 0)
    {
        temp /= base;
        len++;
    }

    *result = (char *)malloc(((len + 1) + is_negative) * sizeof(char));
    if (*result == NULL)
    {
        return INVALID_MEMORY;
    }

    (*result)[len + is_negative] = '\0';
    for (int i = len - 1; i >= 0; i--)
    {
        (*result)[i + is_negative] = array_base[number % base];
        number /= base;
    }

    if (is_negative == 1)
    {
        (*result)[0] = '-';
    }

    return OK;
}
