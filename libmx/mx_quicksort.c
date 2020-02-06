#include "libmx.h"

static void swap(char **a, char **b);
static int partition(char **arr, int low, int high, int *swap_cnt);

int mx_quicksort(char **arr, int left, int right) {
    int swap_cnt = 0;
    int pi;

    if(!arr)
        return -1;
    if (left < right) {
        pi = partition(arr, left, right, &swap_cnt);
        mx_quicksort(arr, left, pi - 1);
        mx_quicksort(arr, pi + 1, right);
    }
    return swap_cnt;
}

static void swap(char **a, char **b) {
    char *buf = *a;
    *a = *b;
    *b = buf;
}

static int partition(char **arr, int low, int high, int *swap_cnt) {
    char *pivot = arr[high - ((high - low) / 2)];
    int i = low;

    for (int j = low +1; j <= high; j++) {
        if (mx_strcmp(arr[j], pivot) < 0) {
            i++;
            swap(&arr[i], &arr[j]);
            *(swap_cnt) += 1;
        }
    }
    swap(&arr[i + 1], &arr[high]);
    *(swap_cnt) += 1;

    return (i + 1);
}
