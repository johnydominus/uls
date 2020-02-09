#include "uls.h"

static bool alpha_sort (void *data1, void *data2) {
    struct dirent *d1 = (struct dirent*) data1;
    struct dirent *d2 = (struct dirent*) data2;

    if (mx_strcmp(d1->d_name, d2->d_name) > 0)
        return true;
    else
        return false;
}

void mx_sort_lists (t_flags *flags, t_list **stats, t_list **entries) {
    (void)flags;
    (void)stats;
    //mx_sort_list(*stats, alpha_sort);
    mx_sort_list(*entries, alpha_sort);
}
