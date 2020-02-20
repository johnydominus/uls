#include "uls.h"

void mx_output(t_list **files, t_flags *flags) {
    if (TEST) printf(">mx_output\n");
    t_list *current_file = *files;
    static bool first = true;

    while (current_file) {
        t_file *current_data = current_file->data;
        t_list *temp_file = *(current_data->subdir);
        t_file *t_data = temp_file->data;

        if (!first && MX_ISDIR(t_data->m_mode)) {
            mx_printchar('\n');
            if (flags->R) {
                mx_printstr(current_data->path);
                mx_printstr(":\n");
            }
        }
        else
            continue;
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
        current_file = current_file->next;
    }
}
