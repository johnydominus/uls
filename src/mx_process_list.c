#include "uls.h"

static void print_path(char *path, t_flags *flags) {
    if(flags->first == false)
        mx_printstr("\n");
    else
        flags->first = false;
    mx_printstr(path);
    mx_printstr(":\n");
}

void mx_process_list(t_print arguments, t_list *files, t_flags *flags) {
    t_list *subdir = NULL;

    if (arguments == ALL) {
        mx_sort_files(files, flags);
        mx_output(flags, files);
    }
    else if (arguments == DIREC) {
        for (t_list *iter = files; iter; iter = iter->next) {
            t_file *data = iter->data;

            if (MX_ISDIR(data->stat.st_mode) || mx_strcmp(data->d_name, ".") == 0) { 
// If we do not have argumetns then in t_file we have only d_name = "." 
                t_list *subdir = mx_process_dir(data, flags);
                mx_sort_files(subdir, flags);
                mx_process_list(ALL, subdir, flags);
                print_path(data->full_path, flags); // It does not work now
                if (flags->R)
                    mx_process_list(DIREC, subdir, flags);
            }
        }
    }
    if (subdir != NULL) {
        mx_free_list(&subdir);
    }
}
