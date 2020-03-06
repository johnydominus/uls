#include "libmx.h"

int mx_strlen_delim (const char *s, char delim) {
    int cntr = 0;

    while (s[cntr] && s[cntr] != delim)
        cntr++;
    return cntr;
}
