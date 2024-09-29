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
        case OK:
            printf("Число является простым\n");
            break;
        case PRIME_NEGATIVE:
            printf("Отрицательные числа не являются ни простыми, ни составными\n");
            break;
        case PRIME_NOT:
            printf("Число является составным\n");
            break;
        case PRIME_NOT_NATURAL:
            printf("Число не является ни простым, ни составным\n");
            break;
        default:
            printf("Ошибка при проверке на простоту\n");
            break;
        }
        break;

    case 's':
        char *result_s;
        int count;
        enum Errors err_s = hex_digit(number, &result_s, &count);
        if (err_s == INVALID_MEMORY)
        {
            printf("Ошибка выделения памяти.\n");
            return INVALID_MEMORY;
        }
        else if (err_s != OK)
        {
            printf("Произошла неизвестная ошибка.\n");
            return err_s;
        }
        else
        {
            for (int i = 0; i < count; ++i)
            {
                printf("%c ", result_s[i]);
            }
            printf("\n");
        }
        free(result_s);

        break;

    case 'e':
        long long int **result_e = NULL;
        enum Errors err_e = degree_of_table(number, &result_e);

        if (err_e == INVALID_INPUT)
        {
            {
                printf("Ошибка ввода.\n");
                return INVALID_INPUT;
            }
        }
        else if (err_e == INVALID_MEMORY)
        {
            {
                printf("Ошибка выделения памяти.\n");
                return INVALID_MEMORY;
            }
        }
        printf("       |");
        for (int j = 1; j <= number; j++)
        {
            printf("%7d", j);
        }
        printf("\n-------|");

        for (int j = 1; j <= number; j++)
        {
            printf("-------");
        }
        printf("\n");
        for (int i = 1; i <= 10; i++)
        {
            printf("%7d|", i);
            for (int j = 1; j <= number; j++)
            {
                printf("%7lld", result_e[i - 1][j - 1]);
            }
            printf("\n");
        }
        for (int j = 0; j < 10; j++)
        {
            if (result_e[j] != NULL)
                free(result_e[j]);
        }
        free(result_e);

        break;

    case 'a':
        long long int result_a;
        enum Errors err = sum_of_numbers(number, &result_a);
        if (err == INVALID_MEMORY)
        {
            printf("Ошибка выделения памяти\n");
            return INVALID_MEMORY;
        }
        else if (err == INVALID_INPUT)
        {
            printf("Ошибка: некорректный ввод числа\n");
            return INVALID_INPUT;
        }

        printf("Сумма всех натуральных чисел от 1 до %ld: %lld\n", number, result_a);
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
        break;

    default:
        printf("Ошибка: такого флага нет в доступных флагах: %s\n", argv[1]);
        break;
    }

    return 0;
}
