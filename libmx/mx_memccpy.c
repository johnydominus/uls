#include "libmx.h"

void *mx_memccpy(void *restrict dst,
                 const void *restrict src,
                 int c,
                 size_t n) {
    unsigned char *d = dst;
    const unsigned char *s = src;

    for (int i = 0; i < (int)n; ++i) {
        d[i] = s[i];
        if(d[i] == c)
            return &d[++i];
    }
    return NULL;
}
