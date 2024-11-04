#include "header.h"

int main()
{
    unsigned int n = 3; // размерность
    vector vect_1, vect_2, vect_3;
    enum Errors error_1 = vector_init(n, &vect_1, 3.0, -2.0, 5.0);
    if (error_1 == INVALID_MEMORY)
    {
        printf("Invalid memory: baaaad\n");
        return INVALID_MEMORY;
    }
    else if ((error_1) == INVALID_INPUT)
    {
        return INVALID_INPUT;
    }

    enum Errors error_2 = vector_init(n, &vect_2, 6.0, 1.0, 1.0);
    if (error_2 == INVALID_MEMORY)
    {
        vector_kill(&vect_1);
        printf("Invalid memory: baaaad\n");
        return INVALID_MEMORY;
    }
    else if ((error_2) == INVALID_INPUT)
    {
        vector_kill(&vect_1);
        return INVALID_INPUT;
    }

    enum Errors error_3 = vector_init(n, &vect_3, 1.0, 1.0, 1.0);
    if (error_3 == INVALID_MEMORY)
    {
        vector_kill(&vect_1);
        vector_kill(&vect_2);

        printf("Invalid memory: baaaad\n");
        return INVALID_MEMORY;
    }
    else if ((error_3) == INVALID_INPUT)
    {
        vector_kill(&vect_1);
        vector_kill(&vect_2);
        return INVALID_INPUT;
    }

    vector *result_1 = NULL;
    vector *result_2 = NULL;
    vector *result_3 = NULL;
    int size_1, size_2, size_3;
    enum Errors error = main_func(2, norm_inf, norm_p, norm_m, &size_1, &size_2,
                                  &size_3, &result_1, &result_2, &result_3, &vect_1, &vect_2, &vect_3);
    if (error != OK)
    {
        vector_kill(&vect_1);
        vector_kill(&vect_2);
        vector_kill(&vect_3);
        printf("Error: everything is not good \n");
        return error;
    }
    printf("Result:\n");
    for (int i = 0; i < size_1; i++)
    {
        print_vect(&result_1[i]);
    }
    for (int i = 0; i < size_2; i++)
    {
        print_vect(&result_2[i]);
    }
    for (int i = 0; i < size_3; i++)
    {
        print_vect(&result_3[i]);
    }
    vector_kill(&vect_1);
    vector_kill(&vect_2);
    vector_kill(&vect_3);
    vector_kill(result_1);
    vector_kill(result_2);
    vector_kill(result_3);

    free(result_1); 
    free(result_2); 
    free(result_3); 
}