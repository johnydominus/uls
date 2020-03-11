#include "uls.h"

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

static void mx_push_link(t_file **file,
t_list **files_args, t_list **dir_args) {
    t_file *new_file = mx_create_t_file();

    stat((*file)->d_name, &new_file->stat);
    mx_strcpy(new_file->d_name, (*file)->d_name);
    free(*file);
    if (MX_ISDIR(new_file->stat.st_mode) == true)
        mx_push_front(dir_args, new_file);
    else 
        mx_push_front(files_args, new_file);
}

static void push_file(t_file **file, char *argv,
t_list **files_args, t_list **dir_args) {
    mx_strcpy((*file)->d_name, argv);
    if (MX_ISLNK((*file)->stat.st_mode) == true && mx_omg_auditor(2) == false)
        mx_push_link(file, files_args, dir_args);
    else if (MX_ISDIR((*file)->stat.st_mode) == true)
        mx_push_front(dir_args, (*file));
    else 
        mx_push_front(files_args, *file);

}

static void *return_dot(t_file **file, t_list **dir_args) {
    mx_strcpy((*file)->d_name, ".");
    mx_push_front(dir_args, *file);
    return NULL;
}

t_list *mx_file_args_to_list(int *i, t_list **dir_args,
int argc, char **argv) {
    t_list *files_args = NULL;
    t_list *errors = NULL;
    t_file *file = mx_create_t_file();

    if (argc == *i)
        return return_dot(&file, dir_args);
    else {
        for (; *i < argc; (*i)++) {
            if (lstat(argv[*i], &file->stat) == 0)
                push_file(&file, argv[*i], &files_args, dir_args);
            else {
                mx_push_front(&errors, mx_four_to_one("uls: ", argv[*i],
                ": ", strerror(errno)));
            }
            file = mx_create_t_file();
        }
    }
    mx_print_errors_list(errors);
    free(file);
    return files_args;
}
