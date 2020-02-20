#include "uls.h"

static struct t_file *copy_info(struct dirent *fdirent, struct stat *fstat) {
    t_file *new_file = (t_file*)malloc(sizeof(t_file));
    
    new_file->m_stat = fstat;
    new_file->f_name = mx_strdup(fdirent->d_name);
    return new_file;
}

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
void mx_save_info(char *arg, t_flags *flags, t_list **files) {
    if (TEST) printf(">mx_save_info\n");
    DIR *m_dir = NULL;
    struct stat *temp_stat = NULL;
    struct dirent *temp_entry = NULL;
    t_file *new_file = NULL;
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
            new_file = copy_info(temp_entry, temp_stat);
            mx_push_front(files, new_file);
            if (MX_ISDIR(temp_stat->st_mode)) {
            if (!mx_strcmp(new_file->f_name, ".") 
                || !mx_strcmp(new_file->f_name, "..")) {}
            else
                mx_process_arg(new_arg, flags);
            }
        }
    }
    free_save_info(m_dir, temp_stat, temp_entry, new_arg);    
    if (errno == ENOENT)
        mx_error(NO_FILE, arg);
}
