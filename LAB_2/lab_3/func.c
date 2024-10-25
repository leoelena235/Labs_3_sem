#include "header.h"
// для вычисления хеша подстроки
long long int calculate_hash(const char *str, int len, int begin)
{
    long long int hash = 0;
    long long int power = 1;

    for (int i = 0; i < len; i++)
    {
        hash = (hash + str[(begin + i) % len] * power) % HASH_SPREAD;
        power = (power * BASE) % HASH_SPREAD;
    }

    return hash;
}

// для поиска вхождений подстроки в файле
enum Errors search_substring_in_file(int **result, int *cur_elem, const char *filename, long long int str_hash, int substring_len)
{
    if (filename == NULL)
    {
        return INVALID_INPUT;
    }
    if (result == NULL)
    {
        return INVALID_INPUT;
    }
    if (cur_elem == NULL)
    {
        return INVALID_INPUT;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return ERROR_OPEN_FILE;

    char buffer[substring_len];
    int buffer_index = 0, c;
    long long int current_hash;
    int line = 1, simbol = 0, is_start = 0;

    while ((c = fgetc(file)) != EOF)
    {
        if (is_start + 1 < substring_len)
        {
            is_start++;
        }
        else if (buffer[buffer_index] == '\n')
        {
            line++;
            simbol = 1;
        }
        else
        {
            simbol++;
        }

        buffer[buffer_index] = c;
        buffer_index = (buffer_index + 1) % substring_len;
        current_hash = calculate_hash(buffer, substring_len, buffer_index);
        if (current_hash == str_hash)
        {
            (*result)[*cur_elem] = line;
            (*cur_elem)++;
            (*result)[*cur_elem] = simbol;
            (*cur_elem)++;
        }
    }

    fclose(file);

    return OK;
}

// main func для поиска подстроки в файлах
enum Errors find_substring(int **result, int *count_val, const char *substr, const int count, ...)
{
    if (count <= 0)
    {
        printf("Uncorrect count\n");
        return INVALID_INPUT;
    }
    if (result == NULL)
    {
        return INVALID_INPUT;
    }
    if (substr == NULL)
    {
        return INVALID_INPUT;
    }

    long long int substr_hash = calculate_hash(substr, strlen(substr), 0);

    va_list args;
    va_start(args, count);

    int match_count = 0;

    for (int i = 0; i < count; i++)
    {
        const char *filename = va_arg(args, const char *);
        enum Errors status = search_substring_in_file(result, &match_count, filename, substr_hash, strlen(substr));
        if (status != OK)
            return INVALID_INPUT;
    }

    (*result) = (int *)malloc(match_count * 2 * sizeof(int));
    if (*result == NULL)
        return INVALID_MEMORY;
    *count_val = 0;

    va_end(args);
    va_start(args, count);

    for (int i = 0; i < count; i++)
    {
        const char *filename = va_arg(args, const char *);
        enum Errors status = search_substring_in_file(result, count_val, filename, substr_hash, strlen(substr));
        if (status != OK)
        {
            free(*result);
            return INVALID_INPUT;
        }
    }

    va_end(args);

    return OK;
}
