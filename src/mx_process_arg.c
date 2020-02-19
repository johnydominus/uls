#include "uls.h"

static t_file *copy_info(struct dirent *fdirent, struct stat *fstat) {
    t_file *new_file = (t_file*)malloc(sizeof(t_file));
    
    new_file->m_dev = fstat->st_dev;
    new_file->m_ino = fstat->st_ino;
    new_file->m_mode = fstat->st_mode;
    new_file->m_nlink = fstat->st_nlink;
    new_file->m_uid = fstat->st_uid;
    new_file->m_gid = fstat->st_gid;
    new_file->m_rdev = fstat->st_rdev;
    new_file->m_atime = fstat->st_atime;
//    new_file->m_atimensec = fstat->st_atimensec;
    new_file->m_mtime = fstat->st_mtime;
//    new_file->m_mtimensec = fstat->st_mtimensec;
    new_file->m_ctime = fstat->st_mtime;
//    new_file->m_ctimensec = fstat->st_mtimensec;
    new_file->m_size = fstat->st_size;
    new_file->m_blocks = fstat->st_blocks;
    new_file->m_blksize = fstat->st_blksize;
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

static void free_lists(t_list **files) {
    t_list *temp_file = *files;

    while (temp_file) {
        t_list *temp = temp_file;

        temp_file = temp_file->next;
        free(temp);
    }
    free(files);
}

//FILE PRIME FUNCTION!
void mx_process_arg(char **args, t_flags *flags) {
    t_list **files = (t_list**)malloc(sizeof(t_list*));
    *files = NULL;
    char **temp_args = args;
    int i = 0;

    while (temp_args[i]) {
        DIR *m_dir = NULL;
        struct stat *temp_stat = NULL;
        struct dirent *temp_entry = NULL;
        t_file *new_file = NULL;
        char **new_arg = (char**)malloc(sizeof(char*) * 2);
        int j = 0;

        new_arg[0] = NULL;
        new_arg[1] = NULL;
        if ((m_dir = opendir(temp_args[i])) != NULL) {
            while ((temp_entry = readdir(m_dir)) != NULL) {
                if (!flags->a) {
                    if (temp_entry->d_name[0] == '.')
                        continue;
                }
                new_arg[0] = rec_arg(temp_args[i], temp_entry);
                lstat(new_arg[0], temp_stat);
                new_file = copy_info(temp_entry, temp_stat);
                mx_push_front(files, new_file);
                if(temp_stat) {
                    if (MX_ISDIR(temp_stat->st_mode)) {
                        printf("?\n");
                        if (!mx_strcmp(new_file->f_name, ".") 
                            || !mx_strcmp(new_file->f_name, "..")) {}
                        else {
                            new_arg[j++] = rec_arg(temp_args[i], temp_entry);
                        }
                    }
                }
            }
            if (!flags->f)
                mx_sort_lists(flags, files);
            mx_output(flags, files, args);
            if(flags->R)
                mx_process_arg(new_arg, flags);
        }
        free_save_info(m_dir, temp_stat, temp_entry, new_arg);    
        if (errno == ENOENT)
            mx_error(NO_FILE, temp_args[i]);
        ++i;
    }
    free_lists(files);
}
