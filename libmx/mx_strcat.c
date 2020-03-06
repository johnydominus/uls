#include "libmx.h"

char *mx_strcat(char *dst, const char *src) {
    int i,j;

    for (i = 0; dst[i] != '\0'; ++i) {}
    for (j = 0; src[j] != '\0'; ++j)
        dst[i + j] = src[j];
    dst[i + j] = '\0';
    return dst;
}
