#include "header.h"

enum Errors dichotomy_method(double left, double right, double epsilon, double (*function)(double), double *result)
{

    if (left > right)
        return INVALID_INPUT;

    if (epsilon <= 0)
        return INVALID_INPUT;

    if (function(left) * function(right) > 0)
        return NO_ROOTS;
    // f(a)⋅f(b)<0
    double middle;
    int max_iterations = 1000;
    int iteration = 0;
    while (fabs(right - left) >= epsilon && iteration < max_iterations)
    {
        middle = (left + right) / 2;
        if (function(middle) == 0)
        {
            *result = middle;
            return OK;
        }
        if (function(middle) * function(left) < 0)
        {
            right = middle;
        }
        else
        {
            left = middle;
        }
        iteration++;
    }

    *result = middle;
    return OK;
}

// rand func

double function_1(double x)
{
    return x * x - 4;
}

double function_2(double x)
{
    return sin(x) - 0.5;
}

double function_3(double x)
{
    return exp(x) - 2;
}

double function_4(double x)
{
    return x * x * x - 2 * x * x + x - 1;
}

double function_5(double x)
{
    return pow(x - 1, 2)/(x - 1);
}

double function_6(double x)
{
    return tanh(x) - 0.5;
}

double function_7(double x)
{
    return x * x - 2 * x + 1 - exp(x);
}

double function_8(double x)
{
    return sqrt(x) - 2;
}

double function_9(double x)
{
    return 1 / x - 2;
}