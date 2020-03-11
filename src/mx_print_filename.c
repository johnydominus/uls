#include "uls.h"

static void set_color(mode_t mode) {
    if (MX_ISLNK(mode))
        mx_printstr(MX_MAGENTA);
    else if (MX_ISSOCK(mode))
        mx_printstr(MX_GREEN);
    else if (MX_ISEXEC(mode))
        mx_printstr(MX_RED);
    else if (MX_ISDIR(mode))
        mx_printstr(MX_BLUE);
}

void mx_print_filename (t_file *file, t_flags *flags) {
    if (flags->G)
        set_color(file->stat.st_mode);
    mx_printstr(file->d_name);
    if (flags->G)
        mx_printstr(MX_RESET);
}
