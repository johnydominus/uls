#include "uls.h"

static bool alpha_sort (void *data1, void *data2, t_flags *flags) {
    if (TEST) printf(">alpha_sort\n");
    t_file *d1 = (t_file*) data1;
    t_file *d2 = (t_file*) data2;

    if (d1 && d2 && d1->f_name && d2->f_name) {
        if (!flags->r) {
            if (mx_strcmp(d1->f_name, d2->f_name) > 0)
                return true;
        }
        else {
            if (mx_strcmp(d1->f_name, d2->f_name) < 0)
                return true;
        }
    }
    return false;
}

static t_list *sort_list(t_list *files,
                      t_flags *flags,
                      bool (*cmp)(void *, void*, t_flags *flags)) {
    if (TEST) printf(">sort_list\n");
    t_list *iter = files;

    while (iter) {
        printf("!\n");
        t_file *temp = iter->data;
        t_list *i = *(temp->subdir);
        t_list *j = NULL;

        if (!files && !cmp)
            return NULL;
        while (i) {
            j = i->next;
            while (j) {
                if(!i->data)
                    if (TEST) printf("n>o i data\n");
                if(!j->data)
                    if (TEST) printf(">no j data\n");
                if (cmp(i->data, j->data, flags)) {
                    void *tmp = i->data;
                    
                    i->data = j->data;
                    j->data = tmp;
                }
                j = j->next;
            }
            i = i->next;
        }
        iter = iter->next;
    }
    if (TEST) printf(">Sorting done!\n");
    return files;
}

void mx_sort_lists (t_list **files, t_flags *flags) {
    if (TEST) printf(">mx_sort_lists\n");
        *files = sort_list(*files, flags, alpha_sort);
}
