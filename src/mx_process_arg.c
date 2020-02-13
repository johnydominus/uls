#include "uls.h"

static void free_lists(t_list **stats, t_list **entries) {
    t_list *temp_stat = *stats;
    t_list *temp_entry = *entries;

    while (temp_entry) {
        t_list *temp = temp_stat;

        temp_stat = temp_stat->next;
        free(temp);
        temp = temp_entry;
        temp_entry = temp_entry->next;
        free(temp);
    }
    free(stats);
    free(entries);
}

//FILE PRIME FUNCTION!
void mx_process_arg(char **args, t_flags *flags) {
    t_list **stats = (t_list**)malloc(sizeof(t_list*));
    t_list **entries = (t_list**)malloc(sizeof(t_list*));
    char **temp_args = args;
    int i = 0;

    *stats = NULL;
    *entries = NULL;
    while (temp_args[i])
        mx_save_info(temp_args[i++], flags, stats, entries);
    if (!flags->f)
        mx_sort_lists(flags, stats, entries);
    mx_output(flags, stats, entries, args);
    free_lists(stats, entries);
}
