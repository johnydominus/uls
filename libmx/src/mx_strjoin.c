#include "libmx.h"

char *mx_strjoin(const char *s1, const char *s2) {
    if (s1 && s2) {
        char *res = mx_strnew(mx_strlen(s1) + mx_strlen(s2));

        mx_strcpy(res, s1);
        mx_strcat(res, s2);
        if (res)
            return res;
        else
            return NULL;
    }
    else if (s1 && !s2)
        return mx_strdup(s1);
    else if (!s1 && s2)
        return mx_strdup(s2);
    else
        return NULL;
}
