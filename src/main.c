#include "uls.h"

static void auditor_costil(t_list *alist, t_flags *flags, t_print fd) {
    mx_sort_files(alist, flags);
    mx_process_list(fd, alist, flags);
    mx_free_list(&alist);
}

int main (int argc, char **argv) {
    t_flags *flags = mx_init_flags();
    t_list *files_args = NULL;
    t_list *dirs_args = NULL;
    int i = 1;

    mx_flag_parser(&i, argc, argv, flags);
    flags->printpath = (i + 2 > argc) ? false : true;
    files_args = mx_file_args_to_list(&i, &dirs_args, argc, argv);
    if (files_args != NULL) {
        auditor_costil(files_args, flags, ALL);
        if (dirs_args)
            mx_printchar('\n');
    }
    if (dirs_args != NULL)
        auditor_costil(dirs_args, flags, DIREC);
    free(flags);
}
