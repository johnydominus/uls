#include "libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    char *buf = (char*)haystack;
    int need_len = mx_strlen(needle);

    if(!needle)
        return (char*)haystack;
    while(*buf) {
        if(!mx_strncmp(buf, needle, need_len))
            return buf;
        ++buf;
    }
    return NULL;    
}
