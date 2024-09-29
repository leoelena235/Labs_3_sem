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

double result_a(double x)
{
    if (fabs(x) < 1e-10)
    {
        return 1.0; //  при x -> 0
    }
    return log(1 + x) / x;
}

double result_b(double x)
{
    return exp(-x * x / 2);
}

double result_c(double x)
{
    if (x >= 1.0 - 1e-10)
    {
        return 1.0; // Если x очень близко к 1, возвращаем 1
    }
    if (x <= 1e-10)
    {
        return 0.0; // Если x очень близко к 0, возвращаем 0
    }
    return log(1 / (1 - x));
}
double result_d(double x)
{
    return pow(x, x);
}

double trapezoidal_method(double (*f)(double), double a, double b, int n)
{
    double h = (b - a) / n;
    double sum = 0.0;
    sum += f(a) + f(b);

    for (int i = 1; i < n; i++)
    {
        sum += 2 * f(a + i * h);
    }

    return (h / 2) * sum;
}

double integral_with_eps(double epsilon, double (*f)(double), double a, double b)
{
    int n = 1000;
    double previous_result = 0.0;
    double result = trapezoidal_method(f, a, b, n);
    int max_iterations = 1000000;
    while (fabs(result - previous_result) > epsilon)
    {
        previous_result = result;
        n *= 2;
        result = trapezoidal_method(f, a, b, n);
    }
    if (n >= max_iterations)
    {
        printf("достигнуто максимальное количество итераций.\n");
    }
    return result;
}
