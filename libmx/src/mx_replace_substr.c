#include "libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    int diff = mx_strlen(replace) - mx_strlen(sub);
    char *res = mx_strnew(mx_strlen(str) + (diff * mx_count_substr(str, sub)));
    int i = 0;
    int j = 0;

    if(!str || !sub || !replace)
        return NULL;
    while(str[i]) {
        if(mx_strncmp(&str[i], sub, mx_strlen(sub)) == 0) {
            mx_strncpy(&res[j], replace, mx_strlen(replace));
            i += mx_strlen(sub);
            j += mx_strlen(replace);
        }
        else
            res[j++] = str[i++];
    }
    res[j] = '\0';
    return res;
}
