#include "uls.h"

void mx_output(t_flags *flags, t_list **stats, t_list **entries) {
    //t_list *temp_stat = *stats;
    (void)stats;
    t_list *temp_entry = *entries;
    (void)flags;

    while(temp_entry) {
        struct dirent *temp_dirent = temp_entry->data;
        mx_printstr(temp_dirent->d_name);
    }
}
