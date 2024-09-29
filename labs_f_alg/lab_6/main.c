#include "header.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Ошибка: неверное количество аргументов.\n");
        return INVALID_INPUT;
    }
    double epsilon;
    enum Errors err = convert_str_to_double(argv[1], &epsilon);
    if (err != OK)
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
    double a = 0.0;
    double b = 1.0;

    double integral_a = integral_with_eps(epsilon, result_a, a, b);
    printf("a: %lf\n", integral_a);
    double integral_b = integral_with_eps(epsilon, result_b, a, b);
    printf("b: %lf\n", integral_b);
    double integral_c = integral_with_eps(epsilon, result_c, a, b);
    printf("c: %lf\n", integral_c);
    double integral_d = integral_with_eps(epsilon, result_d, a, b);
    printf("d: %lf\n", integral_d);

    return 0;
}
