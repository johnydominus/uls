#include "uls.h"

int main (int argc, char **argv) {
    t_flags *flags = mx_init_flags();
    t_list *files_args = NULL;
    t_list *dirs_args = NULL;
    int i = 1;

    mx_flag_parser(&i, argc, argv, flags);
    
    i = 1;
    files_args = mx_file_args_to_list(&i, &dirs_args, argc, argv);
    if (files_args != NULL)
        mx_process_list(ALL, files, flags);
    mx_free_list(&files_args);
    if (dirs_args != NULL)
        mx_process_list(DIREC, dirs, flags);
    mx_free_list(&dirs_args);
    free(flags);
    // struct winsize w;
    // ioctl(0, TIOCGWINSZ, &w);
    //printf ("lines %d\n", w.ws_row);
    //printf ("columns %d\n", w.ws_col);
    free(flags);
}
