#include "uls.h"

void mx_print_name_list(t_list *files, t_flags* flags) {
    for (t_list *cur = files; cur; cur = cur->next) {
        t_file *temp = (t_file*)cur->data;
            
        mx_print_filename(temp, flags);
        mx_printstr("\n");
    }
}

t_file *mx_create_t_file(void) {
    t_file *file = (t_file*)malloc(sizeof(t_file));

    file->full_path = NULL;
    file->error = false;
    return file;
}

void mx_output(t_flags *flags, t_list *files) {
    if (flags->one
        || (!isatty(1)
        && !flags->forcedc && !flags->l && !flags->x && !flags->m))
        mx_print_name_list(files, flags);
    else if (flags->m)
        mx_m_output(files, flags);
    else if (flags->l)
        mx_print_long_format(files, flags);
    else if (flags->C || flags->x)
        mx_multicol_output(files, flags);
}
