#include "uls.h"

// static void free_save_info(DIR *m_dir, 
                           // struct stat *temp_stat, 
                           // struct dirent *temp_entry,
                           // char *file_name) {
    // if (m_dir)
        // free(m_dir);
    // if (temp_stat)
        // free(temp_stat);
    // if (temp_entry)
        // free(temp_entry);
    // if (file_name) {
        // free(file_name);
    // }
// }

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
void mx_process_dir(char *arg, t_list **files, t_flags *flags, DIR **m_dir) {
    char *file_name = (char*)malloc(sizeof(char*));
    t_file *file = mx_create_t_file();

    if ((*m_dir = opendir(arg)) != NULL) {
        while ((file->dirent = readdir(*m_dir)) != NULL) {
            if (flags->a == false) { //wtf?? flag -A does not work 
                if (file->dirent->d_name[0] == '.')
                    continue;
            }
            file_name = rec_arg(arg, file->dirent);
            lstat(file_name, file->stat);
            // mx_fill_t_file(file, read_result, stat_result);
            mx_push_front(files, file);
            if (file->dirent->d_type == DT_DIR && flags->R) {
                if (!mx_strcmp(file->dirent->d_name, ".") 
                    || !mx_strcmp(file->dirent->d_name, "..")) {}
                else
                    mx_process_arg(&file_name, flags);
            }
            file = mx_create_t_file();
        }
    }
    free(file);
    mx_strdel(&file_name);
}
