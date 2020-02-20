#include "uls.h"

static void free_save_info(DIR *m_dir, 
                           struct stat *temp_stat, 
                           struct dirent *temp_entry,
                           char **new_arg) {
    if (m_dir)
        free(m_dir);
    if (temp_stat)
        free(temp_stat);
    if (temp_entry)
        free(temp_entry);
    if (new_arg) {
        if (new_arg[0])
            free(new_arg[0]);
        free(new_arg);
    }
}

static char *rec_arg(char *arg, struct dirent *entry) {
    char *temp_arg = mx_strjoin(arg, "/");
    char *new_arg = mx_strjoin(temp_arg, entry->d_name);

    free(temp_arg);
    return new_arg;
}

//FILE PRIME FUNCTION!
void mx_save_info(char *arg, 
                   t_flags *flags,
                   t_list **stats,
                   t_list **entries) {
    DIR *m_dir = NULL;
    struct stat *temp_stat = NULL;
    struct dirent *temp_entry = NULL;
    char **new_arg = (char**)malloc(sizeof(char*) * 2);
    new_arg[0] = NULL;
    new_arg[1] = NULL;

    if ((m_dir = opendir(arg)) != NULL) {
        while ((temp_entry = readdir(m_dir)) != NULL) {
            if (!flags->a) {
                if (temp_entry->d_name[0] == '.')
                    continue;
            }
            new_arg[0] = rec_arg(arg, temp_entry);
            lstat(new_arg[0], temp_stat);
            mx_push_front(stats, temp_stat);
            mx_push_front(entries, temp_entry);
            if (temp_entry->d_type == DT_DIR && flags->R) {
            if (!mx_strcmp(temp_entry->d_name, ".") 
                || !mx_strcmp(temp_entry->d_name, "..")) {}
            else
                mx_process_arg(new_arg, flags);
            }
        }
    }
    free_save_info(m_dir, temp_stat, temp_entry, new_arg);    if (errno == ENOENT)
        mx_error(NO_FILE, arg);
}
