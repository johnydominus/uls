#include "libmx.h"

char *mx_strdup(const char *str) {
    char *new_str = mx_strnew(mx_strlen(str) * sizeof(char));
    mx_strcpy(new_str, (char*)str);
    return new_str;
}
