#include "libmx.h"

void mx_pop_back(t_list **head) {
    if(head == NULL || *head == NULL)
        return;
    if((*head)->next == NULL) {
        free(*head);
        *head = NULL;
    }
    else {
        t_list *buf = *head;
        while (buf->next->next)
            buf = buf->next;
        free(buf->next);
        buf->next = NULL;
    }
}
