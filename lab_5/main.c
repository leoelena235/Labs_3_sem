#include "header.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Uncorrect count of arguments");
        return INVALID_INPUT;
    }

    FILE *in = fopen(argv[1], "r");
    if (in == NULL)
    {
        printf("Error opening file \n");
        return ERROR_OPEN_FILE;
    }

    Student *input_array = NULL;
    int size = 0, capacity = 2;
    if (read_from_file(in, &input_array, &size, &capacity) != OK)
    {
        printf("Error reading from file\n");
        fclose(in);
        free(input_array);
        return INVALID_INPUT;
    }

    fclose(in);

    