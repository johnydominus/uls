#include "uls.h"

static void auditor_costil(t_list *alist, t_flags *flags,
t_print fd, t_list *dirs_args) {
    mx_sort_files(alist, flags);
    mx_process_list(fd, alist, flags);
    mx_free_list(&alist);
}

bool mx_omg_auditor(int set) {
    static bool l_flag = false;

    if (set == 1)
        l_flag = true;
    else if (set == 0)
        l_flag = false;
    return l_flag;
}

int main (int argc, char **argv) {
    t_flags *flags = mx_init_flags();
    t_list *files_args = NULL;
    t_list *dirs_args = NULL;
    int i = 1;

    mx_flag_parser(&i, argc, argv, flags);
    flags->printpath = (i + 2 > argc) ? false : true;
    if (flags->l == true)
       mx_omg_auditor(1);
    files_args = mx_file_args_to_list(&i, &dirs_args, argc, argv);
    if (files_args != NULL) {
        flags->file_args = true;
        auditor_costil(files_args, flags, ALL, dirs_args);
        if (dirs_args)
            mx_printchar('\n');
    }
    if (dirs_args != NULL) {
        flags->file_args = false;
        auditor_costil(dirs_args, flags, DIREC, dirs_args);
    }
    free(flags);
}
