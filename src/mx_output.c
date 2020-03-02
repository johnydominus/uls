#include "uls.h"

void mx_print_name_list(t_list *files) {
    for (t_list *cur = files; cur; cur = cur->next) {
        t_file *temp = (t_file*)cur->data; 
            mx_printstr(temp->d_name);
            mx_printstr("\n");
    }
}

void mx_output(t_flags *flags, t_list *files) {
    // static bool first = true;

    // if (!first) {
        // mx_printchar('\n');
        // if (flags->R) {
            // mx_printstr(args[0]);
            // mx_printstr(":\n");
        // }
    // }
    mx_print_name_list(files);
    // first = false;
    // for (t_list *cur = files; cur; cur = cur->next) {
        // t_file *temp = (t_file*)cur->data; 
        // if (flags->A) {
            // if (!mx_strcmp(temp_dirent->d_name, ".") 
             // || !mx_strcmp(temp_dirent->d_name, "..")) {
                // temp_entry = temp_entry->next;
                // continue;
             // }
        // }
        // if (mx_strlen(file->d_dirent->d_name) > 0) {   //TODO: unprinted characters
            // if (flags->F || flags->p) {
            // if (temp_dirent->d_type == DT_DIR)
                // mx_printchar('/');
            // else if (flags->F && temp_dirent->d_type == DT_LNK)
                // mx_printchar('@');
            // else if (flags->F && temp_dirent->d_type == DT_SOCK)
                // mx_printchar('=');
            // else if (flags->F && temp_dirent->d_type == DT_FIFO)
                // mx_printchar('|');
            // else if (flags->F && temp_st && temp_st->st_mode & S_IXUSR)
                // mx_printchar('*');
            // }
        // }
    // }
}
