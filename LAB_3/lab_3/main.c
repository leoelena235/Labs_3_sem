#include "header.h"

int main(int argc, char *argv[])
{
    enum Errors error = input_valid(argc, argv);
    if (error != OK)
    {
        printf("Invalid input: incorrect number of arguments or invalid arguments\n");
        return INVALID_INPUT;
    }

    FILE *in = fopen(argv[1], "r");
    if (!in)
    {
        printf("Error opening input file\n");
        return ERROR_OPEN_FILE;
    }

    FILE *out = fopen(argv[3], "w");
    if (!out)
    {
        fclose(in);
        printf("Error opening output file\n");
        return ERROR_OPEN_FILE;
    }

    Employee *input_array = (Employee*)malloc(2 * sizeof(Employee));
    if (!input_array)
    {
        fclose(in);
        fclose(out);
        printf("Memory allocation error\n");
        return INVALID_MEMORY;
    }

    int size = 0, capacity = 2;
    if (read_from_file(in, &input_array, &size, &capacity) != OK)
    {
        printf("Error reading data\n");
        free(input_array);
        fclose(in);
        fclose(out);
        return INVALID_MEMORY;
    }

    fclose(in);

    switch (argv[2][1])
    {
    case 'a': // по возрастанию
        qsort(input_array, size, sizeof(Employee), compare_a);
        break;
    case 'd': // по убыванию
        qsort(input_array, size, sizeof(Employee), compare_d);
        break;
    default:
        printf("Invalid sorting flag\n");
        free(input_array);
        fclose(out);
        return INVALID_INPUT;
    }

    for (int i = 0; i < size; i++)
    {
        fprintf(out, "%d %s %s %.2f\n", input_array[i].id, input_array[i].name, input_array[i].surname, input_array[i].salary);
    }

    free(input_array);
    fclose(out);

    return OK;
}
