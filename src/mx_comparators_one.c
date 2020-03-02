#include "uls.h"

bool mx_size_cmp_rev(void *data1, void *data2) {
    t_file *d1 = (t_file*)data1;
    t_file *d2 = (t_file*)data2;

    if (d1->stat.st_size < d2->stat.st_size)
        return true;
    else
        return false;
}

bool mx_size_cmp(void *data1, void *data2) {
    t_file *d1 = (t_file*) data1;
    t_file *d2 = (t_file*) data2;

    if (d1->stat.st_size > d2->stat.st_size)
        return true;
    else
        return false;
}

bool mx_time_chngd_cmp_rev(void *data1, void *data2) {
    t_file *d1 = (t_file*) data1;
    t_file *d2 = (t_file*) data2;

    if (d1->stat.st_ctimespec.tv_sec < d2->stat.st_ctimespec.tv_sec)
        return true;
    else if (d1->stat.st_ctimespec.tv_sec == d2->stat.st_ctimespec.tv_sec) {
        if (d1->stat.st_ctimespec.tv_nsec < d2->stat.st_ctimespec.tv_nsec)
            return true;
    }
        return false;
}

bool mx_time_chngd_cmp(void *data1, void *data2) {
    t_file *d1 = (t_file*) data1;
    t_file *d2 = (t_file*) data2;

    if (d1->stat.st_ctimespec.tv_sec > d2->stat.st_ctimespec.tv_sec)
        return true;
    else if (d1->stat.st_ctimespec.tv_sec == d2->stat.st_ctimespec.tv_sec) {
        if (d1->stat.st_ctimespec.tv_nsec > d2->stat.st_ctimespec.tv_nsec)
            return true;
    }
        return false;
}
