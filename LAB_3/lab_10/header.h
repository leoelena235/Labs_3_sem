#ifndef _HEADER_H_
#define _HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

enum Errors {
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OPEN_FILE
};

typedef struct Node {
    char data;
    struct Node *son;
    struct Node *brother;
    struct Node *prev;
} Node;

enum Errors validate_input(int argc, char **argv);
//void init_tree(Node *root);
enum Errors build_tree(FILE *input, FILE *output);
void print_tree(FILE *output, Node *root, int level);
Node* parse_expression(char *expr);
void delete_tree(Node *root);

#endif
