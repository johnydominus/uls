#include "libmx.h"

static int final_length(const char *s);

char *mx_del_extra_spaces(const char *str) {
    char *pre = mx_strtrim(str);
    char *res = mx_strnew(final_length(pre));
    char *iter = res;
    int j = 0;

    if (!str)
        return NULL;
    for (int i = 0; i < mx_strlen(pre); ++i) {
        if (mx_isspace(pre[i]) && mx_isspace(pre[i + 1])) {}
        else {
            if (mx_isspace(pre[i]))
                iter[j++] = ' ';
            else 
                iter[j++] = pre[i];
        }
    }
    return res;
}

static int final_length(const char *s) {
    int spaces = 0;
    int len = 0;

    while (*s) {
        if (spaces) {}
        else
            ++len;
        if (mx_isspace(*s))
            ++spaces;
        else
            spaces = 0;
        ++s;
    }
    return len;
}
