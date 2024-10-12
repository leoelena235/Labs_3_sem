#include "header.h"

int main(int argc, char **argv) { 
    if (argc >= 2){
        double eps;
        switch(convert_str_to_double(argv[1], &eps))
        {
        case INVALID_INPUT:
            printf("INVALID_INPUT");
            return INVALID_INPUT;
        case INVALID_MEMORY:
            printf("INVALID_MEMORY");
            return INVALID_MEMORY;
        default:
            break;
        } 

    }
}