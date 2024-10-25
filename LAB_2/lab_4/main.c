#include "header.h" 

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Invalid input: uncorrect count of arguments\n");
        return INVALID_INPUT;
    }
    if (is_valid_flag(argv[1]) != OK)
    {
        printf("Invalid input: uncorrect flag\n");
        return INVALID_INPUT;
    }

    switch (argv[1][1])
    {
    case '1':
        int res_1;
        enum Errors err = is_convex_polygon(&res_1, 5, 0.0, 3.0, 1.0, 7.0, 5.0, 8.0, 6.0, 6.0, 3.0, 0.0);
        if (err == INVALID_INPUT)
        {
            printf("Invalid input: not enough vertices\n");
            return INVALID_INPUT;
        }
        if (res_1 == 0)
            printf("Result 1: Not Convex\n");

        else if (res_1 == 1)
            printf("Result 1: Convex\n");
        printf("All done good\n");
        break;

    case '2':
        double res_2;
        enum Errors error = evaluate_polynomial(&res_2, 1.0, 2, 3.0, 2.0, 1.0);
        if (error == INVALID_INPUT)
        {
            printf("Invalid input: uncorrect arg \n");
            return INVALID_INPUT;
        }
        printf("Result 2: %f\n", res_2);
        printf("All done good\n");
        break;
    case '3':
        enum Errors error_3 = find_kaprekar_numbers(10, 7, "0", "2", "45", "67", "99", "257", "297");
        if (error_3 == INVALID_INPUT)
        {
            printf("Invalid input \n");
            return INVALID_INPUT;
        }
        printf("All done good\n");
        break;
    default:
        printf("Flag not found\n");
        break;
    }
    return OK;
}