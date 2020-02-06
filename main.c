#include "uls.h"

int main (int argc, char **argv) {
    t_flags *flags = mx_init_flags();
    char **args = NULL;
    int margc;
    int i = 1;

    (void)argc;
    mx_flag_parser(&i, argc, argv, flags);
    args = mx_save_args(&i, &margc, argc, argv);
    mx_bubble_sort(args, margc);
    //
    mx_process_arg(args, flags);
    free(flags);
    int j = 0;
    while (args[j])
        free(args[j++]);
    free(args);
    //lstat(arg, m_stat);
    //m_dir = opendir(arg);
    //while ((entry = readdir(m_dir)) != NULL) {
    //    if(entry->d_name[0] != '.')
    //        printf("%s\n", entry->d_name);
    //}
}
