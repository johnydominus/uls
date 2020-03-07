#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {
    const unsigned char *b = big;
    const unsigned char *l = little;

    if (big_len < little_len || little_len == 0 || big_len == 0)
        return NULL;
    for(int i = 0; i <= (int)(big_len - little_len); ++i) {
        if(!mx_memcmp(&b[i], l, little_len))
            return (void*)&b[i];
    }
    return NULL;
}
