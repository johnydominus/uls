#include "uls.h"

void mx_print_list (t_print arguments, t_list *files, t_flags *flags) {
    if (arguments == ALL)
        mx_output(files, flags);
    else if (arguments = DIREC) {
        for (t_list *iter = files; iter; iter = iter->next) {
            t_file *data = iter->data;

            if (MX_ISDIR(data->stat->st_mode)) {
                t_list *subdir = mx_process_dir(data);

                mx_sort_list(subdir, flags);
                mx_print_list(ALL, subdir, flags);
            }
        }
    }
}