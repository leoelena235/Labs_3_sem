#include "header.h"

enum Errors is_valid_flag(const char *str)
{
    if (str == NULL)
        return INVALID_INPUT;
    if ((str[0] == '-' || str[0] == '/') && str[2] == '\0')
        return OK;
    return INVALID_INPUT;
}

enum Errors is_convex_polygon(int *result, int num_vertices, ...)
{
    if (num_vertices < 3)
    {
        return INVALID_INPUT;
    }

    va_list args;
    va_start(args, num_vertices);

    double x1, y1, x2, y2, x3, y3;
    int sign = 0;

    for (int i = 0; i < num_vertices; i++)
    {
        x1 = va_arg(args, double);
        y1 = va_arg(args, double);
        x2 = va_arg(args, double);
        y2 = va_arg(args, double);
        x3 = va_arg(args, double);
        y3 = va_arg(args, double);

        double current_area = oriented_area(x1, y1, x2, y2, x3, y3);

        if (current_area != 0)
        {
            if (sign == 0)
            {
                if (current_area > 0)
                {
                    sign = 1;
                }
                else
                {
                    sign = -1;
                }
            }
            else if ((current_area > 0 && sign < 0) || (current_area < 0 && sign > 0))
            {
                *result = 0; // не выпуклый
                va_end(args);
                return OK;
            }
        }
    }

    va_end(args);
    *result = 1;
    return OK;
}
// ор площадь
double oriented_area(double x1, double y1, double x2, double y2, double x3, double y3)
{
    return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
}

// 2
enum Errors evaluate_polynomial(double *result, double x, int count, ...)
{
    if (count < 1)
    {
        return INVALID_INPUT;
    }

    va_list args;
    va_start(args, count);

    *result = 0.0;
    double coefficient;

    for (int i = 0; i <= count; i++)
    {
        coefficient = va_arg(args, double);
        *result += coefficient * pow(x, count - i);
    }

    va_end(args);

    if (isnan(*result) || isinf(*result))
    {
        return INVALID_INPUT;
    }

    return OK;
}
// 3

enum Errors find_kaprekar_numbers(int base, size_t count, ...)
{
    if (count <= 0)
    {
        printf("Uncorrect count\n");
        return INVALID_INPUT;
    }

    va_list nums;
    va_start(nums, count);

    size_t count_founded = 0;

    for (size_t i = 0; i < count; i++)
    {
        char *base_number_str = va_arg(nums, char *);
        int decimal_num = convert_to_decimal(base_number_str, base);

        if (decimal_num < 0)
        {
            printf("Invalid input: invalid number\n");
            return INVALID_INPUT;
        }

        if (is_kaprekar(decimal_num, base))
        {
            printf(" %s is Kaprekar\n", base_number_str);
            count_founded++;
        }
        else
        {
            printf(" %s is not Kaprekar\n", base_number_str);
        }
    }

    if (count_founded == 0)
    {
        printf("No Kaprekar numbers were found\n");
        va_end(nums);
        return OK;
    }

    va_end(nums);

    return OK;
}

int is_kaprekar(int num, int base)
{
    if (num == 1)
        return 1;

    int square_num = num * num;
    char *square_str = decimal_to_base(square_num, base);

    int length = strlen(square_str);

    for (int i = 1; i < length; i++)
    {
        char *left_str = (char *)malloc((i + 1) * sizeof(char));
        char *right_str = (char *)malloc((length - i + 1) * sizeof(char));

        strncpy(left_str, square_str, i);
        left_str[i] = '\0';

        strcpy(right_str, square_str + i);

        int left = convert_to_decimal(left_str, base);
        int right = convert_to_decimal(right_str, base);

        if (right > 0 && left + right == num)
        {
            free(left_str);
            free(right_str);
            return 1;
        }

        free(left_str);
        free(right_str);
    }
    return 0;
}

int count_digits(int decimal, int base)
{
    int count = 0;
    while (decimal > 0)
    {
        decimal /= base;
        count++;
    }
    return count;
}

char *decimal_to_base(int decimal, int base)
{
    if (decimal == 0)
    {
        char *result = (char *)malloc(2 * sizeof(char));
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    int is_negative = 0;
    if (decimal < 0)
    {
        is_negative = 1;
        decimal = -decimal;
    }

    // Вычисление количества цифр в числе
    int num_digits = count_digits(decimal, base);
    int buffer_size = num_digits + is_negative + 1; 
    char *result = (char *)malloc(buffer_size * sizeof(char));
    int ind = 0;

    while (decimal > 0)
    {
        int remainder = decimal % base;
        if (remainder < 10)
        {
            result[ind++] = '0' + remainder;
        }
        else
        {
            result[ind++] = 'A' + (remainder - 10);
        }
        decimal /= base;
    }

    if (is_negative)
    {
        result[ind++] = '-';
    }

    result[ind] = '\0';

    // реверс
    for (int i = 0; i < ind / 2; i++)
    {
        char temp = result[i];
        result[i] = result[ind - i - 1];
        result[ind - i - 1] = temp;
    }

    return result;
}

int convert_to_decimal(char *str, int base)
{
    int num = 0;

    while (*str)
    {
        int value;

        if (isdigit(*str))
            value = *str - '0';
        else if (isupper(*str))
            value = *str - 'A' + 10;
        else if (islower(*str))
            value = *str - 'a' + 10;
        else
            return -1;

        if (num > (INT_MAX - value) / base)
            return -1;

        if (value >= base)
            return -1;

        num = num * base + value;
        str++;
    }

    return num;
}
