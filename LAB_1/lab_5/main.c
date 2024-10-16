#include "header.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Ошибка: неверное количество аргументов.\n");
        return INVALID_INPUT;
    }
    double epsilon;
    enum Errors err_1 = convert_str_to_double(argv[1], &epsilon);
    if (err_1 != OK)
    {
        printf("Ошибка: неверный формат числа.\n");
        return INVALID_INPUT;
    }
    else if (epsilon <= 0)
    {
        printf("Ошибка: точность должна быть положительным числом.\n");
        return INVALID_INPUT;
    }

    if (epsilon < 1e-15)
    {
        printf("epsilon слишком маленькое, эпсилон = 1e-15.\n");
        epsilon = 1e-15;
    }

    double x;
    enum Errors err_2 = convert_str_to_double(argv[2], &x);
    if (err_2 != OK)
    {
        printf("Ошибка: неверный формат числа.\n");
        return INVALID_INPUT;
    }

    double res_a;

    enum Errors err_a = func_sum_a(epsilon, x, &res_a);
    if (err_a != OK)
    {
        printf("Ошибка: неверные входные данные для вычисления суммы.\n");
        return INVALID_INPUT;
    }

    printf("A result: %lf\n", res_a);

    double res_b;

    enum Errors err_b = func_sum_b(epsilon, x, &res_b);
    if (err_b != OK)
    {
        printf("Ошибка: неверные входные данные для вычисления суммы.\n");
        return INVALID_INPUT;
    }

    printf("B result: %lf\n", res_b);
    if (fabs(x) < 1)
    {
        double res_c;

        enum Errors err_c = func_sum_c(epsilon, x, &res_c);
        if (err_c != OK)
        {
            printf("Ошибка: неверные входные данные для вычисления суммы.\n");
            return INVALID_INPUT;
        }

        printf("C result: %lf\n", res_c);

        double res_d;
        enum Errors err_d = func_sum_d(epsilon, x, &res_d);
        if (err_d != OK)
        {
            printf("Ошибка: неверные входные данные для вычисления суммы D.\n");
            return INVALID_INPUT;
        }
        printf("D result: %lf\n", res_d);
    }
    else
    {
        printf("x должен быть в интервале (-1;1)\n");
        printf("x должен быть в интервале (-1;1)\n");
    }

    return 0;
}
