#include "libmx.h"

void mx_del_strarr(char ***arr) {
    char **temp = *arr;
    int i = 0;

    while(temp[i] != NULL)
        mx_strdel(&temp[i++]);
    free(temp);
    *arr = NULL;
}
