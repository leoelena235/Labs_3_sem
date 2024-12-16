#include "header.h"
typedef double (*universal)(vector, void *);
//Эта функция копирует данные из одного вектора 
//в другой, выделяя память для нового массива координат.
int CopyVector(vector *dst, const vector *src) {
    if (src == NULL || dst == NULL || src->mass == NULL) {
        return INVALID_INPUT;
    }

    // Если вектор назначения уже имеет выделенную память, освобождаем её
    if (dst->mass != NULL) {
        free(dst->mass);
    }

    dst->size = src->size;
    dst->mass = (double *)malloc(src->size * sizeof(double));
    if (dst->mass == NULL) {
        return INVALID_MEMORY;
    }

    // Копируем данные
    for (int i = 0; i < src->size; i++) {
        dst->mass[i] = src->mass[i];
    }

    return OK;
}



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
                universal SecondNorm, universal ThirdNorm, ...) {
    finaly_ans ans;
    ans.status = OK;

    // Проверка параметров
    if (p < 1 || matrix == NULL) {
        ans.status = INVALID_INPUT;
        return ans;
    }

    // Инициализация массивов
    ans.ans1 = (vector *)calloc(1, sizeof(vector));
    ans.ans2 = (vector *)calloc(1, sizeof(vector));
    ans.ans3 = (vector *)calloc(1, sizeof(vector));
    if (ans.ans1 == NULL || ans.ans2 == NULL || ans.ans3 == NULL) {
        free(ans.ans1);
        free(ans.ans2);
        free(ans.ans3);
        ans.status = INVALID_MEMORY;
        return ans;
    }

    ans.size1 = ans.size2 = ans.size3 = 1;
    ans.anses1 = ans.anses2 = ans.anses3 = 0;

    va_list args;
    va_start(args, ThirdNorm);

    for (int i = 0; i < count; i++) {
        vector current = va_arg(args, vector);

        if (current.size != n) {
            va_end(args);
            free(ans.ans1);
            free(ans.ans2);
            free(ans.ans3);
            ans.status = INVALID_INPUT;
            return ans;
        }

        vector *tmp;

        // Норма 1
        if (FirstNorm(current, NULL) - FirstNorm(ans.ans1[0], NULL) > eps) {
            ans.anses1 = 0;
            if (CopyVector(&ans.ans1[ans.anses1], &current) != OK) {
                free(ans.ans1);
                free(ans.ans2);
                free(ans.ans3);
                ans.status = INVALID_MEMORY;
                return ans;
            }
        } else if (fabs(FirstNorm(current, NULL) - FirstNorm(ans.ans1[0], NULL)) <= eps) {
            ans.anses1++;
            if (ans.anses1 >= ans.size1) {
                ans.size1 *= 2;
                tmp = (vector *)realloc(ans.ans1, ans.size1 * sizeof(vector));
                if (tmp == NULL) {
                    free(ans.ans1);
                    free(ans.ans2);
                    free(ans.ans3);
                    ans.status = INVALID_MEMORY;
                    return ans;
                }
                ans.ans1 = tmp;
            }
            CopyVector(&ans.ans1[ans.anses1], &current);
        }

        // Норма 2
        if (SecondNorm(current, &p) - SecondNorm(ans.ans2[0], &p) > eps) {
            ans.anses2 = 0;
            if (CopyVector(&ans.ans2[ans.anses2], &current) != OK) {
                free(ans.ans1);
                free(ans.ans2);
                free(ans.ans3);
                ans.status = INVALID_MEMORY;
                return ans;
            }
        } else if (fabs(SecondNorm(current, &p) - SecondNorm(ans.ans2[0], &p)) <= eps) {
            ans.anses2++;
            if (ans.anses2 >= ans.size2) {
                ans.size2 *= 2;
                tmp = (vector *)realloc(ans.ans2, ans.size2 * sizeof(vector));
                if (tmp == NULL) {
                    free(ans.ans1);
                    free(ans.ans2);
                    free(ans.ans3);
                    ans.status = INVALID_MEMORY;
                    return ans;
                }
                ans.ans2 = tmp;
            }
            CopyVector(&ans.ans2[ans.anses2], &current);
        }

        // Норма 3
        if (ThirdNorm(current, matrix) - ThirdNorm(ans.ans3[0], matrix) > eps) {
            ans.anses3 = 0;
            if (CopyVector(&ans.ans3[ans.anses3], &current) != OK) {
                free(ans.ans1);
                free(ans.ans2);
                free(ans.ans3);
                ans.status = INVALID_MEMORY;
                return ans;
            }
        } else if (fabs(ThirdNorm(current, matrix) - ThirdNorm(ans.ans3[0], matrix)) <= eps) {
            ans.anses3++;
            if (ans.anses3 >= ans.size3) {
                ans.size3 *= 2;
                tmp = (vector *)realloc(ans.ans3, ans.size3 * sizeof(vector));
                if (tmp == NULL) {
                    free(ans.ans1);
                    free(ans.ans2);
                    free(ans.ans3);
                    ans.status = INVALID_MEMORY;
                    return ans;
                }
                ans.ans3 = tmp;
            }
            CopyVector(&ans.ans3[ans.anses3], &current);
        }
    }

    va_end(args);
    return ans;
}
