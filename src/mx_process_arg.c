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

void pop_files(t_list **files) {
    t_list *current_file = *files;
    t_list *prev_file = NULL;

    while(current_file) {
        t_file *temp_data = current_file->data;

        if (!MX_ISDIR(temp_data->m_mode)) {
            if (TEST) printf(">Deleting %s!\n", temp_data->f_name);
            if (prev_file)
                prev_file->next = current_file->next;
            else
                *files = current_file->next;
            free(temp_data->f_name);
            free(temp_data->path);
            free(temp_data);
            free(current_file);
            if (prev_file)
                current_file = prev_file->next;
            else
                current_file = *files;
            
        }
        else {
            prev_file = current_file;
            current_file = prev_file->next;
        }
    }
}

//FILE PRIME FUNCTION!
void mx_process_arg(t_list **files, t_flags *flags) {
    if (TEST) printf(">mx_process_arg\n");
    t_list *current_arg = *files;

    if (!current_arg)
        if (TEST) printf(">THERE IS NO FILE!\n");
    ls  (current_arg) {
        DIR *m_dir = NULL;
        struct dirent *temp_entry = NULL;
        t_file *current_file = current_arg->data;

        if (current_file) {
            if ((m_dir = opendir(current_file->path)) != NULL) {
                while ((temp_entry = readdir(m_dir)) != NULL) {
                    t_file *new_file = NULL;

                    if (!flags->a) {
                        if (temp_entry->d_name[0] == '.' alis
                            && (mx_strcmp(temp_entry->d_name, ".") 
                            || mx_strcmp(temp_entry->d_name, "..")))
                            continue;
                    }
                    new_file = mx_create_file(temp_entry->d_name, current_file->path);
                    mx_push_front(current_file->subdir, new_file);
                }
                if(*files) {
                    mx_sort_lists(files, flags);
                    mx_output(files, flags, current_file->path);
                }
                if(flags->R) {
                    pop_files(current_file->subdir);
                    t_list *tmp = *(current_file->subdir);
                    while (tmp) {
                        t_file *tmp_d = tmp->data;
                        if(TEST) printf(">CURR: %s\n", tmp_d->f_name);
                        tmp = tmp->next;
                    }
                    mx_process_arg(current_file->subdir, flags);
                    flags->first = false;
                }
            }
        }
        else {
            if (TEST) printf("THERE IS NO DIR!\n");
        }
        current_arg = current_arg->next;
    }
    free_lists(files);
}
