#include "uls.h"

bool mx_time_access_cmp_rev(void *data1, void *data2) {
    t_file *d1 = (t_file*)data1;
    t_file *d2 = (t_file*)data2;

    if (d1->stat.st_atimespec.tv_sec < d2->stat.st_atimespec.tv_sec)
        return true;
    else if (d1->stat.st_atimespec.tv_sec == d2->stat.st_atimespec.tv_sec) {
        if (d1->stat.st_atimespec.tv_nsec < d2->stat.st_atimespec.tv_nsec)
            return true;
    }
        return false;
}

bool mx_time_access_cmp(void *data1, void *data2) {
    t_file *d1 = (t_file*)data1;
    t_file *d2 = (t_file*)data2;

    if (d1->stat.st_atimespec.tv_sec > d2->stat.st_atimespec.tv_sec)
        return true;
    else if (d1->stat.st_atimespec.tv_sec == d2->stat.st_atimespec.tv_sec) {
        if (d1->stat.st_atimespec.tv_nsec > d2->stat.st_atimespec.tv_nsec)
            return true;
    }
        return false;
}

bool mx_time_creat_cmp_rev(void *data1, void *data2) {
    t_file *d1 = (t_file*)data1;
    t_file *d2 = (t_file*)data2;

    if (d1->stat.st_birthtimespec.tv_sec < d2->stat.st_birthtimespec.tv_sec)
        return true;
    else if (d1->stat.st_birthtimespec.tv_sec == d2->stat.st_birthtimespec.tv_sec) {
        if (d1->stat.st_birthtimespec.tv_nsec < d2->stat.st_birthtimespec.tv_nsec)
            return true;
    }
        return false;
}

bool mx_time_creat_cmp(void *data1, void *data2) {
    t_file *d1 = (t_file*)data1;
    t_file *d2 = (t_file*)data2;

    if (d1->stat.st_birthtimespec.tv_sec > d2->stat.st_birthtimespec.tv_sec)
        return true;
    else if (d1->stat.st_birthtimespec.tv_sec == d2->stat.st_birthtimespec.tv_sec) {
        if (d1->stat.st_birthtimespec.tv_nsec > d2->stat.st_birthtimespec.tv_nsec)
            return true;
    }
        return false;
}
