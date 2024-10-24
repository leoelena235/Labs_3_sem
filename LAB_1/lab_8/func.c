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
    int has_sign = 0;

    while ((simbols = fgetc(*input)) != EOF)
    {
        if (isspace(simbols))
        {
            if (*len > 0)
            {
                break;
            }
            else
            {
                continue; // пропускаем ведущие пробелы
            }
        }

        if (*len >= *capacity - 1)
        {
            *capacity *= 2;
            char *new_buffer = (char *)realloc(*buffer, *capacity * sizeof(char));
            if (new_buffer == NULL)
            {
                free(*buffer); 
                return INVALID_MEMORY;
            }
            *buffer = new_buffer;
        }

        // пропускаем ведущие нули, но не минус
        if (leading_zeros && simbols == '0' && !has_sign)
        {
            continue;
        }
        else if (simbols == '-' && *len == 0)
        {
            has_sign = 1; // если минус
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
    int all_zeros = 1;
    int start = 0;

    if (number[0] == '-')
    {
        start = 1;
    }

    for (int i = start; number[i]; i++)
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
        if (digit != 0)
        {
            all_zeros = 0;
        }
        if (digit > max_digit)
        {
            max_digit = digit;
        }
    }
    if (all_zeros)
    {
        return 2;
    }
    else
    {
        return max_digit + 1;
    }
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