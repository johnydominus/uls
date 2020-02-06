#include "libmx.h"

int mx_isspace(char c) {
    if (c == ' '  ||
        c == '\t' ||
        c == '\r' ||
        c == '\n' ||
        c == '\v' ||
        c == '\f')
        return 1;
    else
        return 0;
}
