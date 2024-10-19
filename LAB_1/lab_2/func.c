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
        return OVERFLOW;
    }

    return OK;
}

double limit_e(double epsilon)
{
    double n = 1;
    double prev = 0;
    int max_iterations = 1000000; // ограничим итерации
    int iteration = 0;
    double cur = pow((1.0 + 1.0 / n), n); // чтобы цикл начался, для первого знач было не 0-0=:(
    n++;                                  // нач с 2

    while (fabs(cur - prev) >= epsilon && iteration < max_iterations)
    {
        prev = cur;
        n++;
        cur = pow((1.0 + 1.0 / n), n);

        iteration++;
    }

    if (iteration >= max_iterations)
    {
        printf("Limit iterations\n");
    }

    return cur;
}

double limit_pi(double epsilon)
{
    int n = 2;
    double current = 4.0, previous = 0;

    while (fabs(previous - current) >= epsilon)
    {
        previous = current;
        current *= (4.0 * n * (n - 1.0)) / pow(2.0 * n - 1.0, 2);
        n++;
    }
    return current;
}

double limit_ln(double epsilon)
{
    double n = 1;
    double current = 1, previous = 0;

    while (fabs(previous - current) >= epsilon)
    {
        previous = current;
        n *= 2;
        current = n * (pow(2.0, 1.0 / n) - 1.0);
    }
    return current;
}

double limit_sqrt(double epsilon)
{
    double n = 1;
    double current = -0.5, previous = 0;

    while (fabs(previous - current) >= epsilon)
    {
        previous = current;
        n++;
        current = (2.0 * previous - pow(previous, 2.0) + 2.0) / 2.0; //*2
    }
    return current;
}

double limit_y(double epsilon)
{
    double previous = 0;
    double current = 1;
    int n = 1;

    while (fabs(previous - current) >= epsilon)
    {
        previous = current;
        n *= 2;
        current = sum(n) - log(n);
    }

    return current;
}

double row_e(double epsilon)
{
    double cur = 0.0, prev = 0; // current для суммы ряда
    double factorial = 1;       // 0!=1
    int n = 0;

    while (1)
    {
        if (n > 0) // 0!=1
            factorial *= n;
        cur += 1.0 / factorial;
        if (fabs(cur - prev) < epsilon)
            return cur;
        prev = cur;
        n++;
    }
    return cur;
}

double row_pi(double epsilon)
{
    int n = 1;
    double current = 1.0, previous = 0;

    while (fabs(previous - current) >= epsilon)
    {
        previous = current;
        n++;
        current -= 1.0 / (2.0 * n - 1.0);
        n++;
        current += 1.0 / (2.0 * n - 1.0);
    }

    return current * 4;
}

double row_ln(double epsilon)
{
    int n = 1;
    double current = 1.0, previous = 0;

    while (fabs(previous - current) >= epsilon)
    {
        previous = current;
        n++;
        current -= 1.0 / n; // чет
        n++;
        current += 1.0 / n; // нечет
    }

    return current;
}

double row_sqrt(double epsilon)
{
    int k = 2;
    double current = pow(2.0, 1.0 / 4.0), previous = 0;

    while (fabs(previous - current) >= epsilon)
    {
        previous = current;
        ++k;
        current *= pow(2, 1.0 / pow(2, k));
    }

    return current;
}
double row_y(double epsilon)
{
    double previous = 0;
    double current = 0.5;
    int k = 2;
    double l = 0;
    while (fabs(previous - current) >= epsilon)
    {
        previous = current;
        k++;
        l = sqrt(k);
        if (fmod(l, 1.0) == 0)
        {
            k++;
            l = (int)pow(k, 1.0 / 2.0);
        }
        current += 1.0 / pow((int)l, 2.0) - 1.0 / k;
    }

    return (current - pow(M_PI, 2) / 6);
}

double equation_e(double epsilon) // Метод Ньютона->Хn+1=Xn-(F(xn)/F'(xn))
{
    double x = 3; // ближе к е, дальше от 0
    double f_val = 1;
    double df_val;
    int iteration = 0;
    while (fabs(f_val) > epsilon && iteration < MAX_ITERATIONS)
    {
        f_val = log(x) - 1;
        df_val = 1.0 / x;
        x -= f_val / df_val;
        iteration++;
    }
    if (iteration >= MAX_ITERATIONS)
    {
        printf("Limit iterations\n");
    }
    return x;
}

double equation_pi(double epsilon)
{
    double x = 3; // близкое к π
    double f = 1, df;
    while (fabs(f) > epsilon)
    {
        f = cos(x) + 1;
        df = -sin(x);
        x = x - f / df;
    }
    return x;
}

double equation_ln(double epsilon)
{
    double x = 1;
    double f = 1, df;
    while (fabs(f) > epsilon)
    {
        f = exp(x) - 2;
        df = exp(x);
        x = x - f / df;
    }
    return x;
}

double equation_sqrt(double epsilon)
{
    double x = 1;
    double f = 1, df;
    while (fabs(f) > epsilon)
    {
        f = x * x - 2;
        df = 2 * x;
        x = x - f / df;
    }
    return x;
}

double sum(int n)
{
    double sum = 1;
    for (int i = 2; i <= n; i++)
    {
        sum += 1.0 / i;
    }

    return sum;
}

double equation_y(double epsilon)
{
    int p = 2;
    double current = log(2) * 0.5;
    double previous = 0;
    double product = 0.5;
    while (fabs(previous - current) >= epsilon)
    {
        previous = current;
        do
        {
            p++;
        } while (is_prime(p));
        product *= (p - 1.0) / p;
        current = log(p) * product;
    }

    return (-log(current));
}

int is_prime(int number)
{
    if (number < 0)
        number *= -1;

    if (number == 0 || number == 1 || number == 2)
        return 0;

    if (number % 2 == 0)
        return 1;

    for (int i = 3; i <= floor(sqrt(number)); i += 2)
    {
        if (number % i == 0)
            return 1;
    }
    return 0;
}
