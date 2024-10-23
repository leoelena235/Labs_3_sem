#include "header.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Invalid input: incorrect count of arguments\n");
        return INVALID_INPUT;
    }

    if (argc == 3)
    {
        printf("Choose task:\n");
        printf("1. Calculate geometric mean\n");
        printf("2. Raise a number to a power\n");
        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            double result;
            enum Errors error = geometric_mean(&result, 1, (double[]){strtod(argv[1], NULL)});
            if (error != OK)
            {
                printf("Error: %d\n", error);
                return INVALID_ARGUMENT;
            }
            printf("Geometric mean: %f\n", result);
            break;

        case 2:
            double base = strtod(argv[1], NULL);
            long long int exp;
            enum Errors status = convert_str_to_int(argv[2], &exp, 10);
            if (status != OK)
            {
                printf("Error: %d\n", status);
                return INVALID_INPUT;
            }

            double result_2;
            enum Errors error_2 = recurse_double_in_int_pow(base, (int)exp, &result_2);
            if (error_2 != OK)
            {
                printf("Error: %d\n", error_2);
                return INVALID_INPUT;
            }
            printf("Result of %f^%lld: %f\n", base, exp, result_2);
            break;

        default:
            printf("Invalid choice\n");
            return INVALID_INPUT;
        }
    }
    else if (argc >= 4)
    {
        long long int count;
        enum Errors status = convert_str_to_int(argv[argc - 1], &count, 10);
        if (status != OK || count <= 0 || count != argc - 2)
        {
            printf("Invalid argument count.\n");
            return INVALID_INPUT;
        }

        double numbers[count];
        for (int i = 0; i < count; i++)
        {
            char *endptr;
            numbers[i] = strtod(argv[i + 1], &endptr);
            if (*endptr != '\0')
            {
                printf("Invalid number: %s\n", argv[i + 1]);
                return INVALID_ARGUMENT;
            }
        }

        double result;
        enum Errors error = geometric_mean(&result, count, numbers);

        if (error != OK)
        {
            printf("Error: %d\n", error);
            return INVALID_ARGUMENT;
        }

        printf("Geometric mean: %f\n", result);
    }

    return OK;
}