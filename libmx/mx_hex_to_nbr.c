#include "libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    unsigned long decimal = 0;
    unsigned long base = 1;
    int len = 0;

    while(hex[len] != '\0')
        len++;
    for (int i = len -1; i >= 0; i--) {
        if (hex[i] > 47 && hex[i] < 58)
            decimal += (hex[i] - '0') * base;
        else if (hex[i] >= 'a' && hex[i] <= 'f')
            decimal += (hex[i] - 'a' + 10) * base;
        else if (hex[i] >= 'A' && hex[i] <= 'F')
            decimal += (hex[i] - 'A' + 10) * base;
        base *= 16;
    }
    return decimal;
}
