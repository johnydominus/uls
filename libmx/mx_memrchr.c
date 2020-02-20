#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    const unsigned char *s1 = s;

    for (int i = (int)n; i; --i) {
        if (s1[i] == c)
            return (void*)&s1[i];
    }
    return NULL;
}
