#include "uls.h"

static t_multicol *multicol_subinit(t_multicol *multicol) {
    multicol->col_width = ((8 - (multicol->max % 8)) + multicol->max);
    while (multicol->col_width % 8 != 0)
        ++multicol->col_width;
    multicol->cols = multicol->win_size.ws_col / multicol->col_width;
    if (multicol->cols == 0)
        multicol->cols = 1;
    if (multicol->files_num % multicol->cols)
        multicol->rows =  (multicol->files_num / multicol->cols) + 1;
    else
        multicol->rows = multicol->files_num / multicol->cols;
    return multicol;
}

static t_multicol *multicol_init(t_list *files) {
    t_multicol *multicol = (t_multicol*)malloc(sizeof(t_multicol));

    multicol->files_num = 0;
    multicol->max = 0;
    if (isatty(1))
        ioctl(0, TIOCGWINSZ, &multicol->win_size);
    else
        multicol->win_size.ws_col = 80;
    for (t_list *iter = files; iter != NULL; iter = iter->next) {
        t_file *temp = iter->data;
        int len = mx_strlen(temp->d_name);

        ++multicol->files_num;
        if (len > multicol->max)
            multicol->max = len; 
    }
    return multicol_subinit(multicol);
}

void mx_multicol_output(t_list *files, t_flags *flags) {
    t_multicol *multicol = multicol_init(files);
    t_list *iter = files;

    if (flags->x)
        mx_x_output(iter, flags, multicol);
    else
        mx_c_output(iter, flags, multicol);
    free (multicol);
}
