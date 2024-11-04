#include "header.h"

int main(int argc, char *argv[])
{
    enum Errors error = input_valid(argc, argv);
    if (error != OK)
    {
        printf("Invalid input: uncorrect count of aguments or uncorrect arguments\n");
        return INVALID_INPUT;
    }

    FILE *in = fopen(argv[2], "r");
    if (!in)
    {
        fclose(in);
        printf("Error opening file");
        return ERROR_OPEN_FILE;
    }
    FILE *out = fopen(argv[3], "w");
    if (!out)
    {
        flose(out);
        printf("Error opening file");
        return ERROR_OPEN_FILE;
    }
    // x3
    Employee *input_array = NULL;
    int size = 0, capacity_array = 2;

    switch (argv[1][2])
    {
    case 'a':
        if (read_from_file(in, &input_array, &size, &capacity_array) != OK)
        {

            printf("error work");
            fclode(in);
            fclose(out);
            free(input_array);
            return INVALID_INPUT;
        }
       if else
        {    qsort(data, size_data, sizeof(Employee), compare_a);
            for (int i = 0; i < capacity_array; i++)
            {
                fprintf(output, "%u %s %s %lf\n", data[i].id, data[i].name, data[i].surname, data[i].salary);
            }
        }
        break;
    case 'd':
        break;

    default:
        printf("Error \n");
        break;
    }
}
fclose(in);
fclose(out);

return 0;
}
