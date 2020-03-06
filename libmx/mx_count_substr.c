#include "libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    int i = 0;
    int sub_len = mx_strlen(sub);
    int cntr = 0;

    if (!sub || !str)
        return -1;
    while (str[i]) {
        if (!mx_strncmp(&str[i], sub, sub_len))
            ++cntr;
        ++i;
    }
    return cntr;
}
