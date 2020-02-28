#include "uls.h"

int main (int argc, char **argv) {
    t_list *files = NULL;
    t_list *dirs = NULL;
    t_flags *flags = mx_args_to_list(argc, argv, files, dirs);

    if (files)
        mx_process_list(ALL, files, flags);
    mx_free_list(files);
    if (dirs)
        mx_process_list(DIREC, dirs, flags);
    mx_free_list(dirs);
    free(flags);
}
