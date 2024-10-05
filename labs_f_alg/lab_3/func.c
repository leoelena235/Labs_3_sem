#include <stdio.h>
#include "header.h"
enum Errors input_fl_err(int argc, char *argv[], int *flag)
{
    if (argc < 2)
    {
        return INVALID_INPUT;
    }

    if (!((argv[1][0] == '-' || argv[1][0] == '/') && argv[1][2] == '\0'))
    {
        return INVALID_INPUT;
    }
    *flag = argv[1][1];

    return OK;
}

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
        return OVERFLOW;
    }

    return OK;
}

void solve_quadratic_equation(double a, double b, double c, double epsilon, double *x1, double *x2)
{
    if (fabs(a) < epsilon && fabs(b) < epsilon && fabs(c) < epsilon) //обработка бесконечного числа реш-ий, при 0 0 0
    {
        *x1 = INFINITY; 
        *x2 = INFINITY;
    }
    else if (fabs(a) < epsilon) // решение, если линейное уравнение
    {
        if (fabs(b) < epsilon) // b == 0
        {
            *x1 = NAN;
            *x2 = NAN;
        }
        else
        {
            *x1 = -c / b;
            *x2 = *x1;
        }
    }
    else
    {
        double discriminant = b * b - 4 * a * c;

        if (fabs(discriminant) < epsilon)
        {
            *x1 = -b / (2 * a);
            *x2 = *x1;
        }
        else if (discriminant > 0)
        {
            *x1 = (-b + sqrt(discriminant)) / (2 * a);
            *x2 = (-b - sqrt(discriminant)) / (2 * a);
        }
        else
        {
            *x1 = NAN;
            *x2 = NAN;
        }
    }
}

void print_solutions(double epsilon, double coefficients[3])
{
    double x1, x2;
    solve_quadratic_equation(coefficients[0], coefficients[1], coefficients[2], epsilon, &x1, &x2);

    if (isinf(x1))
    {
        printf("Уравнение %.2fx^2 + %.2fx + %.2f = 0 имеет бесконечное число решений\n", coefficients[0], coefficients[1], coefficients[2]);
    }
    else if (isnan(x1))
    {
        printf("Уравнение %.2fx^2 + %.2fx + %.2f = 0 не имеет действительных корней\n", coefficients[0], coefficients[1], coefficients[2]);
    }
    else
    {
        printf("Уравнение %.2fx^2 + %.2fx + %.2f = 0 имеет корни: x1 = %.6f, x2 = %.6f\n", coefficients[0], coefficients[1], coefficients[2], x1, x2);
    }
}


enum Errors generate_permutations(double coefficients[3], double epsilon)
{
    double *perm = (double *)malloc(3 * sizeof(double));
    if (perm == NULL)
    {
        printf("Ошибка выделения памяти");
        return INVALID_MEMORY;
    }
    memcpy(perm, coefficients, 3 * sizeof(double));

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i == j)
                continue;
            for (int k = 0; k < 3; k++)
            {
                if (i == k || j == k)
                    continue;
                perm[0] = coefficients[i];
                perm[1] = coefficients[j];
                perm[2] = coefficients[k];
                print_solutions(epsilon, perm);
            }
        }
    }
    free(perm);
    return OK;
}

enum Errors input_num_convert_err(const char *str, long long int *number)
{
    if (*str == '\0')
    {
        return INVALID_INPUT;
    }

    char *endptr;
    long long int result = strtoll(str, &endptr, 10);

    if (*endptr != '\0' || (str == endptr))
    {
        return INVALID_INPUT;
    }
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (i == 0 && str[i] == '-')
        {
            continue;
        }
        if (!isdigit(str[i]))
        {
            return INVALID_INPUT;
        }
    }
    if (result > LLONG_MAX || result < LLONG_MIN)
    {
        return OVERFLOW;
    }
    *number = result;
    return OK;
}

int is_multiple(long int num1, long int num2)
{
    return (num1 % num2 == 0);
}

int is_right_triangle(double a, double b, double c, double epsilon)
{
    if (a > b)
    {
        double temp = a;
        a = b;
        b = temp;
    }
    if (b > c)
    {
        double temp = b;
        b = c;
        c = temp;
    }
    if (a > b)
    {
        double temp = a;
        a = b;
        b = temp;
    }

    return (c * c - (a * a + b * b)) < epsilon;
}