#include "libmx.h"

char *mx_strdup_delim(const char *s1, char n) {
    size_t len = mx_strlen_delim(s1, n);
    char *new_str = mx_strnew(len * sizeof(char));

    if(!new_str)
        return NULL;
    return mx_strncpy(new_str, s1, len);
}
