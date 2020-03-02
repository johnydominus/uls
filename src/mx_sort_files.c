#include "uls.h"

static void time_n_alpha_sort(t_list *files, t_flags *flags) {
    if (flags->t && flags->c && flags->r)
        mx_merge_sort(&files, mx_time_chngd_cmp_rev);
    else if (flags->t && flags->c)
        mx_merge_sort(&files, mx_time_chngd_cmp);
    else if (flags->t && flags->u && flags->r)
        mx_merge_sort(&files, mx_time_access_cmp_rev);
    else if (flags->t && flags->u)
        mx_merge_sort(&files, mx_time_access_cmp);
    else if (flags->t && flags->U && flags->r)
        mx_merge_sort(&files, mx_time_creat_cmp_rev);
    else if (flags->t && flags->U)
        mx_merge_sort(&files, mx_time_creat_cmp);
    else if (flags->t && flags->r)
        mx_merge_sort(&files, mx_time_mod_cmp_rev);
    else if (flags->t)
        mx_merge_sort(&files, mx_time_mod_cmp);
    else if (flags->r)
        mx_merge_sort(&files, mx_alpha_cmp_rev);
    else
        mx_merge_sort(&files, mx_alpha_cmp);
}

void mx_sort_files(t_list *files, t_flags *flags) {
    if (flags->f) {}
    else {
        if (flags->S && flags->r)
            mx_merge_sort(&files, mx_size_cmp_rev);
        else if (flags->S)
            mx_merge_sort(&files, mx_size_cmp);
        else
            time_n_alpha_sort(files, flags);
    }
}

//SORTING FLAGS:
//-S    by size
//-t    by time modified
//-tc   by time status changed
//-tu   by time of last access
//-tU   by time of creation
//-r    reverse sort order
//-f    not sorted

//OVERLAPING:
// c u U

//OVERRIDING:
// S over t
