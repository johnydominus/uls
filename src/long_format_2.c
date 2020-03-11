#include "uls.h"

char mx_which_file(t_file *file) {
    if (MX_ISLNK(file->stat.st_mode) == true)
        return 'l';
    else if (MX_ISBLK(file->stat.st_mode) == true)
        return 'b';
    else if (MX_ISCHR(file->stat.st_mode) == true)
        return 'c';
    else if (MX_ISDIR(file->stat.st_mode) == true)
        return 'd';
    else if (MX_ISFIFO(file->stat.st_mode) == true)
        return 'p';
    else if (MX_ISSOCK(file->stat.st_mode) == true)
        return 's';
    else 
        return '-';
}

static char get_file_acl(t_file *file) {
        acl_t tmp;
        char *name = (file->full_path == NULL) ?
                      file->d_name : file->full_path;

        if (listxattr(name, NULL, 0, XATTR_NOFOLLOW) > 0)
            return '@';
        if ((tmp = acl_get_file(name, ACL_TYPE_EXTENDED))) {
            acl_free(tmp);
            return '+';
        }
        return ' ';
}

void mx_file_mode(t_file *file) {
    char f_mode[12];
    mode_t st_mode = file->stat.st_mode;

    f_mode[0] = mx_which_file(file);
    f_mode[1] = (st_mode & S_IRUSR) ? 'r' : '-';
    f_mode[2] = (st_mode & S_IWUSR) ? 'w' : '-';
    f_mode[3] = (st_mode & S_IXUSR) ? 'x' : '-';
    f_mode[4] = (st_mode & S_IRGRP) ? 'r' : '-';
    f_mode[5] = (st_mode & S_IWGRP) ? 'w' : '-';
    f_mode[6] = (st_mode & S_IXGRP) ? 'x' : '-';
    f_mode[7] = (st_mode & S_IROTH) ? 'r' : '-';
    f_mode[8] = (st_mode & S_IWOTH) ? 'w' : '-';
    f_mode[9] = (st_mode & S_IXOTH) ? 'x' : '-';
    f_mode[10] = get_file_acl(file);
    f_mode[11] = '\0';
    S_ISUID & st_mode ? (f_mode[3] = f_mode[3] == '-' ? 'S' : 's') : 0;
    S_ISGID & st_mode ? (f_mode[6] = f_mode[6] == '-' ? 'S' : 's') : 0;
    S_ISVTX & st_mode ? (f_mode[9] = f_mode[9] == '-' ? 'T' : 't') : 0;
    mx_printstr(&f_mode[0]);
}

static void print_hex(long minor) {
    char *hex = NULL;

    hex = mx_nbr_to_hex(minor);
    mx_printstr(" 0x");
    for (int i = mx_strlen(hex); i < 8; i++)
        mx_printchar('0');
    mx_printstr(hex);
    mx_strdel(&hex);
}

void mx_print_major_minor(t_file *file, long ma_size) {
    long major = ((int)(((unsigned int)file->stat.st_rdev >> 24) & 0xff));
    long minor = ((int)((unsigned int)(file->stat.st_rdev) & 0xffffff));
    int size_of_minor = 1;

    mx_print_with_tabl(major, ma_size, false);
    mx_printchar(',');
    if (minor < 256) {
        if (minor != 0)
            for (int largest = minor; largest > 0; largest /= 10)
                size_of_minor++;
        else
            size_of_minor++;
        for (; size_of_minor < 5; size_of_minor++)
            mx_printchar(' ');
       mx_printint(minor);
    }
    else
        print_hex(minor);
}
