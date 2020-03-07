#include "uls.h"

void mx_print_name_list(t_list *files) {
    for (t_list *cur = files; cur; cur = cur->next) {
        t_file *temp = (t_file*)cur->data; 
        mx_printstr(temp->d_name);
        mx_printstr("\n");
    }
}


// bool is_raplace(char c) {
    // if (c < 32 && c > 0)
        // return true;
    // else
        // return false;
// }

// void replase_wspace_char(t_list *files) {
    // for (t_list *cur = files; cur; cur = cur->next) {
        // t_file *file = (t_file*)cur->data;

        // for (int i = 0; file->d_name[i] != '\0' || i < 256; i++) {
            // if (is_raplace(file->d_name[i]) == true) {
                // file->d_name[i] = '?';
            // }
        // }
    // }
// }

void mx_output(t_flags *flags, t_list *files) {
    // replase_wspace_char(files);
    if (flags->l == true)
        mx_print_long_format(files, flags);
    else
        mx_print_name_list(files);
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
