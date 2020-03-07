#include "libmx.h"

double mx_pow(double n, unsigned int pow) {
    double temp;

    if(pow == 0)
        return 1;
    temp = mx_pow(n, pow / 2);
    if(pow % 2 == 0)
        return temp * temp;
    else
        return n * temp * temp;
}
