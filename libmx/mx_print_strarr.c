#include "libmx.h"

void mx_print_strarr(char **arr, const char *delim) {
    if(arr == NULL || delim == NULL) {}
    else {
        int i = 0;

        while(arr[i]) {
            if(i > 0)
                mx_printstr(delim);
            mx_printstr(arr[i++]);
        }
        mx_printstr("\n");
    }
}
