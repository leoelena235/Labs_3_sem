#include "header.h"

enum Errors convert_str_to_ll_int(const char *str, long long *result, int base)
{
    if (str == NULL || result == NULL)
    {
        return INVALID_INPUT;
    }

    *result = 0;
    int len = strlen(str);
    int sign = 1;

    // проверка на знак
    int start = 0;
    if (str[0] == '-')
    {
        sign = -1;
        start = 1;
    }

    for (int i = start; i < len; i++)
    {
        char c = toupper(str[i]);
        int digit;

        if (c >= '0' && c <= '9')
        {
            digit = c - '0';
        }
        else if (c >= 'A' && c <= 'Z')
        {
            digit = c - 'A' + 10;
        }
        else
        {
            return INVALID_INPUT;
        }

        if (digit >= base)
        {
            return INVALID_INPUT;
        }

        *result = *result * base + digit;
    }

    *result *= sign;
    return OK;
}

void fill_array_with_random_numbers_1(int *array, int size, int a, int b)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = a + rand() % (b - a + 1);
    }
}

enum Errors find_min_max_and_swap(int *array, int size)
{
    if (size == 0)
    {
        return INVALID_INPUT;
    }
    int min_num = 0, max_num = 0;
    for (int i = 1; i < size; i++)
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
    int temp = array[min_num];
    array[min_num] = array[max_num];
    array[max_num] = temp;
    return OK;
}

void print_array_int(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int int_comparator(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int closest_value(int *arr, int size, int value)
{ // бин поиск
    int left = 0;
    int right = size - 1;
    int mid;

    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (arr[mid] == value)
        {
            return arr[mid];
        }
        else if (arr[mid] < value)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    // проверка граничных чисел
    if (right < 0)
    {
        return arr[left];
    }
    else if (left >= size)
    {
        return arr[right];
    }
    else
    {
        if (abs(arr[left] - value) < abs(arr[right] - value))
        {
            return arr[left];
        }
        else
        {
            return arr[right];
        }
    }
}

    enum Errors task_2(int len, int *A, int *B, int **C){
    
        if (len <= 0)
        {
            return INVALID_INPUT;
        }

        *C = malloc(sizeof(int) * len);
        if (*C == NULL)
        {
            printf("Ошибка выделения памяти\n");
            return INVALID_MEMORY;
        }

        qsort(B, len, sizeof(int), int_comparator);

        for (int i = 0; i < len; i++)
        {
            int nearest = closest_value(B, len, A[i]);
            (*C)[i] = A[i] + nearest;
        }

        return OK;
    }