#include "header.h"

int main()
{
    int *result;
    int count_val;
    char substr[] = "hello";
    enum Errors error = find_substring(&result, &count_val, substr, 3, "test/test1.txt", "test/test2.txt", "test/test3.txt");

    if (error == INVALID_INPUT)
    {
        printf("Invalid input \n");
        return INVALID_INPUT;
    }
    else if (error == INVALID_MEMORY)
    {
        printf("Bad memory");
        return INVALID_MEMORY;
    }
    else if (error == ERROR_OPEN_FILE)
    {
        printf("File don't open");
        return ERROR_OPEN_FILE;
    }

    for (int i = 0; i < count_val; i++)
    {
        printf("line %i: simbol %i\n", result[i], result[i + 1]);
        i++;
    }

    printf("Result: %i\n", count_val / 2);
    free(result);
    return OK;
}
