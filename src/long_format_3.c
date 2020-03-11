#include "uls.h"

long mx_strlen_grp(t_file *file) {
    struct group *group = getgrgid(file->stat.st_gid);
    long result = 1;

    if (group == NULL) {
        for (gid_t gid = file->stat.st_gid; gid > 0; gid /= 10)
            result++;
    }
    else
        return mx_strlen(group->gr_name);
    return result;
}

void mx_set_daddy(t_daddy *daddy) {
    daddy->n_link = 0;
    daddy->own_name = 0;
    daddy->grp_name = 0;
    daddy->size = 0;
    daddy->ma_size = 0;
    daddy->total = 0;
}

void mx_print_link(t_file *file) {
    if (MX_ISLNK(file->stat.st_mode)) {
        char *buf = NULL;
        ssize_t size = (file->stat.st_size < 100) ? 100 : file->stat.st_size;
        char *name = (file->full_path != NULL) ?
        file->full_path : file->d_name;

        buf = mx_strnew(size + 1);
        size = readlink(name, buf, size + 1);
        if (size > 0) {
            mx_printstr(" -> ");
            mx_printstr(buf);
        }
        if (buf != NULL)
            free(buf);
    }
}

void mx_print_with_tabl(long num, long num_of_dig, bool name) {
    char *result = mx_itoa(num);

    if (name == true) {
        mx_printstr(result);
        for (num_of_dig = num_of_dig - mx_strlen(result) - 1; num_of_dig > 0;
             num_of_dig--)
            mx_printchar(' ');
    }
    else {
        for (num_of_dig = num_of_dig - mx_strlen(result); num_of_dig > 0;
             num_of_dig--)
            mx_printchar(' ');
        mx_printstr(result);
    }
}

long mx_strlen_own(t_file *file) {
    struct passwd *pw = getpwuid(file->stat.st_uid);
    long result = 0;

    if (pw == NULL) {
        for (uid_t uid = file->stat.st_uid; uid > 0; uid /= 10)
            result++;
    }
    else
        return strlen(pw->pw_name);
    return result;
}
