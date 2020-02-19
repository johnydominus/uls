#include "uls.h"

static bool alpha_sort (void *data1, void *data2, t_flags *flags) {
    t_file *d1 = (t_file*) data1;
    t_file *d2 = (t_file*) data2;

    if (!flags->r) {
        if (mx_strcmp(d1->f_name, d2->f_name) > 0)
            return true;
    }
    else {
        if (mx_strcmp(d1->f_name, d2->f_name) < 0)
            return true;
    }
    return false;
}

static t_list *sort_list(t_list *files,
                      t_flags *flags, 
                      bool (*cmp)(void *, void*, t_flags *flags)) {
    if (!files && !cmp)
       return NULL;
    for (t_list *i = files; i->next; i = i->next) {
        for (t_list *j = i->next; j; j = j->next) {
            if (cmp(i->data, j->data, flags)) {
                void *tmp = i->data;
                
                i->data = j->data;
                j->data = tmp;
            }
        }
    }
    return files;
}

void mx_sort_lists (t_flags *flags, t_list **files) {
    if (*files)
        *files = sort_list(*files, flags, alpha_sort);
}
