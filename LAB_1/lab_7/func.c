#include "header.h"

// для проверки пути
char *get_filename_from_path(const char *path)
{
    char *last_slash = strrchr(path, '/');
    if (last_slash == NULL)
    {
        last_slash = strrchr(path, '\\');
    }
    if (last_slash != NULL)
    {
        return last_slash + 1;
    }
    else
    {
        return (char *)path;
    }
}
enum Errors input_fl_err(int argc, char *argv[], int *flag)
{
    if (argc != 5 && argc != 4)
    {
        printf("Ошибка ввода\n");
        return INVALID_INPUT;
    }

    if (!((argv[1][0] == '-' || argv[1][0] == '/') && argv[1][2] == '\0'))
    {
        printf("Ошибка ввода\n");
        return INVALID_INPUT;
    }
    *flag = argv[1][1];

    return OK;
}

char *read_lexeme(FILE *file)
{
    if (!file)
        return NULL;

    char buffer[256];
    int i = 0;
    int c;

    while ((c = fgetc(file)) != EOF && isspace(c))
    {
    }

    if (c == EOF)
    {
        return NULL;
    }

    buffer[i++] = c;
    while ((c = fgetc(file)) != EOF && !isspace(c))
    {
        buffer[i++] = c;
    }
    buffer[i] = '\0';

    char *lexeme = (char *)malloc(i + 1);
    if (lexeme)
    {
        strcpy(lexeme, buffer);
    }

    return lexeme;
}

enum Errors files_func_1(const char *input_1, const char *input_2, const char *output_file)
{

    char *input_filename_1 = get_filename_from_path(input_1);
    char *input_filename_2 = get_filename_from_path(input_2);
    char *output_filename = get_filename_from_path(output_file);

    if (strcmp(input_filename_1, input_filename_2) == 0 || strcmp(input_filename_1, output_filename) == 0 || strcmp(input_filename_2, output_filename) == 0)
    {
        printf("Ошибка: названия файлов совпадают.\n");
        return FILE_ERROR;
    }

    FILE *f_1 = fopen(input_1, "r");
    FILE *f_2 = fopen(input_2, "r");
    FILE *f_out = fopen(output_file, "w");

    if (f_1 == NULL || f_2 == NULL || f_out == NULL)
    {
        printf("Ошибка открытия файлов\n");
        if (f_1 != NULL)
            fclose(f_1);
        if (f_2 != NULL)
            fclose(f_2);
        if (f_out != NULL)
            fclose(f_out);
        return ERROR_OPEN_FILE;
    }

    fseek(f_1, 0, SEEK_END);
    fseek(f_2, 0, SEEK_END);
    if (ftell(f_1) == 0 && ftell(f_2) == 0)
    {
        printf("Ошибка: входные файлы пусты.\n");
        fclose(f_1);
        fclose(f_2);
        fclose(f_out);
        return FILE_ERROR;
    }
    fseek(f_1, 0, SEEK_SET);
    fseek(f_2, 0, SEEK_SET);

    char *lexeme1 = read_lexeme(f_1);
    char *lexeme2 = read_lexeme(f_2);

    while (lexeme1 || lexeme2)
    {
        read_and_print_lexeme(f_1, f_out, &lexeme1);
        read_and_print_lexeme(f_2, f_out, &lexeme2);
    }

    fclose(f_1);
    fclose(f_2);
    fclose(f_out);
    return OK;
}
void read_and_print_lexeme(FILE *file, FILE *f_out, char **lexeme)
{
    if (*lexeme)
    {
        fprintf(f_out, "%s ", *lexeme);
        free(*lexeme);
        *lexeme = read_lexeme(file);
    }
}

//-a
enum Errors convert_str_to_double(const char *str, double *result)
{
    if (*str == '\0')
    {
        return INVALID_INPUT;
    }
    char *endptr;
    *result = strtod(str, &endptr);

    if (endptr == str || *endptr != '\0')
    {
        return INVALID_INPUT;
    }
    if (*result == HUGE_VAL || *result == -HUGE_VAL)
    {
        return OVERFLOW_ERROR;
    }

    return OK;
}
void convert_to_base4(char *dest, char c)
{
    int ascii = (int)c;
    int i = 0;
    char base4[10];

    do
    {
        base4[i++] = (ascii % 4) + '0';
        ascii /= 4;
    } while (ascii > 0);

    while (i < 4)
    {
        base4[i++] = '0';
    }

    // переворачиваем строку
    for (int j = 0; j < i; j++)
    {
        dest[j] = base4[i - j - 1];
    }

    dest[i] = '\0';
}

void convert_to_base8(char *dest, char c)
{
    int ascii = (int)c;
    sprintf(dest, "%03o", ascii);
}

enum Errors files_func_2(const char *input_file, const char *output_file)
{
    char *input_filename = get_filename_from_path(input_file);
    char *output_filename = get_filename_from_path(output_file);

    if (strcmp(input_filename, output_filename) == 0)
    {
        printf("Ошибка: названия файлов совпадают.\n");
        return FILE_ERROR;
    }


    FILE *f_in = fopen(input_file, "r");
    FILE *f_out = fopen(output_file, "w");

    if (f_in == NULL || f_out == NULL) 
    {
        printf("Ошибка открытия файлов\n");
        if (f_in != NULL)
            fclose(f_in);
        if (f_out != NULL)
            fclose(f_out);
        return ERROR_OPEN_FILE;
    }

    fseek(f_in, 0, SEEK_END);
    if (ftell(f_in) == 0)
    {
        printf("Ошибка: входной файл пуст.\n");
        fclose(f_in);
        fclose(f_out);
        return FILE_ERROR;
    }
    fseek(f_in, 0, SEEK_SET);

    char *lexeme;
    int lexeme_count = 0;
    char base4[5], base8[4];

    while ((lexeme = read_lexeme(f_in)) != NULL)
    {
        lexeme_count++;

        if (lexeme_count % 10 == 0)
        {
            for (int i = 0; lexeme[i] != '\0'; i++)
            {
                convert_to_base4(base4, tolower(lexeme[i]));
                fprintf(f_out, "%s", base4);
            }
        }
        else if (lexeme_count % 2 == 0 && lexeme_count % 10 != 0)
        {
            for (int i = 0; lexeme[i] != '\0'; i++)
            {
                fprintf(f_out, "%c", tolower(lexeme[i]));
            }
        }
        else if (lexeme_count % 5 == 0 && lexeme_count % 10 != 0)
        {
            for (int i = 0; lexeme[i] != '\0'; i++)
            {
                convert_to_base8(base8, lexeme[i]);
                fprintf(f_out, "%s", base8);
            }
        }
        else
        {
            fprintf(f_out, "%s", lexeme);
        }

        fprintf(f_out, " ");
        free(lexeme);
    }

    fclose(f_in);
    fclose(f_out);
    return OK;
}