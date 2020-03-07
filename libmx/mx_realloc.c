#include "libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    unsigned char *newPtr;

    if (!ptr)
        return malloc(size);
    else if (MALLOC_SIZE(ptr) >= size)
        return ptr;
    else if (size == 0) {
        free(ptr);
        return malloc(MALLOC_SIZE(NULL));
    }
    else {
        newPtr = malloc(size);
        mx_memcpy(newPtr, ptr, MALLOC_SIZE(ptr));
        free(ptr);
    }
    return newPtr;
}
