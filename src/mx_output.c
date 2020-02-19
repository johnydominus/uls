#include "uls.h"

void mx_output(t_flags *flags, t_list **files, char **args) {
    t_list *temp_file = *files;
    static bool first = true;

    if (!first) {
        mx_printchar('\n');
        if (flags->R) {
            mx_printstr(args[0]);
            mx_printstr(":\n");
        }
    }
    first = false;
    while(temp_file) {
        t_file *temp_data = temp_file->data;

        if (flags->A) {
            if (!mx_strcmp(temp_data->f_name, ".") 
             || !mx_strcmp(temp_data->f_name, "..")) {
                temp_file = temp_file->next;
                continue;
             }
        }
        if (mx_strlen(temp_data->f_name) > 0) {     //TODO: unprinted characters
            mx_printstr(temp_data->f_name);
            if (flags->F || flags->p) {
                if (MX_ISDIR(temp_data->m_mode))        //
                    mx_printchar('/');
                else if (MX_ISLNK(temp_data->m_mode))
                    mx_printchar('@');
                else if (MX_ISSOCK(temp_data->m_mode))
                    mx_printchar('=');
                else if (MX_ISFIFO(temp_data->m_mode))
                    mx_printchar('|');
                else if (MX_ISEXEC(temp_data->m_mode))
                    mx_printchar('*');
            }
            mx_printchar('\n');
        }
        temp_file = temp_file->next;
    }
}
