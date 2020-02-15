#include "libmx.h"

char *mx_strncpy(char *dst, const char *src, int len) {
    if(dst == NULL)
        return dst;
    else {
        int i = 0;

        while(i < len && src[i]) {
            dst[i] = src[i];
            ++i;
        }
        while(i < len)
            dst[i++] = '\0';
        return dst;
    }
}
