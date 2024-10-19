#include "header.h"

int main(int argc, char *argv[])
{

    if (input_fl_err(argc, argv) != OK)
    {
        return INVALID_INPUT;
    }
    switch (argv[1][1])
    {
    case 'l':
        if (argc != 3)
        {
            printf("Invalid input: uncorrect counts agruments\n");
            return INVALID_INPUT;
        }
        int lenght = len_string(argv[2]);
        printf("Len string: %d\n", lenght);
        break;
    case 'r':
        if (argc != 3)
        {
            printf("Invalid input: uncorrect counts agruments\n");
            return INVALID_INPUT;
        }
        char *reversed_str;
        enum Errors err_r = reversed_string(argv[2], &reversed_str);
        if (err_r != OK)
        {
            return INVALID_MEMORY;
        }
        printf("Reversed string: %s\n", reversed_str);
        free(reversed_str);
        break;
    case 'u':
        if (argc != 3)
        {
            printf("Invalid input: uncorrect counts agruments\n");
            return INVALID_INPUT;
        }
        char *new_str_u;
        enum Errors err_u = upper_str(argv[2], &new_str_u);
        if (err_u != OK)
        {
            return INVALID_MEMORY;
        }
        printf("New string: %s\n", new_str_u);
        free(new_str_u);
        break;
    case 'n':
        if (argc != 3)
        {
            printf("Invalid input: uncorrect counts agruments\n");
            return INVALID_INPUT;
        }
        char *new_str_n;
        enum Errors err_n = sort_simbols(argv[2], &new_str_n);
        if (err_n != OK)
        {
            return INVALID_MEMORY;
        }
        printf("Result string: %s\n", new_str_n);
        free(new_str_n);
        break;
    case 'c':
        if (argc <= 3)
        {
            printf("Invalid input: uncorrect counts agruments\n");
            return INVALID_INPUT;
        }
        int count_str = argc - 3;
        long long int seed;
        if (convert_str_to_int(argv[2], &seed, 10) != OK)
        {
            printf("INVALID_INPUT");
            return INVALID_INPUT;
        }
        char *new_str_c;
        enum Errors err_c = concotenation_str((argv + 3), &new_str_c, count_str, seed);

        if (err_c != OK)
        {
            return INVALID_MEMORY;
        }

        printf("String after concotenation: %s\n", new_str_c);
        free(new_str_c);
        break;
    default:
        printf("Uncorrect flag\n");
        break;
    }
    return OK;
}