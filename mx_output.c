#include "uls.h"

void mx_output(t_flags *flags, 
               t_list **stats, 
               t_list **entries, 
               char **args) {
    (void)stats;
    (void)flags;
    t_list *temp_entry = *entries;
    t_list *temp_stat = *stats;
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
        struct stat *temp_st = temp_stat->data;

        if (flags->A) {
            if (!mx_strcmp(temp_dirent->d_name, ".") 
             || !mx_strcmp(temp_dirent->d_name, "..")) {
                temp_entry = temp_entry->next;
                continue;
             }
        }
        if (mx_strlen(temp_dirent->d_name) > 0) {   //TODO: unprinted characters
            mx_printstr(temp_dirent->d_name);
            if (flags->F || flags->p) {
            if (temp_dirent->d_type == DT_DIR)
                mx_printchar('/');
            else if (flags->F && temp_dirent->d_type == DT_LNK)
                mx_printchar('@');
            else if (flags->F && temp_dirent->d_type == DT_SOCK)
                mx_printchar('=');
            else if (flags->F && temp_dirent->d_type == DT_FIFO)
                mx_printchar('|');
            else if (flags->F && temp_st && temp_st->st_mode & S_IXUSR)
                mx_printchar('*');
            }
            mx_printchar('\n');
        }
        temp_entry = temp_entry->next;
        temp_stat = temp_stat->next;
    }
}
