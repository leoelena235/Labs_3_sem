#include "header.h"
int main()
{
    char result[100];
    int count = 0;

    enum Errors error = func_10_to_2_in_pow_r(23, 4, result, &count);
    if (error == INVALID_INPUT)
    {
        printf("Invalid input: incorrect arguments\n");
        return INVALID_INPUT;
    }

    print_num(result, count);

    return 0;
}