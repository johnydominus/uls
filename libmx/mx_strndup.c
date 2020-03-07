#include "libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    size_t len = mx_strlen(s1);
    char *new_str = NULL;

    if(n < len)
        len = n;
    new_str = mx_strnew(len * sizeof(char));
    if(!new_str)
        return NULL;
    return mx_strncpy(new_str, s1, len);
}
