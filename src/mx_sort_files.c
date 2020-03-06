#include "uls.h"

void mx_sort_files(t_list *files, t_flags *flags) {
    if (flags->f) {}
    else {
        mx_sort_lists(files, mx_alpha_cmp, flags);
        if (flags->S)
            mx_sort_lists(files, mx_size_cmp, flags);
        else if (flags->t && flags->c)
            mx_sort_lists(files, mx_time_chngd_cmp, flags);
        else if (flags->t && flags->u)
            mx_sort_lists(files, mx_time_access_cmp, flags);
        else if (flags->t && flags->U)
            mx_sort_lists(files, mx_time_creat_cmp, flags);
        else if (flags->t)
            mx_sort_lists(files, mx_time_mod_cmp, flags);
        else
            mx_sort_lists(files, mx_alpha_cmp, flags);
    }
}
