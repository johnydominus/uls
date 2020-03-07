#include "uls.h"

int main (int argc, char **argv) {
    t_flags *flags = mx_init_flags();
    t_list *files_args = NULL;
    t_list *dirs_args = NULL;
    int i = 1;

    mx_flag_parser(&i, argc, argv, flags);
    files_args = mx_file_args_to_list(&i, &dirs_args, argc, argv);
    if (files_args != NULL) {
        mx_process_list(ALL, files_args, flags);
        mx_free_list(&files_args);
    }
    if (dirs_args != NULL) {
        mx_process_list(DIREC, dirs_args, flags);
        mx_free_list(&dirs_args);
    }
    system("leaks -q uls");
}
