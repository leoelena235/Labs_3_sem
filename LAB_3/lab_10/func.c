#include "header.h"

enum Errors validate_input(int argc, char **argv)
{
    if (argc != 3)
    {
        return INVALID_INPUT;
    }
    if (strcmp(argv[1], argv[2]) == 0)
    {
        return INVALID_INPUT;
    }
    return OK;
}

// void init_tree(Node *root)
// {
//     root->brother = NULL;
//     root->prev = NULL;
//     root->son = NULL;
// }

enum Errors build_tree(FILE *input, FILE *output)
{
    if (!input || !output)
    {
        return INVALID_INPUT;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), input))
    {
        buffer[strcspn(buffer, "\n")] = 0;

        Node *root = parse_expression(buffer);
        if (!root)
        {
            return INVALID_MEMORY;
        }

        print_tree(output, root, 0);
        if (fprintf(output, "\n") < 0)//check
        {
            delete_tree(root);
            return INVALID_INPUT;
        }

        delete_tree(root);
    }
    return OK;
}

Node *parse_expression(char *expr)
{
    Node *root = NULL;
    Node *current = NULL;

    while (*expr)
    {
        if (*expr == '(')
        {
            if (!current)
                return NULL;

            Node *new_node = (Node *)malloc(sizeof(Node));
            if (!new_node)
                return NULL;

            new_node->data = '\0';
            new_node->son = NULL;
            new_node->brother = NULL;
            new_node->prev = current;
            current->son = new_node;
            current = new_node;
        }
        else if (*expr == ')')
        {
            if (!current)
                return NULL;
            current = current->prev;
        }
        else if (*expr == ',')
        {
            if (!current || !current->prev)
                return NULL;

            Node *new_node = (Node *)malloc(sizeof(Node));
            if (!new_node)
                return NULL;

            new_node->data = '\0';
            new_node->son = NULL;
            new_node->brother = NULL;
            new_node->prev = current->prev;
            current->brother = new_node;
            current = new_node;
        }
        else if (isalpha(*expr))
        {
            if (!root)
            {
                root = (Node *)malloc(sizeof(Node));
                if (!root)
                    return NULL;

                root->data = *expr;
                root->son = NULL;
                root->brother = NULL;
                root->prev = NULL;
                current = root;
            }
            else
            {
                current->data = *expr;
            }
        }
        expr++;
    }
    return root;
}

void print_tree(FILE *output, Node *root, int level)
{
    if (!root)
        return;

    for (int i = 0; i < level; i++)
    {
        fprintf(output, "│   ");
    }

    if (root->brother)
    {
        fprintf(output, "├── ");
    }
    else
    {
        fprintf(output, "└── ");
    }

    if (root->data)
    {
        fprintf(output, "%c\n", root->data);
    }

    print_tree(output, root->son, level + 1);
    print_tree(output, root->brother, level);
}

void delete_tree(Node *root)
{
    if (!root)
        return;
    delete_tree(root->son);
    delete_tree(root->brother);
    free(root);
}
