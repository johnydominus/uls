#include "libmx.h"

static char *get_leaving(int buf_size, char delim, const int fd);

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    char *res = get_leaving(buf_size, delim, fd);
    static char *leavings[4096];
    char *temp = mx_strjoin(leavings[fd], res);
    int del_ind = mx_get_char_index(temp, delim);

    if (fd < 0 || fd > 4096 || buf_size < 1 || read(fd, 0, 0) < 0)
        return -2;
    if(!res)
        return -2;
    temp[del_ind] = '\0';
    leavings[fd] = mx_strdup(temp + del_ind + 1);
    *lineptr = mx_strdup(temp);
    mx_strdel(&temp);
    if(del_ind == -1)
        return -1;
    else
        return mx_strlen(*lineptr);
}

static char *get_leaving(int buf_size, char delim, const int fd) {
    char *tmp = NULL;
    char *res = NULL;
    char buf[buf_size + 1];
    int rd = 0;
    int del_ind;

    while ((rd = read(fd, buf, buf_size)) > 0) {
        buf[rd] = '\0';
        tmp = mx_strjoin(res, buf);
        mx_strdel(&res);
        res = mx_strdup(tmp);
        mx_strdel(&tmp);
        del_ind = mx_get_char_index(res, delim);

        if (del_ind >= 0)
            break;
    }
    return res;
}
