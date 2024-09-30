#include "header.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Ошибка ввода: неверное число аргументов\n");
        return INVALID_INPUT;
    }

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    if (input == NULL || output == NULL)
    {
        printf("Ошибка: не получилось открыть файл\n");
        close_files(input, output);
        return ERROR_OPEN_FILE;
    }

    int capacity = MAX_LINE_LENGTH;
    char *buffer = (char *)malloc(capacity * sizeof(char));
    if (buffer == NULL)
    {
        printf("Ошибка выделения памяти\n");
        fclose(input);
        fclose(output);
        return INVALID_MEMORY;
    }

    int len = 0;
    int simbols;
    while ((simbols = fgetc(input)) != EOF)
    {
        ungetc(simbols, input);
        enum Errors err = main_func(input, output, buffer, &len, &capacity);
        if (err == INVALID_INPUT)
        {
            printf("Некорректный ввод\n");
            fclose(input);
            fclose(output);
            free(buffer);
            return INVALID_INPUT;
        }
        else if (err == INVALID_MEMORY)
        {
            printf("Ошибка выделения памяти\n");
            fclose(input);
            fclose(output);
            free(buffer);
            return INVALID_MEMORY;
        }
    }

    printf("Запись в файл сделана\n");

    fclose(input);
    fclose(output);
    free(buffer);

    return 0;
}