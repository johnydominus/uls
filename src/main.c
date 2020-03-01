#include "uls.h"

int main (int argc, char **argv) {
    t_flags *flags = mx_init_flags();
    t_list *files_args;
    t_list *dirs_args;
    int i = 1;
    // char **args = NULL;
    // int margc;

    mx_flag_parser(&i, argc, argv, flags);
    // args = mx_save_args(&i, &margc, argc, argv);
    i = 1;
    files_args = mx_file_args_to_list(&i, &dirs_args, argc, argv);
    // mx_bubble_sort(args, margc);
    // struct winsize w;
    // ioctl(0, TIOCGWINSZ, &w);
    //printf ("lines %d\n", w.ws_row);
    //printf ("columns %d\n", w.ws_col);
    // mx_process_arg(args, flags);
    free(flags);
    // for (int j = 0; args[j]; j++)
        // free(args[j]);
    // free(args);
}
