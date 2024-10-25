#include "header.h"

enum Errors char_to_int(int *value, char chr, int base)
{
    int temp_value;

    if (isdigit(chr))
        temp_value = chr - '0';
    else if (isalpha(chr))
        temp_value = toupper(chr) - 'A' + 10;
    else
        return INVALID_INPUT;

    if (temp_value >= base)
        return INVALID_INPUT;

    *value = temp_value;
    return OK;
}

char int_to_char(int num)
{
    return (num < 10) ? num + '0' : num - 10 + 'A';
}

enum Errors add_numbers_in_base(char **result, const char *num_1, const char *num_2, int base)
{
    int len_1 = strlen(num_1);
    int len_2 = strlen(num_2);

    int max_length;
    if (len_1 > len_2)
    {
        max_length = len_1;
    }
    else
    {
        max_length = len_2;
    }

    // выделение памяти для result с учетом нулевого символа
    *result = (char *)malloc(max_length + 2);
    if (*result == NULL)
    {
        return INVALID_MEMORY;
    }

    (*result)[max_length + 1] = '\0';

    int carry = 0;
    int i = len_1 - 1;
    int j = len_2 - 1;
    int k = max_length;

    while (k >= 0)
    {
        int sum = carry;

        // Сложение цифр первого числа
        if (i >= 0)
        {
            int digit1;
            enum Errors status = char_to_int(&digit1, num_1[i], base);
            i--;
            if (status != OK)
            {
                free(*result);
                return status;
            }
            sum += digit1;
        }

        // Сложение цифр второго числа
        if (j >= 0)
        {
            int digit2;
            enum Errors status = char_to_int(&digit2, num_2[j], base);
            j--;
            if (status != OK)
            {
                free(*result);
                return status;
            }
            sum += digit2;
        }
        (*result)[k--] = int_to_char(sum % base);
        carry = sum / base;
    }

    if (carry > 0)
    {
        (*result)[0] = int_to_char(carry);
        return OK;
    }
    // удаление ведущ нуля
    if ((*result)[0] == '0')
    {
        char *new_result = (char *)malloc(strlen(*result));
        if (new_result == NULL)
        {
            free(*result);
            return INVALID_MEMORY;
        }

        memcpy(new_result, *result + 1, strlen(*result));
        new_result[strlen(*result) - 1] = '\0';

        free(*result);
        *result = new_result;
        return OK;
    }

    return OK;
}

enum Errors sum_of_numbers(int base, int count, ...)
{
    if (base < 2 || base > 36)
    {
        printf("Uncorrect base\n");
        return INVALID_INPUT;
    }

    if (count <= 0)
    {
        printf("Invalid count of numbers\n");
        return INVALID_INPUT;
    }

    va_list args;
    va_start(args, count);

    // Выделение памяти для строки "0"
    char *result = (char *)malloc(2);
    if (result == NULL)
    {
        va_end(args);
        return INVALID_MEMORY;
    }
    strcpy(result, "0");

    for (int i = 0; i < count; i++)
    {
        const char *num = va_arg(args, const char *);

        char *new_result = (char *)malloc(strlen(result) + 1);
        if (new_result == NULL)
        {
            free(result);
            va_end(args);
            return INVALID_MEMORY;
        }
        strcpy(new_result, result);

        enum Errors error = add_numbers_in_base(&new_result, result, num, base);
        if (error != OK)
        {
            free(result);
            free(new_result);
            va_end(args);
            return error;
        }

        free(result);
        result = new_result;
    }

    va_end(args);

    char *ptr = result;

    while (*ptr == '0' && *(ptr + 1) != '\0')
        ptr++;

    if (ptr != result)
    {
        char *temp = strdup(ptr);
        free(result);
        result = temp;
    }

    printf("Result after summation: %s\n", result);

    free(result);

    return OK;
}