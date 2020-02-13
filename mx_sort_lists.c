#include "uls.h"

static bool alpha_sort (void *data1, void *data2, t_flags *flags) {
    struct dirent *d1 = (struct dirent*) data1;
    struct dirent *d2 = (struct dirent*) data2;

    if (!flags->r) {
        if (mx_strcmp(d1->d_name, d2->d_name) > 0)
            return true;
    }
    else {
        if (mx_strcmp(d1->d_name, d2->d_name) < 0)
            return true;
    }
    return false;
}

static void sort_list(t_list *entries, 
                         t_list *stats,
                         t_flags *flags, 
                         bool (*cmp)(void *, void*, t_flags *flags)) {
    t_list *i = NULL;
    t_list *x = NULL;
    t_list *j = NULL;
    t_list *y = NULL;

    if (!entries && !stats && !cmp)
       return;
    for (i = entries, x = stats; i->next; i = i->next, x = x->next) {
        for (j = i->next, y = x->next; j; j = j->next, y = y->next) {
            if (cmp(i->data, j->data, flags)) {
                void *tmp = i->data;
                
                i->data = j->data;
                j->data = tmp;
                tmp = x->data;
                x->data = y->data;
                y->data = x->data;
            }
        }
    }
}

void mx_sort_lists (t_flags *flags, t_list **stats, t_list **entries) {
    if (*entries && *stats)
        sort_list(*entries, *stats, flags, alpha_sort);
}
