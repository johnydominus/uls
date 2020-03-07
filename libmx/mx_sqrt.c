#include "libmx.h"

int mx_sqrt(int x) {
    int div = 1;
    int res = 0;
    int b = x;

    while (x > 0) {
        x -=div;
        div +=2;
        res += x < 0 ? 0 : 1;
    }
    if (res * res == b)
        return res;
    else
        return 0;
}
