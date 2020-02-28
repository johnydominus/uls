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
    if (arguments == ALL)
        mx_output(files, flags);
    else if (arguments = DIREC) {
        for (t_list *iter = files; iter; iter = iter->next) {
            t_file *data = iter->data;

            if (MX_ISDIR(data->stat->st_mode)) {
                t_list *subdir = mx_process_dir(data);

                mx_sort_list(subdir, flags);
                mx_process_list(ALL, subdir, flags);
                print_path(data->full_path);
                if (flags->R)
                    mx_process_list(DIREC, subdir, flags);
            }
        }
    }
}
