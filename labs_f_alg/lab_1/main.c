#include "header.h"

int main(int argc, char *argv[])
{
    int flag;
    long int number;

    if (input_fl_err(argc, argv, &flag) != OK)
    {
        printf("Ошибка: некорректный ввод");
        return INVALID_INPUT;
    }

    if (input_num_convert_err(argv[2], &number) != OK)
    {
        printf("Ошибка: некорректный ввод числа\n");
        return INVALID_INPUT;
    }

    switch (argv[1][1])
    {
    case 'h':
        int multiple = (int)number;
        switch (find_multiples(multiple))
        {
        case OK:
            break;
        case NO_MULTIPLES:
            printf("В диапазоне [1, 100] нет чисел, кратных %d.\n", multiple);
            break;
        case INVALID_MEMORY:
            printf("Ошибка выделения памяти.\n");
            break;
        default:
            printf("Ошибка: неизвестная ошибка.\n");
        }
        break;

    case 'p':

        switch (prime_err(number))
        {
        case PRIME_OK:
            printf("Число является простым\n");
            break;
        case PRIME_NEGATIVE:
            printf("Отрицательные числа не являются ни простыми, ни составными\n");
            break;
        case PRIME_NOT:
            printf("Число является составным\n");
            break;
        case PRIME_NOT_NATURAL:
            printf("Число не является натуральным\n");
            break;
        default:
            printf("Ошибка при проверке на простоту\n");
            break;
        }
        break;

    case 's':

        int size_arr_result_s = (number == 0) ? 1 : log10l(labs(number));
        char *result_s = NULL;
        enum Errors status_s = split_number_to_digits(number, &result_s, &size_arr_result_s);
        if (status_s == INVALID_MEMORY)
        {
            printf("Ошибка: ошибка работы с памятью\n");
            if (result_s != NULL)
                free(result_s);
            return INVALID_MEMORY;
        }
        for (int i = 0; i < size_arr_result_s; ++i)
        {
            printf("%c ", result_s[i]);
        }
        printf("\n");
        if (result_s != NULL)
            free(result_s);

        break;

    case 'e':
        if (number > 10 || number < 0)
        {
            printf("Ошибка: некорректное число\n");
            return INVALID_INPUT;
        }

        long int **result_e = NULL;
        if (table_of_degrees(&result_e, number) == INVALID_MEMORY)
        {
            printf("Ошибка: =ошибка работы с памятью\n");
            // тут ничего не делаем, я там очистила
            return INVALID_MEMORY;
        }

        for (int i = 0; i <= 10; i++)
        {
            for (int j = 0; j <= number; ++j)
            {
                printf("%d^%d = %ld\n", i, j, result_e[i][j]);
            }
            printf("\n");
        }

        for (int i = 0; i <= 10; ++i)
            if (result_e[i] != NULL)
                free(result_e[i]);
        if (result_e != NULL)
            free(result_e);

        break;

    case 'a':

        long long int result_a = 0;
        if (sum_of_numbers(number, &result_a) == INVALID_MEMORY)
        {
            printf("Ошибка: произошло переполнение\n");
            return INVALID_MEMORY;
        }
        printf("%lld\n", result_a);
        break;

    case 'f':
        enum Errors result = factorial_with_overflow_check(number);
        if (result == OK)
        {
            printf("%ld\n", factorial(number));
        }
        else if (result == INVALID_INPUT)
        {
            printf("Ошибка: факториал от отрицательного числа не определён\n");
            return result;
        }
        else
        {
            printf("Ошибка: слишком большое число для вычисления факториала\n");
            return result;
        }

        // unsigned long long int result_f = 1;
        // if (factorial_of_a_number(number, &result_f) == INVALID_MEMORY)
        // {
        //     printf("Ошибка: произошло переполнение\n");
        //     return INVALID_MEMORY;
        // }
        // printf("%llu\n", result_f);
        break;

    default:
        printf("Ошибка: такого флага нет в доступных флагах: %s\n", argv[1]);
        break;
    }

    return 0;
}