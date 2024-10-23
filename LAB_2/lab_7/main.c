#include "header.h"

int main()
{
    double result;
    enum Errors error = dichotomy_method(0.5, 1.511111, 0.0000000001, function_5, &result);
    if (error == OK)
    {
        printf("root is %lf\n", result);
    }
    else if (error == INVALID_INPUT)
    {
        printf("Invalid input: uncorrect\n");
    }
    else if (error == NO_ROOTS)
    {
        printf("No roots in the interval\n");
    }

    else
    {
        printf("Unknown error\n");
    }

    return 0;
}
