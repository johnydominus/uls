#include "uls.h"

int mx_add_symb(t_file *file, t_flags *flags) {
    if (flags->F || flags->p) {
        if (MX_ISDIR(file->stat.st_mode))
            return 1;
    }
    if (flags->F) {
        if (MX_ISLNK(file->stat.st_mode))
            return 1;
        else if (MX_ISSOCK(file->stat.st_mode))
            return 1;
        else if (MX_ISFIFO(file->stat.st_mode))
            return 1;
        else if (MX_ISEXEC(file->stat.st_mode))
            return 1;
    }
    return 0;
}

static t_multicol *multicol_init(t_list *files, t_flags *flags) {
    t_multicol *multicol = (t_multicol*)malloc(sizeof(t_multicol));
    
    multicol->files_num = 0;
    multicol->max = 0;
    if (isatty(1))
        ioctl(0, TIOCGWINSZ, &multicol->win_size);
    else
        multicol->win_size.ws_col = 1;
    for (t_list *iter = files; iter != NULL; iter = iter->next) {
        t_file *temp = iter->data;
        int len = mx_strlen(temp->d_name);

        ++multicol->files_num;
        if (len > multicol->max)
            multicol->max = len /*+ mx_add_symb(temp, flags)*/;
    }
    multicol->col_width = ((8 - (multicol->max % 8)) + multicol->max);
    while (multicol->col_width % 8 != 0)
        ++multicol->col_width;
    multicol->cols = multicol->win_size.ws_col / multicol->col_width;
    if (multicol->files_num % multicol->cols)
        multicol->rows =  (multicol->files_num / multicol->cols) + 1;
    else
        multicol->rows = multicol->files_num / multicol->cols;
    // printf("cols: %d\n", multicol->cols);
    // printf("rows: %d\n", multicol->rows);
    // printf("files_num: %d\n", multicol->files_num);
    // printf("max: %d\n", multicol->max);
    // printf("col_width: %d\n", multicol->col_width);
    // printf("win_size rows: %d\n", multicol->win_size.ws_row);
    // printf("win_size cols: %d\n", multicol->win_size.ws_col);
    return multicol;
}

void mx_multicol_output(t_list *files, t_flags *flags) {
    t_multicol *multicol = multicol_init(files, flags);
    t_list *iter = files;

    if (flags->x)
        mx_x_output(iter, flags, multicol);
    else
        mx_c_output(iter, flags, multicol);
    free (multicol);
}
