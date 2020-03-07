#include "libmx.h"

char *mx_strtrim(const char *str) {
    int st_spaces = 0;
    int end_spaces = mx_strlen(str);

    if(!str)
        return NULL;
    while(mx_isspace(str[st_spaces]))
        ++st_spaces;
    while(mx_isspace(str[end_spaces - 1]))
        --end_spaces;
    return mx_strndup (&str[st_spaces], end_spaces - st_spaces);  
}
