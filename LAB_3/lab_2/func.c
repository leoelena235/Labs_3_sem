#include "header.h"
int InitVector(vector *vec, int size)
{
    vec->size = size;
    vec->mass = (double *)calloc(size, sizeof(double)); // выделяет память под массив
    if (vec->mass == NULL)
    {
        return INVALID_MEMORY;
    }
    return OK;
}
int createVector(vector *vec, int size, ...)
{
    if (InitVector(vec, size))
    {
        return INVALID_MEMORY;
    }
    va_list args;
    va_start(args, size);
    for (int i = 0; i < size; i++)
    {
        vec->mass[i] = va_arg(args, double);
    }
    va_end(args);
    return OK;
}

double FirstNorm(vector vec, void *arg)
{
    (void)arg;
    double ans = 0; // хранение тек макс знач
    for (int i = 0; i < vec.size; i++)
    {
        if (fabs(vec.mass[i]) > ans)
        {
            ans = fabs(vec.mass[i]);
        }
    }
    return ans;
}

double SecondNorm(vector vec, void *arg)
{
    // явное приведение
    double p = *(double *)arg;
    double ans = 0; // промежут норма
    for (int i = 0; i < vec.size; i++)
    {
        ans += pow(fabs(vec.mass[i]), p);
    }
    return pow(ans, 1 / p);
}

double ThirdNorm(vector vec, void *arg)
{
    vector *matrix = (vector *)arg;
    int size = vec.size;
    double help[size]; // промеж рез
    double ans = 0;    // рез
    // идем по строкам матрицы
    for (int i = 0; i < size; i++)
    {
        help[i] = 0;
        for (int j = 0; j < size; j++)
        {
            help[i] += matrix[i].mass[j] * vec.mass[j];
        }
    } // скалярное произв итой стр матрицы и вектора
    for (int i = 0; i < size; i++)
    {
        ans += help[i] * vec.mass[i];
    }
    return sqrt(ans);
}

// Сохраняет те векторы, которые имеют максимум по каждой из норм
finaly_ans Task(int n, int count, double eps, double p, vector *matrix, universal FirstNorm,
                universal SecondNorm, universal ThirdNorm, ...)
{
    finaly_ans ans;
    ans.status = OK;
    if (p < 1)
    {
        ans.status = INVALID_INPUT;
        return ans;
    }
    va_list args;
    ans.ans1 = (vector *)calloc(1, sizeof(vector));
    if (ans.ans1 == NULL)
    {
        ans.status = INVALID_MEMORY;
        return ans;
    }
    ans.size1 = 1;
    ans.ans2 = (vector *)calloc(1, sizeof(vector));
    if (ans.ans2 == NULL)
    {
        free(ans.ans1);
        ans.status = INVALID_MEMORY;
        return ans;
    }
    ans.size2 = 1;
    ans.ans3 = (vector *)calloc(1, sizeof(vector));
    if (ans.ans3 == NULL)
    {
        free(ans.ans2);
        free(ans.ans3);
        ans.status = INVALID_MEMORY;
        return ans;
    }
    ans.size3 = 1;
    va_start(args, ThirdNorm);
    vector current;
    vector *tmp;
    for (int i = 0; i < count; i++)
    {
        current = va_arg(args, vector);
        if (current.size != n)
        {
            ans.status = INVALID_INPUT;
            return ans;
        } // если текущ норма превышает  макс найд, то обновл массив
        if (FirstNorm(current, NULL) - FirstNorm(ans.ans1[0], NULL) > eps)
        {
            ans.anses1 = 0;                 // инд макс вект уст в 0
            ans.ans1[ans.anses1] = current; // устанавл новый макс

        } // если равен норме
        else if (fabs(FirstNorm(current, NULL) - FirstNorm(ans.ans1[0], NULL)) <= eps)
        {
            ans.anses1++; // добавл тек вект в конец
            if (ans.anses1 >= ans.size1)
            { // при переполн массива удв размер
                ans.size1 = ans.anses1 * 2;
                tmp = (vector *)realloc(ans.ans1, ans.size1 * sizeof(vector));
                if (tmp == NULL)
                {
                    free(ans.ans2);
                    free(ans.ans3);
                    ans.status = INVALID_MEMORY;
                    return ans;
                }
                ans.ans1 = tmp;
            }
            ans.ans1[ans.anses1] = current; // текущ вект в массив макс векторв добавл
        }

        if (SecondNorm(current, &p) - SecondNorm(ans.ans2[0], &p) > eps)
        {
            ans.anses2 = 0;
            ans.ans2[ans.anses2] = current;
        }
        else if (fabs(SecondNorm(current, &p) - SecondNorm(ans.ans2[0], &p)) <= eps)
        {
            ans.anses2++;
            if (ans.anses2 >= ans.size2)
            {
                ans.size2 = ans.anses2 * 2;
                tmp = (vector *)realloc(ans.ans2, ans.size2 * sizeof(vector));
                if (tmp == NULL)
                {
                    free(ans.ans1);
                    free(ans.ans3);
                    ans.status = INVALID_MEMORY;
                    return ans;
                }
                ans.ans2 = tmp;
            }
            ans.ans2[ans.anses2] = current;
        }

        if (ThirdNorm(current, matrix) - ThirdNorm(ans.ans3[0], matrix) > eps)
        {
            ans.anses3 = 0;
            ans.ans3[ans.anses3] = current;
        }
        else if (fabs(ThirdNorm(current, matrix) - ThirdNorm(ans.ans3[0], matrix)) <= eps)
        {
            ans.anses3++;
            if (ans.anses3 >= ans.size3)
            {
                ans.size3 = ans.anses3 * 2;
                vector *tmp = (vector *)realloc(ans.ans3, ans.size3 * sizeof(vector));
                if (tmp == NULL)
                {
                    free(ans.ans1);
                    free(ans.ans2);
                    ans.status = INVALID_MEMORY;
                    return ans;
                }
                ans.ans3 = tmp;
            }
            ans.ans3[ans.anses3] = current;
        }
    }
    return ans;
}
