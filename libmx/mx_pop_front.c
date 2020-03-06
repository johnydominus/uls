#include "libmx.h"

void mx_pop_front(t_list **head) {
    t_list *buf = (*head)->next;

    if(head == NULL || *head == NULL)
        return;
    free(*head);
    *head = buf;
}
