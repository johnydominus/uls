#include "libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    int l = 0;
    int r = size - 1;
    int mid = (r + l) / 2;

    if (mx_strcmp(arr[r], s) < 0 || size < 1) {}
    else {
        while (r >= l) {
            (*count)++;
            if(mx_strcmp(arr[mid], s) == 0)
                return mid;
            else if(mx_strcmp(arr[mid], s) > 0) {
                r = mid - 1;
                mid = (r + l) / 2;
            }
            else {
                l = mid + 1;
                mid = (r + l) / 2;
            }
        }
    }
    *count = 0;
    return -1;
}
