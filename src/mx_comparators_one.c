#include "uls.h"

static bool time_cmp(struct timespec t1, struct timespec t2, bool rev) {
    if (!rev)
        return (t1.tv_sec >= t2.tv_sec) ? 0 : 1;
    return (t1.tv_sec > t2.tv_sec) ? 1 : 0;
}

bool mx_time_chngd_cmp(void *data1, void *data2, bool rev) {
    t_file *d1 = (t_file*) data1;
    t_file *d2 = (t_file*) data2;

 if (d1->stat.st_ctimespec.tv_sec == d2->stat.st_ctimespec.tv_sec) {
        if (d1->stat.st_ctimespec.tv_nsec == d2->stat.st_ctimespec.tv_nsec)
            return mx_alpha_cmp(d1, d2, rev);
        else {
            if (!rev)
                return (d1->stat.st_ctimespec.tv_nsec
                        >= d2->stat.st_ctimespec.tv_nsec) ? 0 : 1;
            return (d1->stat.st_ctimespec.tv_nsec
                    >= d2->stat.st_ctimespec.tv_nsec) ? 1 : 0;
        }
    }
    else
        return time_cmp(d1->stat.st_ctimespec, d2->stat.st_ctimespec, rev);
}

bool mx_time_access_cmp(void *data1, void *data2, bool rev) {
    t_file *d1 = (t_file*)data1;
    t_file *d2 = (t_file*)data2;

    if (d1->stat.st_atimespec.tv_sec == d2->stat.st_atimespec.tv_sec) {
        if (d1->stat.st_atimespec.tv_nsec == d2->stat.st_atimespec.tv_nsec)
            return mx_alpha_cmp(d1, d2, rev);
        else {
            if (!rev)
                return (d1->stat.st_atimespec.tv_nsec
                        >= d2->stat.st_atimespec.tv_nsec) ? 0 : 1;
            return (d1->stat.st_atimespec.tv_nsec
                    >= d2->stat.st_atimespec.tv_nsec) ? 1 : 0;
        }
    }
    else
        return time_cmp(d1->stat.st_atimespec, d2->stat.st_atimespec, rev);
}

bool mx_time_creat_cmp(void *data1, void *data2, bool rev) {
    t_file *d1 = (t_file*)data1;
    t_file *d2 = (t_file*)data2;

    if (d1->stat.st_birthtimespec.tv_sec == d2->stat.st_birthtimespec.tv_sec) {
        if (d1->stat.st_birthtimespec.tv_nsec
            == d2->stat.st_birthtimespec.tv_nsec)
            return mx_alpha_cmp(d1, d2, rev);
        else {
            if (!rev)
                return (d1->stat.st_birthtimespec.tv_nsec
                        >= d2->stat.st_birthtimespec.tv_nsec) ? 0 : 1;
            return (d1->stat.st_birthtimespec.tv_nsec
                    >= d2->stat.st_birthtimespec.tv_nsec) ? 1 : 0;
        }
    }
    else
        return time_cmp(d1->stat.st_birthtimespec,
                        d2->stat.st_birthtimespec, 
                        rev);
}

bool mx_time_mod_cmp(void *data1, void *data2, bool rev) {
    t_file *d1 = (t_file*)data1;
    t_file *d2 = (t_file*)data2;

    if (d1->stat.st_mtimespec.tv_sec == d2->stat.st_mtimespec.tv_sec) {
        if (d1->stat.st_mtimespec.tv_nsec == d2->stat.st_mtimespec.tv_nsec)
            return mx_alpha_cmp(d1, d2, rev);
        else {
            if (!rev)
                return (d1->stat.st_mtimespec.tv_nsec
                        >= d2->stat.st_mtimespec.tv_nsec) ? 0 : 1;
            return (d1->stat.st_mtimespec.tv_nsec
                    >= d2->stat.st_mtimespec.tv_nsec) ? 1 : 0;
        }
    }
    else
        return time_cmp(d1->stat.st_mtimespec, d2->stat.st_mtimespec, rev);
}
