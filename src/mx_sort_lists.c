#include "uls.h"

static bool alpha_sort (void *data1, void *data2, t_flags *flags) {
    printf("alpha_sort\n");
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
    printf("sort_list\n");
    t_list *i = files;
    t_list *j;

    if (!files && !cmp)
       return NULL;
    while (i) {
        j = i->next;
        while (j) {
            if (cmp(i->data, j->data, flags)) {
                if(!i->data)
                    printf("no i data\n");
                if(!j->data)
                    printf("no j data\n");
                void *tmp = i->data;
                
                i->data = j->data;
                j->data = tmp;
            }
            j = j->next;
        }
        i = i->next;
    }
/*    for (t_list *i = files; i->next; i = i->next) {
        for (t_list *j = i->next; j; j = j->next) {
            if (!i && !j)
                break;
            if (cmp(i->data, j->data, flags)) {
                void *tmp = i->data;
                
                i->data = j->data;
                j->data = tmp;
            }
        }
    }
    */
    printf("Sorting done!\n");
    return files;
}

void mx_sort_lists (t_flags *flags, t_list **files) {
    printf("mx_sort_lists\n");
    if (*files)
        *files = sort_list(*files, flags, alpha_sort);
}
