#include "header.h"

enum Errors convert_str_to_double(const char *str, double *result)
{
    if (*str == '\0')
    {
        return INVALID_INPUT;
    }
    char *endptr;
    *result = strtod(str, &endptr);

    if (endptr == str || *endptr != '\0')
    {
        return INVALID_INPUT;
    }
    if (*result == HUGE_VAL || *result == -HUGE_VAL)
    {
        return OVERFLOW_ERROR;
    }

    return OK;
}

enum Errors func_sum_a(const double epsilon, const double x, double *res_a)
{
    if (res_a == NULL || fabs(x) > sqrt(DBL_MAX) || epsilon < 0)
    {
        return INVALID_INPUT;
    }
    *res_a = 0.0;
    double term = 1.0; // первый член ряда
    int n = 0;

    *res_a += term;

    while (fabs(term) > epsilon)
    {
        n++;
        term *= x / n;
        *res_a += term;
    }
    return OK;
}

// считаем факториала
double factorial(int n)
{
    double result = 1.0;
    for (int i = 1; i <= n; i++)
    {
        result *= i;
    }
    return result;
}


enum Errors func_sum_b(const double epsilon, const double x, double *res_b)
{
    if (res_b == NULL || fabs(x) > sqrt(DBL_MAX) || epsilon < 0)
    {
        return INVALID_INPUT;
    }
    *res_b = 0.0;
    double term = 1.0; // первый член ряда
    int n = 0;

    *res_b += term;

    while (fabs(term) > epsilon)
    {
        n++;
        term = pow(-1, n) * pow(x, 2 * n) / factorial(2 * n);
        *res_b += term;
        if (n >= pow(10, 7))
            return INVALID_INPUT;
    }
    return OK;
}

enum Errors func_sum_c(const double epsilon, const double x, double *res_c)
{
    if (res_c == NULL || fabs(x) > sqrt(DBL_MAX) || epsilon < 0)
        return INVALID_INPUT;
    *res_c = 0.0;
    double term = 1.0;
    int n = 0;

    while (fabs(term) > epsilon)
    {
        *res_c += term;
        n++;
        term *= (9.0 * pow(n, 2) * pow(x, 2)) / (9.0 * pow(n, 2) - 9.0 * n + 2.0);
        if (n >= pow(10, 7))
            return INVALID_INPUT;
    }
    return OK;
}

enum Errors func_sum_d(const double epsilon, const double x, double *res_d)
{
    if (res_d == NULL || fabs(x) > sqrt(DBL_MAX) || epsilon < 0)
        return INVALID_INPUT;
    *res_d = 0.0;
    double term = -1.0 * x * x / 2.0;
    int n = 0.0;

    while (fabs(term) > epsilon)
    {
        *res_d += term;
        n++;
        term *= (-1.0 * x * x * (2.0 * n - 1)) / (2.0 * n);
        if (n >= pow(10, 7))
            return INVALID_INPUT;
    }

    return OK;
}