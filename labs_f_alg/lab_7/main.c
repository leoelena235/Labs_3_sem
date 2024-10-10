#include "header.h"

int main(int argc, char *argv[])
{
    int flag;

    if (input_fl_err(argc, argv, &flag) != OK)
    {
        printf("Ошибка: некорректный ввод");
        return INVALID_INPUT;
    }

    switch (argv[1][1])
    {
    case 'r':
        if (argc != 5)
        {
            printf("Ошибка ввода\n");
            return INVALID_INPUT;
        }
        enum Errors error = files_func_1(argv[2], argv[3], argv[4]);
        if (error != OK)
        {
            printf("Ошибка при работе с файлами\n");
            break;
        }
        else
        {
            printf("Результат записан в файл\n");
        }
        break;
    case 'a':
            if (argc != 4)
        {
            printf("Ошибка ввода\n");
            return INVALID_INPUT;
        }
        enum Errors err = files_func_2(argv[2], argv[3]);
        if (err!= OK){
            printf("Ошибка при работе с файлами\n");
            break;
        }
        else{
            printf("Запись в файл сделана\n");
        }
        break;

    default:
        printf("Ошибка: такого флага нет в доступных флагах: %s\n", argv[1]);
        break;
    }

    return 0;
}