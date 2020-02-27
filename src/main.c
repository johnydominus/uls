#include "uls.h"

static void fill_files(t_list **files, char **args, int margc) {
    t_file *temp_file = NULL;

    if (margc == 0) {
        temp_file = mx_create_file(".", "");
        
        if (TEST) printf(">%s\n", temp_file->path);
        mx_push_front(files, temp_file);
    }
    else {
        for (int y = 0; y < margc - 1; ++y) {
            if (TEST) printf(">%d\n", y);
            if (!mx_strcmp(args[y], "/") || !mx_strcmp(args[y], "~"))
                temp_file = mx_create_file(args[y], "");
            else
                temp_file = mx_create_file(args[y], ".");
            int temp_fd;

            if ((temp_fd = open(args[y], O_RDONLY != -1))) {
                if (TEST) printf(">path: %s\n", temp_file->path);
                mx_push_back(files, temp_file);
                close(temp_fd);
            }
            else {
                mx_error(NO_FILE, args[y]);
            }
        }
    }
}

int main (int argc, char **argv) {
    // if (TEST) printf(">main\n");
    t_flags *flags = mx_init_flags();
    t_list **files = (t_list**)malloc(sizeof(t_list*));
    char **args = NULL;
    int margc;
    int i = 1;
    int j = 0;

    *files = NULL;
    mx_flag_parser(&i, argc, argv, flags);
    args = mx_save_args(&i, &margc, argc, argv);
    int s = 0;
    if (TEST) while (args[s])
        if (TEST) printf("%s ", args[s++]);
    if (TEST) putchar('\n');
    if (TEST) printf(">margc = %d\n", margc);
    mx_bubble_sort(args, margc - 1);
    fill_files(files, args, margc);
    mx_process_arg(files, flags);
    free(flags);
    while (args[j])
        free(args[j++]);
    free(args);
 	//system("leaks -q uls");
}
