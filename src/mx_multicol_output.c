#include "uls.h"

void mx_multicol_output(t_list *files, t_flags *flags) {
    int cols;
    int rows;
    int files_num = 0;
    int longest_name = 0;
    int col_width;
    struct winsize win_size;

    ioctl(0, TIOCGWINSZ, &win_size);
    for (t_list *iter = files; files != NULL; iter = iter->next) {
        t_file *temp = iter->data;

        ++files_num;
        if (mx_strlen(temp->d_name) > longest_name)
            longest_name = mx_strlen(temp->d_name);
    }
    col_width = longest_name + 1;
    while (col_width%4 != 0)
        ++col_width;
    cols = win_size.
}
