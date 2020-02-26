#include "uls.h"

static void set_color(mode_t mode) {
    if (MX_ISLNK(mode))
        mx_printstr(ANSI_COLOR_MAGENTA);
    else if (MX_ISSOCK(mode))
        mx_printstr(ANSI_COLOR_GREEN);
    else if (MX_ISEXEC(mode))
        mx_printstr(ANSI_COLOR_RED);
    else if (MX_ISDIR(mode))
        mx_printstr(ANSI_COLOR_BLUE);
}

static void mx_print_filename (t_file *file, t_flags *flags) {
    if (TEST) printf(">print_filename\n");
    if (flags->G)
        set_color(file->m_mode);
    mx_printstr(file->f_name);
    if (flags->F || flags->p) {
        if (MX_ISDIR(file->m_mode))
            mx_printchar('/');
    }
    if (flags->F) {
        if (MX_ISLNK(file->m_mode))
            mx_printchar('@');
        else if (MX_ISSOCK(file->m_mode))
            mx_printchar('=');
        else if (MX_ISFIFO(file->m_mode))
            mx_printchar('|');
        else if (MX_ISEXEC(file->m_mode))
            mx_printchar('*');
    }
    if (flags->G)
        mx_printstr(ANSI_COLOR_RESET);
}

void mx_output(t_list **files, t_flags *flags, char *path) {
    if (TEST) printf(">mx_output\n");
    t_list *current_file = *files;
    
    if (!flags->first) {
        mx_printchar('\n');
        mx_printstr(path);
        mx_printstr(":\n");
    }
    flags->first = false;
    while (current_file) {
        t_file *current_data = current_file->data;
        t_list *temp_file = *(current_data->subdir);

        static int i = 0;
        if (TEST) printf("%d %s\n", i++, current_data->f_name);

        while (temp_file) {
            t_file *temp_data = temp_file->data;
            if (flags->A) {
                if (!mx_strcmp(temp_data->f_name, ".")
                    || !mx_strcmp(temp_data->f_name, "..")) {
                    temp_file = temp_file->next;
                    continue;
                }
            }
            if (mx_strlen(temp_data->f_name) > 0) {
                mx_print_filename(temp_data, flags);
                mx_printchar('\n');
            }
            temp_file = temp_file->next;
        }
        current_file = current_file->next;
    }
}
