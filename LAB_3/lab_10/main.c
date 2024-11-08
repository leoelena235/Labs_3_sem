#include "header.h"

int main(int argc, char **argv) {
    enum Errors error = validate_input(argc, argv);
    if (error != OK) {
        printf("error: uncorrect arguments\n");
        return INVALID_INPUT;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        printf("Error opening the file\n");
        return ERROR_OPEN_FILE;
    }

    FILE *output = fopen(argv[2], "w");
    if (!output) {
        fclose(input);
        printf("Error opening the out file\n");
        return ERROR_OPEN_FILE;
    }

    enum Errors err = build_tree(input, output);
    if (err != OK) {
        printf("Invalid memory: memory allocation error \n");
        fclose(input);
        fclose(output);
        return INVALID_MEMORY;
    }

    fclose(input);
    fclose(output);

    printf("All done. The tree in the file\n");
    return 0;
}
