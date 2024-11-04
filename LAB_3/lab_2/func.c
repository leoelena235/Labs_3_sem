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
enum Errors vector_kill(vector *vect)
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

void print_vect(vector *vect)
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
    for ( int i = 0; i < vect->n; i++)
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
        printf("Uncorrect p\n");
        return INVALID_INPUT;
    }
    double sum = 0.0;
    for ( int i = 0; i < vect->n; i++)
    {
        double abs_val = fabs(vect->coordinats[i]);
        double pow_val = pow(abs_val, p);
        sum += pow_val;
    }
    double norm_val = pow(sum, 1.0 / p);
    *norm = norm_val;
    return OK;
}

enum Errors matrix_multipl(double **A, double *x, double **result, int n)
{
    *result = (double *)malloc(sizeof(double) * n);
    if (*result == NULL)
    {
        return INVALID_MEMORY;
    }

    for (int i = 0; i < n; i++)
    {
        (*result)[i] = 0.0;
        for (int j = 0; j < n; j++)
        {
            (*result)[i] += A[i][j] * x[j];
        }
    }

    return OK;
}

//
enum Errors norm_m(vector *vect, double *norm)
{
    if (vect == NULL || vect->coordinats == NULL || norm == NULL)
    {
        return INVALID_MEMORY;
    }

    int n = vect->n;
    double **A = NULL;
    double *result = NULL;
    int i, j;

    // Выделение памяти для матрицы A
    A = (double **)malloc(sizeof(double *) * n);
    if (A == NULL)
    {
        return INVALID_MEMORY;
    }

    for (i = 0; i < n; i++)
    {
        A[i] = (double *)malloc(sizeof(double) * n);
        if (A[i] == NULL)
        {
            for (j = 0; j < i; j++)
            {
                free(A[j]);
            }
            free(A);
            return INVALID_MEMORY;
        }
        // Единичная матрица - положительно определенная
        for (j = 0; j < n; ++j)
        {
            if (i == j)
            {
                A[i][j] = 1;
            }
            else
            {
                A[i][j] = 0;
            }
        }
    }

    // Умножение матрицы A на вектор vect->elems
    if (matrix_multipl(A, vect->coordinats, &result, n) == INVALID_MEMORY)
    {
        for (i = 0; i < n; ++i)
        {
            free(A[i]);
        }
        free(A);
        return INVALID_MEMORY;
    }

    // Вычисление нормы вектора
    *norm = 0;
    for (i = 0; i < n; ++i)
    {
        *norm += result[i] * vect->coordinats[i];
    }

    // Освобождение памяти
    for (i = 0; i < n; ++i)
    {
        free(A[i]);
    }
    free(A);
    free(result);

    // Вычисление квадратного корня из нормы
    *norm = sqrt(*norm);
    return OK;
}

enum Errors main_func(unsigned int p,
                      enum Errors (*norm_inf)(vector *, double *),
                      enum Errors (*norm_p)(vector *, double *, unsigned int),
                      enum Errors (*norm_m)(vector *, double *),
                      int *size_1, int *size_2, int *size_3,
                      vector** result_1, vector** result_2, vector** result_3, ...)
{ // valid dont forget
    if (size_1 == NULL || size_2 == NULL || size_3 == NULL ||
        result_1 == NULL || result_2 == NULL || result_3 == NULL)
    {
        return INVALID_INPUT;
    }
    // malloc for results
    // тут надо выделить память для результата, не забывая
    // про освобождение памяти
    // size_1 = 0;
    // size_2 = 0;
    // size_3 = 0;

    // Выделение памяти для результатов
    int quantity = 3; // Количество переданных векторов
    (*result_1) = (vector *)malloc(sizeof(vector) * quantity);
    if (*result_1 == NULL)
    {
        return INVALID_MEMORY;
    }
    (*result_2) = (vector *)malloc(sizeof(vector) * quantity);
    if (*result_2 == NULL)
    {
        free(*result_1);
        return INVALID_MEMORY;
    }
    (*result_3) = (vector *)malloc(sizeof(vector) * quantity);
    if (*result_3 == NULL)
    {
        free(*result_1);
        free(*result_2);
        return INVALID_MEMORY;
    }

    va_list ptr;
    va_start(ptr, result_3);

    int ind_1 = 0, ind_2 = 0, ind_3 = 0;
    double max_1 = 0, max_2 = 0, max_3 = 0, cur_1, cur_2, cur_3;
    for (int i = 0; i < quantity; i++)
    {
        vector *vec = va_arg(ptr, vector *);

        norm_inf(vec, &cur_1);
        if (fabs(cur_1 - max_1) < Eps)
        {
            ind_1++;
            (*result_1)[ind_1] = *vec;
        }
        else if (cur_1 - max_1 > Eps)
        {
            max_1 = cur_1;
            ind_1 = 0;
            (*result_1)[0] = *vec;
        }

        if (norm_p(vec, &cur_2, p) == INVALID_INPUT)
        {
            free(*result_1);
            free(*result_2);
            free(*result_3);
            return INVALID_INPUT;
        }

        if (fabs(cur_2 - max_2) < Eps)
        {
            ind_2++;
            (*result_2)[ind_2] = *vec;
        }
        else if (cur_2 - max_2 > Eps)
        {
            max_2 = cur_2;
            ind_2 = 0;
            (*result_2)[0] = *vec;
        }

        if (norm_m(vec, &cur_3) == INVALID_MEMORY)
        {
            free(*result_1);
            free(*result_2);
            free(*result_3);
            return INVALID_MEMORY;
        }

        if (fabs(cur_3 - max_3) < Eps)
        {
            ind_3++;
            (*result_3)[ind_3] = *vec;
        }
        else if (cur_3 - max_3 > Eps)
        {
            max_3 = cur_3;
            ind_3 = 0;
            (*result_3)[0] = *vec;
        }
    }

    va_end(ptr);

    *size_1 = ind_1 + 1;
    *size_2 = ind_2 + 1;
    *size_3 = ind_3 + 1;

    return OK;
}