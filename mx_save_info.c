#include "uls.h"

static void process_file(char *arg, t_list **stats, t_list **entries) {   //TODO: files as arguments
    (void)arg;
    (void)stats;
    (void)entries;
    return;
}

//FILE PRIME FUNCTION!
void mx_save_info(char *arg, 
                   t_flags *flags,
                   t_list **stats,
                   t_list **entries) {
    mx_process_dir(arg, stats, entries, flags);
    if (errno == ENOTDIR)
        process_file(arg, stats, entries);
    if (errno == ENOENT)
        mx_error(NO_FILE, arg);
}
