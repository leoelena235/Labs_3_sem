#include "header.h"

enum Errors file_func(int argc, char *argv[], FILE **input, FILE **output, char *output_filename)
{
    if (argc < 3 || argc > 4)
    {
        printf("Ошибка: некорректный ввод\n");
        return INVALID_INPUT;
    }

    if (!((argv[1][0] == '-' || argv[1][0] == '/') && (argv[1][2] == '\0' || argv[1][3] == '\0')))
    {
        printf("Ошибка: некорректный ввод флага\n");
        return INVALID_INPUT;
    }

    *input = fopen(argv[2], "r");
    if (*input == NULL)
    {
        printf("Ошибка: не получилось открыть файл %s\n", argv[2]);
        return ERROR_FILE;
    }

    int first_char = fgetc(*input);
    if (first_char == EOF)
    {
        printf("Ошибка: входной файл пустой\n");
        fclose(*input);
        return ERROR_FILE;
    }
    fseek(*input, 0, SEEK_SET);

    if (argv[1][1] == 'n')
    {
        if (argc != 4)
        {
            printf("Ошибка: некорректный ввод\n");
            fclose(*input);
            return INVALID_INPUT;
        }
        strcpy(output_filename, argv[3]);
    }
    else
    {
        strcpy(output_filename, "out_");
        strcat(output_filename, argv[2]);
    }

    if (strcmp(argv[2], output_filename) == 0)
    {
        printf("Ошибка: имена входного и выходного файлов совпадают\n");
        fclose(*input);
        return ERROR_FILE;
    }

    *output = fopen(output_filename, "w");
    if (*output == NULL)
    {
        printf("Ошибка: не получилось открыть файл %s или его не существует\n", output_filename);
        fclose(*input);
        return ERROR_FILE;
    }

    return OK;
}

// for d
void remove_arabic_numerals(FILE *input, FILE *output)
{
    char simbols;
    while ((simbols = fgetc(input)) != EOF)
    {
        if (!isdigit(simbols))
        {
            fputc(simbols, output);
        }
    }
}
// for i
enum Errors count_latin_letters(FILE *input, FILE *output)
{
    char line[1024];
    int count;

    while (fgets(line, sizeof(line), input) != NULL)
    {
        count = 0;
        for (int i = 0; line[i] != '\0'; i++)
        {
            if (isalpha(line[i]))
            {
                count++;
            }
        }
        if (fprintf(output, "%d\n", count) < 0)
        {
            printf("Ошибка: не удалось записать в файл.\n");
            fclose(input);
            fclose(output);
            return ERROR_FILE;
        }
    }

    if (!feof(input))
    {
        printf("Ошибка: чтение из файла не удалось.\n");
        return ERROR_FILE;
        fclose(input);
        fclose(output);
    }
    fclose(input);
    fclose(output);
    return OK;
}
// for s
void count_special_characters(FILE *input, FILE *output)
{
    char line[1024];

    // Читаем строку за строкой из входного файла
    while (fgets(line, sizeof(line), input) != NULL)
    {
        int count = 0;
        int i = 0;

        // Проходим по каждому символу в строке
        while (line[i] != '\0')
        {
            char current_char = line[i];

            // Проверяем, является ли символ буквой латинского алфавита, цифрой, пробелом или символом новой строки
            if (!((current_char >= 'a' && current_char <= 'z') ||
                  (current_char >= 'A' && current_char <= 'Z') ||
                  (current_char >= '0' && current_char <= '9') ||
                  (current_char == ' ') ||
                  (current_char == '\n')))
            {

                // Если символ не является буквой, цифрой, пробелом или символом новой строки, увеличиваем счетчик
                count++;
            }

            // Переходим к следующему символу
            i++;
        }

        // Записываем результат в выходной файл
        fprintf(output, "%d\n", count);
    }
}
// for a
void change_simb(FILE *input, FILE *output)
{
    int c;
    while ((c = fgetc(input)) != EOF)
    {
        if (isdigit(c))
        {
            // Если символ является цифрой, записываем его как есть
            fputc(c, output);
        }
        else
        {
            // Иначе записываем его ASCII код в шестнадцатеричной системе счисления
            fprintf(output, "%X", c);
        }
    }
}