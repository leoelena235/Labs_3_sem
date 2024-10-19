#include "header.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Error input: uncorrect count arguments\n");
        return INVALID_INPUT;
    }
    double epsilon;
    if (convert_str_to_double(argv[1], &epsilon) != OK ||
        epsilon <= 0)
    {
        printf("Error input: uncorrect epsilon\n");
        return INVALID_INPUT;
    }

    double results[15];
    double (*functions[15])(double) = {
        limit_e, limit_pi, limit_ln, limit_sqrt, limit_y,
        row_e, row_pi, row_ln, row_sqrt, row_y,
        equation_e, equation_pi, equation_ln, equation_sqrt, equation_y};

    char *constants[5] = {"e", "pi", "ln2", "sqrt2", "gamma"};
    char *ways[3] = {"Limits:", "Rows:", "Equations:"};

    for (int i = 0; i < 15; i++)
    {
        results[i] = functions[i](epsilon);
    }

    for (int i = 0; i < 15; i++)
    {
        if (i % 5 == 0)
        {
            printf("\n %c%s", ' ', ways[i / 5]);
        }
        printf("\n %s ==", constants[i % 5]);
        if (results[i] != INFINITY && !isnan(results[i]))
        {
            printf(" %.*f", 6, results[i]);
        }
        else
        {
            printf(" couldn't calculate constant with given accuracy");
        }
    }

    return 0;
}