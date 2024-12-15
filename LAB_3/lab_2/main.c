#include "header.h"

int main()
{
    vector vec;
    vector first;
    vector second;
    if (createVector(&vec, 2, 1.2, 1.3))
    {
        printf("memory trouble");
        return INVALID_MEMORY;
    }
    if (createVector(&first, 2, 1.5, 0.1))
    {
        free(vec.mass);
        printf("memory trouble");
        return INVALID_MEMORY;
    }
    if (createVector(&second, 2, 0.1, 1.5))
    {
        free(vec.mass);
        free(first.mass);
        printf("memory trouble");
        return INVALID_MEMORY;
    }
    int size = vec.size;
    vector *matrix = (vector *)malloc(sizeof(vector) * size);
    if (matrix == NULL)
    {
        free(vec.mass);
        free(first.mass);
        free(second.mass);
        printf("memory trouble");
        return INVALID_MEMORY;
    }
    for (int i = 0; i < size; i++)
    {
        matrix[i].mass = (double *)calloc(size, sizeof(double));
        if (matrix[i].mass == NULL)
        {
            for (int j = i - 1; j >= 0; j--)
            {
                free(matrix[j].mass);
            }
            free(matrix);
            free(vec.mass);
            free(first.mass);
            free(second.mass);
            printf("memory trouble");
            return INVALID_MEMORY;
        }
        matrix[i].mass[i] = 1.0; // 2 на 2 единичн матрица
    }

    finaly_ans ans; // размерномть,кол-ов векторов,эпсилон,р
    ans = Task(2, 3, 0.0001, 1.0, matrix, FirstNorm, SecondNorm, ThirdNorm, vec, first, second);
    switch (ans.status)
    {
    case OK:
        printf("Norm 1 %d:\n", ans.anses1 + 1);
        for (int i = 0; i <= ans.anses1; i++)
        {
            for (int j = 0; j < size; j++)
            {
                printf("%f ", ans.ans1[i].mass[j]);
            }
            printf("\n");
        }
        printf("Norm 2 %d:\n", ans.anses2 + 1);
        for (int i = 0; i <= ans.anses2; i++)
        {
            for (int j = 0; j < size; j++)
            {
                printf("%f ", ans.ans2[i].mass[j]);
            }
            printf("\n");
        }
        printf("Norm 3 %d:\n", ans.anses3 + 1);
        for (int i = 0; i <= ans.anses3; i++)
        {
            for (int j = 0; j < size; j++)
            {
                printf("%f ", ans.ans3[i].mass[j]);
            }
            printf("\n");
        }
        break;
    case INVALID_INPUT:
        printf("incorrect arguments");
        break;
    case INVALID_MEMORY:
        free(matrix);
        free(vec.mass);
        free(first.mass);
        free(second.mass);
        printf("memory trouble");
        return INVALID_MEMORY;
    }
    for (int i = 0; i < size; i++)
    {
        free(matrix[i].mass);
    }
    free(matrix);
    free(vec.mass);
    free(first.mass);
    free(second.mass);
    free(ans.ans1);
    free(ans.ans2);
    free(ans.ans3);
    return ans.status;
}
