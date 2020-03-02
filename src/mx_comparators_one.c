#include "uls.h"

bool mx_size_cmp(void *data1, void *data2, bool reverse) {
    t_file *d1 = (t_file*) data1;
    t_file *d2 = (t_file*) data2;

    if (d1->stat.st_size == d2->stat.st_size)
        return mx_alpha_cmp(d1, d2, reverse);
    else {
        if (!reverse)
            return (d1->stat.st_size >= d2->stat.st_size) ? 0 : 1;
        return (d1->stat.st_size > d2->stat.st_size) ? 1 : 0;
    }
}

bool mx_time_chngd_cmp(void *data1, void *data2, bool reverse) {
    t_file *d1 = (t_file*) data1;
    t_file *d2 = (t_file*) data2;

 if (d1->stat.st_ctimespec.tv_sec == d2->stat.st_ctimespec.tv_sec) {
        if (d1->stat.st_ctimespec.tv_nsec == d2->stat.st_ctimespec.tv_nsec)
            return mx_alpha_cmp(d1, d2, reverse);
        else {
            if (!reverse)
                return (d1->stat.st_ctimespec.tv_nsec >= d2->stat.st_ctimespec.tv_nsec)
                    ? 0 : 1;
            return (d1->stat.st_ctimespec.tv_nsec >= d2->stat.st_ctimespec.tv_nsec)
                ? 1 : 0;
        }
    }
    else {
        if (!reverse)
            return (d1->stat.st_ctimespec.tv_sec >= d2->stat.st_ctimespec.tv_sec)
                ? 0 : 1;
        return (d1->stat.st_ctimespec.tv_sec > d2->stat.st_ctimespec.tv_sec) ? 1 : 0;
    }
}

bool mx_time_access_cmp(void *data1, void *data2, bool reverse) {
    t_file *d1 = (t_file*)data1;
    t_file *d2 = (t_file*)data2;

    if (d1->stat.st_atimespec.tv_sec == d2->stat.st_atimespec.tv_sec) {
        if (d1->stat.st_atimespec.tv_nsec == d2->stat.st_atimespec.tv_nsec)
            return mx_alpha_cmp(d1, d2, reverse);
        else {
            if (!reverse)
                return (d1->stat.st_atimespec.tv_nsec >= d2->stat.st_atimespec.tv_nsec)
                    ? 0 : 1;
            return (d1->stat.st_atimespec.tv_nsec >= d2->stat.st_atimespec.tv_nsec)
                ? 1 : 0;
        }
    }
    else {
        if (!reverse)
            return (d1->stat.st_atimespec.tv_sec >= d2->stat.st_atimespec.tv_sec)
                ? 0 : 1;
        return (d1->stat.st_atimespec.tv_sec > d2->stat.st_atimespec.tv_sec) ? 1 : 0;
    }
}

bool mx_time_creat_cmp(void *data1, void *data2, bool reverse) {
    t_file *d1 = (t_file*)data1;
    t_file *d2 = (t_file*)data2;

    if (d1->stat.st_birthtimespec.tv_sec == d2->stat.st_birthtimespec.tv_sec) {
        if (d1->stat.st_birthtimespec.tv_nsec == d2->stat.st_birthtimespec.tv_nsec)
            return mx_alpha_cmp(d1, d2, reverse);
        else {
            if (!reverse)
                return (d1->stat.st_birthtimespec.tv_nsec >= d2->stat.st_birthtimespec.tv_nsec)
                    ? 0 : 1;
            return (d1->stat.st_birthtimespec.tv_nsec >= d2->stat.st_birthtimespec.tv_nsec)
                ? 1 : 0;
        }
    }
    else {
        if (!reverse)
            return (d1->stat.st_birthtimespec.tv_sec >= d2->stat.st_birthtimespec.tv_sec)
                ? 0 : 1;
        return (d1->stat.st_birthtimespec.tv_sec > d2->stat.st_birthtimespec.tv_sec) ? 1 : 0;
    }
}

bool mx_time_mod_cmp(void *data1, void *data2, bool reverse) {
    t_file *d1 = (t_file*)data1;
    t_file *d2 = (t_file*)data2;

    if (d1->stat.st_mtimespec.tv_sec == d2->stat.st_mtimespec.tv_sec) {
        if (d1->stat.st_mtimespec.tv_nsec == d2->stat.st_mtimespec.tv_nsec)
            return mx_alpha_cmp(d1, d2, reverse);
        else {
            if (!reverse)
                return (d1->stat.st_mtimespec.tv_nsec >= d2->stat.st_mtimespec.tv_nsec)
                    ? 0 : 1;
            return (d1->stat.st_mtimespec.tv_nsec >= d2->stat.st_mtimespec.tv_nsec)
                ? 1 : 0;
        }
    }
    else {
        if (!reverse)
            return (d1->stat.st_mtimespec.tv_sec >= d2->stat.st_mtimespec.tv_sec)
                ? 0 : 1;
        return (d1->stat.st_mtimespec.tv_sec > d2->stat.st_mtimespec.tv_sec) ? 1 : 0;
    }
}
