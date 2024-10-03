#include "header.h"

int main(int argc, char *argv[])
{
    FILE *input = NULL;
    FILE *output = NULL;
    char *output_filename = NULL;

    output_filename = (char *)malloc(256 * sizeof(char));
    if (output_filename == NULL)
    {
        printf("Ошибка выделения памяти\n");
        return INVALID_MEMORY;
    }

    enum Errors result = file_func(argc, argv, &input, &output, output_filename);
    if (result != OK)
    {
        free(output_filename);
        return result;
    }

    switch (argv[1][strlen(argv[1]) - 1])
    {
    case 'd':
        remove_arabic_numerals(input, output);
        printf("Из исходного файла удалены арабские цифры\n");
        break;
    case 'i':
        enum Errors res_i = count_latin_letters(input, output);
        if (res_i != OK)
        {
            free(output_filename);
            return res_i;
        }
        else
        {
            printf("Количество латинских букв в каждой строке записано в выходной файл\n");
            return OK;
        }
        break;
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
        free(output_filename);
        return INVALID_INPUT;
        break;
    }

    fclose(input);
    fclose(output);
    free(output_filename);
    return OK;
}