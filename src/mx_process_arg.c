#include "uls.h"

static void free_list(t_list **files) {
    t_list *temp_files = *files;
    while (temp_files) {
        t_list *temp = temp_files;

        temp_files = temp_files->next;
        free(temp);
    }
}


//FILE PRIME FUNCTION!
void mx_process_arg(char **args, t_flags *flags) {
    t_list *files = NULL;
    DIR *m_dir = NULL;
    char **temp_args = args; // Why don't use args?

    for (int i = 0; temp_args[i]; i++)
        mx_process_dir(temp_args[i], &files, flags, &m_dir);

    // mx_print_list(files);
    // if (!flags->f)
        // mx_sort_lists(flags, stats, entries);
    mx_output(flags, files, args);
    free_list(&files);
    closedir(m_dir);
}
