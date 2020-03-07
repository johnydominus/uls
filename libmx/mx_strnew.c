#include "libmx.h"

char *mx_strnew(const int size) {
    char *result = NULL;

    if (size < 0 || size == 2147483647) {}
    else {
        result = (char*)malloc((size + 1) * sizeof(char));
        for (int i = 0; i < size + 1; i++)
            result[i] = '\0';
    }
    if (!result)
        return NULL;
    else
        return result;
}
