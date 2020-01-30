#include "libmx.h"                                                                         

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    const unsigned char *m1 = s1;
    const unsigned char *m2 = s2;

    while (n--) {
        if (*m1 != *m2)
            return *m1 - *m2;
        ++m1;
        ++m2;
    }
    return 0;
}
