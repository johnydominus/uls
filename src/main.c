#include "uls.h"

int main (int argc, char **argv) {
    struct t_list *stats = NULL;
    struct t_list *entries = NULL;
    DIR *m_dir = NULL;
    char *arg = NULL;
    t_flags *flags = mx_init_flags();
    int i = 0;

    (void)argc;
    for (i = 0; i < argc; ++i) {
        if (i == 0) {}
        else {
            if (argv[i][0] == '-') {
                mx_flag_parser(argv[i], flags);
            } else 
                break;
        }
    if (i == argc) {
        arg = '.';
    }
    else {
        for(; i < argc; ++i) {
            mx_save_info(argv[i], stats, entries);
        }
    }
    if (argc > 1) {
        mx_sort_lists(flags, stats, entries);   //TODO this function
    for (int i = 0; i < argc; ++i) {
        if (argc == 1)
            mx_output(".");     //TODO this function
        else if (i == 0) {}
        else
            mx_output(argv[i]);
    }
    free_everything();          //TODO this function

    //lstat(arg, m_stat);
    //m_dir = opendir(arg);
    //while ((entry = readdir(m_dir)) != NULL) {
    //    if(entry->d_name[0] != '.')
    //        printf("%s\n", entry->d_name);
    //}
}
