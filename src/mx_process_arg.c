#include "uls.h"

static void free_lists(t_list **files) {
    if (TEST) printf(">free_lists\n");
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
void mx_process_arg(t_list **files, t_flags *flags) {
    if (TEST) printf(">mx_process_arg\n");
    t_list *current_arg = *files;

    if (!current_arg)
        if (TEST) printf(">THERE IS NO FILE!\n");
    while (current_arg) {
        DIR *m_dir = NULL;
        struct dirent *temp_entry = NULL;
        t_file *current_file = current_arg->data;

        if ((m_dir = opendir(current_file->path)) != NULL) {
            while ((temp_entry = readdir(m_dir)) != NULL) {
                t_file *new_file = NULL;

                if (!flags->a) {
                    if (temp_entry->d_name[0] == '.' 
                        && (mx_strcmp(temp_entry->d_name, ".") 
                        || mx_strcmp(temp_entry->d_name, "..")))
                        continue;
                }
                new_file = mx_create_file(temp_entry->d_name, current_file->path);
                mx_push_front(current_file->subdir, new_file);
            }
            mx_sort_lists(files, flags);
            mx_output(files, flags, current_file->path);
            if(flags->R) {
                mx_process_arg(current_file->subdir, flags);
                flags->first = false;
            }
        }
        if (errno == ENOENT)
            mx_error(NO_FILE, current_file->path);
        current_arg = current_arg->next;
    }
    free_lists(files);
}
