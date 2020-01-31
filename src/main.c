#include "uls.h"

int main (int argc, char **argv) {
    struct t_list *stats = NULL;
    struct t_list *entries = NULL;
    DIR *m_dir = NULL;
    char *arg = NULL;
    bool flag = true;
    t_flags *flags = mx_init_flags();

    (void)argc;
    for (int i = 0; i < argc; ++i) {
        if (argc == 1) {}
        else {
            if (i == 0) {}
            else {
                if (flag) {
                    if (argv[i][0] == '-') {
                        mx_flag_parser(flags);  //TODO this function
                    } else 
                        flag == false;
                } else
                    mx_save_info(argv[i], stats, entries);  //TODO this function
            }
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
