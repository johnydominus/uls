#include "libmx.h"

int mx_list_size(t_list *list) {
    t_list *temp = list;
    int cntr = 0;

    if (list == NULL)
        return cntr;
    while (temp->next) {
        ++cntr;
        temp = temp->next;
    }
    return ++cntr;
}
