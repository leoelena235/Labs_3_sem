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
    // если одинаковые названия файлов при вводе
    if (strcmp(argv[1], argv[2]) == 0)
    {
        printf("Ошибка: входной и выходной файлы не могут иметь одинаковое имя\n");
        close_files(input, output);
        return INVALID_INPUT;
    }

    int capacity = MAX_LINE_LENGTH;
    char *buffer = (char *)malloc(capacity * sizeof(char));
    if (buffer == NULL)
    {
        printf("Ошибка выделения памяти\n");
        close_files(input, output);
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
            close_files(input, output);
            free(buffer);
            return INVALID_INPUT;
        }
        else if (err == INVALID_MEMORY)
        {
            printf("Ошибка выделения памяти\n");
            close_files(input, output);
            free(buffer);
            return INVALID_MEMORY;
        }
    }
    // если пустой файл
    if (len == 0)
    {
        fprintf(output, "Файл пустой\n");
    }
    printf("Запись в файл сделана\n");

    close_files(input, output);
    free(buffer);

    return 0;
}