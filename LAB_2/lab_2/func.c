#include "header.h"

enum Errors convert_str_to_int(const char *str, long long int *number, int base)
{
    if (*str == '\0')
    {
        return INVALID_INPUT;
    }

    char *endptr;
    long long int result = strtoll(str, &endptr, base);

    if (*endptr != '\0' || (str == endptr))
    {
        return INVALID_INPUT;
    }

    *number = result;
    return OK;
}

enum Errors geometric_mean(double *result, int count, double numbers[])
{
    if (count <= 0)
    {
        return INVALID_ARGUMENT_COUNT;
    }
    
    double product = 1.0; 
    for (int i = 0; i < count; i++)
    {
        if (numbers[i] <= 0.0)
        {
            return INVALID_INPUT;
        }
        product *= numbers[i];
    }

    *result = pow(product, 1.0 / count);
    return OK;
}

enum Errors recurse_double_in_int_pow(double base, int exp, double *result)
{
    if (exp == 0)
    {
        *result = 1.0;
        return OK;
    }

    if (exp < 0)
    {
        return recurse_double_in_int_pow(1.0 / base, -exp, result);
    }

    double temp;
    enum Errors status = recurse_double_in_int_pow(base, exp / 2, &temp);
    if (status != OK)
    {
        return status;
    }

    if (exp % 2 == 0)
    {
        *result = temp * temp;
    }
    else
    {
        *result = base * temp * temp;
    }

    return OK;
}
