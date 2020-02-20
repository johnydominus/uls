#include "uls.h"

static char *make_fullpath(char *arg, struct dirent *entry) {
    if (TEST) printf(">rec_arg\n");
    char *temp_arg = mx_strjoin(arg, "/");
    char *new_arg = mx_strjoin(temp_arg, entry->d_name);

    free(temp_arg);
    if (TEST) printf(">argument: %s\n", new_arg);
    return new_arg;
}

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
//    t_list **files = (t_list**)malloc(sizeof(t_list*));
//    *files = NULL;
//    char **temp_args = args;
    if (!current_arg)
        if (TEST) printf(">THERE IS NO FILE!\n");
    while (current_arg) {
        DIR *m_dir = NULL;
        struct dirent *temp_entry = NULL;
        t_file *current_file = current_arg->data;
//        char **new_arg = (char**)malloc(sizeof(char*));
        char *temp_filename = NULL;

//        new_arg[0] = NULL;
//        new_arg[1] = NULL;
        if ((m_dir = opendir(current_file->path)) != NULL) {
            while ((temp_entry = readdir(m_dir)) != NULL) {
                t_file *new_file = NULL;
                
                if (!flags->a) {
                    if (temp_entry->d_name[0] == '.')
                        continue;
                }
                temp_filename = make_fullpath(current_file->path, temp_entry);
                new_file = mx_create_file(temp_entry->d_name, temp_filename);
                mx_push_front(current_file->subdir, new_file);
            }
            mx_sort_lists(files, flags);
            mx_output(files, flags);
            if(flags->R)
                mx_process_arg(current_file->subdir, flags);
        }
        if (errno == ENOENT)
            mx_error(NO_FILE, current_file->path);
        current_arg = current_arg->next;
    }
    free_lists(files);
}
