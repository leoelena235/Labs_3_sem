#include "header.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Uncorrect count of values\n");
        return INVALID_INPUT;
    }

    int base;
    enum Errors status = valid_base(argv[1], &base);
    if (status != OK)
    {
        return INVALID_INPUT;
    }
    double fractions[argc - 2];
    for (int i = 2; i < argc; i++)
    {
        char *endptr;
        double fraction = strtod(argv[i], &endptr);

        if (*endptr != '\0' || endptr == argv[i])
        {
            printf("Incorrect fraction: not a double\n");
            return INVALID_INPUT;
        }

        fractions[i - 2] = fraction;
    }

    status = check_fractions(base, argc - 2, fractions[0], fractions[1], fractions[2], fractions[3], fractions[4], fractions[5], fractions[6], fractions[7], fractions[8], fractions[9]);

    if (status != OK)
    {
        return INVALID_INPUT;
    }

    return OK;
}