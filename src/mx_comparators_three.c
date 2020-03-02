#include "uls.h"

bool mx_time_mod_cmp_rev(void *data1, void *data2) {
    t_file *d1 = (t_file*)data1;
    t_file *d2 = (t_file*)data2;

    if (d1->stat.st_mtimespec.tv_sec < d2->stat.st_mtimespec.tv_sec)
        return true;
    else if (d1->stat.st_mtimespec.tv_sec == d2->stat.st_mtimespec.tv_sec) {
        if (d1->stat.st_mtimespec.tv_nsec < d2->stat.st_mtimespec.tv_nsec)
            return true;
    }
        return false;
}

bool mx_time_mod_cmp(void *data1, void *data2) {
    t_file *d1 = (t_file*)data1;
    t_file *d2 = (t_file*)data2;

    if (d1->stat.st_mtimespec.tv_sec < d2->stat.st_mtimespec.tv_sec)
        return true;
    else if (d1->stat.st_mtimespec.tv_sec == d2->stat.st_mtimespec.tv_sec) {
        if (d1->stat.st_mtimespec.tv_nsec < d2->stat.st_mtimespec.tv_nsec)
            return true;
    }
        return false;
}

bool mx_alpha_cmp_rev(void *data1, void *data2) {
    t_file *d1 = (t_file*)data1;
    t_file *d2 = (t_file*)data2;
    int len1 = mx_strlen(d1->d_name);
    int len2 = mx_strlen(d2->d_name);
    char *name1 = mx_strndup(d1->d_name, len1);
    char *name2 = mx_strndup(d2->d_name, len2);

    if (mx_strcmp(name1, name2) < 0) {
        free(name1);
        free(name2);
        return true;
    }
    else {
        free(name1);
        free(name2);
        return false;
    }
}

bool mx_alpha_cmp(void *data1, void *data2) {
    t_file *d1 = (t_file*)data1;
    t_file *d2 = (t_file*)data2;
    int len1 = mx_strlen(d1->d_name);
    int len2 = mx_strlen(d2->d_name);
    char *name1 = mx_strndup(d1->d_name, len1);
    char *name2 = mx_strndup(d2->d_name, len2);

    if (mx_strcmp(name1, name2) > 0) {
        free(name1);
        free(name2);
        return true;
    }
    else {
        free(name1);
        free(name2);
        return false;
    }
}
