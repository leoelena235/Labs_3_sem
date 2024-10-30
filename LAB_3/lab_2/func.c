#include "header.h"

enum Errors vector_init(int n, vector *vect, ...)
{
    if (vect == NULL)
    {
        return INVALID_INPUT;
    }
    if (n < 0)
    {
        printf("Uncorrect n\n");
        return INVALID_INPUT;
    }
    vect->n = n;
    double *coordinats = (double *)malloc(n * sizeof(double));
    if (coordinats == NULL)
    {
        printf("Error allocation\n");
        return INVALID_MEMORY;
    }
    vect->coordinats = coordinats;
    va_list arg;
    va_start(arg, vect);
    for (int i = 0; i < n; i++)
    {
        vect->coordinats[i] = va_arg(arg, double);
    }

    va_end(arg);
    return OK;
}
// освбожодаем память и сбрасываем поля структуры
vector_kill(vector *vect)
{
    if (vect == NULL)
    {
        return INVALID_INPUT;
    }
    free(vect->coordinats);
    vect->n = 0;
    vect->coordinats = NULL;
    return OK;
}

void print_vector(vector *vect)
{
    for (int i = 0; i < vect->n; i++)
    {
        printf("%.3f ", vect->coordinats[i]);
    }
    printf("\n");
}
// just abs
enum Errors norm_inf(vector *vect, double *norm)
{
    if (vect == NULL || norm == NULL)
    {
        return INVALID_INPUT;
    }
    double max_val = 0.0;
    for (unsigned i = 0; i < vect->n; i++)
    {
        double current_element = vect->coordinats[i];

        double absolute_value = fabs(current_element);

        if (absolute_value > max_val)
        {
            max_val = absolute_value;
        }
    }

    *norm = max_val;

    return OK;
}
//
enum Errors norm_p(vector *vect, double *norm, unsigned int p)
{
    if (vect == NULL || norm == NULL)
    {
        return INVALID_INPUT;
    }
    if (p < 1)
    {
        printf("Unvorrect p\n");
        return INVALID_INPUT;
    }
    double sum = 0.0;
    for (unsigned int i = 0; i < vect->n; i++)
    {
        double abs_val = fabs(vect->coordinats[i]);
        double pow_val = pow(abs_val, p);
        sum += pow_val;
    }
    double norm_val = pow(sum, 1.0 / p);
    *norm = norm_val;
    return OK;
}

//
enum Errors norm_m() {}

enum Errors main_func(unsigned int p,
                      enum Errors (*norm_inf)(vector *, double *),
                      enum Errors (*norm_p)(vector *, double *, unsigned int),
                      enum Errors (*norm_m)(vector *, double *),
                      int size_1, int size_2, int size_3,
                      double *result_1, double *result_2, double *result_3,
                      vector *vect_1, vector *vect_2, vector *vect_3, ...)
{ // valid dont forget
    if (vect_1 == NULL || vect_2 == NULL || vect_3 == NULL ||
        result_1 == NULL || result_2 == NULL || result_3 == NULL)
    {
        return INVALID_INPUT;
    }
    // malloc for results
    va_list arg;
    va_start(arg, vect_3);

    va_end(arg);

    return OK;
}