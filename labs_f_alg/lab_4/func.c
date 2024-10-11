#include "header.h"

enum Errors valid_flag(const char *str)
{
    if (str == NULL)
        return INVALID_INPUT;
    if ((str[0] == '-' || str[0] == '/') && (str[2] == '\0' || (str[3] == '\0' && str[1] == 'n')))
        return OK;
    return INVALID_INPUT;
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
            printf("Error writing to the file\n");
            fclose(input);
            fclose(output);
            return ERROR_FILE;
        }
    }

    if (!feof(input))
    {
        printf("Error: Reading from the file failed\n");
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

    while (fgets(line, sizeof(line), input) != NULL)
    {
        int count = 0;
        int i = 0;

        while (line[i] != '\0')
        {
            char current_char = line[i];

            if (!((current_char >= 'a' && current_char <= 'z') ||
                  (current_char >= 'A' && current_char <= 'Z') ||
                  (current_char >= '0' && current_char <= '9') ||
                  (current_char == ' ') ||
                  (current_char == '\n')))
            {

                count++;
            }

            i++;
        }

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