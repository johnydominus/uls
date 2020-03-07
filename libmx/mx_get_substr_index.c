#include "libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
    int i = 0;
    int sub_len = mx_strlen(sub);

    if(!sub || !str)
        return -2;
    while(str[i]) {
        if(!mx_strncmp(&str[i], sub, sub_len))
            return i;
        i++;
    }
    return -1;
}
