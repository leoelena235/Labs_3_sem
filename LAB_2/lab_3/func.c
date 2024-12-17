#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

finalyAns *Task(char *str, ...)
{
    if (!str)
        return NULL;
    // Длина подстроки
    int len = SizeOfStr(str);
    if (len == 0)
    {
        return NULL; 
    }

    // Выделение памяти для префикс-функции
    int *prefix_mass = (int *)malloc(len * sizeof(int));
    if (!prefix_mass)
    {
        return NULL; 
    }

    // Вычисление префикс-функции
    calculate_prefix(str, prefix_mass, len);

    va_list args;
    va_start(args, str);

    finalyAns *answer = NULL; // Основной массив результатов
    finalyAns *tmp = NULL;
    int count_files = 0; // Счётчик обработанных файлов

    while (1)
    {
        char *filename = va_arg(args, char *);
        if (!filename)
        {
            break; // Конец списка аргументов
        }

        count_files++;

        // Расширение массива результатов для нового файла
        tmp = (finalyAns *)realloc(answer, count_files * sizeof(finalyAns));
        if (!tmp)
        {
            free(answer);
            free(prefix_mass);
            return NULL; // Ошибка выделения памяти
        }
        answer = tmp;

        values *ans = NULL; // Для хранения результатов поиска в текущем файле
        int count_ans = StrInFile(str, filename, prefix_mass, len, &ans);

        answer[count_files - 1].filename = filename;

        if (count_ans == OPEN_PROBLEM)
        {
            answer[count_files - 1].status = OPEN_PROBLEM;
            continue;
        }
        if (count_ans == INVALID_MEMORY)
        {
            answer[count_files - 1].status = INVALID_MEMORY;
            continue;
        }

        // Запись результата для текущего файла
        answer[count_files - 1].status = OK;
        answer[count_files - 1].ans_for_file = ans;
        answer[count_files - 1].ans_for_file_len = count_ans;
    }

    if (count_files > 0)
    {
        answer[0].count_files = count_files; // Сохраняем общее количество файлов
    }

    free(prefix_mass); // Освобождаем память для префикс-функции
    va_end(args);
    return answer;
}

void calculate_prefix(char *str, int *prefix_mass, int len)
{
    prefix_mass[0] = 0;
    int prefix_len = 0;

    for (int i = 1; i < len; i++)
    {
        while (prefix_len > 0 && str[i] != str[prefix_len])
        {
            prefix_len = prefix_mass[prefix_len - 1];
        }
        if (str[prefix_len] == str[i])
        {
            prefix_len++;
        }
        prefix_mass[i] = prefix_len;
    }
}

int StrInFile(char *str, char *file, int *prefix_mass, int len, values **start)
{
    FILE *in = fopen(file, "r");
    if (!in)
    {
        return OPEN_PROBLEM;
    }

    char current;
    int count_n = checkStr(str); // Количество символов '\n' в подстроке
    int count_sovpad = 0;        // Количество совпавших символов
    int count = 0;               // Текущая позиция в строке файла
    int count_str_number = 1;    // Номер текущей строки
    int count_ans = 0;           // Количество найденных вхождений
    int start_in = 0;            // Позиция начала текущего вхождения

    values *ans = NULL;

    while ((current = fgetc(in)) != EOF)
    {
        count++;

        // Проверяем совпадение символов строки и подстроки
        while (count_sovpad > 0 && current != str[count_sovpad])
        {
            count_sovpad = prefix_mass[count_sovpad - 1];
        }

        if (current == '\n')
        {
            count = 0;          // Обнуляем позицию в строке
            count_str_number++; // Переходим к следующей строке
        }

        if (count_sovpad == 0 && current == str[count_sovpad])
        {
            start_in = count;
        }

        if (current == str[count_sovpad])
        {
            count_sovpad++;
        }

        // Полное совпадение найдено
        if (count_sovpad == len)
        {
            count_ans++;

            // Расширение массива результатов для нового вхождения
            ans = (values *)realloc(*start, sizeof(values) * count_ans);
            if (!ans)
            {
                fclose(in);
                return INVALID_MEMORY; // Ошибка выделения памяти
            }
            *start = ans;

            ans[count_ans - 1].str_number = count_str_number - count_n;
            ans[count_ans - 1].symbol_number = start_in;

            count_sovpad = prefix_mass[count_sovpad - 1];
        }
    }

    fclose(in);
    return count_ans;
}

int checkStr(char *s)
{
    int ans = 0;
    for (int i = 0; s[i] != 0; i++)
    {
        if (s[i] == '\n')
        {
            ans++;
        }
    }
    return ans;
}

int SizeOfStr(char *s)
{
    int ans = 0;
    while (s[ans] != 0)
    {
        ans++;
    }
    return ans;
}
