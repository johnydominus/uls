#include "uls.h"

static t_multicol *multicol_init(t_list *files) {
    t_multicol *multicol = (t_multicol*)malloc(sizeof(t_multicol));
    
    multicol->files_num = 0;
    multicol->longest_name = 0;

    ioctl(0, TIOCGWINSZ, &multicol->win_size);
    for (t_list *iter = files; iter != NULL; iter = iter->next) {
        t_file *temp = iter->data;

        ++multicol->files_num;
        if (mx_strlen(temp->d_name) > multicol->longest_name)
            multicol->longest_name = mx_strlen(temp->d_name);
    }
    multicol->col_width = multicol->longest_name + 1;
    while (multicol->col_width%4 != 0)
        ++multicol->col_width;
    multicol->cols = multicol->win_size.ws_row / multicol->col_width;
    multicol->rows = multicol->cols / multicol->files_num;
    return multicol;
}

void mx_multicol_output(t_list *files, t_flags *flags) {
    t_multicol *multicol = multicol_init(files);
    t_list *iter = files;

    if (flags->x) {
        while (iter) {
            t_file *data = iter->data;

            int temp_cols = 0;
            int temp_rows = 0;
            int x_col = 0;

            mx_print_filename(data, flags);
            x_col += mx_strlen(data->d_name);
            ++temp_cols;
            if (temp_cols < multicol->cols) {
                while (x_col%multicol->col_width != 0)
                    ++x_col;
            } else {
                mx_printchar('\n');
                ++temp_rows;
                temp_cols = 0;
                x_col = 0;
            }
            iter = iter->next;
        }
    }
    free (multicol);
}
