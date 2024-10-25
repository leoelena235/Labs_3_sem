#include "header.h"

int main()
{
    double *coefs; 
    int count = 3; 
    enum Errors error = decomposition_of_a_polynomial(count, 0.0001, 0, &coefs, 1.0, -2.0, 1.0);
    if (error == INVALID_INPUT)
    {
        printf("Invalid input\n");
        return INVALID_INPUT;
    }
    else if (error == INVALID_MEMORY)
    {
        printf("Invalid memory \n");
        return INVALID_MEMORY;
    }
    printf("Result: ");
    for (int i = 0; i < count; i++)
    {
        printf("%lf ", coefs[i]);
    }
    free(coefs);
    printf("\n");
    return 0;
}