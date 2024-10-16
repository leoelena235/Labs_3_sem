#include "header.h"

int main()
{
    int base;
    char *input_str = NULL;

    if (base_input(&base) != OK)
    {
        return INVALID_INPUT;
    }
    if (err_memory(&input_str) != OK)
    {
        return INVALID_MEMORY;
    }

    long long int max_number = LLONG_MIN;
    int numbers_entered = 0;
    char *stop_word = "Stop";

    while (scanf("%100s", input_str) == 1)
    {
        if (strcmp(input_str, stop_word) == 0)
        {
            break;
        }

        if (number_input(input_str, base) == INVALID_INPUT)
        {
            printf("Ошибка: некорректное число %s\n", input_str);
            free(input_str);
            return INVALID_INPUT;
        }

        long long int current_number;
        if (convert_str_to_ll_int(input_str, &current_number, base) == INVALID_INPUT)
        {
            printf("Ошибка: некорректное число %s\n", input_str);
            free(input_str);
            return INVALID_INPUT;
        }

        if (llabs(current_number) > llabs(max_number))
        {
            max_number = current_number;
        }
        numbers_entered = 1;
    }

    if (numbers_entered)
    {
        convert_and_print_max_number(base, max_number);
    }

    free(input_str);
    return 0;
}
