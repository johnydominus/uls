#include "libmx.h"                                                                         

void *mx_memset(void *b, int c, size_t len) {
    unsigned char *s = b;

    for (int i = 0; i < (int)len; ++i)
        s[i] = c;
    return b;
}
