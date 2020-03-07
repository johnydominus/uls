#include "libmx.h"

char *mx_strcpy(char *dst, const char *src) {
    if(dst == NULL) { 
        return dst;
    } 
    else {
        char *ptr = dst;
        while ((*dst++ = *src++) != '\0') {
        }
        return ptr;
    }
}
