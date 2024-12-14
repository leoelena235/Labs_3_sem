#include "header.h"
int main()
{
    double *result = NULL;
    int count = 0;
    enum Errors error = check_fractions(8, &count, &result, 6, 0.125, 0.5, 0.0001, 0.25, 0.625, 0.0005);
    if (error == INVALID_MEMORY)
    {
        printf("Invalid memory: memory allocation\n");
        return INVALID_MEMORY;
    }
    else if (error == INVALID_INPUT)
    {
        // printf("invalid base\n");
        return INVALID_INPUT;
    }

    if (result == NULL)
    {
        printf("No numbers have finale representation\n");
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            if (fabs(result[i]) > EPSILON)
            {
                printf("Fraction %d has finale representation in this base\n", i + 1);
            }
            else
            {
                printf("Fraction %d does not have finale representation in this base\n", i + 1);
            }
        }

        free(result);
    }

    return 0;
}