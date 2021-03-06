#include "uls.h"

static char *rec_arg(char *arg, struct dirent *entry) {
    if (mx_strcmp(arg, "/") == 0)
        return mx_strjoin(arg, entry->d_name);
    char *temp_arg = mx_strjoin(arg, "/");
    char *file_name = mx_strjoin(temp_arg, entry->d_name);

    free(temp_arg);
    return file_name;
}

static void print_error(char *first_part, char *text,
                        char *second_part, char *third_part) {
    int len1 = mx_strlen(first_part);
    int len2 = mx_strlen(text);
    int len3 = mx_strlen(second_part);
    int len4 = mx_strlen(third_part);
    char *error = mx_strnew(len1 + len2 + len3 + len4);

    mx_strcat(error, first_part);
    mx_strcat(error, text);
    mx_strcat(error, second_part);
    mx_strcat(error, third_part);
    mx_printerr(error);
    mx_printerr("\n");
    free(error);
}

static bool if_dot(char *d_name) {
    if (d_name[0] == '.' && d_name[1] == '.' && d_name[2] == '\0')
        return true;
    if (d_name[0] == '.' && d_name[1] == '\0')
        return true;
    else
        return false;
}

static void fill_list(DIR *m_dir, t_flags *flags,
                      t_list **files, t_file *dir) {
    t_file *file = NULL;
    t_dirent *dirent = NULL;

    while ((dirent = readdir(m_dir)) != NULL) {
        file = mx_create_t_file();
        if (flags->A == false || if_dot(dirent->d_name) == true) {
            if (dirent->d_name[0] == '.') {
                free(file);
                continue;
            }
        }
        if (dir->full_path != NULL)
            file->full_path = rec_arg(dir->full_path, dirent);
        else
            file->full_path = rec_arg(dir->d_name, dirent);
        lstat(file->full_path, &file->stat);
        mx_strcpy(file->d_name, dirent->d_name);
        mx_push_front(files, file);
    }
}

t_list *mx_process_dir(t_file *dir, t_flags *flags) {
    DIR *m_dir = NULL;
    t_list *files = NULL;

    if (dir->full_path != NULL)
        m_dir = opendir(dir->full_path);
    else
        m_dir = opendir(dir->d_name);
    if (m_dir != NULL) {
        fill_list(m_dir, flags, &files, dir);
        closedir(m_dir);
    }
    else {
        mx_print_path(dir, flags);
        print_error("uls: ", dir->d_name, ": ", strerror(errno));
        dir->error = true;
    }
    mx_sort_files(files, flags);
    return files;
}
