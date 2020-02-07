#include "uls.h"

static bool alpha_sort (struct dirent *data1, struct dirent *data2) {
    if (!mx_strcmp(data1->d_name, data2->d_name))
        return true;
    else
        return false;
}

void mx_sort_lists (t_flags *flags, t_list **stats, t_list **entries) {
    (void)flags;
    mx_sort_list(*stats, alpha_sort);
    mx_sort_list(*entries, alpha_sort);
}
