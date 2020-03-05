#include "uls.h"

void mx_free_list(t_list **files) {
    t_list *temp_files = *files;

    while (temp_files) {
        t_list *temp = temp_files;

        temp_files = temp_files->next;
        free(((t_file*)temp->data)->full_path);
        free(temp->data);
        free(temp);
    }
}
