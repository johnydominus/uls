#include "libmx.h"

t_list *mx_create_node(void *data) {
    t_list *head_node = malloc(sizeof(t_list));

    head_node->data = data;
    head_node->next = NULL;
    return head_node;
}
