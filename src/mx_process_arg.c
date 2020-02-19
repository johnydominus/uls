#include "uls.h"

static t_file *copy_info(struct dirent *fdirent, struct stat *fstat) {
    printf("copy_info\n");
    t_file *new_file = (t_file*)malloc(sizeof(t_file));
    if(!fstat)
        printf("THERE IS NO STAT!\n");
    
    printf("m_dev\n");
    new_file->m_dev = fstat->st_dev;
    printf("m_ino\n");
    new_file->m_ino = fstat->st_ino;
    printf("m_mode\n");
    new_file->m_mode = fstat->st_mode;
    printf("m_nlink\n");
    new_file->m_nlink = fstat->st_nlink;
    printf("m_uid\n");
    new_file->m_uid = fstat->st_uid;
    printf("m_gid\n");
    new_file->m_gid = fstat->st_gid;
    printf("m_rdev\n");
    new_file->m_rdev = fstat->st_rdev;
    printf("m_atime\n");
    new_file->m_atime = fstat->st_atime;
//    new_file->m_atimensec = fstat->st_atimensec;
    printf("m_mtime\n");
    new_file->m_mtime = fstat->st_mtime;
//    new_file->m_mtimensec = fstat->st_mtimensec;
    printf("m_ctime\n");
    new_file->m_ctime = fstat->st_mtime;
//    new_file->m_ctimensec = fstat->st_mtimensec;
    printf("m_size\n");
    new_file->m_size = fstat->st_size;
    printf("m_blocks\n");
    new_file->m_blocks = fstat->st_blocks;
    printf("m_blksize\n");
    new_file->m_blksize = fstat->st_blksize;
    printf("f_name\n");
    new_file->f_name = mx_strdup(fdirent->d_name);
    printf("copy done!\n");
    return new_file;
}

static void free_save_info(DIR *m_dir, 
                           struct stat *temp_stat, 
                           struct dirent *temp_entry,
                           char **new_arg) {
    printf("free_save_info\n");
    int i = 0;
    printf("m_dir freeing\n");
    if (m_dir)
        free(m_dir);
    printf("temp_stat freeing\n");
    if (temp_stat)
        free(temp_stat);
    printf("temp_entry freeing\n");
    if (temp_entry)
        free(temp_entry);
    printf("new_arg freeing\n");
    if (new_arg) {
        while (new_arg[i])
            free(new_arg[i++]);
        free(new_arg);
    }
}

static char *rec_arg(char *arg, struct dirent *entry) {
    printf("rec_arg\n");
    char *temp_arg = mx_strjoin(arg, "/");
    char *new_arg = mx_strjoin(temp_arg, entry->d_name);

    free(temp_arg);
    return new_arg;
}

static void free_lists(t_list **files) {
    printf("free_lists");
    if (files) {
        t_list *temp_file = *files;

        if (temp_file) {
            while (temp_file) {
                t_list *temp = temp_file;

                temp_file = temp_file->next;
                free(temp);
            }
        }
        free(files);
    }
}

//FILE PRIME FUNCTION!
void mx_process_arg(char **args, t_flags *flags) {
    printf("mx_process_arg\n");
    t_list **files = (t_list**)malloc(sizeof(t_list*));
    *files = NULL;
    char **temp_args = args;
    int i = 0;

    while (temp_args[i]) {
        DIR *m_dir = NULL;
        struct stat *temp_stat = (struct stat*)malloc(sizeof(struct stat));
        struct dirent *temp_entry = NULL;
        t_file *new_file = NULL;
        char **new_arg = (char**)malloc(sizeof(char*));
        char *temp_filename = NULL;
        int j = 0;

        new_arg[0] = NULL;
        new_arg[1] = NULL;
        if ((m_dir = opendir(temp_args[i])) != NULL) {
            while ((temp_entry = readdir(m_dir)) != NULL) {
                if (!flags->a) {
                    if (temp_entry->d_name[0] == '.')
                        continue;
                }
                temp_filename = rec_arg(temp_args[i], temp_entry);
                printf("%s\n", temp_filename);
                stat(temp_filename, temp_stat);
                perror(NULL);
                free(temp_filename);
                new_file = copy_info(temp_entry, temp_stat);
                printf("!\n");
                mx_push_front(files, new_file);
                if(temp_stat) {
                    if (MX_ISDIR(temp_stat->st_mode)) {
                        if (!mx_strcmp(new_file->f_name, ".") 
                            || !mx_strcmp(new_file->f_name, "..")) {}
                        else {
                            new_arg[j++] = rec_arg(temp_args[i], temp_entry);
                            new_arg[j] = NULL;
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
