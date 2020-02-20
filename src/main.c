#include "uls.h"

int main (int argc, char **argv) {
    printf("main\n");
    t_flags *flags = mx_init_flags();
    char **args = NULL;
    int margc;
    int i = 1;

    (void)argc;
    mx_flag_parser(&i, argc, argv, flags);
    args = mx_save_args(&i, &margc, argc, argv);
    mx_bubble_sort(args, margc);
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
    mx_process_arg(args, flags);
    free(flags);
    int j = 0;
    while (args[j])
        free(args[j++]);
    free(args);
}
