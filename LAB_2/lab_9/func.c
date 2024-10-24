#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>
#include "header.h"

enum Errors validate_base(int base)
{
    if (base < 2 || base > 36)
    {
        printf("Incorrect base: out of range\n");
        return INVALID_INPUT;
    }
    return OK;
}

int gcd(int a, int b) // НОД Евклид
{
    while (a > 0 && b > 0)
    {
        if (a > b)
        {
            a = a % b;
        }
        else
        {
            b = b % a;
        }
    }
    if (a == 0)
    {
        return b;
    }
    return a;
}
bool is_prime(int number)
{
    if (number <= 1)
    {
        return false;
    }
    if (number <= 3)
    {
        return true;
    }
    if (number % 2 == 0 || number % 3 == 0)
    {
        return false;
    }

    // от 5 до корня,скип четные числа, шаг 6 на скип фигни
    for (int i = 5; i * i <= number; i += 6)
    {
        if (number % i == 0 || number % (i + 2) == 0)
        {
            return false;
        }
    }
    return true;
}

enum Errors finale_representation(double fraction, int base)
{
    if (fraction <= 0 || fraction >= 1)
    {
        return INVALID_INPUT;
    }
    int numerator, denominator = 1;
    // чек дробн часть
    while (fabs(fraction - floor(fraction)) > 1e-10)
    {
        fraction *= 10;
        denominator *= 10;
    }

    numerator = (int)fraction;

    int gcd_ = gcd(numerator, denominator);
    if (gcd_ != 1)
    {
        denominator /= gcd_;
    }

    // проверка на конечное представление
    for (int i = 2; i <= denominator; i++) // наим прост число - 2
    {
        if (denominator % i == 0 && is_prime(i))
        {
            if (base % i != 0)
            {
                return NO_FINALE_REPRESENTATION;
            }
        }
    }

    return FINALE_REPRESENTATION;
}
enum Errors check_fractions(int base, int *count, double **result, int arg_count, ...)
{
    va_list args;
    va_start(args, arg_count);

    if (arg_count <= 0)
    {
        printf("Invalid number of arguments\n");
        va_end(args);
        return INVALID_INPUT;
    }
    enum Errors base_error = validate_base(base);
    if (base_error != OK)
    {
        va_end(args);
        return INVALID_INPUT;
    }
    *count = arg_count;

    *result = (double *)malloc(sizeof(double) * arg_count);
    if (*result == NULL)
    {
        va_end(args);
        return INVALID_MEMORY;
    }

    for (int i = 0; i < arg_count; i++)
    {
        double fraction = va_arg(args, double);

        if (fraction <= 0.0 || fraction >= 1.0)
        {
            printf("Fraction %d is out of range (0; 1)\n", i + 1);
            va_end(args);
            free(*result);
            *result = NULL;
            return INVALID_INPUT;
        }

        enum Errors representation_result = finale_representation(fraction, base);
        if (representation_result == FINALE_REPRESENTATION)
        {
            (*result)[i] = fraction;
        }
        else
        {
            (*result)[i] = 0.0;
        }
    }

    va_end(args);
    return OK;
}