#include "header.h"

int main()
{
    enum Errors error = sum_of_numbers(10, 3, "123", "456", "789");
    if (error == INVALID_INPUT)
    {
        printf("Invalid input\n");
        return INVALID_INPUT;
    }
    else if (error == INVALID_INPUT)
    {
        printf("Invalid memory\n");
        return INVALID_INPUT;
    }

    return 0;
}