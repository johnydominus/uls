#include "uls.h"

void mx_output(t_flags *flags, 
               t_list **stats, 
               t_list **entries, 
               char **args) {
    //t_list *temp_stat = *stats;
    (void)stats;
    (void)flags;
    t_list *temp_entry = *entries;
    static bool first = true;

    if (!first) {
        mx_printchar('\n');
        if (flags->R) {
            mx_printstr(args[0]);
            mx_printstr(":\n");
        }
    }
    first = false;
    while(temp_entry) {
        struct dirent *temp_dirent = temp_entry->data;
        mx_printstr(temp_dirent->d_name);
        mx_printchar('\n');
        temp_entry = temp_entry->next;
    }
}
