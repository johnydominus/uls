#include "libmx.h"

int mx_strlen(const char *s) {
    int cntr = 0;

    if(!s)
        return 0;
    while(s[cntr])
        cntr++;
    return cntr;
}
