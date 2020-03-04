#include "uls.h"

void mx_print_name_list(t_list *files, t_flags* flags) {
    for (t_list *cur = files; cur; cur = cur->next) {
        t_file *temp = (t_file*)cur->data; 
            mx_print_filename(temp, flags);
            mx_printstr("\n");
    }
}

void mx_output(t_flags *flags, t_list *files) {
    if (flags->one)
        mx_print_name_list(files, flags);
    else if (flags->C)
        mx_multicol_output(files, flags);
    else if (flags->x)
        mx_multicross_output(files, flags);
    else if (flags->l)
        mx_long_output(files, flags);
}
