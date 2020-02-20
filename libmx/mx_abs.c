#include "libmx.h"

int mx_abs(int n) {
    if (n == -2147483648)
        return -1;
    else if (n < 0)
        return -n;
    else
        return n;
}
