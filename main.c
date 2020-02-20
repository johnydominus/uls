#include "uls.h"

int main (int argc, char **argv) {
    if (TEST) printf(">main\n");
    t_flags *flags = mx_init_flags();
    t_list **files = (t_list**)malloc(sizeof(t_list*));
    
    *files = NULL;
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
    if (margc == 0) {
        t_file *temp_file = mx_create_file(".", "");
        if (TEST) printf(">%s\n", temp_file->path);
        mx_push_front(files, temp_file);
    }
    else {
        for (int y = margc - 2; y >= 0; --y) {
            if (TEST) printf(">%d\n", y);
            t_file *temp_file = mx_create_file(args[y], ".");

            temp_file->path = mx_strdup(args[y]);
            temp_file->f_name = NULL;
            temp_file->subdir = (t_list**)malloc(sizeof(t_list*));
            *(temp_file->subdir) = NULL;
            if (TEST) printf(">%s\n", temp_file->path);
            mx_push_front(files, temp_file);
        }
    }
    //
    struct winsize w;
    
    ioctl(0, TIOCGWINSZ, &w);
    //printf ("lines %d\n", w.ws_row);
    //printf ("columns %d\n", w.ws_col);
 //   printf("?\n");
 //   if(args)
 //       printf("%s\n", args[0]);
 //   if(flags)
 //       printf("flags\n");
    mx_process_arg(files, flags);
    free(flags);
    while (args[j])
        free(args[j++]);
    free(args);
 	//system("leaks -q uls");

}
