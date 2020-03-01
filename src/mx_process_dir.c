#include "uls.h"

static char *rec_arg(char *arg, struct dirent *entry) {
    char *temp_arg = mx_strjoin(arg, "/");
    char *file_name = mx_strjoin(temp_arg, entry->d_name);

    free(temp_arg);
    return file_name;
}

t_file *mx_create_t_file() {
    t_file *file = (t_file*)malloc(sizeof(t_file));
    file->full_path = NULL;
    file->error = NULL;
    return file;
}

//FILE PRIME FUNCTION
t_list *mx_process_dir(t_file *dir, t_flags *flags) {
    // char *file_name = (char*)malloc(sizeof(char*));
    t_file *file = mx_create_t_file();
    t_dirent *dirent = NULL;
    DIR *m_dir = NULL;
    t_list *files = NULL;

    if ((m_dir = opendir(dir->d_name)) != NULL) {
        while ((dirent = readdir(m_dir)) != NULL) {
            if (flags->a == false) { //wtf?? flag -A does not work 
                if (dirent->d_name[0] == '.')
                    continue;
            }
            // file_name = rec_arg(dir->d_name, dirent);
            file->full_path = rec_arg(dir->d_name, dirent);
            lstat(file->full_path, &file->stat);
            mx_strcpy(file->d_name, dirent->d_name);
            mx_push_front(&files, file);
            file = mx_create_t_file();
        }
    }
    free(file);
    // mx_strdel(&file_name);
    closedir(m_dir);
    return files;
}
