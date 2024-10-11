#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 3 || argc > 4)
    {
        printf("Errors input: uncorrect flag\n");
        return INVALID_INPUT;
    }
    if (valid_flag(argv[1]) != OK)
    {
        printf("Error input: uncorrect flag\n");
        return INVALID_INPUT;
    }
      if (argc == 4 && strcmp(argv[2], argv[3]) == 0)
    {
        printf("Error: input_file has the same name as out_file\n");
        return ERROR_FILE;
    }
    
    FILE *input = fopen(argv[2], "r");
    if (input == NULL)
    {
        printf("Error opening the file %s\n", argv[2]);
        return ERROR_FILE;
    }

    int first_char = fgetc(input);
    if (first_char == EOF)
    {
        printf("Ошибка: входной файл пустой\n");
        fclose(input);
        return ERROR_FILE;
    }
    fseek(input, 0, SEEK_SET);

    FILE *output = NULL;
    char *output_filename = NULL;//

    if (argv[1][1] == 'n')
    {
        if (argc != 4)
        {
            printf("Error input\n");
            if(input != NULL)fclose(input);
            return INVALID_INPUT;
        }

        output = fopen(argv[3], "w");
        if (output == NULL)
        {
            printf("Error opening the file %s\n", argv[3]);
           if(input != NULL)fclose(input);
            return ERROR_FILE;
        }
    }
    else
    {
        if (argc != 3)
        {
            printf("Error: uncorrect input\n");
           if(input != NULL) fclose(input);
            return INVALID_INPUT;
        }
        // Находим последний символ '\' в пути к файлу
        char *last_backslash = strrchr(argv[2], '\\');
        if (last_backslash == NULL)
        {
            // Если '\' не найден, используем весь путь как имя файла
            last_backslash = argv[2] - 1;
        }

        // Выделяем память для нового пути
        output_filename = (char *)malloc((last_backslash - argv[2] + 1 + 5 + strlen(last_backslash + 1)) * sizeof(char));
        if (output_filename == NULL)
        {
            printf("Error memory\n");
            if(input != NULL) fclose(input);
            return INVALID_INPUT;
        }

        // Копируем путь до последнего '\'
        strncpy(output_filename, argv[2], last_backslash - argv[2] + 1);
        output_filename[last_backslash - argv[2] + 1] = '\0';

        // Добавляем "out_"
        strcat(output_filename, "out_");

        // Добавляем имя файла
        strcat(output_filename, last_backslash + 1);

        output = fopen(output_filename, "w");
        if (output == NULL)
        {
            printf("Error opening the file %s\n", output_filename);
            free(output_filename);
            if(input != NULL) fclose(input);
            return ERROR_FILE;
        }
    }
    // if (strcmp(argv[2], output_filename) == 0)
    // {
    //     printf("Error: input_file has name, like out_file\n");
    //     free(output_filename);
    //     fclose(input);
    //     fclose(output);
    //     return ERROR_FILE;
    // }

    // output = fopen(output_filename, "w");
    // if (output == NULL)
    // {
    //     printf("Ошибка: не получилось открыть файл %s или его не существует\n", output_filename);
    //     fclose(input);
    //     return ERROR_FILE;
    // }

    switch (argv[1][strlen(argv[1]) - 1])
    {
    case 'd':
        remove_arabic_numerals(input, output);
        printf("All arabic simbols have been delited from the file\n");
        break;
    case 'i':
        enum Errors res_i = count_latin_letters(input, output);
        if (res_i != OK)
        {
            fclose(input);
            fclose(output);
            return res_i;
        }
        else
        {
            printf("Количество латинских букв в каждой строке записано в выходной файл\n");
            break;
        }
    case 's':
        count_special_characters(input, output);
        printf("Количество символов, отличных от букв латинского алфавита, арабских цифр и пробела, записано в выходной файл\n");
        break;
    case 'a':
        change_simb(input, output);
        printf("Символы, отличные от символов цифр, заменены на их ASCII код в шестнадцатеричной системе счисления\n");
        break;
    default:
        printf("Ошибка: неизвестный флаг\n");
        fclose(input);
        fclose(output);
        return INVALID_INPUT;
    }
    printf("All done\n");
    //free(output_filename);
    fclose(input);
    fclose(output);
    return OK;
}