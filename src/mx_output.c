#include "uls.h"

static t_file *get_nth_file(t_list *files, int n) {
    int i = 0;
    t_list *iter = files;

    while (iter) {
        if (i == n)
            return iter->data;
        ++i;
        iter = iter->next;
    }
    return NULL;
}

static void count_tabs(int max_len, int prev_len) {
    int spaces_count = 0;
    int tabs_count = 0;

    if (!(max_len % 8))
        spaces_count = max_len + 8;
    else {
        spaces_count = max_len;
        while (spaces_count % 8)
            spaces_count++;
    }
    tabs_count = (spaces_count - prev_len) / 8;
    if (!(prev_len % 8))
        tabs_count--;
    while (tabs_count--)
        mx_printchar('\t');
    mx_printchar('\t');
}

void mx_c_output(t_list *files, t_flags *flags, t_multicol *mltcl) {
    int prev_len = 0;
    t_file *data = NULL;

    for (int i = 0; i < mltcl->rows; ++i) {
        for (int j = 0; j < mltcl->files_num; j += mltcl->rows) {
            data = get_nth_file(files, i + j);
            if (j != 0 && ((i + j) < mltcl->files_num))
                count_tabs(mltcl->max, prev_len);
            if (i + j < mltcl->files_num) {
                mx_print_filename(data, flags);
                prev_len = mx_strlen(data->d_name) + mx_add_symb(data, flags);
            }
        }
        mx_printchar('\n');
    }
}

void mx_x_output(t_list *files, t_flags *flags, t_multicol *mltcl) {
    int prev_len = 0;
    t_list *file = files;
    t_file *data = NULL;

    for (int i = 0; i < mltcl->rows; ++i) {
        for (int j = 0; j < mltcl->files_num; j += mltcl->rows) {
            if (j != 0 && ((i + j) < mltcl->files_num))
                count_tabs(mltcl->max, prev_len);
            if (i + j < mltcl->files_num) {
                data = file->data;
                mx_print_filename(data, flags);
                prev_len = mx_strlen(data->d_name) + mx_add_symb(data, flags);
            }
            file = file->next;
        }
        mx_printchar('\n');
    }
}

void mx_print_name_list(t_list *files, t_flags* flags) {
    for (t_list *cur = files; cur; cur = cur->next) {
        t_file *temp = (t_file*)cur->data; 
            mx_print_filename(temp, flags);
            mx_printstr("\n");
    }
}

void mx_output(t_flags *flags, t_list *files) {
    if (flags->one)
        mx_print_name_list(files, flags);
    else if (flags->C || flags->x)
        mx_multicol_output(files, flags);
    // else if (flags->l)
    //      mx_print_long_format(files, flags);
}
