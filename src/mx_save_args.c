#include "uls.h"

void mx_print_errors_list(t_list *files) {
    for (t_list *cur = files; cur; cur = cur->next) {
        char *temp = (char*)cur->data; 
            mx_printerr(temp);
            mx_printerr("\n");
    }
}

char *mx_four_to_one(char *first_part, char *text,
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
    return error;
}

t_list *mx_file_args_to_list (int *i, t_list **dir_args, int argc, char **argv) {
    t_list *files_args = NULL;
    t_list *errors = NULL;
    t_file *file = mx_create_t_file();

    if (argc == *i) {
        mx_strcpy(file->d_name, ".");
        mx_push_front(dir_args, file);
        return NULL;
    }
    else {
        for (; *i < argc; (*i)++) {
            if (lstat(argv[*i], &file->stat) == 0) {
                mx_strcpy(file->d_name, argv[*i]);
                if (MX_ISDIR(file->stat.st_mode) == true)
                    mx_push_front(dir_args, file);
                else 
                    mx_push_front(&files_args, file);
            }
            else {
                mx_push_front(&errors, mx_four_to_one("uls: ", argv[*i],
                ": ", strerror(errno)));
            }
            file = mx_create_t_file();
        }
    }
    //TODO add sorting
    mx_print_errors_list(errors);
    mx_free_list(&errors);
    free(file);
    return files_args;
}
