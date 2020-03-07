#include "uls.h"

static void if_first(int *cols, t_file *data, struct winsize *window) {
    if (*cols == 0) {}
    else {
        mx_printstr(", ");
        (*cols) += 2;
        if (*cols + mx_strlen(data->d_name) + 1 < window->ws_col) {}
        else {
            mx_printchar('\n');
            *cols = 0;
        }
    }
}

void mx_m_output(t_list *files, t_flags *flags) {
    t_list *iter = files;
    struct winsize window;
    int cols = 0;

    if (isatty(1))
        ioctl(0, TIOCGWINSZ, &window);
    else
        window.ws_col = 80;
    while (iter) {
        t_file *data = iter->data;

        if_first(&cols, data, &window);
        mx_print_filename(data, flags);
        cols += mx_strlen(data->d_name);
        iter = iter->next;
    }
    mx_printchar('\n');
}
