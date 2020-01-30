#include "libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
    unsigned char *d = dst;
    const unsigned char *s = src;

    for (int i = 0; i < (int) n; ++i)
        d[i] = s[i];
    return dst;
}
