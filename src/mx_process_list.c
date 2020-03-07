#include "uls.h"

void mx_print_path(t_file *data, t_flags *flags) {
    if (flags->first == true) {
        flags->first = false;
        return;
    }
    mx_printstr("\n");
    if (data->full_path == NULL)
        mx_printstr(data->d_name);
    else
        mx_printstr(data->full_path);
    mx_printstr(":\n");
}

/*
* If we do not have argumetns then in t_file we have only d_name = "." 
*/
void mx_process_list(t_print arguments, t_list *files, t_flags *flags) {
    t_list *subdir = NULL;

    if (arguments == ALL)
        mx_output(flags, files);
    else if (arguments == DIREC) {
        for (t_list *iter = files; iter; iter = iter->next) {
            if (MX_ISDIR(((t_file*)iter->data)->stat.st_mode) ||
                mx_strcmp(((t_file*)iter->data)->d_name, ".") == 0) {
                subdir = mx_process_dir((t_file*)iter->data, flags);
                if(((t_file*)iter->data)->error == true)
                    continue;
                mx_print_path(((t_file*)iter->data), flags);
                mx_process_list(ALL, subdir, flags);
                if (flags->R)
                    mx_process_list(DIREC, subdir, flags);
                if (subdir != NULL)
                    mx_free_list(&subdir);
            }
        }
    }
}
