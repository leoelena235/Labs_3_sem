#include "header.h"

int main(int argc, char *argv[])
{
    int flag;

    if (input_fl_err(argc, argv, &flag) != OK)
    {
        printf("Ошибка: некорректный ввод");
        return INVALID_INPUT;
    }

    switch (flag)
    {
    case 'q':
        if (argc != 6)
        {
            printf("Ошибка: недостаточно или слишком много аргументов\n");
            return INVALID_INPUT;
        }
        double epsilon_q;
        double coefficients[3];
        if (convert_str_to_double(argv[2], &epsilon_q) != OK || epsilon_q <= 0 || epsilon_q < DBL_MIN)
        {
            printf("Ошибка: некорректный ввод числа эпсилон\n");
            return INVALID_INPUT;
        }

        for (int i = 0; i < 3; i++)
        {
            if (convert_str_to_double(argv[3 + i], &coefficients[i]) != OK)
            {
                printf("Ошибка: некорректный ввод коэфициентов%d\n", i + 1);
                return INVALID_INPUT;
            }
        }
        generate_permutations(coefficients, epsilon_q);
        break;

    case 'm':
        if (argc != 4)
        {
            printf("Ошибка: недостаточно или слишком много аргументов\n");
            return INVALID_INPUT;
        }
        long long int num1, num2;
        if (input_num_convert_err(argv[2], &num1) != OK || input_num_convert_err(argv[3], &num2) != OK)
        {
            printf("Ошибка: некорректные числа\n");
            return INVALID_INPUT;
        }

        if (num1 == 0 || num2 == 0)
        {
            printf("Ошибка: числа должны быть ненулевыми\n");
            return INVALID_INPUT;
        }

        if (is_multiple(num1, num2))
        {
            printf("%lld кратно %lld\n", num1, num2);
        }
        else
        {
            printf("%lld не кратно %lld\n", num1, num2);
        }
        break;
    case 't':
        if (argc != 6)
        {
            printf("Ошибка: недостаточно или слишком много аргументов\n");
            return INVALID_INPUT;
        }
        double epsilon;
        double *sides = (double *)malloc(3 * sizeof(double));
        if (sides == NULL)
        {
            printf("Ошибка: не удалось выделить память\n");
            return INVALID_MEMORY;
        }

        if (convert_str_to_double(argv[2], &epsilon) != OK || epsilon <= 0 || epsilon < DBL_MIN)
        {
            printf("Ошибка: некорректный ввод числа epsilon или epsilon должно быть больше нуля и не слишком маленьким\n");
            free(sides);
            return INVALID_INPUT;
        }

        for (int i = 0; i < 3; i++)
        {
            if (convert_str_to_double(argv[3 + i], &sides[i]) != OK || sides[i] <= 0)
            {
                printf("Ошибка: некорректный ввод числа side%d или side%d должно быть больше нуля\n", i + 1, i + 1);
                free(sides);
                return INVALID_INPUT;
            }
        }

        if (is_right_triangle(sides[0], sides[1], sides[2], epsilon))
        {
            printf("Эти числа могут быть длинами сторон прямоугольного треугольника.\n");
        }
        else
        {
            printf("Эти числа не могут быть длинами сторон прямоугольного треугольника.\n");
        }
        free(sides);
        break;
    default:
        printf("Ошибка: неизвестный флаг\n");
        return INVALID_INPUT;
    }

    return OK;
}
