#include "header.h"

enum Errors input_valid(int argc, char **argv)
{
    if ((argc != 4) || (argv[2][0] != '-' && argv[2][0] != '/') || argv[2][2] == '\0')
    {
        return INVALID_INPUT;
    }
    char full_path_1[BUFSIZ], full_path_2[BUFSIZ];
    if (!realpath(argv[1], full_path_1) || !realpath(argv[3], full_path_2))
        return INVALID_INPUT;
    if (!strcmp(full_path_1, full_path_2))
        return INVALID_INPUT;
    return OK;
}

enum Errors read_from_file(){}