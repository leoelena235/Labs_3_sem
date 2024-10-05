#include "header.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    if (argc == 4)
    {
        // Задача 1
        long long a, b, n;
        if (convert_str_to_ll_int(argv[1], &a, 10) != OK || convert_str_to_ll_int(argv[2], &b, 10) != OK)
        {
            printf("Неверный формат чисел a и b\n");
            return INVALID_INPUT;
        }

        if (convert_str_to_ll_int(argv[3], &n, 10) != OK)
        {
            printf("Неверный формат числа n\n");
            return INVALID_INPUT;
        }
        if (a > b)
        {
            printf("Значение левой границы должно быть меньше или равно правой\n");
            return INVALID_INPUT;
        }

        if (n <= 0)
        {
            printf("Размер массива должен быть положительным числом\n");
            return INVALID_INPUT;
        }

        int *array = (int *)malloc(n * sizeof(int));
        if (array == NULL)
        {
            printf("Ошибка выделения памяти\n");
            return INVALID_MEMORY;
        }

        fill_array_with_random_numbers_1(array, n, a, b);
        printf("Исходный массив: ");
        print_array_int(array, n);

        int max_num = 0, min_num = 0;
        for (int i = 1; i < n; i++)
        {
            if (array[i] < array[min_num])
            {
                min_num = i;
            }
            if (array[i] > array[max_num])
            {
                max_num = i;
            }
        }
        printf("минимальный элемент: %d\n", array[min_num]);
        printf("максимальный элемент: %d\n", array[max_num]);
        enum Errors result_1 = find_min_max_and_swap(array, n);
        if (result_1 != OK)
        {
            printf("Ошибка при поиске и обмене элементов: %d\n", result_1);
            free(array);
            return INVALID_INPUT;
        }

        printf("Измененный массив: ");
        print_array_int(array, n);

        free(array);
    }
    else if (argc == 2)
    { // Задача 2
        int len = rand() % (10000 - 10 + 1) + 10;

        int *A = malloc(sizeof(int) * len);
        int *B = malloc(sizeof(int) * len);
        if (A == NULL || B == NULL)
        {
            printf("Ошибка выдедения памяти\n");
            free(A);
            free(B);
            return INVALID_MEMORY;
        }

        for (int i = 0; i < len; i++)
        {
            A[i] = rand() % 2001 - 1000; // Генерация чисел от -1000 до 1000
            B[i] = rand() % 2001 - 1000;
        }

        printf("Массив A: ");
        print_array_int(A, len);
        printf("Массив B: ");
        print_array_int(B, len);

        int *C = NULL;
        enum Errors result = task_2(len, A, B, &C);
        if (result != OK)
        {
            printf("Ошибка при выполнении задачи 2: %d\n", result);
            free(A);
            free(B);
            free(C);
            return result;
        }

        printf("Массив C: ");
        print_array_int(C, len);

        free(A);
        free(B);
        free(C);
    }
    else
    {
        printf("Неверное количество аргументов\n");
        return INVALID_INPUT;
    }

    return 0;
}