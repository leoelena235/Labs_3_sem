#include "header.h"

void close_files(FILE *input, FILE *output)
{
    if (input != NULL)
        fclose(input);
    if (output != NULL)
        fclose(output);
}

enum Errors read_input_from_file(FILE **input, char **buffer, int *len, int *capacity)
{
    int simbols;
    *len = 0;
    int leading_zeros = 1; 

    while ((simbols = fgetc(*input)) != EOF && !isspace(simbols))
    {
        if (*len >= *capacity - 1)
        {
            *capacity *= 2;
            *buffer = (char *)realloc(*buffer, *capacity * sizeof(char));
            if (*buffer == NULL)
            {
                return INVALID_MEMORY;
            }
        }

        // Пропускаем ведущие нули
        if (leading_zeros && simbols == '0')
        {
            continue;
        }
        else
        {
            leading_zeros = 0; 
        }

        (*buffer)[(*len)++] = simbols;
    }

    if (*len == 0)
    {
        (*buffer)[(*len)++] = '0';
    }

    (*buffer)[*len] = '\0';
    return OK;
}

int determine_min_base(const char *number)
{
    int max_digit = 0;
    for (int i = 0; number[i]; i++)
    {
        int digit;
        if (isdigit(number[i]))
        {
            digit = number[i] - '0';
        }
        else if (isalpha(number[i]))
        {
            digit = tolower(number[i]) - 'a' + 10;
        }
        else
        {
            return -1; 
        }
        if (digit > max_digit)
        {
            max_digit = digit;
        }
    }
    return max_digit + 1;
}

enum Errors convert_str_to_ll_int(const char *str, long long *result, int base)
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

enum Errors main_func(FILE *input, FILE *output, char *buffer, int *len, int *capacity)
{
    enum Errors err = read_input_from_file(&input, &buffer, len, capacity);
    if (err != OK)
    {
        return err;
    }

    if (*len > 0)
    {
        int min_base = determine_min_base(buffer);
        if (min_base < 2)
        {
            return INVALID_INPUT;
        }

        long long decimal_value;
        err = convert_str_to_ll_int(buffer, &decimal_value, min_base);
        if (err != OK)
        {
            return INVALID_INPUT;
        }

        fprintf(output, "Входное число: %s\n", buffer);
        fprintf(output, "Минимальное основание: %d\n", min_base);
        fprintf(output, "Число в 10 сс: %lld\n\n", decimal_value);
    }

    return OK;
}
