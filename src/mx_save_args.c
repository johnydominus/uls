#include "uls.h"

char **mx_save_args (int *i, int *margc, int argc, char **argv) {
    printf("mx_save_args\n");
    char **args = NULL;
    *margc = argc - *i;

    if (*margc == 0) {
        args = (char**)malloc(sizeof(char*) * 2);
        args[0] = mx_strdup(".");
        args[1] = NULL;
    }
    else {
        args = (char**)malloc(sizeof(char*) * (*margc + 1));
        for (int j = 0; j <= *margc; ++j) {
            if (j == *margc)
                args[j] = NULL;
            else {
                args[j] = mx_strdup(argv[*i]);
                ++(*i);
            }
        }
    }
    return args;
}
