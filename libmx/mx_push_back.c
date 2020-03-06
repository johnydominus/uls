#include "libmx.h"

void mx_push_back(t_list **list, void *data) {
    t_list *buf = NULL;

    if(list == NULL)
        return;
    if(*list == NULL) {
        *list = mx_create_node(data);
        return;
    }
    else {
        buf = *list;
        while (buf->next)
            buf = buf->next;
        buf->next = mx_create_node(data);
    }
}
