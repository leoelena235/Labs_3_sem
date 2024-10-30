#include "header.h"
int sum(int num1, int num2)
{
    int res = 0;
    int carry = 0;
    res = num1 ^ num2;
    carry = (num1 & num2) << 1;
    if (carry == 0)
    {
        return res;
    }

    return sum(carry, res);
}

int negative(int num)
{
    return sum(~num, 1);
}

enum Errors func_10_to_2_in_pow_r(long int number, int r, char *result, int *count)
{
    if (!result)
    {
        return INVALID_INPUT;
    }
    if (r < 1 || r > 5)
    {
        return INVALID_INPUT;
    }
    int mask;
    int val;
    char all_symb[] = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
    int flag_negat = 0;
    if (number < 0)
    {
        number = negative(number);
        flag_negat = 1; 
    }
    while (number > 0)
    {
        mask = sum(1 << r, -1);
        val = number & mask;
        number >>= r;
        result[*count] = all_symb[val];
        *count = sum(*count, 1);
    };
    if (flag_negat)
    {
        result[*count] = '-';
        *count = sum(*count, 1);
    }
    return OK;
}

void print_num(char *result, int count)
{
    printf("Result: ");
    for (int i = sum(count, -1); i >= 0; i = sum(i, -1))
    {
        printf("%c", result[i]);
    }
    printf("\n");
}